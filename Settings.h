/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse

Projet de TDLog*/

#pragma once

#include <string>

#define TILE_SIZE     16

enum EntityType {ENTITY, CHARACTER};
enum TypeAnim{STILL, MOVE};
enum {HAUT = 0,BAS = 2,GAUCHE = 3,DROITE = 1};

struct Rect
{
    int x;
    int y;
    unsigned int w;
    unsigned int h;
};

struct Point
{
    int x;
    int y;
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

