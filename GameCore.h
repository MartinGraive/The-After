/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include <vector>
#include "Map.h"
#include "RenderingArray.h"
#include "Entity.h"
#include "MainPlayer.h"
#include "Camera.h"

class GameCore
{
    public:
        static GameCore* getInstance();

        static void createInstance(sf::RenderWindow* window);
        void init(sf::RenderWindow* window);

        RenderingArray* getEntities() const;
        Map* getMap() const;
        MainPlayer* getMPlayer() const;
        Character* getCharacters(int i) const;
        Camera* getCamera() const;

        int getNbCharacters() const;

        void addCharacter(Character* i);
    private:
        GameCore();
        ~GameCore();
        static GameCore* instance;
        void drawEntities(sf::RenderWindow* window);
        void process();

        RenderingArray* entities;
        MainPlayer* mplayer;
        std::vector<Character*> characters;
        Map* map;
        Camera* camera;
};

