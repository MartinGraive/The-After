/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#ifndef DEF_TEXTUREHANDLER
#define DEF_TEXTUREHANDLER
#include <SFML/Graphics.hpp>

struct Texture
{
    sf::Texture* t;
};

class TextureHandler
{
    public:
        static TextureHandler* getInstance();
        void loadGame();
        void freeGame();

        Texture getCharas(int i);
        Texture getVigils(int i);
    private:
        TextureHandler();
        ~TextureHandler();
        static TextureHandler* instance;
        Texture loadTexture(std::string src);

        Texture charas[1];
        Texture vigils[1];
};

#endif // DEF_TEXTUREHANDLER


