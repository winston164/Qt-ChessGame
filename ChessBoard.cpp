#include "ChessBoard.h"
#include "PromotionMenu.h"
#include "FEN.h"
#include "EditablePosition.h"
#include "AGChess_Exception.h"
#include <iostream>
#include <QColor>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>

Piece * makePiece(char, int);

Board::Board(int x, int y, QGraphicsScene *scene){
    selectedTile = nullptr;
    promoting = false;
    position.setX(x);
    position.setY(y);

    int scale = 85;
    QFile file("../Chess/Position.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Couldn't open the file";
        exit(1);
    }

    QTextStream in(&file);
    QString line;
    while (!in.atEnd()) {
        line = line + in.readLine();
    }

    wTurn = false;
    if(line.contains(" w "))
        wTurn = true;

    AGChess::EditablePosition editablePosition = AGChess::positionFromFen(line.toStdString());
    try {
        stdPos.copy(editablePosition);
    } catch (AGChess::AGChess_Exception& e) {
        qDebug() << e.what();
        exit(1);
    }

    graphicsScene = scene;
    Tile * t;
    Piece * p;
    for(unsigned char i = 0; i <64; i++){
        t = new Tile(((i%8) * scale)+ x, (((63-i)/8) * scale) + y,
                     AGChess::Square(i),this, scale, scale);
        if((i+ i/8)%2 == 0){
            t->setColor(QColor(130,50,0));
        }

        scene->addItem(t);
        tiles.push_back(t);
    }
    for (unsigned char i = 0; i < 64; i++) {
        p = makePiece(stdPos.at(AGChess::Square(i)), scale);
        if(p != nullptr){
            graphicsScene->addItem(p);
            tiles.at(i)->putPiece(p);
        }
    }
}

void Board::onCLick(Tile *t, QGraphicsSceneMouseEvent *event){
    if(promoting){
        return;
    }
    if(selectedTile == nullptr){
        //if no tile selected previously
        if(t->getPiece() != nullptr){
            //if tile has a piece
            if(wTurn){
                //if white turn
                if(t->getPiece()->getName() < 'a'){
                    //if is a white piece
                    selectTile(t);
                }
            }else{
                //if black turn
                if(t->getPiece()->getName() > 'a'){
                    //if is a black piece
                    selectTile(t);
                }
            }
        }
    }else{
        //if tile selected previously

        //find if tile is a posibility
        bool possibleTile = false;
        for (unsigned int i = 0; i < posibleSquares.size() && !possibleTile; ++i) {
            if(t->getSquare() == posibleSquares.at(i)){
                possibleTile = true;
            }
        }

        //Case: Selected possible move tile
        if(possibleTile){
            //Make move
            selectedTile->movePiece(t);
            AGChess::basic_move m(selectedTile->getSquare(), t->getSquare());

            //Check En Passant
            if(stdPos.isEnPassantCapture(m)){
                int n = t->getSquare();
                if(t->getPiece()->getName() < 'a')
                    tiles.at(n-8)->deletePiece();
                else
                    tiles.at(n+8)->deletePiece();
            }

            //Check castleing
            if(stdPos.isCastle(m)){
                qDebug() << t->getSquare() << AGChess::Square(6);
                if(t->getSquare() == AGChess::Square(6)){
                    tiles.at(7)->movePiece(tiles.at(5));
                }
                if(t->getSquare() == AGChess::Square(2)){
                    tiles.at(0)->movePiece(tiles.at(3));
                }
                if(t->getSquare() == AGChess::Square(62)){
                    tiles.at(63)->movePiece(tiles.at(61));
                }
                if(t->getSquare() == AGChess::Square(58)){
                    tiles.at(56)->movePiece(tiles.at(59));
                }

            }

            //Check Promote
            promoting = stdPos.isPromotion(m);
            stdPos.make(m);
            selectTile(nullptr);

            //Promote
            if(promoting){
                if(t->getPiece()->getName() == 'p'
                        ||t->getPiece()->getName() == 'P'){
                    new PromotionMenu(t,this);
                }else{
                    promoting = false;
                }
            }


            //Change turn
            wTurn = !wTurn;
            char w = winner();
            if(w){
                if(w == 'w'){
                    //if white wins
                    Tile * t = new Tile(position.x() - 200, position.y() + 325,
                                        AGChess::Square(64), this);
                    scene()->addItem(t);

                }
                if(w == 'b'){
                    //black wins
                    Tile * t = new Tile(position.x() - 100, position.y() + 200,
                                        AGChess::Square(64), this);
                    t->setColor(QColor(0,0,0));
                    scene()->addItem(t);
                }
            }


        }

        //Case: Selected not possible move tile(ignore)


        //Case: Select other piece of the same color.
        if(t->getPiece() != nullptr){
            if(wTurn){
                if(t->getPiece()->getName() < 'a'){
                    //if is a white piece
                    selectTile(t);
                }
            }else{
                if(t->getPiece()->getName() > 'a'){
                    //if is a black piece
                    selectTile(t);
                }
            }
        }

    }
}

