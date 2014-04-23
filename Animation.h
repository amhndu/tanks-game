#ifndef ANIMATION_H
#define ANIMATION_H

#include "WorldObject.h"
#include "ResourceIdentifiers.h"

class Animation : public WorldObject
{
    public:
        Animation(TextureIdentifier tid);
        Animation(TextureIdentifier tid,const sf::Vector2i& fsize,const sf::Vector2f& pos = sf::Vector2f(),
                     double spf = 1/15.0,bool loop = false,int startFrame = 0,int endframe = 0);
        inline int getFrame() { return frame; }
        inline bool getRepeat() { return repeat; }
        inline void setRepeat(bool flag) { repeat = flag; }
        inline void setScale(double x,double y) { frameSpr.setScale(x,y); }
        inline sf::Vector2f getPosition() { return frameSpr.getPosition(); }
        inline void setPosition(const sf::Vector2f& pos) { frameSpr.setPosition(pos); }
        inline void setRotation(float angle){ frameSpr.setRotation(angle); }
        inline float getRotation(){ return frameSpr.getRotation(); }
        void setFrameSize(const sf::Vector2i& size);
        void setFrameSize(int x,int y);
        inline const sf::Vector2i& getFrameSize() { return frameSize;}
        void draw(sf::RenderTarget&);
        void step(float dt);
        void handleCollision(WorldObject &b);
        void reset();
        void setSPF(double spf) { secondsPerFrame = spf;}
    private:
        double timer;
        sf::Texture&    baseImage;
        sf::Sprite      frameSpr;
        sf::Vector2i    frameSize;
        bool            repeat;
        sf::Vector2i    frameposition;
        int   frame;
        int endFrame;
        int totalFrames;
        double secondsPerFrame; // spf = 1/fps
    private:
        void updateFrameDimensions();
};

enum AnimationType
{
    MissileExplosionA,
    ArrowDown
};

namespace AnimationCreator
{
    std::unique_ptr<Animation> create(AnimationType t,const sf::Vector2f& position = sf::Vector2f());
}
#endif // ANIMATION_H
