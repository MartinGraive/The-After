/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include"MusicManager.h"

MusicManager* MusicManager::instance = new MusicManager;

MusicManager::MusicManager(){
}

MusicManager* MusicManager::getInstance(){return instance;}

void playMusic(std::string src){
    sf::Music music;
    music.openFromFile(src);
    music.play();
}



