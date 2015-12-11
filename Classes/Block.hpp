//
//  Block.hpp
//  white
//
//  Created by 杨海涛 on 15/12/11.
//
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include <cocos2d.h>
USING_NS_CC;
class Block:public Sprite{
private:
    static Vector<Block*> *blocks;
    int lineIndex;
public:
    static Vector<Block*> *getBlocks();
    static Block * creatWithArgs(Color3B color,Size size,std::string lable,
                                 float fontSize,Color4B textColor);
    virtual bool initWithArgs(Color3B color,Size size,std::string lable,
                              float fontSize,Color4B textColor);
    void removeBlock();
    int getLineIndex();
    void setLineIndex(int v);
    void moveDown();
};
#endif /* Block_hpp */
