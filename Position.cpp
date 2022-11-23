#include "Position.h"
#include <omp.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <chrono>

using namespace std;

Position::Position(string fen) {
    string space_delimiter = " ";
    vector<string> words{};
    size_t pos = 0;
    while ((pos = fen.find(space_delimiter)) != string::npos) {
        words.push_back(fen.substr(0, pos));
        fen.erase(0, pos + space_delimiter.length());
    }
    words.push_back(fen);
    int j;
    int column = 0;
    int row = 7;
    memset(this->chessboard, 0, sizeof(this->chessboard));
    for (char c : words[0]) {
        if (c == '/') {
            row--;
            column = 0;
        } else {
            if (isdigit(c)) {
                column += c - '0';
            } else {
                j = Position::Get_Index_By_Row_And_Column(row, column);
                chessboard[j] = Char_To_Number.at(c);
                if (c == 'k') this->black_king_index = j;
                else if (c == 'K') this->white_king_index = j;
                column++;
            }
        }
    }
    this->white_move = words[1] == "w";
    white_move ? enemy_king_index = black_king_index : enemy_king_index = white_king_index;
    this->white_can_castle_k = words[2].find('K') != std::string::npos;
    this->white_can_castle_q = words[2].find('Q') != std::string::npos;
    this->black_can_castle_k = words[2].find('k') != std::string::npos;
    this->black_can_castle_q = words[2].find('q') != std::string::npos;
    if (words[3][0] != '-' && words[3][0] != ' '){
        this->possible_en_passant = Position::Get_Index_By_Square(words[3]);
    }
    this->halfmove_clock = 0;
    this->fullmove_number = 0;
    if (words.size() > 4) {
        if (words[4] != " " && words[4][0] != '-') this->halfmove_clock = words[4][0] - '0';
        if (words.size() > 5 && words[5][0] != '-' && !isspace(words[5][0])) this->fullmove_number = words[5][0] - '0';
    }
    if (halfmove_clock < 0 || halfmove_clock > 50) halfmove_clock = 0;
}

const string Position::Start_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

inline int Position::Get_Row_By_Index(int index) {
    return (index >> 3);
}

inline int Position::Get_Column_By_Index(int index) {
    return (index & 7);
}

inline int Position::Get_Index_By_Row_And_Column(int row, int column) {
    return row * 8 + column;
}

inline int Position::Get_Index_By_Square(string square) {
    if (square == "-") return 0;
    return Get_Index_By_Row_And_Column(square[1] - '1', square[0] - 'a');
}

bool Position::Are_On_Same_Line(int index1, int index2) {
    return ((Get_Row_By_Index(index1) == Get_Row_By_Index(index2) ||
             Get_Column_By_Index(index1) == Get_Column_By_Index(index2) ||
             (index1 - index2) % 9 == 0 || (index1 - index2) % 7 == 0));
}


void Position::print_board() {
    cout << "" << endl;
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (chessboard[8 * i + j] == 0) cout << "-" << "\t";
            else cout << Number_To_Char.at(chessboard[8 * i + j]) << "\t";
        }
        cout << "" << endl;
    }
    cout << "" << endl;
}

Position Position::copy() {
    Position pos = Position();
    std::copy(std::begin(chessboard), std::end(chessboard), std::begin(pos.chessboard));
    pos.white_move = white_move;
    pos.white_king_index = white_king_index;
    pos.black_king_index = black_king_index;
    pos.enemy_king_index = enemy_king_index;
    pos.white_can_castle_k = white_can_castle_k;
    pos.white_can_castle_q = white_can_castle_q;
    pos.black_can_castle_k = black_can_castle_k;
    pos.black_can_castle_q = black_can_castle_q;
    pos.possible_en_passant = possible_en_passant;
    pos.halfmove_clock = halfmove_clock;
    pos.fullmove_number = fullmove_number;
    pos.best_move = best_move.copy();
    return pos;
}

