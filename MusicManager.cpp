/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include"MusicManager.h"

MusicManager* MusicManager::instance = NULL;

MusicManager::MusicManager(){

}

MusicManager* MusicManager::getInstance(){return instance;}

void MusicManager::createInstance()
    { instance = new MusicManager; }

void MusicManager::playMusic(std::string src){
    music.openFromFile(src);
    music.play();
}

void MusicManager::stopMusic()
    { music.stop(); }



