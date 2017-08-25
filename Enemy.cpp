#pragma once

#include "Enemy.h"
#include "Actor.h"
#include "AnimationBox.h"
#include "GamePlay_Stage_1.h"
#include "CreateMap.h"
#include "GameDataS.h"


//�ִϸ��̼� ����
//�������� ���� �ִϸ��̼�
void CEnemy::DoAni_Sqe_Hurt()
{
	mpEnemy_Hurt->RunAni_Repeat_One();
}
void CEnemy::DoAni_Sqe_Idle()
{
	AllHide();
	StopAllAni();

	mpEnemy_Idle->Show();

	mpEnemy_Idle->RunAni();
}
void CEnemy::DoAni_Sqe_Attack()
{
	mpEnemy_Attack->RunAni_Repeat_One();
}
//���� ������
void CEnemy::Sqe_Enemy_Attack()
{
	auto tDelay = ScaleTo::create(0.57f, 1.0f);

	auto tisAnimating = Sequence::create(
		CallFunc::create(CC_CALLBACK_0(CEnemy::IsAnimating_true, this)),
		CallFunc::create(CC_CALLBACK_0(CEnemy::DoAni_Sqe_Attack, this)),
		tDelay,
		CallFunc::create(CC_CALLBACK_0(CEnemy::DoAni_Sqe_Idle, this)),
		CallFunc::create(CC_CALLBACK_0(CEnemy::IsAnimating_false, this)),
		NULL);

	auto tRepeat = Repeat::create(tisAnimating, 1);

	mpEnemy_Attack->RunAction(tRepeat);
}
//�ǰ� ������
void CEnemy::Sqe_Enemy_Hurt()
{
	auto tDelay = ScaleTo::create(0.25f, 1.0f);

	auto tisAnimating = Sequence::create(
		CallFunc::create(CC_CALLBACK_0(CEnemy::IsAnimating_true, this)),
		CallFunc::create(CC_CALLBACK_0(CEnemy::DoAni_Sqe_Hurt, this)),
		tDelay,
		CallFunc::create(CC_CALLBACK_0(CEnemy::DoAni_Sqe_Idle, this)),
		CallFunc::create(CC_CALLBACK_0(CEnemy::IsAnimating_false, this)),
		NULL);

	auto tRepeat = Repeat::create(tisAnimating, 1);

	mpEnemy_Hurt->RunAction(tRepeat);
}
//�ִϸ��̼� ������ ����
void CEnemy::IsAnimating_false()
{
	mIsAnimating = false;
}
void CEnemy::IsAnimating_true()
{
	mIsAnimating = true;
}
//���º� �ִϸ��̼� ����
void CEnemy::DoAni_State(int tState)
{
	if (false == mIsAnimating)
	{
		//���� ���� ����
		//mEnemy_Prev_State = GetState();

		switch (tState)
		{
			//���
			case ENEMY_STATE_IDLE:
			{
				SetState(ENEMY_STATE_IDLE);

				AllHide();
				StopAllAni();

				mpEnemy_Idle ->Show();
				mpEnemy_Idle ->RunAni();
			}
			break;
			//�ȱ�
			case ENEMY_STATE_WALK:
			{
				SetState(ENEMY_STATE_WALK);

				AllHide();
				StopAllAni();

				mpEnemy_Walk->Show();
				mpEnemy_Walk->RunAni();
			}
			break;
			//����
			case ENEMY_STATE_ATTACK:
			{
				SetState(ENEMY_STATE_ATTACK);
				AllHide();
				StopAllAni();

				mpEnemy_Attack->Show();

				Sqe_Enemy_Attack();
				SwordAttackSqe();
			}
			break;
			//�ǰ�
			case ENEMY_STATE_HURT:
			{
				SetState(ENEMY_STATE_HURT);

				AllHide();
				StopAllAni();
			
				mpEnemy_Hurt->Show();

				Sqe_Enemy_Hurt();
			}
			break;
			//���
			case ENEMY_STATE_DIE:
			{
				SetState(ENEMY_STATE_DIE);

				AllHide();
				StopAllAni();

				mpEnemy_Die->Show();
				mpEnemy_Die->RunAni_Repeat_One();
			}
			break;
		}
	}
}

