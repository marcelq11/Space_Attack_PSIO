QT += core
TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle

SOURCES += \
    SA_main.cpp \
    bullet.cpp \
    drop.cpp \
    enemy.cpp \
    other.cpp \
    player.cpp \
    texturemanager.cpp

INCLUDEPATH += "C:/SFML-2.5.1/include"

LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    bullet.h \
    customrectangleshape.h \
    drop.h \
    enemy.h \
    other.h \
    player.h \
    texturemanager.h
