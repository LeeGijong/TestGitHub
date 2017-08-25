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
	//�ִϸ��̼� ����
	AnimationBox *mpEnemy_Idle = NULL;
	//�ȱ� ���� ���ϸ��̼�
	AnimationBox *mpEnemy_Walk = NULL;
	//���� ���� ���ϸ��̼�
	AnimationBox *mpEnemy_Attack = NULL;
	//�ǰ� ���� ���ϸ��̼�
	AnimationBox *mpEnemy_Hurt = NULL;
	//���� ���ϸ��̼�
	AnimationBox *mpEnemy_Die = NULL;
	//�������� ����Ʈ �ִϸ��̼�
	AnimationBox *mpEnemy_Attack_Sword = NULL;
	//�� ����
	int mEnemy_State = ACTOR_STATE_IDLE;
	int mEnemy_Prev_State = ACTOR_STATE_IDLE;

	//�ִϸ��̼��� ���������� �Ǵ�
	bool mIsAnimating = false;

	//�̵� ����
	float mFastRunSpeed = 15.0f;
	float mMoveSpeed = 2.0f;
	int mMoveEnemyDir = MOVE_DIR_RIGHT;
	float mMoveEnemyX = 0.0f;

	float mClippingMoveX = 0.0f;

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
	int mEnemy_Land = ENEMY_STATE_UP;

	//Ű�����̺�Ʈ�� �����Ǿ� �ִ� ���
	CGamePlay_Stage_1 *mpScene = NULL;

	//���Ӽ��� ���� ��ü���� ���̴� ���̾�.
	Layer *mpLayer = NULL;

	//���� ����

public:
	//���� ����
	void EnemyAttackIsCollision();
	void SwordAttackSqe();
	bool IsShowSwodAttack();
	void DoSwodAttack();
	void StopSwodAttack();
	void SetPositionSwordAttack();
	//�̵� 
	void MoveEnemy();
	void ClippingEnemyMove();
	//���� 
	void Gravity();
	//���ΰ� ������, ���� ������ġ
	Vec2 mVecEnemy;
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
	void Sqe_Enemy_Attack();
	//�ǰ� ������
	void Sqe_Enemy_Hurt();
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
	//Ÿ�ϸ� ����
	void SetTileMap(CTileMap *tpTileMap);		
	void SetActor(CActor *tpActor);
};