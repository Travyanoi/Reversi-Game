#ifndef REVERSI_CHIPS_H
#define REVERSI_CHIPS_H

#include "Board.h"

class Chips: public Board{
private:
    int white_count;
    int black_count;
public:
    Chips(){
        white_count = 0;
        black_count = 0;
    }

    ~Chips() = default;

    int Get_White() const{
        return white_count;
    }
    int Get_Black() const{
        return black_count;
    }
    void Set_White(int value){
        white_count = value;
    }
    void Set_Black(int value){
        black_count = value;
    }
};

#endif //REVERSI_CHIPS_H
