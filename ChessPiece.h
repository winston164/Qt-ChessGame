#pragma once
#ifndef PIECE_H
#define PIECE_H
#include <QPixmap>
#include <QPointer>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Tile;
class PromotionMenu;
class Piece: public QGraphicsPixmapItem{
public:
    Piece(QPixmap pixmap, char name);
    char getName();
    void setTile(Tile * t);
    void setMenu(PromotionMenu *);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
private:
    char name;
    Tile * tile;
    PromotionMenu * menu;
};


#endif // PIECE_H
