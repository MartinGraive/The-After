/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include <stack>
#include <SFML/Graphics.hpp>
#include "AbstractScene.h"

class SceneManager
{
    public:
        static SceneManager* getInstance();
        static void createInstance(sf::RenderWindow* win);

        void stackScene(AbstractScene* scene);
        void popScene();
        void drawScene();
        void processScene();
        bool isEmpty() const;
        AbstractScene* top() const;

        sf::RenderWindow* getWindow() const;
    private:
        SceneManager(sf::RenderWindow* win);
        ~SceneManager();
        static SceneManager* instance;

        std::stack<AbstractScene*> sceneStack;

        sf::RenderWindow* window;
};
