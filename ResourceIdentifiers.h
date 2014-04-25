#ifndef RESOURCEIDENTIFIERS_INCLUDED
#define RESOURCEIDENTIFIERS_INCLUDED
#include <SFML/Graphics.hpp>
enum TextureIdentifier
{
    TankTexture,
    ExplosionA,
//    ExplosionB,
    TurretTexture,
    TurretTarget,
    ArrowDownSpriteSheet,
    TitleBg
};
enum FontIdentifier
{
    FreeSans,
    UbuntuCondensed
};

template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture,TextureIdentifier> TextureManager;
typedef ResourceManager<sf::Font,FontIdentifier> FontManager;


#endif // RESOURCEIDENTIFIERS_INCLUDED
