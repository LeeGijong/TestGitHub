#include <iostream>

#include "SimpleAudioEngine.h"

#include "GamePlay_Stage_1.h"
#include "AnimationBox.h"
#include "Actor.h"
#include "Enemy.h"
#include "CreateMap.h"
#include "GameDataS.h"
#include "GuageBar.h"


USING_NS_CC;
using namespace std;
Scene * CGamePlay_Stage_1::createScene()
{
	return CGamePlay_Stage_1::create();
}
bool CGamePlay_Stage_1::init()
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
                                           CC_CALLBACK_1(CGamePlay_Stage_1::menuCloseCallback, this));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2(750, 20));
	this->addChild(menu, 1);

    // create menu, it's an autorelease object
    /////////////////////////////=====================================================

	////맵 객체를 생성한다.
	mpLayer = Layer::create();
	mpLayer->setAnchorPoint(Vec2(0, 0));
	this->addChild(mpLayer);

	mpTileMap = new CTileMap();
	mpTileMap->CreateBackground("Project/Map/Stage1",mpLayer);

	//주인공 애니메이션 생성
	this->CreateActor();
	//주인공 게이지바 생성
	this->CreateActorGuagebar();

	//적 애니메이션 생성
	this->CreateEnemy();

	//팔로우
	mpLayer->runAction(Follow::create(mpActor->GetSprite(), Rect(0,0, 4096,480)));
	//업데이트
	this->scheduleUpdate();

    return true;
}
//업데이트
void CGamePlay_Stage_1::update(float dt)
{
	//주인공 움직임 관련
	mpActor->MoveActor();
	mpActor->KeyInPutSetActorSpeed();
	mpActor->JumpGravity();
	mpActor->IsCollision();
	//공격 관련

	//스킬 이동
	mpActor->MoveSkill(dt);
	//근거리 공격 포지션 설정
	mpActor->SetPositionSwordAttack();
	//원거리 공격 이동
	mpActor->MoveBullet();

	//MP,XP게이지
	this->MP_XP_GuageBar();
	
	//적 움직임 관련
	mpEnemy->Gravity();
	mpEnemy->IsCollision();
	mpEnemy->MoveEnemy();
	mpEnemy->SetPositionSwordAttack();
}
//주인공 애니메이션 생성
void CGamePlay_Stage_1::CreateActor()
{
	mpActor = new CActor();
	mpActor->Create();

	mpActor->SetScene(this);
	mpActor->SetLayer(mpLayer);
	mpActor->Build(500);
	mpActor->SetTileMap(mpTileMap);
	
	mpActor->mVecActor = Vec2(80,400);
	mpActor->SetPosition(mpActor->mVecActor);

	mpActor->StopAllAni();

	mpActor->AllHide();

	mpActor->DoAni_State(ACTOR_STATE_IDLE);
}
//게이지바 생성
void CGamePlay_Stage_1::CreateActorGuagebar()
{
	//MP바
	mpHpGuageBarMP = new CGuageBar();
	mpHpGuageBarMP->SetScene(this);
	mpHpGuageBarMP->Create("Project/UI/sliderProgress",
		CGameDataS::GetInstance()->GetInstance()->GetActorCurMP(),
		CGameDataS::GetInstance()->GetInstance()->GetActorMaxMP());
	mpHpGuageBarMP->Build(500);

	mpHpGuageBarMP->SetScaleX(0.5f);
	mpHpGuageBarMP->SetScaleY(3.0f);

	mpHpGuageBarMP->SetPosition(Vec2(150,430));
	
	//HP바
	mpHpGuageBarHP = new CGuageBar();
	mpHpGuageBarHP->SetScene(this);
	mpHpGuageBarHP->Create("Project/UI/sliderProgressHP",
		CGameDataS::GetInstance()->GetInstance()->GetActorCurHP(),
		CGameDataS::GetInstance()->GetInstance()->GetActorMaxHP());
	mpHpGuageBarHP->Build(500);

	mpHpGuageBarHP->SetScaleX(0.5f);
	mpHpGuageBarHP->SetScaleY(3.0f);

	mpHpGuageBarHP->SetPosition(Vec2(5, 430));

	//XP바
	mpHpGuageBarXP = new CGuageBar();
	mpHpGuageBarXP->SetScene(this);
	mpHpGuageBarXP->Create("Project/UI/sliderProgressXP",
		CGameDataS::GetInstance()->GetInstance()->GetActorCurXP(),
		CGameDataS::GetInstance()->GetInstance()->GetActorMaxXP());
	mpHpGuageBarXP->Build(500);

	mpHpGuageBarXP->SetScaleX(1.05f);
	mpHpGuageBarXP->SetScaleY(1.5f);

	mpHpGuageBarXP->SetPosition(Vec2(8.5f, 415));
}
void CGamePlay_Stage_1::MP_XP_GuageBar()
{
	mpHpGuageBarMP->BuildGuageRev(CGameDataS::GetInstance()->GetInstance()->GetActorCurMP());
	mpHpGuageBarXP->BuildGuageRev(CGameDataS::GetInstance()->GetInstance()->GetActorCurXP());
}
//적 생성
void CGamePlay_Stage_1::CreateEnemy()
{
	mpEnemy = new CEnemy();
	mpEnemy->Create();

	mpEnemy->SetScene(this);
	mpEnemy->SetLayer(mpLayer);
	mpEnemy->Build(500);
	mpEnemy->SetTileMap(mpTileMap);
	mpEnemy->SetActor(mpActor);

	mpEnemy->mVecEnemy = Vec2(700, 400);
	mpEnemy->SetPosition(mpEnemy->mVecEnemy);

	mpEnemy->StopAllAni();

	mpEnemy->AllHide();

	mpEnemy->DoAni_State(ENEMY_STATE_WALK);
}
//적 게이지바 생성
void CGamePlay_Stage_1::CreateEnemyGuagebar()
{

}
//키보드 키를 눌렸을때
void CGamePlay_Stage_1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	if (mpActor->GetState() != ACTOR_STATE_DIE)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			mpActor->DoAni_State(ACTOR_STATE_WALK);
			mpActor->SetFlipX(true);
			isLeftPressed = true;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			mpActor->DoAni_State(ACTOR_STATE_WALK);
			mpActor->SetFlipX(false);
			isRightPressed = true;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			mpActor->DoAni_State(ACTOR_STATE_JUMP);
			mpActor->JumpStart();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_SHIFT)
		{
			isRunPressed = true;
			if (isLeftPressed == true || isRightPressed == true)
			{
				if (isRunPressed == true)
				{
					mpActor->DoAni_State(ACTOR_STATE_RUN);
				}
			}

		}
		if (keyCode == EventKeyboard::KeyCode::KEY_Z)
		{
			mpActor->DoAni_State(ACTOR_STATE_ATTACK);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_X)
		{
			if (ACTOR_ATTACK_SWORD == mpActor->Get_Attack_State())
			{
				mpActor->Set_Attack_State(ACTOR_ATTACK_BULLET);
			}
			else
			{
				mpActor->Set_Attack_State(ACTOR_ATTACK_SWORD);
			}
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_C)
		{
			if (SKILL_STATE_DEAD == mpActor->mSkill_State && 1 <= CGameDataS::GetInstance()->GetActorCurMP())
			{
				mpActor->DoAni_State(ACTOR_STATE_SKILL);
			}
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_V)
		{
			if (CGameDataS::GetInstance()->GetActorCurMP() < CGameDataS::GetInstance()->GetActorMaxMP())
			{
				CGameDataS::GetInstance()->SetActorCurMP(CGameDataS::GetInstance()->GetActorCurMP() + 1);
			}
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			mpEnemy->DoAni_State(ENEMY_STATE_ATTACK);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			mpEnemy->DoAni_State(ENEMY_STATE_HURT);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			mpEnemy->DoAni_State(ENEMY_STATE_DIE);
		}
	}
}
//키보드 키를 땠을때
void CGamePlay_Stage_1::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	if (mpActor->GetState() != ACTOR_STATE_DIE)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			mpActor->DoAni_State(ACTOR_STATE_IDLE);
			isLeftPressed = false;
			//mpActor->mMoveSpeed = 0;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			mpActor->DoAni_State(ACTOR_STATE_IDLE);
			isRightPressed = false;
			//mpActor->mMoveSpeed = 0;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{

		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_SHIFT)
		{
			isRunPressed = false;
			if (isLeftPressed == true || isRightPressed == true)
			{
				if (isRunPressed == false)
				{
					mpActor->DoAni_Prev();
				}
			}
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_Z)
		{

		}
		//test
		if (keyCode == EventKeyboard::KeyCode::KEY_X)
		{
			
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_C)
		{
			
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_V)
		{
			
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{

		}
		if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{

		}
		if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{

		}
	}
}
void CGamePlay_Stage_1::onEnter()
{
	Scene::onEnter();

	mpListener = EventListenerKeyboard::create();
	mpListener->onKeyPressed = CC_CALLBACK_2(CGamePlay_Stage_1::onKeyPressed, this);
	mpListener->onKeyReleased = CC_CALLBACK_2(CGamePlay_Stage_1::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mpListener, this);
}
void CGamePlay_Stage_1::onExit()
{
	_eventDispatcher->removeEventListener(mpListener);

	Scene::onExit();
}
void CGamePlay_Stage_1::menuCloseCallback(Ref* pSender)
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
