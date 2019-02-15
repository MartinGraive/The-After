/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include <string>

#define TILE_SIZE     16
#define TILESET_WIDTH 30

#define MAX_STUDENTS 25
#define MIN_TIME_SPAWN 10
#define MAX_TIME_SPAWN 35

enum EntityType {ENTITY, CHARACTER};
enum TypeAnim{STILL, MOVE};
enum {HAUT = 0,BAS = 2,GAUCHE = 3,DROITE = 1};

class Rect
{
    public:
        Rect() {}
        Rect(int x1, int y1, int w1, int h1) : x(x1), y(y1), w(w1), h(h1) {}

        int x;
        int y;
        unsigned int w;
        unsigned int h;
};

class Point
{
    public:
        Point() {}
        Point(int x1, int y1) : x(x1), y(y1) {}

        int x;
        int y;
};

class Pointd
{
    public:
        Pointd() {}
        Pointd(double x1, double y1) : x(x1), y(y1) {}

        double x;
        double y;
};

class Settings
{
    public:
        static Settings* getInstance();

        void init();
        void setW(int i);
        void setH(int i);
        void setScale(int i);
        int getW();
        int getH();
        int getScale();
        std::string getPath();
        bool hasQuit();
        void quit();
    private:
        Settings();
        ~Settings();
        static Settings* instance;

        int w;
        int h;
        int scale;
        std::string path;
        bool quitting;
};

