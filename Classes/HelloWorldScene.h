#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Block.hpp"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
private:
    Size visibleSize;
    int linesCount;
    bool showEnd;
    Label *timerLabel;
    Node *gameLayer;
    bool timerRunning;
    long startTime;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void addStartLine();
    void addEndLine();
    void addNormalLine(int LineIndex);
    void startGame();
    
    void moveDown();
    
    virtual void update(float dt);
    void startTimer();
    void stopTimer();
};

#endif // __HELLOWORLD_SCENE_H__
