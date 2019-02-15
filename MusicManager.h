/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include <SFML/Audio.hpp>

class MusicManager
{
    public:
        static MusicManager* getInstance();
        static void createInstance();

        void playMusic(std::string src);
        void stopMusic();

    private:
        MusicManager();
        ~MusicManager();

        sf::Music music;

        static MusicManager* instance;

};
