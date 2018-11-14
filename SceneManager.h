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
#include "AbstractScene.h"

class SceneManager
{
    public:
        static SceneManager* getInstance();
        static void createInstance();

        void stackScene(AbstractScene* scene);
        void drawScene();
        void processScene();
    private:
        SceneManager();
        ~SceneManager();
        static SceneManager* instance;

        std::stack<AbstractScene*> sceneStack;
};