//���� �ִϸ��̼�
void CEnemy::DoAni_Prev()
{
	if (false == mIsAnimating)
	{
		switch (mEnemy_Prev_State)
		{
			case ENEMY_STATE_IDLE:
			{
				SetState(ENEMY_STATE_IDLE);

				AllHide();
				StopAllAni();

				mpEnemy_Idle ->Show();
				mpEnemy_Idle ->RunAni();
			}
			break;
			case ENEMY_STATE_WALK:
			{
				SetState(ENEMY_STATE_WALK);

				AllHide();
				StopAllAni();

				mpEnemy_Walk->Show();
				mpEnemy_Walk->RunAni();
			}
			break;
		}
	}
}
//���� �ִϸ��̼� ũ������Ʈ
void CEnemy::Create()
{
	mpActor = new CActor();

	//��� ���� ���ϸ��̼�
	mpEnemy_Idle  = new AnimationBox();
	mpEnemy_Idle ->Create("Project/Enemy/Enemy_Idle/IDLE_", 7, 0.05, 0.5, 0.0);
	//�ȱ� ���� ���ϸ��̼�
	mpEnemy_Walk = new AnimationBox();
	mpEnemy_Walk->Create("Project/Enemy/Enemy_Walk/WALK_", 7, 0.05, 0.5, 0.0);
	//���� ���� ���ϸ��̼�
	mpEnemy_Attack = new AnimationBox();
	mpEnemy_Attack->Create_Repeat_One("Project/Enemy/Enemy_Attack/ATTACK_", 8, 0.075, 0.5, 0.0);
	mpEnemy_Attack->SetScale(1.11f);
	//�ǰ� ���� ���ϸ��̼�
	mpEnemy_Hurt = new AnimationBox();
	mpEnemy_Hurt->Create_Repeat_One("Project/Enemy/Enemy_Hurt/HURT_", 7, 0.05, 0.5, 0.0);
	mpEnemy_Hurt->SetScale(1.125f);
	//���� ���ϸ��̼�
	mpEnemy_Die = new AnimationBox();
	mpEnemy_Die->Create_Repeat_One("Project/Enemy/Enemy_Die/DIE_", 7, 0.05, 0.5, 0.0);
	mpEnemy_Die->SetScale(1.455f);
	//���� ���� �ִϸ��̼�
	mpEnemy_Attack_Sword = new AnimationBox();
	mpEnemy_Attack_Sword->Create_Repeat_One("Project/Enemy/Attack/Enemy_Effect_", 3, 0.1, 0.0, 0.5);
	mpEnemy_Attack_Sword->SetScale(1.5f);
	mpEnemy_Attack_Sword->SetOpacity(180.0f);
	mpEnemy_Attack_Sword->StopAni();
	mpEnemy_Attack_Sword->Hide();
}
void CEnemy::Destroy()
{
	mpEnemy_Attack_Sword->Destroy();
	mpEnemy_Die->Destroy();
	mpEnemy_Hurt->Destroy();
	mpEnemy_Attack->Destroy();
	mpEnemy_Walk->Destroy();
	mpEnemy_Idle ->Destroy();
}
void CEnemy::Build(int Zorder)
{
	mpEnemy_Idle ->Build(Zorder);
	mpEnemy_Walk->Build(Zorder);
	mpEnemy_Attack->Build(Zorder);
	mpEnemy_Hurt->Build(Zorder);
	mpEnemy_Die->Build(Zorder);
	mpEnemy_Attack_Sword->Build(Zorder);
}
void CEnemy::UnBuild()
{
	mpEnemy_Attack_Sword->UnBuild();
	mpEnemy_Die->UnBuild();
	mpEnemy_Hurt->UnBuild();
	mpEnemy_Attack->UnBuild();
	mpEnemy_Walk->UnBuild();
	mpEnemy_Idle ->UnBuild();
}

void CEnemy::SetScene(CGamePlay_Stage_1 *tpScene)
{
	mpScene = tpScene;
}

