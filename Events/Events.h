/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#ifndef DEF_EVENTS
#define DEF_EVENTS
#include <SFML/Graphics.hpp>

class Keyboard;
class Mouse;

class Events
{
    public:
        static Events* getInstance();
        void handleEvents(sf::RenderWindow* window);

        sf::Event getEvent();
    private:
        Events();
        ~Events();
        static Events* instance;

        sf::Event event;
        Keyboard* key;
        Mouse* mouse;
};

#endif // DEF_EVENTS
