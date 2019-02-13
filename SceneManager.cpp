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

SceneManager::SceneManager(sf::RenderWindow* win) : window(win)
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

void SceneManager::createInstance(sf::RenderWindow* win)
{
    instance = new SceneManager(win);
}

void SceneManager::stackScene(AbstractScene* scene)
    { sceneStack.push(scene); }

void SceneManager::popScene()
{
    delete sceneStack.top();
    sceneStack.pop();
}

void SceneManager::drawScene()
    { sceneStack.top()->draw(); }

void SceneManager::processScene()
{
    if (sceneStack.top()->getNext() != NULL) { //pop and stack
        AbstractScene* next = sceneStack.top()->getNext();
        popScene();
        stackScene(next);
    }
    sceneStack.top()->process();
}

bool SceneManager::isEmpty() const
    { return sceneStack.empty(); }

AbstractScene* SceneManager::top() const
    { return sceneStack.top(); }

sf::RenderWindow* SceneManager::getWindow() const
    { return window; }