void CEnemy::SetLayer(Layer *tpLayer)
{
	mpLayer = tpLayer;

	mpEnemy_Idle ->SetScene(tpLayer);
	mpEnemy_Walk->SetScene(tpLayer);
	mpEnemy_Attack->SetScene(tpLayer);
	mpEnemy_Hurt->SetScene(tpLayer);
	mpEnemy_Die->SetScene(tpLayer);
	mpEnemy_Attack_Sword->SetScene(tpLayer);
}
//���� �ټ�
void CEnemy::SetState(int tState)
{
	mEnemy_State = tState;
}
int CEnemy::GetState()
{
	return mEnemy_State;
}
void CEnemy::SetPosition(Vec2 tVec)
{
	mpEnemy_Idle ->SetPosition(tVec);
	mpEnemy_Walk->SetPosition(tVec);
	mpEnemy_Attack->SetPosition(tVec);
	mpEnemy_Hurt->SetPosition(tVec);
	mpEnemy_Die->SetPosition(tVec);	
}
void CEnemy::SetPositionY(float tVec)
{
	mVecEnemy.y = tVec;

	SetPosition(mVecEnemy);
}
void CEnemy::SetPositionX(float tVec)
{
	mVecEnemy.x = tVec;

	SetPosition(mVecEnemy);
}
Vec2 CEnemy::GetPosition()
{
	return mVecEnemy;
}
void CEnemy::StopAllAni()
{
	mpEnemy_Idle ->StopAni();
	mpEnemy_Walk->StopAni();
	mpEnemy_Attack->StopAni_Repeat_One();
	mpEnemy_Hurt->StopAni_Repeat_One();
	mpEnemy_Die->StopAni_Repeat_One();
}
void CEnemy::AllHide()
{
	mpEnemy_Idle ->Hide();
	mpEnemy_Walk->Hide();
	mpEnemy_Attack->Hide();
	mpEnemy_Hurt->Hide();
	mpEnemy_Die->Hide();
}

