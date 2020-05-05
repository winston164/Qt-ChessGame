#include "ChessPiece.h"
#include "Tile.h"
#include "PromotionMenu.h"
#include <QtDebug>

Piece::Piece(QPixmap pixmap, char n){
    name = n;
    menu = nullptr;
    tile = nullptr;
    setPixmap(pixmap);
}

char Piece::getName(){
    return name;
}

void Piece::setTile(Tile *t){
    tile = t;
}

void Piece::setMenu(PromotionMenu * m){
    menu = m;
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(menu != nullptr){
        menu ->onClick(this);
    }
    if(tile != nullptr)
        tile ->mousePressEvent(event);
}


