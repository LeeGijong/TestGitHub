#pragma once

#include "cocos2d.h"
#include "StateMachine.h"

USING_NS_CC;

using namespace std;

class AnimationBox;
class CTileMap;
class CGamePlay_Stage_1;
class CActor;
class CEnemy
{
protected:

	CActor *mpActor = NULL;

	int ti = 0;
	//애니메이션 관련
	AnimationBox *mpEnemy_Idle = NULL;
	//걷기 상태 에니메이션
	AnimationBox *mpEnemy_Walk = NULL;
	//공격 상태 에니메이션
	AnimationBox *mpEnemy_Attack = NULL;
	//피격 상태 에니메이션
	AnimationBox *mpEnemy_Hurt = NULL;
	//죽음 에니메이션
	AnimationBox *mpEnemy_Die = NULL;
	//근접공격 이펙트 애니메이션
	AnimationBox *mpEnemy_Attack_Sword = NULL;
	//적 상태
	int mEnemy_State = ACTOR_STATE_IDLE;
	int mEnemy_Prev_State = ACTOR_STATE_IDLE;

	//애니메이션이 실행중인지 판단
	bool mIsAnimating = false;

	//이동 관련
	float mFastRunSpeed = 15.0f;
	float mMoveSpeed = 2.0f;
	int mMoveEnemyDir = MOVE_DIR_RIGHT;
	float mMoveEnemyX = 0.0f;

	float mClippingMoveX = 0.0f;

	//맵 관련
	CTileMap *mpTileMap = NULL;
	bool mIsCollision = false;

	float mTileW = 0.0f;
	float mTileH = 0.0f;

	float mTotalColCount = 0.0f;
	float mTotalRowCount = 0.0f;

	float mMapWidthPixel = 0.0f;
	float mMapHeightPixel = 0.0f;

	float mMapHeight = 0.0f;
	float mMapWidth = 0.0f;
	
	//충돌 관련
	int mAttribute = 0;
	int mEnemy_Land = ENEMY_STATE_UP;

	//키보드이벤트가 구현되어 있는 노드
	CGamePlay_Stage_1 *mpScene = NULL;

	//게임세계 내의 객체들을 붙이는 레이어.
	Layer *mpLayer = NULL;

	//공격 관련

public:
	//공격 관련
	void EnemyAttackIsCollision();
	void SwordAttackSqe();
	bool IsShowSwodAttack();
	void DoSwodAttack();
	void StopSwodAttack();
	void SetPositionSwordAttack();
	//이동 
	void MoveEnemy();
	void ClippingEnemyMove();
	//점프 
	void Gravity();
	//주인공 포지션, 공격 실행위치
	Vec2 mVecEnemy;
	Vec2 mAttackVec;
	
	//애니메이션 

	//애니메이션 실행중 관리
	void IsAnimating_false();
	void IsAnimating_true();
	//시퀀스용 애니메이션
	void DoAni_Sqe_Hurt();
	void DoAni_Sqe_Idle();
	void DoAni_Sqe_Attack();
	//이전 애니메이션 실행
	void DoAni_Prev();
	//상태별 애니메이션
	void DoAni_State(int tState);
	//공격 시퀀스
	void Sqe_Enemy_Attack();
	//피격 시퀀스
	void Sqe_Enemy_Hurt();
	//생성
	void Create();
	void Destroy();
	//빌드
	void Build(int Zorder);
	void UnBuild();
	//씬 지정
	void SetScene(CGamePlay_Stage_1 *tpScene);
	//레이어 지정
	void SetLayer(Layer *tpLayer);
	//상태
	void SetState(int tState);
	int GetState();
	//위치
	void SetPosition(Vec2 tVec);
	void SetPositionY(float tVec);
	void SetPositionX(float tVec);
	Vec2 GetPosition();
	//스탑 애니
	void StopAllAni();
	//쇼 하이드
	void AllHide();
	//플립
	void SetFlipX(bool tFlip);
	//충돌 관련
	bool IsCollision();
	//타일맵 셋팅
	void SetTileMap(CTileMap *tpTileMap);		
	void SetActor(CActor *tpActor);
};