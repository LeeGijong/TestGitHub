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
	//�ִϸ��̼� ����

	//��� ���� ���ϸ��̼�
	AnimationBox *mpEnemy_Idle = NULL;
	//�ȱ� ���� ���ϸ��̼�
	AnimationBox *mpActor_Walk = NULL;
	//�޸��� ���� ���ϸ��̼�
	AnimationBox *mpActor_Run = NULL;
	//���� ���� ���ϸ��̼�
	AnimationBox *mpActor_Jump = NULL;
	//���� ���� ���ϸ��̼�
	AnimationBox *mpActor_Attack = NULL;
	//�ǰ� ���� ���ϸ��̼�
	AnimationBox *mpActor_Hurt = NULL;
	//���� ���ϸ��̼�
	AnimationBox *mpActor_Die = NULL;
	//��ų �߻� �ִϸ��̼�
	AnimationBox *mpActor_Skill_1 = NULL;
	AnimationBox *mpActor_Skill_2 = NULL;
	AnimationBox *mpActor_Skill_3 = NULL;
	//�������� ����Ʈ �ִϸ��̼�
	AnimationBox *mpActor_Attack_Sword = NULL;
	//���Ÿ� ���� �Ѿ� �ִϸ��̼�
	AnimationBox *mpActor_Attack_Bullet[20] = { NULL, };

	//���ΰ� ����
	int mActor_State = ACTOR_STATE_IDLE;
	int mActor_Prev_State = ACTOR_STATE_IDLE;

	//�ִϸ��̼��� ���������� �Ǵ�
	bool mIsAnimating = false;

	//���� ����
	float mJumpPower = 0.0f;
	int mJumpState = JUMP_STATE_DEF;
	int mJumpCount = 0;
	float mGravity = 0.0f;

	//�̵� ����
	float mFastRunSpeed = 15.0f;
	float mMoveSpeed = 0.0f;

	//�� ����
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
	
	//�浹 ����
	int mAttribute = 0;

	//Ű�����̺�Ʈ�� �����Ǿ� �ִ� ���
	CGamePlay_Stage_1 *mpScene = NULL;

	//���Ӽ��� ���� ��ü���� ���̴� ���̾�.
	Layer *mpLayer = NULL;

	//���� ����
	//��ų
	int mSkillUseMP = 0;
	float mSkillScale = 1.0f;
	Vec2 mSkillVec;
	int mSkill_Dir = SKILL_DIR_RIGHT;
	//���Ÿ� ���� ����
	int mBullet_Dir[20] = { BULLET_DIR_RIGHT, };
	int mCurBulletIndex = 0;
	Vec2 mBulletVec;
	//���� ���� 
	int mActor_Attack_State;
	


public:
	//���� ����
	int mMoveDir = MOVE_DIR_RIGHT;
	int mSkill_State = SKILL_STATE_DEAD;
	//���� ����
	void ActorAttackIsCollision();
	void SwordAttackSqe();
	bool IsShowSwodAttack();
	void DoSwodAttack();
	void StopSwodAttack();
	void SetPositionSwordAttack();
	//���Ÿ� ����
	bool IsShowBulletAttack(int tIndex);
	void MoveBullet();
	void FireBullet();
	//��ų ����
	bool IsShowSkill();
	void MoveSkill(float dt);
	void FireSkill();
	//�̵� 
	void MoveActor();
	void KeyInPutSetActorSpeed();	
	//���� 
	void JumpStart();
	void JumpGravity();
	//���ΰ� ������, ���� ������ġ
	Vec2 mVecActor;
	Vec2 mAttackVec;
	
	//�ִϸ��̼� 

	//�ִϸ��̼� ������ ����
	void IsAnimating_false();
	void IsAnimating_true();
	//�������� �ִϸ��̼�
	void DoAni_Sqe_Hurt();
	void DoAni_Sqe_Idle();
	void DoAni_Sqe_Attack();
	//���� �ִϸ��̼� ����
	void DoAni_Prev();
	//���º� �ִϸ��̼�
	void DoAni_State(int tState);
	//���� ������
	void Sqe_Actor_Attack();
	//�ǰ� ������
	void Sqe_Actor_Hurt();
	//����
	void Create();
	void Destroy();
	//����
	void Build(int Zorder);
	void UnBuild();
	//�� ����
	void SetScene(CGamePlay_Stage_1 *tpScene);
	//���̾� ����
	void SetLayer(Layer *tpLayer);
	//����
	void SetState(int tState);
	int GetState();
	void Set_Attack_State(int tState);
	int Get_Attack_State();
	//��ġ
	void SetPosition(Vec2 tVec);
	void SetPositionY(float tVec);
	void SetPositionX(float tVec);
	Vec2 GetPosition();
	//��ž �ִ�
	void StopAllAni();
	//�� ���̵�
	void AllHide();
	//�ø�
	void SetFlipX(bool tFlip);
	//�浹 ����
	bool IsCollision();
	void MoveSkillAttribute(AnimationBox *tpAnimationBox, float tScale);
	//Ÿ�ϸ� ����
	void SetTileMap(CTileMap *tpTileMap);		
	//��������Ʈ �޾ƿ���(�ȷο�)
	Sprite *GetSprite();	
};