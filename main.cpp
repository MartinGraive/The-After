/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <experimental/filesystem>
#include "Settings.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Events/Events.h"

int main()
{
    ///Init random seed
    srand(time(NULL));

    Settings::getInstance()->init();
    sf::RenderWindow window(sf::VideoMode(Settings::getInstance()->getW() * Settings::getInstance()->getScale(),
                                          Settings::getInstance()->getH() * Settings::getInstance()->getScale()),
                                          "The after at ENPC");

    SceneManager::createInstance();
    GameScene* scene = new GameScene(&window);

    SceneManager::getInstance()->stackScene(scene);

    sf::Clock clock;
    while (!Settings::getInstance()->hasQuit())
    {
        sf::Time elapsed1 = clock.restart();
        Events::getInstance()->handleEvents(&window);
        SceneManager::getInstance()->processScene();

        window.clear();
        SceneManager::getInstance()->drawScene();
        window.display();
        sf::Time elapsed2 = clock.getElapsedTime();
        if (elapsed2.asMilliseconds() - elapsed1.asMilliseconds() < 20) { sf::sleep(sf::milliseconds(20-elapsed2.asMilliseconds()-elapsed1.asMilliseconds())); }
    }

    window.close();
    return 0;
}
