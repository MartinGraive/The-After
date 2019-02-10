/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#ifndef DEF_ELLIPSESHAPE
#define DEF_ELLIPSESHAPE
#include <SFML/Graphics.hpp>

class EllipseShape : public sf::Shape
{
    public :
        explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0, 0));
        void setRadius(const sf::Vector2f& radius);

        const sf::Vector2f& getRadius() const;

        virtual std::size_t getPointCount() const;

        virtual sf::Vector2f getPoint(std::size_t index) const;

    private :
        sf::Vector2f m_radius;
};

#endif //DEF_ELLIPSEHAPE
