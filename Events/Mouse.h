/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#ifndef DEF_MOUSE
#define DEF_MOUSE
#include <SFML/Graphics.hpp>

class Mouse
{
    public:
        Mouse();
        ~Mouse();

        void handleMouse();
        void pressLeft(int x, int y);
        void pressRight(int x, int y);
        void releaseLeft(int x, int y);
        void releaseRight(int x, int y);
        void motion(int x, int y);
    private:

        bool leftPressed;
        bool rightPressed;
};

#endif // DEF_MOUSE


