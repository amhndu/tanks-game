#ifndef UTILITIES_INCLUDED
#define UTILITIES_INCLUDED
#include <SFML/Graphics.hpp>
#define LERP(t,a,b) ( (a) + (t) * ((b) - (a)) ) //liner interpolation
#define TO_RAD(x) ( (x)*M_PI/180.0 )
#define TO_DEG(x) ( (x)*180.0/M_PI )
#include "constants.h"
    #define DBG
    #ifdef DBG
    #include <iostream>
    #define PRINT_VAR(X) {std::cout << (#X) << " : " << (X) << std::endl;}
    #endif // DBG

bool inline isInWindow(int x, int y)
{
    return (x >= 0 && x < constants::windowWidth && y >= 0 && y < constants::windowHeight);
}
template<class IntType>

bool inline isInRange(IntType t,IntType a,IntType b) //is t under the range [a,b] inclusive
{
    //a must be greater than b , we don't check for
    return (t >= a && t <= b);
}

sf::Color inline grad(double t , sf::Color a, sf::Color b)
{
    sf::Color res;
    res.r = LERP(t, a.r, b.r);
    res.g = LERP(t, a.g, b.g);
    res.b = LERP(t, a.b, b.b);
    res.a = LERP(t, a.a, b.a);
    return res;
}

template<class T>
T inline arctan(T y,T x)
{
    return x?std::atan2(y,x):M_PI_2;
}

template<class T>
T inline sq(T a)
{
    return a*a;
}

inline float round(float number,float divisor)
{
    return divisor*static_cast<long long>(number/divisor+0.5);
}
inline double round(double number,double divisor)
{
    return divisor*static_cast<long long>(number/divisor+0.5);
}

template <typename T> //width and height must be +ve
inline bool contains(T rectX,T rectY,T width,T height,T x, T y)
{
    return (x >= rectX) && (x < rectX+width) && (y >= rectY) && (y < rectY+height);
}

sf::Vector2f RotatePoint(sf::Vector2f Point, sf::Vector2f Origin, double phi);
bool intersects(sf::CircleShape circle, sf::RectangleShape rect);
double cachedSqrt(int num);

#endif // UTILITIES_INCLUDED
