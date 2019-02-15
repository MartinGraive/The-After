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
#include "Settings.h"
#include "SceneManager.h"
#include "Graphics/FontHandler.h"
#include "GameScene.h"
#include "SplashScreenScene.h"
#include "Events/Events.h"
#include "MusicManager.h"

int main()
{
    ///Init random seed
    srand(time(NULL));

    FontHandler::createInstance();
    Settings::getInstance()->init();
    sf::RenderWindow window(sf::VideoMode(Settings::getInstance()->getW() * Settings::getInstance()->getScale(),
                                          Settings::getInstance()->getH() * Settings::getInstance()->getScale()),
                                          "The after at ENPC");
    SceneManager::createInstance(&window);
    MusicManager::createInstance();
    SplashScreenScene* ssscene = new SplashScreenScene(&window);

    SceneManager::getInstance()->stackScene(ssscene);

    sf::Clock clock;
    while (!SceneManager::getInstance()->isEmpty() && !Settings::getInstance()->hasQuit())
    {
        sf::Time elapsed1 = clock.restart();
        SceneManager::getInstance()->processScene();

        window.clear();
        SceneManager::getInstance()->drawScene();
        window.display();

        Events::getInstance()->handleEvents(&window);

        sf::Time elapsed2 = clock.getElapsedTime();
        if (elapsed2.asMilliseconds() - elapsed1.asMilliseconds() < 20) { sf::sleep(sf::milliseconds(20 - elapsed2.asMilliseconds() - elapsed1.asMilliseconds())); }
    }

    window.close();
    return 0;
}
