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
#include "HUD.h"

class GameCore
{
    public:
        static GameCore* getInstance();
        ~GameCore();

        static void createInstance(sf::RenderWindow* window = NULL);
        void init(sf::RenderWindow* window);

        RenderingArray* getEntities() const;
        Map* getMap() const;
        MainPlayer* getMPlayer() const;
        Character* getCharacters(int i) const;
        Camera* getCamera() const;
        HUD* getHUD() const;

        int getNbCharacters() const;

        void addCharacter(Character* i);
        void removeCharacter(Character* c);

        sf::Int32 getElapsedTime() const;
        void stopTime();

    private:
        GameCore();
        static GameCore* instance;
        void drawEntities(sf::RenderWindow* window);
        void process();

        RenderingArray* entities;
        MainPlayer* mplayer;
        std::vector<Character*> characters;
        Map* map;
        HUD* hud;
        Camera* camera;

        sf::Clock clock;
        bool clockStopped;
        sf::Int32 clockValueStopped;
};

