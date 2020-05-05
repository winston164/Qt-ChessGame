#include "PromotionMenu.h"

Piece * makeAPiece(char c, int scale);

PromotionMenu::PromotionMenu(Tile *toPromote, Board * b){
    promoting = toPromote;
    board = b;
    int scale =85;

    //create pieces to fill menu
    if(promoting->getPiece()->getName() < 'a'){
        //White pawn
        //Queen
        pieces.push_back(makeAPiece('Q', scale));
        //Rook
        pieces.push_back(makeAPiece('R', scale));
        //Bishop
        pieces.push_back(makeAPiece('B', scale));
        //Knight
        pieces.push_back(makeAPiece('N', scale));

    }else{
        //Black pawn
        //Queen
        pieces.push_back(makeAPiece('q', scale));
        //Rook
        pieces.push_back(makeAPiece('r', scale));
        //Bishop
        pieces.push_back(makeAPiece('b', scale));
        //Knight
        pieces.push_back(makeAPiece('n', scale));
    }

    //create piece menu
    for(int i = 0; i < 4; i++) {
        pieces.at(i)->setPos(board->getPos().x() - scale,
                             board->getPos().y() + (scale * i));
        pieces.at(i)->setMenu(this);
        board->scene()->addItem(pieces.at(i));
    }
}

void PromotionMenu::onClick(Piece *p){
    promoting->putPiece(p);
    p->setMenu(nullptr);
    for(int i = 0; i < 4; i++) {
        if(p != pieces.at(i)){
            board->scene()->removeItem(pieces.at(i));
            delete pieces.at(i);
        }
    }
    board->finishPromotion(p);
    delete this;
}


Piece * makeAPiece(char c, int scale){
    static Piece * p;
    switch (c) {
        case 'K':
            p = new Piece(QPixmap(":/chessPiece/K.png").scaled(scale + 5, scale +5), 'K');
            break;
        case 'Q':
            p = new Piece(QPixmap(":/chessPiece/Q.png").scaled(scale + 5, scale +5), 'Q');
            break;
        case 'B':
            p = new Piece(QPixmap(":/chessPiece/B.png").scaled(scale + 5, scale +5), 'B');
            break;
        case 'N':
            p = new Piece(QPixmap(":/chessPiece/N.png").scaled(scale + 5, scale +5),'N');
            break;
        case 'R':
            p = new Piece(QPixmap(":/chessPiece/R.png").scaled(scale + 5, scale +5), 'R');
            break;
        case 'P':
            p = new Piece(QPixmap(":/chessPiece/P.png").scaled(scale + 5, scale +5), 'P');
            break;
        case 'k':
            p = new Piece(QPixmap(":/chessPiece/k.png").scaled(scale + 5, scale +5),'k');
            break;
        case 'q':
            p = new Piece(QPixmap(":/chessPiece/q.png").scaled(scale + 5, scale +5),'q');
            break;
        case 'b':
            p = new Piece(QPixmap(":/chessPiece/b.png").scaled(scale + 5, scale +5),'b');
            break;
        case 'n':
            p = new Piece(QPixmap(":/chessPiece/n.png").scaled(scale + 5, scale +5),'n');
            break;
        case 'r':
            p = new Piece(QPixmap(":/chessPiece/r.png").scaled(scale + 5, scale +5),'r');
            break;
        case 'p':
            p = new Piece(QPixmap(":/chessPiece/p.png").scaled(scale + 5, scale +5),'p');
            break;
        default:
            p = nullptr;
            break;
    }
    return p;
}
