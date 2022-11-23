#include <iostream>
#include <vector>
#include "Position.h"
#include <string>
#include "Figure.h"
#include <chrono>
#include <bitset>
#include <algorithm>
#include <stack>
#include <omp.h>

using namespace std;

int main() {

    Position Pos = Position();
    stack<Move> move_stack;


    cout << "Chess Engine" << endl;
    cout << endl;
    cout << "Type '?' to get a list of commands" << endl;
    string input;
    while (true){
        getline(std::cin, input);
        if (input == "?"){
            cout << endl;
            cout << "Commands:" << endl;
            cout << endl;
            cout << "[s]etboard <fen> \t set position to <fen>" << endl;
            cout << "[i]nitial \t \t setup initial position" << endl;
            cout << "[k]iwi \t \t \t setup Kiwipete position (useful for perft tests)" << endl;
            cout << "[b]oard \t \t view current board" << endl;
            cout << "[e]val \t \t \t view evaluation of the current position" << endl;
            cout << "[p]erft <depth>\t \t test the move generation on current position" << endl;
            cout << "[d]ivide <depth> \t run a perft split by move on current position" << endl;
            cout << "[l]ist \t \t \t list the legal moves for current position" << endl;
            cout << "[m]ove <move> \t \t play the move <move>" << endl;
            cout << "[u]ndo \t \t \t undo last played move" << endl;
            cout << "[c]alculate \t \t calculate best move for current position" << endl;
            cout << "[g]ame \t \t \t start a game against the engine on current position" << endl;
            cout << "[ccg]ame \t \t start a game engine vs engine on current position" << endl;
            cout << "[q]uit \t \t \t quit" << endl;
            cout << endl;
        }
        else if (input[0] == 's'){
            cout << endl;
            cout << "setting board..." << endl;
            string fen = input.substr(2);
            Pos = Position(fen);
            Pos.print_board();
            cout << endl;
        }
        else if (input == "i"){
            cout << endl;
            cout << "setting up initial position..." << endl;
            Pos = Position();
            Pos.print_board();
            cout << endl;
        }
        else if (input == "k"){
            cout << endl;
            cout << "setting up kiwipete position..." << endl;
            Pos = Position("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
            Pos.print_board();
            cout << endl;
        }
        else if (input == "b"){
            cout << endl;
            Pos.print_board();
            cout << endl;
        }
        else if (input == "e"){
            cout << endl;
            cout << "Evaluation: " << Pos.evaluate() << endl;
            cout << endl;
        }
        else if (input[0] == 'p'){
            cout << endl;
            int depth = input[2] - '0';
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            long long int perft_result = Pos.perft_parallel(depth);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            cout << "computed " << perft_result << " possible positions (depth " << depth <<
            ") in " << ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000) <<
            " seconds" << endl;
            cout << endl;
        }
        else if (input[0] == 'd'){
            cout << endl;
            int depth = input[2] - '0';
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            long long int perft_result = Pos.perft_divide_parallel(depth);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            cout << endl << endl;
            cout << "computed " << perft_result << " possible positions (depth " << depth <<
                 ") in " << ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000) <<
                 " seconds" << endl;
            cout << endl;
        }
        else if (input == "l"){
            cout << endl;
            vector<Move> moves = Pos.get_all_legal_moves();
            cout << "legal moves: ";
            for (Move move : moves) {
                cout << move.to_letter_string() << " ";
            }
            cout << endl;
            cout << endl;
        }
        else if (input[0] == 'm'){
            cout << endl;
            string move_string = input.substr(2);
            Move move = Move(move_string);
            vector<Move> legal_moves = Pos.get_all_legal_moves();
            if(std::find(legal_moves.begin(), legal_moves.end(), move) != legal_moves.end()) {
                cout << "making move: " << move.to_letter_string() << endl;
                Pos.make_move(move);
                move_stack.push(move);
                Pos.print_board();
            } else {
                cout << "move " << move.to_letter_string() << " is not possible" << endl;
            }
            cout << endl;
        }
        else if (input == "u"){
            cout << endl;
            if (!move_stack.empty()) {
                Move move = move_stack.top();
                cout << "undo move: " << move.to_letter_string() << endl;
                Pos.undo_move(move);
                move_stack.pop();
                Pos.print_board();
            }
            else {
                cout << "no move played yet" << endl;
            }
            cout << endl;
        }
        else if (input == "c"){
            cout << endl;
            cout << "calculating best move..." << endl;
            Move move = Pos.get_best_move();
            cout << endl;
            cout << endl;
        }
        else if (input == "g"){
            cout << endl;
            cout << "starting game vs engine..." << endl;
            cout << "type 'q' to quit game" << endl;
            Pos.print_board();
            int i = 0;
            Move best_move;
            bool quit = false;
            while (!Pos.get_all_legal_moves().empty()){
                if (i % 2 == 0) {
                    vector<Move> legal_moves = Pos.get_all_legal_moves();
                    Move move;
                    while (true){
                        getline(std::cin, input);
                        if (input.size() > 5){
                            string move_string = input.substr(2);
                            move = Move(move_string);
                        } else {
                            move = Move();
                        }
                        if (input[0] == 'm' && find(legal_moves.begin(), legal_moves.end(), move) != legal_moves.end()){
                            break;
                        } else {
                            if (input == "q") {
                                cout << "quitting game..." << endl;
                                quit = true;
                                break;
                            }
                            cout << "invalid input. type 'm <your move>' " << endl;
                        }
                    }
                    if (quit) break;
                    cout << "making move: " << move.to_letter_string() << endl;
                    Pos.make_move(move);
                    Pos.print_board();
                } else {
                    best_move = Pos.get_best_move();
                    cout << "move value: " << best_move.value << endl;
                    Move engine_move = Move(best_move.from, best_move.to); // reset move info!
                    Pos.make_move(engine_move);
                    Pos.print_board();
                }
                i++;
            }
            if (!quit){
                if (Pos.is_threatened(Pos.enemy_king_index)){
                    if (Pos.white_move) cout << "Black won!" << endl;
                    else cout << "White won!" << endl;
                }
                else cout << "Stalemate!" << endl;
                cout << endl;
            }
        }
        else if (input == "ccg"){
            cout << endl;
            Move best_move;
            cout << "starting game engine vs engine..." << endl;
            Pos.print_board();
            while (!Pos.get_all_legal_moves().empty()){
                best_move = Pos.get_best_move();
                Pos.make_move(best_move);
                Pos.print_board();
            }
            if (Pos.is_threatened(Pos.enemy_king_index)){
                if (Pos.white_move) cout << "Black won!" << endl;
                else cout << "White won!" << endl;
            }
            else cout << "Stalemate!" << endl;
            cout << endl;
        }
        else if (input == "q"){
            cout << endl;
            cout << "quitting..." <<  endl;
            break;
        }
    }

    return 0;
}
