#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GamePlay_Stage_1.h"
#include <iostream>


USING_NS_CC;
using namespace std;
Scene * HelloWorld::createScene()
{
	return HelloWorld::create();
}
bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2(750, 20));
	this->addChild(menu, 1);

	auto tStartBtn = MenuItemFont::create("StarteGame",
		CC_CALLBACK_1(HelloWorld::ChangeSceneToGamePlay_Stage_1, this));
	tStartBtn->setPosition(Vec2(400, 240));
	auto tMenu = Menu::create(tStartBtn, NULL);
	tMenu->setPosition(Vec2::ZERO);
	this->addChild(tMenu, 500);
	tMenu->retain();
	

    // create menu, it's an autorelease object
    /////////////////////////////=====================================================
	
    return true;
}

void HelloWorld::ChangeSceneToGamePlay_Stage_1(Ref* pSender)
{
	auto pScene = CGamePlay_Stage_1::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