vector<Move> Position::get_pseudolegal_moves(int index) {
    vector<Move> moves;
    if (chessboard[index] == 0) return moves;
    int figure = chessboard[index];
    int figure_type = Get_Type(figure);
    int row = Get_Row_By_Index(index);
    int column = Get_Column_By_Index(index);
    if (figure_type == Pawn) {
        if (Is_White(figure)) { // White Pawn
            if (chessboard[index + 8] == 0) {
                moves.emplace_back(index, index + 8); // 1 step forward
                if (row == 1 && chessboard[index + 16] == 0) moves.emplace_back(index, index + 16); // 2 steps
            }
            // capture black:
            if (column != 0 && (Is_Black(chessboard[index + 7]) || possible_en_passant == index + 7)) {
                moves.emplace_back(index, index + 7);
            }
            if (column != 7 && (Is_Black(chessboard[index + 9]) || possible_en_passant == index + 9)) {
                moves.emplace_back(index, index + 9);
            }
            if (row == 6){
                if (chessboard[index + 8] == 0) {
                    moves.emplace_back(index, index + 8, 1 << 26); // 1 step forward
                    moves.emplace_back(index, index + 8, 2 << 26);
                    moves.emplace_back(index, index + 8, 3 << 26);
                }
                // capture black:
                if (column != 0 && Is_Black(chessboard[index + 7])) {
                    moves.emplace_back(index, index + 7, 1 << 26);
                    moves.emplace_back(index, index + 7, 2 << 26);
                    moves.emplace_back(index, index + 7, 3 << 26);
                }
                if (column != 7 && Is_Black(chessboard[index + 9])) {
                    moves.emplace_back(index, index + 9, 1 << 26);
                    moves.emplace_back(index, index + 9, 2 << 26);
                    moves.emplace_back(index, index + 9, 3 << 26);
                }
            }
        } else { //Black Pawn
            if (chessboard[index - 8] == 0) {
                moves.emplace_back(index, index - 8);
                if (row == 6 && chessboard[index - 16] == 0) moves.emplace_back(index, index - 16); // 2 steps
            }
            // capture white piece:
            if (column != 0 && (Is_White(chessboard[index - 9]) || possible_en_passant == index - 9)) {
                moves.emplace_back(index, index - 9);
            }
            if (column != 7 && (Is_White(chessboard[index - 7]) || possible_en_passant == index - 7)) {
                Move move = Move(index, index - 7);
                moves.emplace_back(move);
            }
            if (row == 1){
                if (chessboard[index - 8] == 0) {
                    moves.emplace_back(index, index - 8, 1 << 26); // 1 step forward
                    moves.emplace_back(index, index - 8, 2 << 26);
                    moves.emplace_back(index, index - 8, 3 << 26);
                }
                // capture white:
                if (column != 0 && Is_White(chessboard[index - 9])) {
                    moves.emplace_back(index, index - 9, 1 << 26);
                    moves.emplace_back(index, index - 9, 2 << 26);
                    moves.emplace_back(index, index - 9, 3 << 26);
                }
                if (column != 7 && Is_White(chessboard[index - 7])) {
                    moves.emplace_back(index, index - 7, 1 << 26);
                    moves.emplace_back(index, index - 7, 2 << 26);
                    moves.emplace_back(index, index - 7, 3 << 26);
                }
            }
        }
    } else if (Is_Sliding_Piece(figure)) {
        int startIndex = (figure_type == Bishop) ? 4 : 0;
        int endIndex = (figure_type == Rook) ? 4 : 8;
        for (int directionIndex = startIndex; directionIndex < endIndex; ++directionIndex) {
            for (int i = 1; !Is_Same_Colour(figure, chessboard[index + Direction_Offsets[directionIndex] * i]) &&
                            Is_No_Over_Edge_Move(index + Direction_Offsets[directionIndex] * (i - 1),
                                                 index + Direction_Offsets[directionIndex] * i); ++i) {
                moves.emplace_back(index, index + Direction_Offsets[directionIndex] * i);
                if (chessboard[index + Direction_Offsets[directionIndex] * i] != 0) break;
            }
        }
    } else {
        vector<int> offsets;
        if (figure_type == King) {
            offsets = Direction_Offsets;
            //check for castling
            bool kingside;
            bool queenside;
            if (Is_White(figure)) {
                kingside = (white_can_castle_k && is_no_figure_between(W_King_Start_Index, RW_Rook_Start_Index, 1));
                queenside = (white_can_castle_q && is_no_figure_between(W_King_Start_Index, LW_Rook_Start_Index, 1));
            } else {
                kingside = (black_can_castle_k && is_no_figure_between(B_King_Start_Index, RB_Rook_Start_Index, 1));
                queenside = (black_can_castle_q && is_no_figure_between(B_King_Start_Index, LB_Rook_Start_Index, 1));
            }
            // check both sides before checking if king is threatened, because threat-checking is expensive
            if ((kingside || queenside) && !is_threatened(index)) {
                if (kingside && !is_threatened(index + 1)){
                    moves.emplace_back(index, index + 2);
                }
                if (queenside && !is_threatened(index - 1)){
                    moves.emplace_back(index, index - 2);
                }
            }
        } else offsets = Knight_Offsets;
        for (int i: offsets) {
            if (!Is_Same_Colour(figure, chessboard[index + i])
                && Is_No_Over_Edge_Move(index, index + i)) {
                moves.emplace_back(index, index + i);
            }
        }
    }
    return moves;
}

