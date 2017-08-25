#pragma once

#include "Actor.h"
#include "AnimationBox.h"
#include "GamePlay_Stage_1.h"
#include "CreateMap.h"
#include "GameDataS.h"


//애니메이션 관련
//시퀀스용 상태 애니메이션
void CActor::DoAni_Sqe_Hurt()
{
	mpActor_Hurt->RunAni_Repeat_One();
}
void CActor::DoAni_Sqe_Idle()
{
	AllHide();
	StopAllAni();

	mpEnemy_Idle->Show();

	mpEnemy_Idle->RunAni();
}
void CActor::DoAni_Sqe_Attack()
{
	mpActor_Attack->RunAni_Repeat_One();
}
//공격 시퀀스
void CActor::Sqe_Actor_Attack()
{
	auto tDelay = ScaleTo::create(0.57f, 1.0f);

	auto tisAnimating = Sequence::create(
		CallFunc::create(CC_CALLBACK_0(CActor::IsAnimating_true, this)),
		CallFunc::create(CC_CALLBACK_0(CActor::DoAni_Sqe_Attack, this)),
		tDelay,
		CallFunc::create(CC_CALLBACK_0(CActor::DoAni_Sqe_Idle, this)),
		CallFunc::create(CC_CALLBACK_0(CActor::IsAnimating_false, this)),
		NULL);

	auto tRepeat = Repeat::create(tisAnimating, 1);

	mpActor_Attack->RunAction(tRepeat);
}
//피격 시퀀스
void CActor::Sqe_Actor_Hurt()
{
	auto tDelay = ScaleTo::create(0.25f, 1.0f);

	auto tisAnimating = Sequence::create(
		CallFunc::create(CC_CALLBACK_0(CActor::IsAnimating_true, this)),
		CallFunc::create(CC_CALLBACK_0(CActor::DoAni_Sqe_Hurt, this)),
		tDelay,
		CallFunc::create(CC_CALLBACK_0(CActor::DoAni_Sqe_Idle, this)),
		CallFunc::create(CC_CALLBACK_0(CActor::IsAnimating_false, this)),
		NULL);

	auto tRepeat = Repeat::create(tisAnimating, 1);

	mpActor_Hurt->RunAction(tRepeat);
}
//애니메이션 실행중 관리
void CActor::IsAnimating_false()
{
	mIsAnimating = false;
}
void CActor::IsAnimating_true()
{
	mIsAnimating = true;
}
//상태별 애니메이션 실행
void CActor::DoAni_State(int tState)
{
	if (false == mIsAnimating)
	{
		//이전 상태 저장
		mActor_Prev_State = GetState();

		switch (tState)
		{
			//대기
			case ACTOR_STATE_IDLE:
			{
				SetState(ACTOR_STATE_IDLE);

				AllHide();
				StopAllAni();

				mpEnemy_Idle->Show();
				mpEnemy_Idle->RunAni();
			}
			break;
			//점프
			case ACTOR_STATE_JUMP:
			{
				AllHide();
				StopAllAni();

				mpActor_Jump->Show();
				mpActor_Jump->RunAni();
			}
			break;
			//걷기
			case ACTOR_STATE_WALK:
			{
				SetState(ACTOR_STATE_WALK);

				AllHide();
				StopAllAni();

				mpActor_Walk->Show();
				mpActor_Walk->RunAni();
			}
			break;
			//달리기
			case ACTOR_STATE_RUN:
			{
				SetState(ACTOR_STATE_RUN);

				AllHide();
				StopAllAni();

				mpActor_Run->Show();
				mpActor_Run->RunAni();
			}
			break;
			//공격
			case ACTOR_STATE_ATTACK:
			{
				AllHide();
				StopAllAni();

				mpActor_Attack->Show();

				Sqe_Actor_Attack();
				switch (mActor_Attack_State)
				{
					case ACTOR_ATTACK_SWORD:
					{
						SwordAttackSqe();
					}
					break;
					case ACTOR_ATTACK_BULLET:
					{
						FireBullet();
					}
				break;
				}
			}
			break;
			//피격
			case ACTOR_STATE_HURT:
			{
				SetState(ACTOR_STATE_HURT);

				AllHide();
				StopAllAni();
			
				mpActor_Hurt->Show();

				Sqe_Actor_Hurt();
			}
			break;
			//사망
			case ACTOR_STATE_DIE:
			{
				SetState(ACTOR_STATE_DIE);

				AllHide();
				StopAllAni();

				mpActor_Die->Show();
				mpActor_Die->RunAni_Repeat_One();
			}
			break;
			//스킬
			case ACTOR_STATE_SKILL:
			{
				FireSkill();
			}
			break;
		}
	}
}

