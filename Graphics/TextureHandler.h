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

class TextureHandler
{
    public:
        static TextureHandler* getInstance();
        void loadGame();
        void freeGame();

        sf::Texture* getChara1();
        sf::Texture* getTiles();
    private:
        TextureHandler();
        ~TextureHandler();
        static TextureHandler* instance;
        sf::Texture* loadTexture(std::string src);

        sf::Texture* chara1;
        sf::Texture* tiles;
};

#endif // DEF_TEXTUREHANDLER