bool Position::Is_No_Over_Edge_Move(int index_from, int index_to) {
    return (abs(Get_Column_By_Index(index_from) - Get_Column_By_Index(index_to)) < 3 &&
            abs(Get_Row_By_Index(index_from) - Get_Row_By_Index(index_to)) < 3 &&
            index_to >= 0 && index_to < 64);
}

bool Position::is_no_figure_between(int index1, int index2, int a) {
    // check if there's a figure between, on a straight/diagonal line (specified by offset a, e.g. a=1 -> row
    if (index1 > index2) swap(index1, index2);
    // always check if line goes over edge!
    if (abs(Get_Column_By_Index(index1) - Get_Column_By_Index(index1 + a)) > 1 ||
        abs(Get_Column_By_Index(index2) - Get_Column_By_Index(index2 - a)) > 1) {
        return false;
    }
    for (int i = index1 + a; i < index2; i += a) {
        if (chessboard[i] != 0 || abs(Get_Column_By_Index(i) - Get_Column_By_Index(i - a)) > 1) return false;
    }
    return true;
}

bool Position::is_it_your_turn(int figure) {
    return ((white_move + 1) << 3) & figure;
}

void Position::make_move(Move &move) {
    int figure_type = Get_Type(chessboard[move.from]);
    int distance = move.to - move.from;
    // save irreversible info:
    move.info |= (((white_can_castle_k) | (white_can_castle_q << 1) | (black_can_castle_k << 2) |
                   (black_can_castle_q << 3)) << 8);
    move.info |= halfmove_clock << 12;
    move.info |= possible_en_passant << 18;
    // check castling:
    if (white_move && (white_can_castle_k || white_can_castle_q)) {
        if ((move.from == W_King_Start_Index || move.from == LW_Rook_Start_Index) && white_can_castle_q) {
            white_can_castle_q = false;
        }
        if ((move.from == W_King_Start_Index || move.from == RW_Rook_Start_Index) && white_can_castle_k) {
            white_can_castle_k = false;
        }
    }
    if (!white_move && (black_can_castle_k || black_can_castle_q)) {
        if ((move.from == B_King_Start_Index || move.from == LB_Rook_Start_Index) && black_can_castle_q) {
            black_can_castle_q = false;
        }
        if ((move.from == B_King_Start_Index || move.from == RB_Rook_Start_Index) && black_can_castle_k) {
            black_can_castle_k = false;
        }
    }
    // make move:
    move.info |= chessboard[move.to];
    chessboard[move.to] = chessboard[move.from];
    chessboard[move.from] = 0;
    // promotion or en passant?
    possible_en_passant = 128; // default: no en passant possible --> set en passant index outside the board
    if (figure_type == Pawn) {
        if (distance == 16 || distance == -16) {
            possible_en_passant = move.from + (distance / 2);
        } else if (Get_Row_By_Index(move.to) == 7 || Get_Row_By_Index(move.to) == 0) {
            // promotion:
            //cout << "pt: " << move.get_ep_state() << endl;
            if (move.get_promotion_type() == 0){
                //cout << "queen" << endl;
                chessboard[move.to] += 5; // make the pawn a queen
            }
            else if (move.get_promotion_type() == 1){
                chessboard[move.to] += 1; // make the pawn a knight
            }
            else if (move.get_promotion_type() == 2){
                chessboard[move.to] += 3; // make the pawn a bishop
            }
            else if (move.get_promotion_type() == 3){
                //cout << "rook" << endl;
                chessboard[move.to] += 4; // make the pawn a rook
            }
            move.info |= Move::promotion_mask;
        } else if (distance % 8 != 0 && !move.does_capture()) {
            // en passant:
            move.info |= Move::en_passant_mask;
            if (white_move) {
                move.info |= (Black | Pawn);
                chessboard[move.to - 8] = 0;
            } else {
                move.info |= (White | Pawn);
                chessboard[move.to + 8] = 0;
            }
        }
    }
    // castling?
    if (figure_type == Rook) {
        if (move.from == LW_Rook_Start_Index) white_can_castle_q = false;
        if (move.from == RW_Rook_Start_Index) white_can_castle_k = false;
        if (move.from == LB_Rook_Start_Index) black_can_castle_q = false;
        if (move.from == RB_Rook_Start_Index) black_can_castle_k = false;
    }
    if (move.to == LW_Rook_Start_Index) white_can_castle_q = false;
    else if (move.to == RW_Rook_Start_Index) white_can_castle_k = false;
    else if (move.to == LB_Rook_Start_Index) black_can_castle_q = false;
    else if (move.to == RB_Rook_Start_Index) black_can_castle_k = false;
    if (figure_type == King) {
        if (white_move){
            white_king_index = move.to;
            white_can_castle_k = false;
            white_can_castle_q = false;
        } else {
            black_king_index = move.to;
            black_can_castle_k = false;
            black_can_castle_q = false;
        }
        if (distance == 2) {
            // castling short
            chessboard[move.to - 1] = chessboard[move.to + 1];
            chessboard[move.to + 1] = 0;
            move.info |= Move::castling_mask;
        } else if (distance == -2) {
            // castling long
            chessboard[move.to + 1] = chessboard[move.to - 2];
            chessboard[move.to - 2] = 0;
            move.info |= Move::castling_mask;
        }
    }
    (move.does_capture() || figure_type == Pawn ) ? halfmove_clock = 0 : halfmove_clock++;
    if (!white_move){
        fullmove_number++;
        enemy_king_index = black_king_index;
    } else enemy_king_index = white_king_index;
    white_move = !white_move;
}