//이전 애니메이션
void CActor::DoAni_Prev()
{
	if (false == mIsAnimating)
	{
		switch (mActor_Prev_State)
		{
			case ACTOR_STATE_IDLE:
			{
				SetState(ACTOR_STATE_IDLE);

				AllHide();
				StopAllAni();

				mpEnemy_Idle->Show();
				mpEnemy_Idle->RunAni();
			}
			break;
			case ACTOR_STATE_WALK:
			{
				SetState(ACTOR_STATE_WALK);

				AllHide();
				StopAllAni();

				mpActor_Walk->Show();
				mpActor_Walk->RunAni();
			}
			break;
			case ACTOR_STATE_RUN:
			{
				SetState(ACTOR_STATE_RUN);

				AllHide();
				StopAllAni();

				mpActor_Run->Show();
				mpActor_Run->RunAni();
			}
			break;
		}
	}
}
//상태 애니메이션 크리에잇트
void CActor::Create()
{
	//대기 상태 에니메이션
	mpEnemy_Idle = new AnimationBox();
	mpEnemy_Idle->Create("Project/Actor/Actor_Idle/IDLE_", 7, 0.05, 0.5, 0.0);
	//걷기 상태 에니메이션
	mpActor_Walk = new AnimationBox();
	mpActor_Walk->Create("Project/Actor/Actor_Walk/WALK_", 7, 0.05, 0.5, 0.0);
	//달리기 상태 에니메이션
	mpActor_Run = new AnimationBox();
	mpActor_Run->Create("Project/Actor/Actor_Run/RUN_", 7, 0.05, 0.5, 0.0);
	mpActor_Run->SetScale(1.025f);
	//점프 상태 에니메이션
	mpActor_Jump = new AnimationBox();
	mpActor_Jump->Create("Project/Actor/Actor_Jump/JUMP_", 7, 0.05, 0.5, 0.0);
	//공격 상태 에니메이션
	mpActor_Attack = new AnimationBox();
	mpActor_Attack->Create_Repeat_One("Project/Actor/Actor_Attack/ATTACK_", 7, 0.075, 0.5, 0.0);
	mpActor_Attack->SetScale(1.11f);
	//피격 상태 에니메이션
	mpActor_Hurt = new AnimationBox();
	mpActor_Hurt->Create_Repeat_One("Project/Actor/Actor_Hurt/HURT_", 7, 0.05, 0.5, 0.0);
	mpActor_Hurt->SetScale(1.125f);
	//죽음 에니메이션
	mpActor_Die = new AnimationBox();
	mpActor_Die->Create_Repeat_One("Project/Actor/Actor_Die/DIE_", 7, 0.05, 0.5, 0.0);
	mpActor_Die->SetScale(1.455f);
	//근접 공격 애니메이션
	mpActor_Attack_Sword = new AnimationBox();
	mpActor_Attack_Sword->Create_Repeat_One("Project/Actor/Actor_Attack_Sword/sword_", 3, 0.1, 0.5, 0.5);
	mpActor_Attack_Sword->SetScale(1.5f);
	mpActor_Attack_Sword->SetOpacity(180.0f);
	mpActor_Attack_Sword->StopAni();
	mpActor_Attack_Sword->Hide();
	//원거리 공격 애니메이션(총알)
	for (ti = 0; ti < 20; ti++)
	{
		mpActor_Attack_Bullet[ti] = new AnimationBox();
		mpActor_Attack_Bullet[ti]->Create("Project/Actor/Actor_Attack_Bullet/bullet_", 8, 0.05, 0.5, 0.5);
		mpActor_Attack_Bullet[ti]->StopAni();
		mpActor_Attack_Bullet[ti]->Hide();
		mpActor_Attack_Bullet[ti]->SetOpacity(240.0f);
	}
	//스킬 애니메이션
	mpActor_Skill_1 = new AnimationBox();
	mpActor_Skill_1->Create("Project/Actor/Skill/Bullet/bullet_", 8, 0.05, 0.5, 0.5);
	mpActor_Skill_1->StopAni();
	mpActor_Skill_1->Hide();
	mpActor_Skill_1->SetPosition(mVecActor);

	mpActor_Skill_2 = new AnimationBox();
	mpActor_Skill_2->Create("Project/Actor/Skill/BloodBullet/Bbullet_", 7, 0.05, 0.5, 0.5);
	mpActor_Skill_2->StopAni();
	mpActor_Skill_2->Hide();
	mpActor_Skill_2->SetPosition(mVecActor);

	mpActor_Skill_3 = new AnimationBox();
	mpActor_Skill_3->Create("Project/Actor/Skill/UnderFire/Meteor_", 12, 0.1, 1.0, 0.5);
	mpActor_Skill_3->StopAni();
	mpActor_Skill_3->Hide();
	mpActor_Skill_3->SetPosition(mVecActor);
}
void CActor::Destroy()
{
	mpEnemy_Idle->Destroy();
	mpActor_Walk->Destroy();
	mpActor_Run->Destroy();
	mpActor_Jump->Destroy();
	mpActor_Attack->Destroy();
	mpActor_Hurt->Destroy();
	mpActor_Die->Destroy();
	mpActor_Attack_Sword->Destroy();
	for (ti = 0; ti < 20; ti++)
	{
		mpActor_Attack_Bullet[ti]->Destroy();
	}
	mpActor_Skill_1->Destroy();
	mpActor_Skill_2->Destroy();
	mpActor_Skill_3->Destroy();
}

