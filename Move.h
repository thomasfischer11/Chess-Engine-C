#include <string>

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

using namespace std;

class Move {
public:
    Move() : Move(0,0,0,0) {};
    Move(int from, int to) : Move(from, to, 0,0) {};
    Move(int from, int to, int info) : Move(from, to, info,0) {};
    Move(int from, int to, int info, int value);
    explicit Move(string s);
    int from;
    int to;
    int info;
    int value;
    // contains extra info (from least significant bit to most significant): captured figure (5 bits);
    // if it is promotion/en_passant/castling (each 1 bit --> 3 bits);
    // irreversible info about current position: castling rights (4 bits), halfmove clock (6 bits), ep state (8 bits)
    // and promotion type (what figure the move is promoting to, if it is promotion) (2 bits)
    string to_number_string();
    string to_letter_string();
    bool operator==(const Move& rhs);
    bool operator<(Move& rhs);
    Move copy();
    bool does_capture();
    int get_captured_figure();
    bool is_promotion();
    bool is_en_passant();
    bool is_castling();
    int get_castling_rights();
    int get_halfmove_clock();
    int get_ep_state();
    int get_promotion_type();
    void set_promotion_type(int promotion_type);
    static const int promotion_mask = 32;
    static const int en_passant_mask = 64;
    static const int castling_mask = 128;
    static const int castling_rights_mask = 0b1111 << 8;
    static const int halfmove_clock_mask = 0b111111 << 12;
    static const int ep_state_mask = 0b11111111 << 18;
    static const int promotion_type_mask = 0b11 << 26;
};



#endif //CHESS_MOVE_H
