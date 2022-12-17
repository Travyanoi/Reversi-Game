#include "Board.h"

int Board::Get_Board(int row, int col) {
    return board[row][col];
}

void Board::Set_Value_Board(int row, int col, int value) {
    board[row][col] = value;
}
