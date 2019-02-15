/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include "SFML/Audio.hpp"

//struct Music{
//    sf::Music music;
//    sf::SoundBuffer buffer;
//};

class MusicManager{
public:
    static MusicManager* getInstance();
    void playMusic(std::string src);

    MusicManager();

    static MusicManager* instance;

};