QGraphicsScene * Board::scene(){
    return graphicsScene;
}

QPointF Board::getPos(){
    return position;
}

void Board::finishPromotion(Piece * p){
    promoting = false;
    char name = 0;
    if(p->getName() > 'a'){
        name = p->getName() - 32;
    }else {
        name = p->getName();
    }
    stdPos.promote(AGChess::Piece(name));
}

void Board::selectTile(Tile * tile){
    //unhighlihgt previous tiles
    for (unsigned int i = 0; i < posibleSquares.size(); i++) {
       tiles.at(posibleSquares.at(i))->highlight();
    }
    posibleSquares.clear();
    if(selectedTile != nullptr)
        selectedTile->highlight();

    //Select new tile
    selectedTile = tile;
    if(selectedTile != nullptr){
        //hilight selected piece
        selectedTile->highlight();

        //find legal moves
        posibleSquares = legalMoves(selectedTile);

        //highlight legal moves
        for (unsigned int i = 0; i < posibleSquares.size(); i++) {
            tiles.at(posibleSquares.at(i))->highlight();
        }
    }
}

std::vector<AGChess::Square> Board::legalMoves(Tile *t){
    bool error = true;
    std::vector<AGChess::Square> v;
    AGChess::Bitboard bb = stdPos.pseudoLegalMoves(t->getSquare());

    for (int i = 0; i < 64; i++) {
            if(bb & AGChess::SquaresBB[i]){
                AGChess::basic_move m(t->getSquare(), AGChess::Square(i));
                try {
                    if(stdPos.isPromotion(m)
                       && (t->getPiece()->getName() == 'p'
                           || t->getPiece()->getName() == 'P')){
                        v.push_back(AGChess::Square(i));
                        error = true;
                    }else{
                        stdPos.make(m);
                        error = false;
                    }
                } catch (AGChess::AGChess_Exception& e) {
                    error = true;
                }
                if(!error){
                    stdPos.unmake(m);
                    v.push_back(AGChess::Square(i));
                }
            }
        }
    return v;
}

char Board::winner(){
    std::vector<AGChess::Square> moves(0);
    if(wTurn){
        for (int i = 0; i < 64; i++) {
            if(tiles.at(i)->getPiece() != nullptr
                    && tiles.at(i)->getPiece()->getName() < 'a'){
                moves = legalMoves(tiles.at(i));
                if(moves.size() > 0){
                    return 0;
                }
                moves.clear();
            }
        }
        return 'b';
    }else{
        for (int i = 0; i < 64; i++) {
            if(tiles.at(i)->getPiece() != nullptr
                    && tiles.at(i)->getPiece()->getName() > 'a'){
                moves = legalMoves(tiles.at(i));
                if(moves.size() > 0){
                    return 0;
                }
                moves.clear();
            }
        }
        return 'w';
    }
}

Piece * makePiece(char c, int scale){
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


