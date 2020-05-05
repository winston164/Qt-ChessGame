#ifndef PROMOTIONMENU_H
#define PROMOTIONMENU_H
#include "ChessBoard.h"

class PromotionMenu
{
public:
    PromotionMenu(Tile * toPromote, Board *);
    void onClick(Piece *);
private:
    std::vector<Piece *> pieces;
    Tile *promoting;
    Board *board;
};

#endif // PROMOTIONMENU_H
