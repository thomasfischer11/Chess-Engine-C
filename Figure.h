#ifndef CHESS_FIGURE_H
#define CHESS_FIGURE_H
#include <vector>
#include <map>
#include <iostream>

using namespace std;

static const int None = 0;
static const int King = 1;
static const int Pawn = 2;
static const int Knight = 3;
static const int Bishop = 5;
static const int Rook = 6;
static const int Queen = 7;

static const int Black = 8;
static const int White = 16;

static const int Type_Mask = 7;
static const int Colour_Mask = White | Black;

static const int WP_Start_Row = 1; // white pawn start row
static const int BP_Start_Row = 6;

static const vector<int> Direction_Offsets = {1, 8, -1, -8, 7, 9, -7, -9};
static const vector<int> Knight_Offsets = {6, -6, 10, -10, 15, -15, 17, -17};
static const vector<int> W_Pawn_Offsets = {8, 7, 9};
static const vector<int> B_Pawn_Offsets = {-8, -9, -7};

static const map<char, int> Char_To_Number = {
        { 'p', Black | Pawn },
        { 'P', White | Pawn },
        { 'r', Black | Rook },
        { 'R', White | Rook },
        { 'n', Black | Knight },
        { 'N', White | Knight },
        { 'b', Black | Bishop },
        { 'B', White | Bishop },
        { 'q', Black | Queen },
        { 'Q', White | Queen },
        { 'k', Black | King },
        { 'K', White | King },
};

static const map<int, char> Number_To_Char = {
        { Black | Pawn, 'p'},
        { White | Pawn, 'P' },
        { Black | Rook, 'r' },
        { White | Rook, 'R' },
        { Black | Knight, 'n' },
        { White | Knight, 'N' },
        { Black | Bishop, 'b' },
        { White | Bishop, 'B' },
        { Black | Queen, 'q' },
        { White | Queen, 'Q' },
        { Black | King, 'k' },
        { White | King, 'K' },
};

static const map<int, int> Values = {
        { Pawn, 100 },
        { Knight, 320 },
        { Bishop, 350},
        { Rook, 500 },
        { Queen, 900 },
        { King, 20000 }
};

inline static int Get_Colour(int figure){
    return figure & Colour_Mask;
}

inline static int Get_Type(int figure){
    return figure & Type_Mask;
}

inline static bool Is_White(int figure){
    return figure & White;
}

inline static bool Is_Black(int figure){
    return figure & Black;
}

inline static bool Is_Colour(int figure, int colour){
    return Get_Colour(figure) & colour;
}

inline static bool Is_Sliding_Piece(int figure){
    return (figure & 4);
}

inline static bool Is_Same_Colour(int figure1, int figure2){
    return (Get_Colour(figure1) & figure2);
}

inline static bool Is_Opponent(int figure1, int figure2){
    return (figure1 | figure2) > (Black | White);
}

// Give Points to the evaluation of a Position based on where the Figures are standing on the board.

static const int Pawn_Map[] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        50, 50, 50, 50, 50, 50, 50, 50,
        10, 10, 20, 30, 30, 20, 10, 10,
        5,  5, 10, 25, 25, 10,  5,  5,
        0,  0,  0, 26, 25,  0,  0,  0,
        5, -5,-10,  0,  0,-10, -5,  5,
        5, 10, 10,-25,-25, 10, 10,  5,
        0,  0,  0,  0,  0,  0,  0,  0
};

static const int Knight_Map[] = {
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50,
};

static const int Bishop_Map[] = {
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  5,  0,  0,  0,  0,  5,-10,
        -20,-10,-10,-10,-10,-10,-10,-20,
};

static const int Rook_Map[] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        5, 10, 10, 10, 10, 10, 10,  5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        0,  0,  0,  5,  5,  0,  0,  0,
};

static const int Queen_Map[] = {
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5,  5,  5,  5,  0,-10,
        -5,  0,  5,  5,  5,  5,  0, -5,
        0,  0,  5,  5,  5,  5,  0, -5,
        -10,  5,  5,  5,  5,  5,  0,-10,
        -10,  0,  5,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
};

static const int King_Map[] = {
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -10,-20,-20,-20,-20,-20,-20,-10,
        20, 20,  0,  0,  0,  0, 20, 20,
        20, 30, 10,  0,  0, 10, 30, 20
};

inline static int Get_Figure_Value(int figure, int index){
    //if (Is_White(figure)) return Values.at(Get_Type(figure));
    //else return -Values.at(Get_Type(figure));

    int type = Get_Type(figure);
    int value;
    //cout << "index: " << index;
    if (Is_White(figure)) index = 63 - index;
    if (type == Pawn) value = 100 + Pawn_Map[index];
    else if (type == Knight) value = 320 + Knight_Map[index];
    else if (type == Bishop) value = 350 + Bishop_Map[index];
    else if (type == Rook) value = 500 + Rook_Map[index];
    else if (type == Queen) value = 900 + Queen_Map[index];
    else if (type == King) value = 20000 + King_Map[index];
    //cout << " value: " << value << endl;
    if (Is_White(figure)) return value;
    else return -value;
}


#endif //CHESS_FIGURE_H
