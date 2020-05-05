#pragma once
#ifndef TILE_H
#define TILE_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include "StandardPosition.h"
#include "ChessPiece.h"
class Board;
class Tile: public QGraphicsRectItem{
public:
    Tile(int x, int y, AGChess::Square s, Board * b = nullptr, int width = 100, int height = 100);
    void movePiece(Tile * t);
    void putPiece(Piece * p);
    void deletePiece();
    void setColor(QColor color);//QColor(int r, int g, int b, int a = 255)
    void highlight();
    AGChess::Square getSquare();
    Piece * getPiece();
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
private:
    QColor ogColor;
    AGChess::Square square;
    Piece * piece;
    Board * board;
    bool highlighted;
};

#endif // TILE_H
