#include <iostream>
#include "Move.h"
#include "Position.h"

using namespace std;

Move::Move(int from, int to, int info, int value) {
    this->from = from;
    this->to = to;
    this->info = info;
    this->value = value;
}

Move::Move(string s) {
    this->from = (s[1] - '0' - 1) * 8 + s[0] - 'a';
    this->to = (s[3] - '0' - 1) * 8 + s[2] - 'a';
    this->info = 0;
    if (s.size() > 4){
        if (s[4] == 'k') this->info = 1 << 26;
        else if (s[4] == 'b') this->info = 2 << 26;
        else if (s[4] == 'r') this->info = 3 << 26;
    }
}

Move Move::copy() {
    Move m = Move();
    m.from = from;
    m.to = to;
    m.info = info;
    m.value = value;
    return m;
}

string Move::to_number_string() {
    return "From: " + to_string(this->from) + " To: " + to_string(this->to);
}

string Move::to_letter_string() {
    std::string from_column(1, 'a' + (from & 7));
    std::string to_column(1, 'a' + (to & 7));
    string promotion_string;
    if (get_promotion_type() != 0){
        if (get_promotion_type() == 1) promotion_string = 'k';
        else if (get_promotion_type() == 2) promotion_string = 'b';
        else if (get_promotion_type() == 3) promotion_string = 'r';
    }
    return (from_column + to_string((from >> 3) + 1) + to_column + to_string((to >> 3) + 1) + promotion_string);
}

bool Move::operator==(const Move &rhs) {
    return (this->from == rhs.from && this->to == rhs.to);
}

bool Move::operator<(Move &rhs) {
    return (value < rhs.value);
}

bool Move::does_capture() {
    return info & 31;
}

int Move::get_captured_figure() {
    return info & 31;
}

bool Move::is_promotion() {
    return info & promotion_mask;
}

bool Move::is_en_passant() {
    return info & en_passant_mask;
}

bool Move::is_castling() {
    return info & castling_mask;
}

int Move::get_castling_rights() {
    return (info & castling_rights_mask) >> 8;
}

int Move::get_halfmove_clock() {
    return (info & halfmove_clock_mask) >> 12;
}

int Move::get_ep_state() {
    return (info & ep_state_mask) >> 18;
}

int Move::get_promotion_type() {
    return (info & promotion_type_mask) >> 26;
}

void Move::set_promotion_type(int promotion_type){
    info |= (promotion_type << 26);
}










