#include "utilities.h"
#include "Game.h"
#include <unordered_map>

sf::Vector2f RotatePoint(sf::Vector2f Point, sf::Vector2f Origin, double phi)
{
    double c = std::cos(phi) ,s = std::sin(phi);
    sf::Vector2f TranslatedPoint;
    TranslatedPoint.x = (Origin.x + (Point.x - Origin.x) * c
        - (Point.y - Origin.y) * s);
    TranslatedPoint.y = (Origin.y + (Point.y - Origin.y) * c
        + (Point.x - Origin.x) * s);
    return TranslatedPoint;
}
bool intersects(sf::CircleShape circle, sf::RectangleShape rect)
{
    //turn the circle to (-angle of rect) so that rect OBB is now AABB
    circle.setPosition(RotatePoint(circle.getPosition(),rect.getPosition(),TO_RAD(-rect.getRotation())));
    sf::Vector2f circleDistance;
    circleDistance.x = abs(circle.getPosition().x - rect.getPosition().x);
    circleDistance.y = abs(circle.getPosition().y - rect.getPosition().y);
    //check intersection with the edges
    if (circleDistance.x > (rect.getLocalBounds().width/2 + circle.getRadius())) { return false; }
    if (circleDistance.y > (rect.getLocalBounds().height/2 + circle.getRadius())) { return false; }

    if (circleDistance.x <= (rect.getLocalBounds().width/2)) { return true; }
    if (circleDistance.y <= (rect.getLocalBounds().height/2)) { return true; }
    //check corner intersection
    double cornerDistance_sq = sq(circleDistance.x - rect.getLocalBounds().width/2) +
                         sq(circleDistance.y - rect.getLocalBounds().height/2);

    return (cornerDistance_sq <= sq(circle.getRadius()));
}
double cachedSqrt(int num)
{
    static std::unordered_map<int,double> cache;
    auto a = cache.find(num);
    if(a != cache.end())
        return a->second;
    else
    {
        double temp = std::sqrt(num);
        cache[num] = temp;
        return temp;
    }
    return 0;
}
