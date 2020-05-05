#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <QObject>
#include <vector>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include "Tile.h"

class Board: public QObject{
    Q_OBJECT
public:
    Board(int x, int y, QGraphicsScene * scene);
    void onCLick(Tile * t, QGraphicsSceneMouseEvent * event);
    QGraphicsScene * scene();
    QPointF getPos();
    void finishPromotion(Piece *);
private:
    bool promoting;
    bool wTurn;
    void promote(Tile *);
    AGChess::StandardPosition stdPos;
    QGraphicsScene * graphicsScene;
    QPointF position;
    std::vector<Tile *> tiles;
    std::vector<AGChess::Square> posibleSquares; //Highlighted tiles
    Tile * selectedTile;
    void selectTile(Tile * tile);
    void movePiece(Tile* from, Tile* to);
    std::vector<AGChess::Square> legalMoves(Tile* t);
    char winner();

};

#endif // BOARD_H
