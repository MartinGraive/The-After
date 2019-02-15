/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#ifndef DEF_TEXTUREHANDLER
#define DEF_TEXTUREHANDLER
#include <SFML/Graphics.hpp>

#define NB_CHARAS 5

struct Texture
{
    sf::Texture* t;
    int w;
    int h;
};

class TextureHandler
{
    public:
        static TextureHandler* getInstance();
        void loadGame();
        void freeGame();

        Texture getCharas(int i);
        Texture getVigils(int i);
        Texture getTileset();
        Texture getBubble();
        Texture getStars();
        Texture getWeisted();

        Texture loadTexture(std::string src);
    private:
        TextureHandler();
        ~TextureHandler();
        static TextureHandler* instance;

        Texture charas[NB_CHARAS];
        Texture vigils[1];
        Texture tileset;
        Texture bubble;
        Texture stars;
        Texture weisted;
};

#endif // DEF_TEXTUREHANDLER


