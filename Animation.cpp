/*
	No rights Reserved.
	Amish Kumar Naidu
	amhndu at gmail.com
*/
#include "Animation.h"
#include "Application.h"

Animation::Animation(TextureIdentifier tid) :
    WorldObject(PassiveType),
    timer(),
    baseImage(Application::getTexture(tid)),
    frameSpr(baseImage),
    frameSize(),
    repeat(false),
    frameposition(),
    frame(),
    endFrame(),
    totalFrames(),
    secondsPerFrame(1/15.0)
{
    selfDestruct = false;
}
Animation::Animation(TextureIdentifier tid,const sf::Vector2i& fsize,const sf::Vector2f& pos,
                     double spf,bool loop,int startFrame,int endframe ) :
    WorldObject(PassiveType),
    timer(),
    baseImage(Application::getTexture(tid)),
    frameSpr(baseImage),
    frameSize(fsize),
    repeat(loop),
    frameposition(),
    frame(startFrame),
    endFrame(endframe),
    totalFrames(),
    secondsPerFrame(spf)
{
    selfDestruct = false;
    frameSpr.setOrigin(frameSize.x/2,frameSize.y/2);
    frameSpr.setPosition(pos);
    updateFrameDimensions();
}
void Animation::updateFrameDimensions()
{
    //vector of total frames per dimensions
    sf::Vector2i framesPerDim( (baseImage.getSize().x/frameSize.x),(baseImage.getSize().y/frameSize.y) );
    //If we have a grid of x*y frames, then e.g. say 4*4
    //frame.x = currentFrame mod x; e.g 0%4 = 5%4 ...
    //frame.y = (currentFrame - frame.x)/y e.g (2-2)/4 = 0, (6-2)/4 = 1 ...
    //or frame.y = currentFrame/y,since they are integers it does not make a difference
    frameposition.x = frame % framesPerDim.x;
    frameposition.y = frame / framesPerDim.x;
    //Multiply frameSize , to create co-ordinates for sprite
    frameposition.x = frameposition.x * frameSize.x;
    frameposition.y = frameposition.y * frameSize.y;
    totalFrames = framesPerDim.x * framesPerDim.y;
    if(!endFrame) //if not explicitly provided i.e not initialized to zero
        endFrame = totalFrames - 1;
    else
        endFrame %= totalFrames;
    frameSpr.setTextureRect(sf::IntRect(frameposition,frameSize));
}
void Animation::setFrameSize(const sf::Vector2i& size)
{
    frameSize = size;
    frameSpr.setOrigin(frameSize.x/2,frameSize.y/2);
    updateFrameDimensions();
}
void Animation::setFrameSize(int x,int y)
{
    frameSize.x = x;
    frameSize.y = y;
    frameSpr.setOrigin(frameSize.x/2,frameSize.y/2);
    updateFrameDimensions();
}
void Animation::reset()
{
    frame = 0;
    timer = 0;
    updateFrameDimensions();
}
void Animation::draw(sf::RenderTarget& target)
{
    target.draw(frameSpr);
}
void Animation::step(float dt)
{
    timer += dt;
    int c = frame;
    while(timer > secondsPerFrame)
    {
        timer -= secondsPerFrame;
        if(++frame >= endFrame)
        {
            if(!repeat)
                selfDestruct = true;
            else
                frame = 0;
        }
        updateFrameDimensions();
    }
    c = frame - c;
    c = 0;
}
void Animation::handleCollision(WorldObject &b){}

//Animation Creator
std::unique_ptr<Animation> AnimationCreator::create(AnimationType t,const sf::Vector2f& position)
{
    std::unique_ptr<Animation> anim(nullptr);
    switch(t)
    {
    case MissileExplosionA:
        {
            anim.reset(new Animation(ExplosionA,sf::Vector2i(128,128),position,1/25.0));
            anim->setRotation(rand()%360);
            anim->setScale(94.0/128.0,94.0/128.0);// scale = new_size / initial_size
        }
        break;
    case ArrowDown:
        {
            anim.reset(new Animation(ArrowDownSpriteSheet,sf::Vector2i(52,58),position,1/35.0,true));
            anim->setScale(30/52.0,30/52.0);
        }
        break;
    }
    return anim;
}
