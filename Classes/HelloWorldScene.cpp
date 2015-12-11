#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    srand(time(NULL));
    visibleSize=Director::getInstance()->getVisibleSize();
    
    gameLayer=Node::create();
    addChild(gameLayer);
    
    
    timerLabel=Label::create();
    timerLabel->setTextColor(Color4B::BLUE);
    timerLabel->setSystemFontSize(40);
    timerLabel->setPosition(visibleSize.width/2,visibleSize.height*7/8);
    timerLabel->setString("0.0000000");
    addChild(timerLabel);
    
    startGame();
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* t,Event *e){
        auto blo=Block::getBlocks();
        Block* b;
        for (auto it=blo->begin(); it!=blo->end(); ++it) {
            b=*it;
            if(b->getLineIndex()==1&&
               b->getBoundingBox().containsPoint(t->getLocation())){
                if(b->getColor()==Color3B::BLACK){
                    if (!timerRunning) {
                        startTimer();
                    }
                    b->setColor(Color3B::GRAY);
                    this->moveDown();
                }else if (b->getColor() == Color3B::GREEN){
                    this->moveDown();
                    this->stopTimer();
                }
                else{
                    this->stopTimer();
                    MessageBox("oxiba....", "失败了。。。。");
                   // this->startGame();
                }
                break;
            }
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



void HelloWorld::addStartLine()
{
    auto b=Block::creatWithArgs(Color3B::YELLOW, Size(visibleSize.width,visibleSize.height/4), "开始游戏", 80,Color4B::BLUE);
    gameLayer->addChild(b);
    b->setLineIndex(0);
    
}

void HelloWorld::addEndLine()
{
    auto b = Block::creatWithArgs(Color3B::GREEN, visibleSize, "游戏结束", 80, Color4B::BLACK);
    //b->setPosition(visibleSize);
    gameLayer->addChild(b);
    b->setLineIndex(4);
}

void HelloWorld::addNormalLine(int lineIndex)
{
    Block *b;
    int blackIndex = rand()%4;
    for(int i=0;i<4;++i)
    {
        b=Block::creatWithArgs(blackIndex == i?Color3B::BLACK:Color3B::WHITE,Size(visibleSize.width/4-1,visibleSize.height/4-1),
                               "",20,Color4B::BLACK);
        gameLayer->addChild(b);
        b->setPosition(i*visibleSize.width/4,lineIndex*visibleSize.height/4);
        b->setLineIndex(lineIndex);
    }
    ++linesCount;
    
}

void HelloWorld::startGame()
{
    linesCount=0;
    showEnd=false;
    timerRunning=false;
    
    addStartLine();
    addNormalLine(1);
    addNormalLine(2);
    addNormalLine(3);
}

void HelloWorld::moveDown(){
    if (linesCount<10) {
        addNormalLine(4);
    }else {
        if (showEnd==false) {
            addEndLine();
            showEnd=true;
        }
    }
    log("%d",linesCount);
    auto bs = Block::getBlocks();
    
    for (auto it =bs->begin(); it!=bs->end(); ++it) {
        (*it)->moveDown();
    }
    
}




void HelloWorld::update(float dt){
    long offset=clock()-startTime;
   timerLabel->setString( StringUtils::format("%g",((double)offset)/1000000));
}


void HelloWorld::startTimer(){
    if (!timerRunning) {
        scheduleUpdate();
        startTime=clock();
        timerRunning=true;
    }
}

void HelloWorld::stopTimer(){
    if (timerRunning) {
        unscheduleUpdate();
        timerRunning=false;
    }
}
















