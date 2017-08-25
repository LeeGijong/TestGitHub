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

	//�̺�Ʈ ������
	EventListenerKeyboard *mpListener = NULL;
	//��
	CTileMap *mpTileMap = NULL;
	Layer *mpLayer = NULL;
	//���ΰ�
	CActor *mpActor = NULL;
	//��
	CEnemy *mpEnemy = NULL;

	CGuageBar *mpHpGuageBarHP = NULL;
	CGuageBar *mpHpGuageBarMP = NULL;
	CGuageBar *mpHpGuageBarXP = NULL;

public:
	//Ű�Է�
	bool isLeftPressed;
	bool isRightPressed;
	bool isRunPressed;
	bool isJumpPressed;

	//���ΰ�
	void CreateActor();
	void CreateActorGuagebar();

	//��
	void CreateEnemy();
	void CreateEnemyGuagebar();

	void MP_XP_GuageBar();
	//������Ʈ
	virtual void update(float dt);

	//Ű���� ����
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

	//�� Enter, Exit
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