void CActor::Build(int Zorder)
{
	mpEnemy_Idle->Build(Zorder);
	mpActor_Walk->Build(Zorder);
	mpActor_Run->Build(Zorder);
	mpActor_Jump->Build(Zorder);
	mpActor_Attack->Build(Zorder);
	mpActor_Hurt->Build(Zorder);
	mpActor_Die->Build(Zorder);
	mpActor_Attack_Sword->Build(Zorder);
	for (ti = 0; ti < 20; ti++)
	{
		mpActor_Attack_Bullet[ti]->Build(Zorder);
	}
	mpActor_Skill_1->Build(Zorder);
	mpActor_Skill_2->Build(Zorder);
	mpActor_Skill_3->Build(Zorder);
}
void CActor::UnBuild()
{
	mpEnemy_Idle->UnBuild();
	mpActor_Walk->UnBuild();
	mpActor_Run->UnBuild();
	mpActor_Jump->UnBuild();
	mpActor_Attack->UnBuild();
	mpActor_Hurt->UnBuild();
	mpActor_Die->UnBuild();
	mpActor_Attack_Sword->UnBuild();
	for (ti = 0; ti < 20; ti++)
	{
		mpActor_Attack_Bullet[ti]->UnBuild();
	}
	mpActor_Skill_1->UnBuild();
	mpActor_Skill_2->UnBuild();
	mpActor_Skill_3->UnBuild();
}

void CActor::SetScene(CGamePlay_Stage_1 *tpScene)
{
	mpScene = tpScene;
}

void CActor::SetLayer(Layer *tpLayer)
{
	mpLayer = tpLayer;

	mpEnemy_Idle->SetScene(tpLayer);
	mpActor_Walk->SetScene(tpLayer);
	mpActor_Run->SetScene(tpLayer);
	mpActor_Jump->SetScene(tpLayer);
	mpActor_Attack->SetScene(tpLayer);
	mpActor_Hurt->SetScene(tpLayer);
	mpActor_Die->SetScene(tpLayer);
	mpActor_Attack_Sword->SetScene(tpLayer);
	for (ti = 0; ti < 20; ti++)
	{
		mpActor_Attack_Bullet[ti]->SetScene(tpLayer);
	}
	mpActor_Skill_1->SetScene(tpLayer);
	mpActor_Skill_2->SetScene(tpLayer);
	mpActor_Skill_3->SetScene(tpLayer);
}
//상태 겟셋
void CActor::SetState(int tState)
{
	mActor_State = tState;
}
int CActor::GetState()
{
	return mActor_State;
}
void CActor::Set_Attack_State(int tState)
{
	mActor_Attack_State = tState;
}
int CActor::Get_Attack_State()
{
	return mActor_Attack_State;
}

