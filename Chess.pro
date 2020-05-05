#-------------------------------------------------
#
# Project created by QtCreator 2019-05-03T15:09:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Bitboard.cpp \
        Bitboard_MoveGen.cpp \
        Board.cpp \
        Board_MoveGen.cpp \
        ChessBoard.cpp \
        ChessPiece.cpp \
        Color.cpp \
        ColoredPiece.cpp \
        DatabaseFilter.cpp \
        EditablePosition.cpp \
        FEN.cpp \
        GameHeaders.cpp \
        GameTree.cpp \
        Menu.cpp \
        Move.cpp \
        PGNDatabase.cpp \
        PGNLexer.cpp \
        Piece.cpp \
        Position.cpp \
        Position_MoveGen.cpp \
        PromotionMenu.cpp \
        SAN.cpp \
        SearchMask.cpp \
        SimpleGame.cpp \
        SimplePosition.cpp \
        Square.cpp \
        StandardChessGame.cpp \
        StandardPosition.cpp \
        TagPair.cpp \
        Tile.cpp \
        chess_iterator.cpp \
        main.cpp

HEADERS += \
    AGChess_Common.h \
    AGChess_Exception.h \
    Bitboard.h \
    Bitboard_MoveGen.h \
    Board.h \
    Board_MoveGen.h \
    ChessBoard.h \
    ChessPiece.h \
    Color.h \
    ColoredPiece.h \
    DatabaseFilter.h \
    EditablePosition.h \
    FEN.h \
    GameHeaders.h \
    GameTree.h \
    Menu.h \
    Move.h \
    MoveTreeNode.h \
    PGNDatabase.h \
    PGNLexer.h \
    Piece.h \
    Position.h \
    PromotionMenu.h \
    SAN.h \
    SearchMask.h \
    SimpleGame.h \
    SimplePosition.h \
    Square.h \
    StandardChessGame.h \
    StandardPosition.h \
    StartPos.h \
    TagPair.h \
    Tile.h \
    Token.h \
    chess_iterator.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
