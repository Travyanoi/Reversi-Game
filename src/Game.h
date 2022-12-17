#ifndef REVERSI_COURSE_WORK_GAME_H
#define REVERSI_COURSE_WORK_GAME_H

#include "Chips.h"

class Game: public Chips{
private:
    int current_Turn;
    bool gameOver;
    bool skipped;
    void flip(int row, int col);
    void nextTurn();
    void possibleMoves();
public:
    Game(){
       current_Turn = 2;
       gameOver = false;
       skipped = false;
       possibleMoves();
    }

    ~Game() = default;

    bool isValidMove(int row, int col);
    int flipCount(int row, int col);
    void click(int row, int col);
    int GetCurrentTurn() const;
    bool Get_gameOver() const;
};

#endif //REVERSI_COURSE_WORK_GAME_H
