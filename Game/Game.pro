QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chesspiece.cpp \
    introwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    onlinegame.cpp \
    player_type.cpp \
    promotion.cpp \
    src/AlphaBetaPruner.cpp \
    src/Bishop.cpp \
    src/ChessBoard.cpp \
    src/ChessGame.cpp \
    src/King.cpp \
    src/Knight.cpp \
    src/Pawn.cpp \
    src/Queen.cpp \
    src/Rook.cpp \
    winer.cpp

HEADERS += \
    chesspiece.h \
    include/AlphaBetaPruner.h \
    include/ChessBoard.h \
    include/ChessDefinitions.h \
    include/ChessGame.h \
    include/ChessPieces.h \
    includesFile.h \
    introwindow.h \
    mainwindow.h \
    onlinegame.h \
    player_type.h \
    promotion.h \
    winer.h

FORMS += \
    introwindow.ui \
    mainwindow.ui \
    onlinegame.ui \
    player_type.ui \
    promotion.ui \
    winer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
