/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#ifndef DEF_FONTHANDLER
#define DEF_FONTHANDLER
#include <SFML/Graphics.hpp>

struct Font
{
    sf::Font* t;
};

class FontHandler
{
    public:
        static FontHandler* getInstance();
        static void createInstance();

        sf::Font* getFont();
    private:
        void loadFonts();

        FontHandler();
        ~FontHandler();
        static FontHandler* instance;

        sf::Font* font;
};

#endif // DEF_FONTHANDLER



