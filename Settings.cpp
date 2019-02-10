/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include "Settings.h"

#include <stdio.h>  /* defines FILENAME_MAX */

#ifdef _WIN32
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

Settings* Settings::instance = new Settings;

Settings::Settings() : path(""), quitting(false)
{
    #ifdef __APPLE__
        path = "../";
    #elif __linux__
        char buff[FILENAME_MAX];
        GetCurrentDir( buff, FILENAME_MAX );
        std::string current_working_dir(buff);
        if (current_working_dir.substr(current_working_dir.length()-5)=="build") path = current_working_dir + "/../";
        else path = current_working_dir + '/';
    #endif
}

Settings::~Settings()
{
}

Settings* Settings::getInstance() { return instance; }

void Settings::init()
{
    w = 384*3;
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

