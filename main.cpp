#include "ChessBoard.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QGraphicsScene * scene = new QGraphicsScene;
    scene->setBackgroundBrush(QBrush(QColor(225,225,225)));

    Board board(300,10,scene);


    QGraphicsView * view = new QGraphicsView;
    view->setScene(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(1000,700);
    scene->setSceneRect(0,0,1000,700);
    view->show();

    return a.exec();
}