void CEnemy::SetFlipX(bool tFlip)
{
	mpEnemy_Idle ->SetFlipX(tFlip);
	mpEnemy_Walk->SetFlipX(tFlip);
	mpEnemy_Attack->SetFlipX(tFlip);
	mpEnemy_Hurt->SetFlipX(tFlip);
	mpEnemy_Die->SetFlipX(tFlip);
}
//���� ���� Visible �Ǵ�
bool CEnemy::IsShowSwodAttack()
{
	return mpEnemy_Attack_Sword->IsShow();
}
//�ٰŸ� ���� ����
void CEnemy::DoSwodAttack()
{
	if (MOVE_DIR_LEFT == mMoveEnemyDir)
	{
		mpEnemy_Attack_Sword->SetAnchorPoint(Vec2(1.0f,0.5f));
		mpEnemy_Attack_Sword->SetFlipX(false);
	}
	else
	{
		mpEnemy_Attack_Sword->SetAnchorPoint(Vec2(0.0f,0.5f));
		mpEnemy_Attack_Sword->SetFlipX(true);
	}

	mpEnemy_Attack_Sword->Show();

	mpEnemy_Attack_Sword->SetPosition(mAttackVec);

	mpEnemy_Attack_Sword->RunAni_Repeat_One();

}
//�ٰŸ� ���� ��������
void CEnemy::SetPositionSwordAttack()
{
	mAttackVec.x = mVecEnemy.x + mMoveEnemyDir * 7.5;
	mAttackVec.y = mVecEnemy.y + 30;
	mpEnemy_Attack_Sword->SetPosition(mAttackVec);
}
//�ٰŸ� ���� ����
void CEnemy::StopSwodAttack()
{
	mpEnemy_Attack_Sword->Hide();
}
//���� ���� ������
void CEnemy::SwordAttackSqe()
{
	auto tDelay = ScaleTo::create(0.3f, 1.0f);

	auto tSwordAttackSqe = Sequence::create(
		CallFunc::create(CC_CALLBACK_0(CEnemy::DoSwodAttack, this)),
		tDelay,
		CallFunc::create(CC_CALLBACK_0(CEnemy::StopSwodAttack, this)),
		NULL);

	auto tRepeat = Repeat::create(tSwordAttackSqe, 1);

	mpEnemy_Attack_Sword->RunAction(tRepeat);
}
void CEnemy::EnemyAttackIsCollision()
{

}
//�̵� ����
void CEnemy::MoveEnemy()
{
	if (mEnemy_State != ENEMY_STATE_HURT && mEnemy_Land == ENEMY_STATE_LAND)
	{
		mMoveEnemyX = mVecEnemy.x + mMoveEnemyDir * mMoveSpeed;
		
		float tDistanceA = mpActor->mVecActor.x - mVecEnemy.x;

		float tDistanceB = abs(tDistanceA);					

		ClippingEnemyMove();

		if (mEnemy_State != ENEMY_STATE_ATTACK)
		{
			this->SetPositionX(mMoveEnemyX);
		}
		if (tDistanceB < 80 && tDistanceA > 0 && mMoveEnemyDir > 0)
		{
			DoAni_State(ENEMY_STATE_ATTACK);
		}

		else if (tDistanceB < 80 && tDistanceA < 0 && mMoveEnemyDir < 0)
		{
			DoAni_State(ENEMY_STATE_ATTACK);
		}

		if (tDistanceB > 80 && tDistanceA > 0 && mMoveEnemyDir > 0)
		{
			DoAni_State(ENEMY_STATE_WALK);
		}
		else if (tDistanceB > 80 && tDistanceA < 0 && mMoveEnemyDir < 0)
		{
			DoAni_State(ENEMY_STATE_WALK);
		}
	}
}
//�¿� Ŭ����
void CEnemy::ClippingEnemyMove()
{
	//���ʹ� x�� + Ȱ�� ���� == Ŭ���� ���� Ŭ���� ����
	int tRow = mTotalRowCount - (mVecEnemy.y + 32) / mTileH;

	if (MOVE_DIR_LEFT == mMoveEnemyDir)
	{
		int tCol = (mMoveEnemyX - 16) / mTileW;
		mAttribute = mpTileMap->GetAttributeWith(tRow, tCol);

		if (mMoveEnemyX <= 500)
		{
			this->SetFlipX(false);
			mMoveEnemyDir = MOVE_DIR_RIGHT;
		}

		if (1 == mAttribute)
		{
			this->SetFlipX(false);
			mMoveEnemyDir = MOVE_DIR_RIGHT;
		}
	}
	if (MOVE_DIR_RIGHT == mMoveEnemyDir)
	{
		int tCol = (mMoveEnemyX + 17) / mTileW;
		mAttribute = mpTileMap->GetAttributeWith(tRow, tCol);

		if (mMoveEnemyX >= 1000)
		{
			this->SetFlipX(true);
			mMoveEnemyDir = MOVE_DIR_LEFT;
		}

		if (1 == mAttribute)
		{
			this->SetFlipX(true);
			mMoveEnemyDir = MOVE_DIR_LEFT;
		}
	}
}
//��
void CEnemy::SetTileMap(CTileMap *tpTileMap)
{
	mpTileMap = tpTileMap;
}
void CEnemy::SetActor(CActor *tpActor)
{
	mpActor = tpActor;
}
//�ٴ� �浹
bool CEnemy::IsCollision()
{
	mIsCollision = false;

	mTileW = mpTileMap->mpMap->getTileSize().width;
	mTileH = mpTileMap->mpMap->getTileSize().height;

	mTotalColCount = mpTileMap->mpMap->getMapSize().width;
	mTotalRowCount = mpTileMap->mpMap->getMapSize().height;


	mMapWidthPixel = mTileW*mTotalColCount;
	mMapHeightPixel = mTileH * mTotalRowCount;

	int tCol = mVecEnemy.x / mTileW;
	int tRow = mTotalRowCount - mVecEnemy.y / mTileH;

	mAttribute = mpTileMap->GetAttributeWith(tRow, tCol);
	
	//y�� Attribute �� �浹 ����
	if (1 == mAttribute)
	{
		mMapHeight = (mTotalRowCount - tRow)*mTileH;		
		
		mEnemy_Land = ENEMY_STATE_LAND;

		this->SetPositionY(mMapHeight);
	
		mIsCollision = true;
	}
	if (2 == mAttribute)
	{
		mMapHeight = (mTotalRowCount - tRow)*mTileH;		
		this->SetPositionY(mMapHeight);
	
		this->AllHide();
	}
	return true;
}
//�߷�
void CEnemy::Gravity()
{
	float tGravity = 4.0f;

	float tGravityPower = 0.0f;

	tGravityPower -= tGravity;

	this->SetPositionY(this->GetPosition().y + tGravityPower);
}