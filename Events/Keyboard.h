/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#ifndef DEF_KEYBOARD
#define DEF_KEYBOARD
#include <SFML/Graphics.hpp>

class Events;

class Keyboard
{
    public:
        Keyboard(Events* ev);
        ~Keyboard();

        void punctualPress();
        void handleKeys();
    private:
        Events* events;
};

#endif // DEF_KEYBOARD