void CActor::SetPosition(Vec2 tVec)
{
	mpEnemy_Idle->SetPosition(tVec);
	mpActor_Walk->SetPosition(tVec);
	mpActor_Run->SetPosition(tVec);
	mpActor_Jump->SetPosition(tVec);
	mpActor_Attack->SetPosition(tVec);
	mpActor_Hurt->SetPosition(tVec);
	mpActor_Die->SetPosition(tVec);	
}
void CActor::SetPositionY(float tVec)
{
	mVecActor.y = tVec;

	SetPosition(mVecActor);
}
void CActor::SetPositionX(float tVec)
{
	mVecActor.x = tVec;

	SetPosition(mVecActor);
}
Vec2 CActor::GetPosition()
{
	return mVecActor;
}
void CActor::StopAllAni()
{
	mpEnemy_Idle->StopAni();
	mpActor_Walk->StopAni();
	mpActor_Run->StopAni();
	mpActor_Jump->StopAni();
	mpActor_Attack->StopAni_Repeat_One();
	mpActor_Hurt->StopAni_Repeat_One();
	mpActor_Die->StopAni_Repeat_One();
}
void CActor::AllHide()
{
	mpEnemy_Idle->Hide();
	mpActor_Walk->Hide();
	mpActor_Run->Hide();
	mpActor_Jump->Hide();
	mpActor_Attack->Hide();
	mpActor_Hurt->Hide();
	mpActor_Die->Hide();
}

void CActor::SetFlipX(bool tFlip)
{
	mpEnemy_Idle->SetFlipX(tFlip);
	mpActor_Walk->SetFlipX(tFlip);
	mpActor_Run->SetFlipX(tFlip);
	mpActor_Jump->SetFlipX(tFlip);
	mpActor_Attack->SetFlipX(tFlip);
	mpActor_Hurt->SetFlipX(tFlip);
	mpActor_Die->SetFlipX(tFlip);
}
//공격 관련

