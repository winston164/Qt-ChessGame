#include "Tile.h"
#include "ChessBoard.h"
#include "ChessPiece.h"
#include <QDebug>
#include <QBrush>
#include <QPen>

Tile::Tile(int x, int y, AGChess::Square s, Board * b, int width, int height){
    board = b;
    square = s;
    setPos(x,y);
    setRect(0, 0, width, height);
    ogColor = Qt::white;
    setBrush(ogColor);
    setPen(QPen(ogColor));
    highlighted = false;
    piece = nullptr;
}

void Tile::movePiece(Tile *t){
    t->putPiece(piece);
    piece = nullptr;
}


void Tile::putPiece(Piece *p){
    if(piece != nullptr){
        deletePiece();
    }
    piece = p;
    piece->setTile(this);
    piece->setPos(pos());
}

void Tile::deletePiece(){
    board->scene()->removeItem(piece);
    delete piece;
    piece = nullptr;
}

void Tile::setColor(QColor color){
    ogColor = color;
    setBrush(ogColor);
    setPen(QPen(ogColor));
}

void Tile::highlight(){
    highlighted = !highlighted;
    if(highlighted){
        setBrush(QColor(0,70,0));
        setPen(QPen(QColor(0,0,0)));
    }else{
        setPen(ogColor);
        setBrush(ogColor);
    }
}

AGChess::Square Tile::getSquare(){
    return square;
}

Piece *Tile::getPiece(){
    return piece;
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event){
    board->onCLick(this, event);
}


