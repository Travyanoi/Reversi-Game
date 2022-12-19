#ifndef REVERSI_BOARD_H
#define REVERSI_BOARD_H

class Board{
private:
    int board[8][8] = {};
public:
    Board(){
        // Заполняем начальное положение первых двух фигур по правилам
        board[3][3] = 1;
        board[3][4] = 2;
        board[4][3] = 2;
        board[4][4] = 1;
    }
    ~Board() = default;

    int Get_Board(int row, int col);
    void Set_Value_Board(int row, int col, int value);
};

#endif //REVERSI_BOARD_H
