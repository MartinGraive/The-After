/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "SceneManager.h"

SceneManager* SceneManager::instance = NULL;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
    /// Free all stacked scenes
    while (!sceneStack.empty()) {
        delete sceneStack.top();
        sceneStack.pop();
    }
}

SceneManager* SceneManager::getInstance() { return instance; }

void SceneManager::createInstance()
{
    instance = new SceneManager;
}

void SceneManager::stackScene(AbstractScene* scene)
    { sceneStack.push(scene); }

void SceneManager::drawScene()
    { sceneStack.top()->draw(); }

void SceneManager::processScene()
    { sceneStack.top()->process(); }
