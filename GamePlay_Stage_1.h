#pragma once

#include "cocos2d.h"
#include "StateMachine.h"

USING_NS_CC;
class CActor;
class CTileMap;
class CGuageBar;
class CEnemy;

class CGamePlay_Stage_1 : public cocos2d::Scene
{
//protected:
public:

	//이벤트 리스너
	EventListenerKeyboard *mpListener = NULL;
	//맵
	CTileMap *mpTileMap = NULL;
	Layer *mpLayer = NULL;
	//주인공
	CActor *mpActor = NULL;
	//적
	CEnemy *mpEnemy = NULL;

	CGuageBar *mpHpGuageBarHP = NULL;
	CGuageBar *mpHpGuageBarMP = NULL;
	CGuageBar *mpHpGuageBarXP = NULL;

public:
	//키입력
	bool isLeftPressed;
	bool isRightPressed;
	bool isRunPressed;
	bool isJumpPressed;

	//주인공
	void CreateActor();
	void CreateActorGuagebar();

	//적
	void CreateEnemy();
	void CreateEnemyGuagebar();

	void MP_XP_GuageBar();
	//업데이트
	virtual void update(float dt);

	//키보드 관련
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

	//씬 Enter, Exit
	virtual void onEnter();
	virtual void onExit();

public:

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(CGamePlay_Stage_1);
};