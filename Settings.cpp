/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include "Settings.h"

Settings* Settings::instance = new Settings;

Settings::Settings() : path(""), quitting(false)
{
    #ifndef WIN32
        path = "../";
    #endif
}

Settings::~Settings()
{
}

Settings* Settings::getInstance() { return instance; }

void Settings::init()
{
    w = 384*3; // bon ca va pas du tout je veux des multiples de 13 --Martin
    h = 216*3;
    scale = 1;
}

void Settings::setW(int i)
    { w=i; }

void Settings::setH(int i)
    { h=i; }

void Settings::setScale(int i)
    { scale=i; }

int Settings::getW()
    { return w; }

int Settings::getH()
    { return h; }

int Settings::getScale()
    { return scale; }

std::string Settings::getPath()
    { return path; }

bool Settings::hasQuit()
    { return quitting; }

void Settings::quit()
    { quitting = true; }