//근접 공격 Visible 판단
bool CActor::IsShowSwodAttack()
{
	return mpActor_Attack_Sword->IsShow();
}//근거리 공격 실행
void CActor::DoSwodAttack()
{
	if (MOVE_DIR_LEFT == mMoveDir)
	{
		mpActor_Attack_Sword->SetFlipX(true);
	}
	else
	{
		mpActor_Attack_Sword->SetFlipX(false);
	}

	mpActor_Attack_Sword->Show();

	mpActor_Attack_Sword->SetPosition(mAttackVec);

	mpActor_Attack_Sword->RunAni_Repeat_One();

}
//근거리 공격 셋포지션
void CActor::SetPositionSwordAttack()
{
	mAttackVec.x = mVecActor.x + mMoveDir * 30;
	mAttackVec.y = mVecActor.y + 35;
	mpActor_Attack_Sword->SetPosition(mAttackVec);
}
//근거리 공격 중지
void CActor::StopSwodAttack()
{
	mpActor_Attack_Sword->Hide();
}
//근접 공격 시퀀스
void CActor::SwordAttackSqe()
{
	auto tDelay = ScaleTo::create(0.3f, 1.0f);

	auto tSwordAttackSqe = Sequence::create(
		CallFunc::create(CC_CALLBACK_0(CActor::DoSwodAttack, this)),
		tDelay,
		CallFunc::create(CC_CALLBACK_0(CActor::StopSwodAttack, this)),
		NULL);

	auto tRepeat = Repeat::create(tSwordAttackSqe, 1);

	mpActor_Attack_Sword->RunAction(tRepeat);
}
//원거리 Visible 판단
bool CActor::IsShowBulletAttack(int tIndex)
{
	return mpActor_Attack_Bullet[tIndex]->IsShow();
}
//발사
void CActor::FireBullet()
{
	
	mBullet_Dir[mCurBulletIndex]= mMoveDir;

	if (mBullet_Dir[mCurBulletIndex] == MOVE_DIR_LEFT)
	{
		mpActor_Attack_Bullet[mCurBulletIndex]->SetFlipX(true);
	}
	else
	{
		mpActor_Attack_Bullet[mCurBulletIndex]->SetFlipX(false);
	}

	mpActor_Attack_Bullet[mCurBulletIndex]->Show();

	mpActor_Attack_Bullet[mCurBulletIndex]->RunAni();

	mBulletVec.x = mVecActor.x + mMoveDir * 30;
	mBulletVec.y = mVecActor.y + 25;
	mpActor_Attack_Bullet[mCurBulletIndex]->SetPosition(mBulletVec);

	if (mCurBulletIndex < 20 - 1)
	{
		mCurBulletIndex++;
	}
	else
	{
		mCurBulletIndex = 0;
	}
}
//총알 이동
void CActor::MoveBullet()
{
	for (ti = 0; ti < 20; ti++)
	{
		if (true == IsShowBulletAttack(ti))
		{
			Vec2 tVec = mpActor_Attack_Bullet[ti]->GetPosition();
			
			mMapWidthPixel = mTileW*mTotalColCount;
			mMapHeightPixel = mTileH * mTotalRowCount;

			int tCol = tVec.x / mTileW;
			int tRow = mTotalRowCount - tVec.y / mTileH;

			mAttribute = mpTileMap->GetAttributeWith(tRow, tCol);
						
			tVec.x = tVec.x + mBullet_Dir[ti] * 7;
			
			mpActor_Attack_Bullet[ti]->SetPosition(tVec);
		}
		if (1 == mAttribute)
		{
			mpActor_Attack_Bullet[ti]->StopAni();
			mpActor_Attack_Bullet[ti]->Hide();
		}
	}
}
//스킬 관련
//스킬 Visible 판단
//bool CActor::IsShowSkill()
//{
//	return mpActor_Skill_1->IsShow();
//}
//스킬 발사
void CActor::FireSkill()
{
	mSkillUseMP = CGameDataS::GetInstance()->GetActorCurMP();

	if (2 <= mSkillUseMP)
	{
		mSkill_Dir = mMoveDir;
		switch (mSkillUseMP)
		{
		case 2:
		{
			mpActor_Skill_1->Show();
			mpActor_Skill_1->RunAni();

			CGameDataS::GetInstance()->SetActorCurMP(
				CGameDataS::GetInstance()->GetActorCurMP() - 2);

			Vec2 tSkillVec;

			tSkillVec.x = mVecActor.x + mMoveDir * 5;
			tSkillVec.y = mVecActor.y + 50;
			mpActor_Skill_1->SetPosition(mSkillVec);
		}
		break;
		case 4:
		{
			mpActor_Skill_2->Show();
			mpActor_Skill_2->RunAni();

			CGameDataS::GetInstance()->SetActorCurMP(
				CGameDataS::GetInstance()->GetActorCurMP() - 4);

			Vec2 tSkillVec;

			tSkillVec.x = mVecActor.x + mMoveDir * 5;
			tSkillVec.y = mVecActor.y + 70;
			mpActor_Skill_2->SetPosition(mSkillVec);
		}
		break;
		case 6:
		{
			mpActor_Skill_3->Show();
			mpActor_Skill_3->RunAni();

			Vec2 tSkillVec;

			tSkillVec.x = mVecActor.x + mMoveDir * 5;
			tSkillVec.y = mVecActor.y + 50;
			mpActor_Skill_3->SetPosition(mSkillVec);

			CGameDataS::GetInstance()->SetActorCurMP(
				CGameDataS::GetInstance()->GetActorCurMP() - 6);
		}
		break;
		}
		/*
		if (2 == mSkillUseMP || 3 == mSkillUseMP)
		{
			mpActor_Skill_1->Show();
			mpActor_Skill_1->RunAni();

			CGameDataS::GetInstance()->SetActorCurMP(
				CGameDataS::GetInstance()->GetActorCurMP() - 2);

			Vec2 tSkillVec;

			tSkillVec.x = mVecActor.x + mMoveDir * 5;
			tSkillVec.y = mVecActor.y + 50;
			mpActor_Skill_1->SetPosition(mSkillVec);
		}
		else if (4 == mSkillUseMP || 5 == mSkillUseMP)
		{
			mpActor_Skill_2->Show();
			mpActor_Skill_2->RunAni();

			CGameDataS::GetInstance()->SetActorCurMP(
				CGameDataS::GetInstance()->GetActorCurMP() - 4);

			Vec2 tSkillVec;

			tSkillVec.x = mVecActor.x + mMoveDir * 5;
			tSkillVec.y = mVecActor.y + 70;
			mpActor_Skill_2->SetPosition(mSkillVec);
		}
		else if (6 == mSkillUseMP)
		{
			mpActor_Skill_3->Show();
			mpActor_Skill_3->RunAni();

			Vec2 tSkillVec;

			tSkillVec.x = mVecActor.x + mMoveDir * 5;
			tSkillVec.y = mVecActor.y + 50;
			mpActor_Skill_3->SetPosition(mSkillVec);

			CGameDataS::GetInstance()->SetActorCurMP(
				CGameDataS::GetInstance()->GetActorCurMP() - 6);
		}*/

		if (mSkill_Dir == MOVE_DIR_LEFT)
		{
			mpActor_Skill_1->SetAnchorPoint(Vec2(0.5f, 0.5f));
			mpActor_Skill_1->SetFlipX(true);

			mpActor_Skill_2->SetAnchorPoint(Vec2(0.0f, 0.5f));
			mpActor_Skill_2->SetFlipX(true);

			mpActor_Skill_3->SetAnchorPoint(Vec2(0.0f, 0.5f));
			mpActor_Skill_3->SetFlipX(true);
		}
		else
		{
			mpActor_Skill_1->SetAnchorPoint(Vec2(0.5f, 0.5f));
			mpActor_Skill_1->SetFlipX(false);

			mpActor_Skill_2->SetAnchorPoint(Vec2(1.0f, 0.5f));
			mpActor_Skill_2->SetFlipX(false);

			mpActor_Skill_3->SetAnchorPoint(Vec2(1.0f, 0.5f));
			mpActor_Skill_3->SetFlipX(false);
		}
		mSkill_State = SKILL_STATE_ALIVE;
	}
}
//스킬 이동
void CActor::MoveSkill(float dt)
{
	if (mSkill_State == SKILL_STATE_ALIVE)
	{
		switch (mSkillUseMP)
		{
			case 2:
			{
				this->MoveSkillAttribute(mpActor_Skill_1, 2.0f);
			}
			break;
			case 4:
			{
				this->MoveSkillAttribute(mpActor_Skill_2, 1.5f);
			}
			break;
			case 6:
			{
				this->MoveSkillAttribute(mpActor_Skill_3, 6.0f);
			}
			break;
		}
	}
}