void Position::undo_move(Move move) {
    int figure_type = Get_Type(chessboard[move.to]);
    int distance = move.to - move.from;
    int castling_info = move.get_castling_rights();
    white_can_castle_k = castling_info & 1;
    white_can_castle_q = castling_info & 2;
    black_can_castle_k = castling_info & 4;
    black_can_castle_q = castling_info & 8;
    halfmove_clock = move.get_halfmove_clock();
    possible_en_passant = move.get_ep_state();
    // undo move:
    chessboard[move.from] = chessboard[move.to];
    chessboard[move.to] = move.get_captured_figure();
    // promotion or en passant or castling?
    if (move.is_promotion()) {
        white_move ? chessboard[move.from] = Black | Pawn : chessboard[move.from] = White | Pawn; // make it a pawn
    } else if (move.is_en_passant()) {
        white_move ? chessboard[move.to + 8] = chessboard[move.to] : chessboard[move.to - 8] = chessboard[move.to];
        chessboard[move.to] = 0;
    } else if (figure_type == King) {
        white_move ? black_king_index = move.from : white_king_index = move.from;
        if (distance == 2) {
            // castling short
            chessboard[move.to + 1] = chessboard[move.to - 1];
            chessboard[move.to - 1] = 0;
        } else if (distance == -2) {
            // castling long
            chessboard[move.to - 2] = chessboard[move.to + 1];
            chessboard[move.to + 1] = 0;
        }
    }
    if (white_move){
        fullmove_number--;
        enemy_king_index = white_king_index;
    } else enemy_king_index = black_king_index;
    white_move = !white_move;
}

