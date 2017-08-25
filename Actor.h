#pragma once

#include "cocos2d.h"
#include "StateMachine.h"

USING_NS_CC;

using namespace std;

class AnimationBox;
class CTileMap;
class CGamePlay_Stage_1;

class CActor
{
protected:
	int ti = 0;
	//애니메이션 관련

	//대기 상태 에니메이션
	AnimationBox *mpEnemy_Idle = NULL;
	//걷기 상태 에니메이션
	AnimationBox *mpActor_Walk = NULL;
	//달리기 상태 에니메이션
	AnimationBox *mpActor_Run = NULL;
	//점프 상태 에니메이션
	AnimationBox *mpActor_Jump = NULL;
	//공격 상태 에니메이션
	AnimationBox *mpActor_Attack = NULL;
	//피격 상태 에니메이션
	AnimationBox *mpActor_Hurt = NULL;
	//죽음 에니메이션
	AnimationBox *mpActor_Die = NULL;
	//스킬 발사 애니메이션
	AnimationBox *mpActor_Skill_1 = NULL;
	AnimationBox *mpActor_Skill_2 = NULL;
	AnimationBox *mpActor_Skill_3 = NULL;
	//근접공격 이펙트 애니메이션
	AnimationBox *mpActor_Attack_Sword = NULL;
	//원거리 공격 총알 애니메이션
	AnimationBox *mpActor_Attack_Bullet[20] = { NULL, };

	//주인공 상태
	int mActor_State = ACTOR_STATE_IDLE;
	int mActor_Prev_State = ACTOR_STATE_IDLE;

	//애니메이션이 실행중인지 판단
	bool mIsAnimating = false;

	//점프 관련
	float mJumpPower = 0.0f;
	int mJumpState = JUMP_STATE_DEF;
	int mJumpCount = 0;
	float mGravity = 0.0f;

	//이동 관련
	float mFastRunSpeed = 15.0f;
	float mMoveSpeed = 0.0f;

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

	//키보드이벤트가 구현되어 있는 노드
	CGamePlay_Stage_1 *mpScene = NULL;

	//게임세계 내의 객체들을 붙이는 레이어.
	Layer *mpLayer = NULL;

	//공격 관련
	//스킬
	int mSkillUseMP = 0;
	float mSkillScale = 1.0f;
	Vec2 mSkillVec;
	int mSkill_Dir = SKILL_DIR_RIGHT;
	//원거리 공격 관련
	int mBullet_Dir[20] = { BULLET_DIR_RIGHT, };
	int mCurBulletIndex = 0;
	Vec2 mBulletVec;
	//공격 상태 
	int mActor_Attack_State;
	


public:
	//공격 관련
	int mMoveDir = MOVE_DIR_RIGHT;
	int mSkill_State = SKILL_STATE_DEAD;
	//근접 공격
	void ActorAttackIsCollision();
	void SwordAttackSqe();
	bool IsShowSwodAttack();
	void DoSwodAttack();
	void StopSwodAttack();
	void SetPositionSwordAttack();
	//원거리 공격
	bool IsShowBulletAttack(int tIndex);
	void MoveBullet();
	void FireBullet();
	//스킬 공격
	bool IsShowSkill();
	void MoveSkill(float dt);
	void FireSkill();
	//이동 
	void MoveActor();
	void KeyInPutSetActorSpeed();	
	//점프 
	void JumpStart();
	void JumpGravity();
	//주인공 포지션, 공격 실행위치
	Vec2 mVecActor;
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
	void Sqe_Actor_Attack();
	//피격 시퀀스
	void Sqe_Actor_Hurt();
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
	void Set_Attack_State(int tState);
	int Get_Attack_State();
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
	void MoveSkillAttribute(AnimationBox *tpAnimationBox, float tScale);
	//타일맵 셋팅
	void SetTileMap(CTileMap *tpTileMap);		
	//스프라이트 받아오기(팔로우)
	Sprite *GetSprite();	
};