void CActor::ActorAttackIsCollision()
{

}
//이동 관련
void CActor::MoveActor()
{
		
	if (true == mpScene->isLeftPressed || true == mpScene->isRightPressed)
	{
		if (mActor_State != ACTOR_STATE_HURT)
		{
			float tMoveActorX = mVecActor.x + mMoveDir * mMoveSpeed;

			//x축 Attribute 와 충돌 판정
			int tRow = mTotalRowCount - (mVecActor.y + 32) / mTileH;

			if (MOVE_DIR_LEFT == mMoveDir)
			{
				int tCol = (tMoveActorX - 16) / mTileW;
				mAttribute = mpTileMap->GetAttributeWith(tRow, tCol);

				if (1 == mAttribute)
				{
					tMoveActorX = this->GetPosition().x;
				}
			}
			if (MOVE_DIR_RIGHT == mMoveDir)
			{
				int tCol = (tMoveActorX + 17) / mTileW;
				mAttribute = mpTileMap->GetAttributeWith(tRow, tCol);

				if (1 == mAttribute)
				{
					tMoveActorX = this->GetPosition().x;
				}
			}
			this->SetPositionX(tMoveActorX);
		}
	}
}
void CActor::KeyInPutSetActorSpeed()
{
	//달리기 모드
	if (mpScene->isRunPressed == true)
	{	
		//왼쪽 이동
		if (mpScene->isLeftPressed == true)
		{
			mMoveDir = MOVE_DIR_LEFT;
			mMoveSpeed = 8;
		}
		//오른쪽 이동
		else if (mpScene->isRightPressed == true)
		{
			mMoveDir = MOVE_DIR_RIGHT;
			mMoveSpeed = 8;
		}
		//왼쪽 오른쪽 모두 안눌렀을때는 움직이지 X
		else
		{
			mMoveSpeed = 0;
		}
	}
	//걷기 모드
	else if(mpScene->isRunPressed == false)
	{
		//왼쪽 이동
		if (mpScene->isLeftPressed == true)
		{
			mMoveDir = MOVE_DIR_LEFT;
			mMoveSpeed = 4;
		}
		//오른쪽 이동
		else if (mpScene->isRightPressed == true)
		{
			mMoveDir = MOVE_DIR_RIGHT;
			mMoveSpeed = 4;
		}
		//왼쪽 오른쪽 모두 안눌렀을때는 움직이지 X
		else
		{
			mMoveSpeed = 0;
		}
	}
	//양쪽 모두 눌려졌을때 움직이지 X
	if (mpScene->isLeftPressed == true && mpScene->isRightPressed == true)
	{
		mMoveSpeed = 0;
	}
}
//점프 관련
void CActor::JumpStart()
{
	float tPower = 20.0f;

	if (mJumpCount <= 1)
	{
		if (tPower > 0)
		{
			mJumpPower = tPower;
			mJumpState = JUMP_STATE_UP;
			mJumpCount = mJumpCount + 1;
		}
		else if (tPower <= 0)
		{
			mJumpPower = tPower;
			mJumpState = JUMP_STATE_DOWN;
			mJumpCount = mJumpCount + 1;
		}
	}
}
void CActor::JumpGravity()
{
	float tGravity = 2.0f;

	if (mJumpPower < 0)
	{
		mJumpState = JUMP_STATE_DOWN;
	}

	if (mJumpState == JUMP_STATE_UP)
	{
		mJumpPower -= tGravity;

		this->SetPositionY(this->GetPosition().y + mJumpPower);
	}
	else if (mJumpState == JUMP_STATE_DOWN)
	{
		mJumpPower += tGravity;

		this->SetPositionY(this->GetPosition().y - mJumpPower);
	}
	//착지시 이전 애니메이션 실행
	else if (mJumpState == JUMP_STATE_LANDING)
	{
		DoAni_Prev();		

		mJumpState = JUMP_STATE_DEF;
	}
	else if (mJumpState == JUMP_STATE_DEF)
	{

		mJumpCount = 0;
		mJumpPower = 0;
	}
}
//맵
void CActor::SetTileMap(CTileMap *tpTileMap)
{
	mpTileMap = tpTileMap;
}
//바닥 충돌
bool CActor::IsCollision()
{
	mIsCollision = false;

	mTileW = mpTileMap->mpMap->getTileSize().width;
	mTileH = mpTileMap->mpMap->getTileSize().height;

	mTotalColCount = mpTileMap->mpMap->getMapSize().width;
	mTotalRowCount = mpTileMap->mpMap->getMapSize().height;


	mMapWidthPixel = mTileW*mTotalColCount;
	mMapHeightPixel = mTileH * mTotalRowCount;

	int tCol = mVecActor.x / mTileW;
	int tRow = mTotalRowCount - mVecActor.y / mTileH;

	mAttribute = mpTileMap->GetAttributeWith(tRow, tCol);

	if (mJumpState != JUMP_STATE_UP)
	{
		//y축 Attribute 와 충돌 판정
		if (1 == mAttribute)
		{
			mMapHeight = (mTotalRowCount - tRow)*mTileH;		
			
			this->SetPositionY(mMapHeight);
			
			if (mJumpState == JUMP_STATE_DOWN)
			{
				mJumpState = JUMP_STATE_LANDING;
			}

			mJumpCount = 0;
			mIsCollision = true;
		}
	}
	if (2 == mAttribute)
	{
		mMapHeight = (mTotalRowCount - tRow)*mTileH;		
		this->SetPositionY(mMapHeight);
		
		this->AllHide();
	}

	if (false == mIsCollision)
	{
		if (mJumpState != JUMP_STATE_UP)
		{
			mJumpState = JUMP_STATE_DOWN;
		}
	}

	return true;
}
//지형 충돌 X축
void CActor::MoveSkillAttribute(AnimationBox *tpAnimationBox,float tScale)
{
	mMapWidthPixel = mTileW*mTotalColCount;
	mMapHeightPixel = mTileH * mTotalRowCount;

	Vec2 tVec = tpAnimationBox->GetPosition();

	int tCol = tVec.x / mTileW;
	int tRow = mTotalRowCount - tVec.y / mTileH;

	auto tAttribute = mpTileMap->GetAttributeWith(tRow, tCol);

	tVec.x = tVec.x + mSkill_Dir * 7;

	tpAnimationBox->SetScale(tScale);
	tpAnimationBox->SetPosition(tVec);

	if (1 == tAttribute)
	{
		mSkill_State = SKILL_STATE_DEAD;

		tpAnimationBox->StopAni();
		tpAnimationBox->Hide();
		tpAnimationBox->SetScale(1.0f);
	}
}

Sprite *CActor::GetSprite()
{
	return mpEnemy_Idle->GetSprite();
}
