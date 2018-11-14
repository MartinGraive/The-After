/*Random Game
Started on 27/01/2018

Grade (programming / Concept)*/

#ifndef DEF_ELLIPSESHAPE
#define DEF_ELLIPSESHAPE
#include <SFML/Graphics.hpp>

class EllipseShape : public sf::Shape
{
    public :
        explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0, 0));
        void setRadius(const sf::Vector2f& radius);

        const sf::Vector2f& getRadius() const;

        virtual unsigned int getPointCount() const;

        virtual sf::Vector2f getPoint(unsigned int index) const;

    private :
        sf::Vector2f m_radius;
};

#endif //DEF_ELLIPSEHAPE
