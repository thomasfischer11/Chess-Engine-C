#include "Figure.h"
#include "Move.h"
#include <vector>

using namespace std;

#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H

#include <string>

class Position {
public:

    static const int LW_Rook_Start_Index = 0; // left white rook
    static const int RW_Rook_Start_Index = 7; // right white rook
    static const int LB_Rook_Start_Index = 56; // left black rook (white's POV)
    static const int RB_Rook_Start_Index = 63; // right black rook
    static const int W_King_Start_Index = 4;
    static const int B_King_Start_Index = 60;
    const static string Start_FEN;

    explicit Position() : Position(Start_FEN) {};
    explicit Position(string fen);
    static int Get_Row_By_Index(int index);
    static int Get_Column_By_Index(int index);
    static int Get_Index_By_Row_And_Column(int row, int column);
    static int Get_Index_By_Square(string square);
    static string Get_Square_By_Index(int index);
    static bool Is_No_Over_Edge_Move(int index_from,  int index_to);
    static bool Are_On_Same_Line(int index1,  int index2);
    int chessboard[64];
    bool white_move; // does white move next
    int white_king_index;
    int black_king_index;
    int enemy_king_index;
    bool white_can_castle_k; // white can castle kingside
    bool white_can_castle_q; // white can castle queenside
    bool black_can_castle_k;
    bool black_can_castle_q;
    int possible_en_passant; // if a pawn just made a two-square move, this is the index of the square "behind" the pawn
    int halfmove_clock; // number of halfmoves since the last capture or pawn advance, used for fifty-move rule
    int fullmove_number; // number of the full move. starts at 1, and is incremented after black's move
    Move best_move;

    void print_board();
    Position copy();
    vector<Move> get_pseudolegal_moves(int index);
    bool is_no_figure_between(int index1, int index2, int i);
    bool is_it_your_turn(int figure);
    vector<Move> get_all_pseudolegal_moves();
    vector<Move> get_all_pseudolegal_capture_moves();
    vector<Move> get_all_legal_moves();
    void make_move(Move &move);
    void undo_move(Move move);
    bool is_hanging(int index);
    bool is_hanging_by_pawn(int index);
    bool is_threatened(int index);
    bool is_threatened_by_pawn(int index);
    long long int perft_divide(int depth, int max_depth);
    long long int perft_divide_parallel(int depth);
    long long int perft(int depth);
    long long int perft_parallel(int depth);
    long long int other_perft(int depth);
    int evaluate();
    int minimax(int depth, int max_depth, int alpha, int beta);
    int search_captures(int alpha, int beta);
    void sort_moves(vector<Move> &moves);
    Move get_best_move();
    int  minimax_parallel(int depth, int alpha, int beta);
};

#endif //CHESS_POSITION_H
