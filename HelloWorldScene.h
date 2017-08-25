#pragma once
#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
protected:

public:

	void ChangeSceneToGamePlay_Stage_1(Ref* pSender);

public:

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};