#include "Game.h"

bool Game::isValidMove(int row, int col) {
    if(row < 0 || row > 7 || col < 0 || col > 7){
        return false;
    }
    if (Get_Board(row, col) > 0) {
        return false;
    }

    return flipCount(row, col) > 0;
}

int Game::flipCount(int row, int col) {
    if (row >= 8 || col >= 8 || row < 0 || col < 0) {
        return 0;
    }

    int dirX;
    int dirY;
    int dist = 1;
    int curX = col;
    int curY = row;
    int flipCount = 0;

    for(dirX = -1; dirX < 2; dirX++) {
        for(dirY = -1; dirY < 2; dirY++) {
            dist = 1;

            while(true){
                curX = col + (dist * dirX);
                curY = row + (dist * dirY);

                if(curX < 0 || curY < 0 || curX > 7 || curY > 7){
                    break;
                }
                if(Get_Board(curY, curX) < 1){
                    break;
                }
                if(Get_Board(curY, curX) == current_Turn){
                    flipCount += dist - 1;
                    break;
                }
                if(dirX == 0 && dirY == 0){
                    break;
                }

                dist++;
            }
        }
    }

    return flipCount;
}

void Game::click(int row, int col) {
    if(isValidMove(row, col)){
        Set_Value_Board(row, col, current_Turn);
        flip(row, col);
        nextTurn();
    }
}

void Game::flip(int row, int col) {
    if (row >= 8 || col >= 8 || row < 0 || col < 0) {
        return;
    }

    int dirX;
    int dirY;
    int dist = 1;
    int curX = col;
    int curY = row;

    for(dirX = -1; dirX < 2; dirX++) {
        for(dirY = -1; dirY < 2; dirY++) {
            dist = 1;

            while(true){
                curX = col + (dist * dirX);
                curY = row + (dist * dirY);

                if(curX < 0 || curY < 0 || curX > 7 || curY > 7){
                    break;
                }
                if(Get_Board(curY, curX) < 1){
                    break;
                }
                if(Get_Board(curY, curX) == current_Turn){
                    for (dist--; dist > 0; dist--) {
                        curX = col + (dist * dirX);
                        curY = row + (dist * dirY);
                        Set_Value_Board(curY, curX, current_Turn);
                    }
                    break;
                }
                if(dirX == 0 && dirY == 0){
                    break;
                }

                dist++;
            }
        }
    }
}

int Game::GetCurrentTurn() const {
    return current_Turn;
}

bool Game::Get_gameOver() const {
    return gameOver;
}

void Game::nextTurn() {
    current_Turn = current_Turn == 1 ? 2 : 1;
    possibleMoves();

    if (gameOver) {
        return;
    }
}

void Game::possibleMoves() {
    int moves = 0;
    int blacks = 0;
    int whites = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(Get_Board(i, j) > 0) {

                if(Get_Board(i, j) == 1) {
                    whites++;
                    Set_White(whites);
                } else {
                    blacks++;
                    Set_Black(blacks);
                }

                continue;
            } else {
                Set_Value_Board(i, j, 0);
            }

            if(flipCount(i, j) > 0){
                Set_Value_Board(i, j, -1);
                skipped = false;
                moves++;
            }
        }
    }

    if(moves == 0 && !skipped) {
        skipped = true;
        nextTurn();
    } else if(moves == 0 && skipped) {
        gameOver = true;
    }
}