vector<Move> Position::get_all_pseudolegal_moves() {
    vector<Move> all_moves;
    for (int i = 0; i < 64; ++i) {
        if (is_it_your_turn(chessboard[i])) {
            vector<Move> moves = get_pseudolegal_moves(i);
            all_moves.insert(all_moves.end(), moves.begin(), moves.end());
        }
    }
    return all_moves;
}

bool Position::is_hanging(int index) {
    int row = Get_Row_By_Index(index);
    int column = Get_Column_By_Index(index);
    int row_i;
    int column_i;
    int figure_type;
    int distance;
    for (int i = 0; i < 64; ++i) {
        if (is_it_your_turn(chessboard[i])) {
            figure_type = Get_Type(chessboard[i]);
            distance = index - i;
            row_i = Get_Row_By_Index(i);
            column_i = Get_Column_By_Index(i);
            if (figure_type == Pawn) {
                if ((white_move && ((distance == 7 && column_i != 0) || (distance == 9 && column_i != 7))) ||
                    (!white_move && ((distance == -7 && column_i != 7) || (distance == -9 && column_i != 0)))) {
                    //cout << white_move << distance << row_i << endl;
                    // cout << "pawn" << endl;
                    return true;
                }
            } else if (figure_type == Knight) {
                if (abs(row - row_i) < 3 && abs(column - column_i) < 3 &&
                    find(Knight_Offsets.begin(), Knight_Offsets.end(), distance) != Knight_Offsets.end()) {
                    // cout << "knight: " << i << endl;
                    return true;
                }
            } else if (figure_type == Rook) {
                if ((row_i == row && is_no_figure_between(index, i, 1)) ||
                    (column_i == column && is_no_figure_between(index, i, 8))) {
                    // cout << "rook" << endl;
                    return true;
                }
            } else if (figure_type == Bishop){
                if ((((index - i) % 7 == 0) && is_no_figure_between(index, i, 7)) ||
                    (((index - i) % 9 == 0) && is_no_figure_between(index, i, 9))) {
                    // cout << "bishop" << endl;
                    return true;
                }
            } else if (figure_type == Queen){
                if ((row_i == row && is_no_figure_between(index, i, 1)) ||
                    (column_i == column && is_no_figure_between(index, i, 8)) ||
                    (((index - i) % 7 == 0) && is_no_figure_between(index, i, 7)) ||
                    (((index - i) % 9 == 0) && is_no_figure_between(index, i, 9))) {
                    // cout << "queen" << endl;
                    return true;
                }
            } else if (figure_type == King) {
                if (abs(row - row_i) <= 1 && abs(column - column_i) <= 1){
                    // cout << "king" << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Position::is_hanging_by_pawn(int index) {
    int column_i;
    int figure_type;
    int distance;
    for (int i = 0; i < 64; ++i) {
        if (is_it_your_turn(chessboard[i])) {
            figure_type = Get_Type(chessboard[i]);
            distance = index - i;
            column_i = Get_Column_By_Index(i);
            if (figure_type == Pawn) {
                if ((white_move && ((distance == 7 && column_i != 0) || (distance == 9 && column_i != 7))) ||
                    (!white_move && ((distance == -7 && column_i != 7) || (distance == -9 && column_i != 0)))) {
                    //cout << white_move << distance << row_i << endl;
                    // cout << "pawn" << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Position::is_threatened(int index) {
    white_move = !white_move;
    bool ret = is_hanging(index);
    white_move = !white_move;
    return ret;
}

bool Position::is_threatened_by_pawn(int index) {
    white_move = !white_move;
    bool ret = is_hanging_by_pawn(index);
    white_move = !white_move;
    return ret;
}

vector<Move> Position::get_all_legal_moves() {
    vector<Move> moves = get_all_pseudolegal_moves();
    vector<Move> legal_moves;
    for (Move move : moves) {
        make_move(move);
        if (!is_hanging(enemy_king_index)) legal_moves.emplace_back(move);
        undo_move(move);
    }
    return legal_moves;
}

long long int Position::perft(int depth) {
    if (depth == 0) {
        if (is_hanging(enemy_king_index)){
            return 0;
        }
        return 1;
    }
    vector<Move> moves = get_all_pseudolegal_moves();
    for (Move move : moves) {
        if (move.to == enemy_king_index) {
            return 0;
        }
    }
    long long int num_pos = 0;
    for (Move move : moves) {
        make_move(move);
        num_pos += perft(depth - 1);
        undo_move(move);
    }
    return num_pos;
}

long long int Position::perft_parallel(int depth) {
    vector<Move> legal_moves = get_all_legal_moves();
    long long int perft_result = 0;
#pragma omp parallel num_threads(omp_get_max_threads())
    {
#pragma omp for schedule(dynamic, 1) reduction(+ : perft_result)
        for (Move move : legal_moves) {
            Position p = copy();
            p.make_move(move);
            perft_result += p.perft(depth - 1);
        }
    }
    return perft_result;
}

long long int Position::perft_divide(int depth, int max_depth) {
    if (depth == 0) return 1;
    vector<Move> moves = get_all_legal_moves();
    long long int num_pos = 0;
    for (Move move : moves) {
        if (depth == max_depth) cout << "making move: " << move.to_letter_string();
        make_move(move);
        num_pos += perft_divide(depth - 1, max_depth);
        undo_move(move);
    }
    if (depth == max_depth - 1) cout << "\t | number of positions: " << num_pos << endl;
    return num_pos;
}

long long int Position::perft_divide_parallel(int depth) {
    vector<Move> legal_moves = get_all_legal_moves();
    long long int perft_result = 0;
#pragma omp parallel num_threads(omp_get_max_threads())
    {
#pragma omp for schedule(dynamic, 1) reduction(+ : perft_result)
        for (Move move : legal_moves) {
            Position p = copy();
            p.make_move(move);
            int num_pos = p.perft(depth - 1);
            cout << "making move: " << move.to_letter_string() << "\t | number of positions: " << num_pos << endl;
            perft_result += num_pos;
        }
    }
    return perft_result;
}


long long int Position::other_perft(int depth) {
    if (depth == 0) return 1;
    vector<Move> moves = get_all_legal_moves();
    long long int num_pos = 0;
    for (Move move : moves) {
        make_move(move);
        num_pos += other_perft(depth - 1);
        undo_move(move);
    }
    return num_pos;
}

int Position::evaluate() {
    int value = 0;
    for (int i = 0; i < 64; i++) {
        if (chessboard[i] != 0) value += Get_Figure_Value(chessboard[i], i);
    }
    if (!white_move) value = -value;
    return value;
}

Move Position::get_best_move() {
    vector<Move> legal_moves = get_all_legal_moves();
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end;
    double time_passed = 0.0;
    int i = 1;
    for (; time_passed < 1.0; ++i) {
        int value = minimax(i, i, -30000, 30000);
        end = std::chrono::steady_clock::now();
        if (value == -25000){
            return get_all_legal_moves()[0];
        }
        time_passed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000);
    }
    cout << "computed best move:  " << best_move.to_letter_string() << " (depth " << i - 1 << ") in " << time_passed <<
    " seconds" << endl;
    return best_move;
}

int Position::minimax_parallel(int depth, int alpha, int beta) {
    vector<Move> legal_moves = get_all_legal_moves();
    int max_value = -25000;
#pragma omp parallel num_threads(omp_get_max_threads())
    {
#pragma omp for schedule(dynamic, 2)
        for (Move move : legal_moves) {
            Position p = copy();
            p.make_move(move);
            int local_value = -p.minimax(depth-1, depth-1, alpha, beta);
            Move local_move = p.best_move;
            #pragma omp critical
            if (local_value > max_value){
                max_value = local_value;
                best_move = local_move;
                best_move.value = max_value;
            }
        }
    }
    return max_value;
}

void Position::sort_moves(vector<Move> &moves) {
    // evaluate moves:
    int move_score;
    int figure_type;
    int capture_type;
    for (Move &move : moves) {
        figure_type = Get_Type(chessboard[move.from]);
        capture_type = Get_Type(chessboard[move.to]);
        move_score = 0;
        // reward capturing
        if (capture_type != 0) move_score = 10 * Values.at(capture_type) - Values.at(figure_type);
        // reward promotion
        if (figure_type == Pawn && (move.to >= 56 || move.to <= 7)){
            move_score += 900;
            if (move.get_promotion_type() != 0) move_score -= 400;
        }
        // punish moving to a square that is threatened by a pawn
        if (is_threatened_by_pawn(move.to)) move_score -= Values.at(figure_type);
        move.value = move_score;
    }
    // order moves:
    sort(moves.begin(), moves.end(), [](const auto& lhs, const auto& rhs)
    {
        return lhs.value > rhs.value;
    });
}

int Position::minimax(int depth, int max_depth, int alpha, int beta) {
    if (depth == 0) return search_captures(alpha, beta);
    vector<Move> moves = get_all_pseudolegal_moves();
    sort_moves(moves);
    int max_value = alpha;
    int value;
    for (Move move : moves) {
        make_move(move);
        if (is_hanging(enemy_king_index)){
            value = -25000;
        }
        else value = -minimax(depth - 1, max_depth, -beta, -max_value);
        undo_move(move);
        if (value > max_value){
            max_value = value;
            if (depth == max_depth){
                best_move = move;
                best_move.value = max_value;
            }
            if (max_value >= beta) break;
        }
    }
    return max_value;
}

int Position::search_captures(int alpha, int beta) {
    int eval = evaluate();
    if (eval >= beta) return beta;
    alpha = max(alpha, eval);
    vector<Move> capture_moves = get_all_pseudolegal_capture_moves();
    sort_moves(capture_moves);
    for(Move capture_move : capture_moves){
        make_move(capture_move);
        if (is_hanging(enemy_king_index)) eval = -25000;
        else eval = -search_captures(-beta, -alpha);
        undo_move(capture_move);
        if (eval >= beta) return beta;
        alpha = max(alpha, eval);
    }
    return alpha;
}

vector<Move> Position::get_all_pseudolegal_capture_moves() {
    vector<Move> capture_moves;
    for (int i = 0; i < 64; ++i) {
        if (is_it_your_turn(chessboard[i])) {
            vector<Move> moves = get_pseudolegal_moves(i);
            for (Move move : moves) {
                if (chessboard[move.to] != 0) capture_moves.emplace_back(move);
            }
        }
    }
    return capture_moves;
}








