#pragma once

#include "Enemy.h"
#include "Actor.h"
#include "AnimationBox.h"
#include "GamePlay_Stage_1.h"
#include "CreateMap.h"
#include "GameDataS.h"


//애니메이션 관련
//시퀀스용 상태 애니메이션
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
//공격 시퀀스
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
//피격 시퀀스
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
//애니메이션 실행중 관리
void CEnemy::IsAnimating_false()
{
	mIsAnimating = false;
}
void CEnemy::IsAnimating_true()
{
	mIsAnimating = true;
}
//상태별 애니메이션 실행
void CEnemy::DoAni_State(int tState)
{
	if (false == mIsAnimating)
	{
		//이전 상태 저장
		//mEnemy_Prev_State = GetState();

		switch (tState)
		{
			//대기
			case ENEMY_STATE_IDLE:
			{
				SetState(ENEMY_STATE_IDLE);

				AllHide();
				StopAllAni();

				mpEnemy_Idle ->Show();
				mpEnemy_Idle ->RunAni();
			}
			break;
			//걷기
			case ENEMY_STATE_WALK:
			{
				SetState(ENEMY_STATE_WALK);

				AllHide();
				StopAllAni();

				mpEnemy_Walk->Show();
				mpEnemy_Walk->RunAni();
			}
			break;
			//공격
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
			//피격
			case ENEMY_STATE_HURT:
			{
				SetState(ENEMY_STATE_HURT);

				AllHide();
				StopAllAni();
			
				mpEnemy_Hurt->Show();

				Sqe_Enemy_Hurt();
			}
			break;
			//사망
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

//이전 애니메이션
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
//상태 애니메이션 크리에잇트
void CEnemy::Create()
{
	mpActor = new CActor();

	//대기 상태 에니메이션
	mpEnemy_Idle  = new AnimationBox();
	mpEnemy_Idle ->Create("Project/Enemy/Enemy_Idle/IDLE_", 7, 0.05, 0.5, 0.0);
	//걷기 상태 에니메이션
	mpEnemy_Walk = new AnimationBox();
	mpEnemy_Walk->Create("Project/Enemy/Enemy_Walk/WALK_", 7, 0.05, 0.5, 0.0);
	//공격 상태 에니메이션
	mpEnemy_Attack = new AnimationBox();
	mpEnemy_Attack->Create_Repeat_One("Project/Enemy/Enemy_Attack/ATTACK_", 8, 0.075, 0.5, 0.0);
	mpEnemy_Attack->SetScale(1.11f);
	//피격 상태 에니메이션
	mpEnemy_Hurt = new AnimationBox();
	mpEnemy_Hurt->Create_Repeat_One("Project/Enemy/Enemy_Hurt/HURT_", 7, 0.05, 0.5, 0.0);
	mpEnemy_Hurt->SetScale(1.125f);
	//죽음 에니메이션
	mpEnemy_Die = new AnimationBox();
	mpEnemy_Die->Create_Repeat_One("Project/Enemy/Enemy_Die/DIE_", 7, 0.05, 0.5, 0.0);
	mpEnemy_Die->SetScale(1.455f);
	//근접 공격 애니메이션
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
//상태 겟셋
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
//근접 공격 Visible 판단
bool CEnemy::IsShowSwodAttack()
{
	return mpEnemy_Attack_Sword->IsShow();
}
//근거리 공격 실행
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
//근거리 공격 셋포지션
void CEnemy::SetPositionSwordAttack()
{
	mAttackVec.x = mVecEnemy.x + mMoveEnemyDir * 7.5;
	mAttackVec.y = mVecEnemy.y + 30;
	mpEnemy_Attack_Sword->SetPosition(mAttackVec);
}
//근거리 공격 중지
void CEnemy::StopSwodAttack()
{
	mpEnemy_Attack_Sword->Hide();
}
//근접 공격 시퀀스
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
//이동 관련
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
//좌우 클리핑
void CEnemy::ClippingEnemyMove()
{
	//에너미 x값 + 활동 범위 == 클리핑 랜덤 클리핑 ㅇㅇ
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
//맵
void CEnemy::SetTileMap(CTileMap *tpTileMap)
{
	mpTileMap = tpTileMap;
}
void CEnemy::SetActor(CActor *tpActor)
{
	mpActor = tpActor;
}
//바닥 충돌
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
	
	//y축 Attribute 와 충돌 판정
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
//중력
void CEnemy::Gravity()
{
	float tGravity = 4.0f;

	float tGravityPower = 0.0f;

	tGravityPower -= tGravity;

	this->SetPositionY(this->GetPosition().y + tGravityPower);
}