#pragma once
#include "GameDataS.h"

CGameDataS *CGameDataS::mpInstance = NULL;
CGameDataS::CGameDataS()
{

}
CGameDataS::~CGameDataS()
{

}
CGameDataS *CGameDataS::GetInstance()
{
	if (NULL == mpInstance)
	{
		mpInstance = new CGameDataS();
		return mpInstance;
	}
	return mpInstance;
}
void CGameDataS::SetActorData(float tMaxHP, float tMaxMP, float tMaxXP)
{
	mActorMaxHP = tMaxHP;
	mActorMaxMP = tMaxMP;
	mActorMaxXP = tMaxXP;
}
//주인공 최대 HP
void CGameDataS::SetActorMaxHP(float tMaxHP)
{
	mActorMaxHP = tMaxHP;
}
float CGameDataS::GetActorMaxHP()
{
	return mActorMaxHP;
}
//주인공 현재 HP
void CGameDataS::SetActorCurHP(float tCurHP)
{
	mActorCurHP = tCurHP;
}
float CGameDataS::GetActorCurHP()
{
	return mActorCurHP;
}
//주인공 현재 MP
void CGameDataS::SetActorCurMP(float tCurMP)
{
	mActorCurMP = tCurMP;
}
unsigned int CGameDataS::GetActorCurMP()
{
	return mActorCurMP;
}
unsigned int CGameDataS::GetActorMaxMP()
{
	return mActorMaxMP;
}
//주인공 최대 XP
void CGameDataS::SetActorMaxXP(float tMaxXP)
{
	mActorMaxXP = tMaxXP;
}
float CGameDataS::GetActorMaxXP()
{
	return mActorMaxXP;
}
//주인공 현재 XP
void CGameDataS::SetActorCurXP(float tCurXP)
{
	mActorCurXP = tCurXP;
}
float CGameDataS::GetActorCurXP()
{
	return mActorCurXP;
}
//주인공 데미지
void CGameDataS::SetActorDamages(float tDamages)
{
	mActorDamages = tDamages;
}
float CGameDataS::GetActorDamages()
{
	return mActorDamages;
}
//주인공 스킬 데미지
void CGameDataS::SetActorSkillDamages(float tSkillDamages)
{
	mActorSkillDamages = tSkillDamages;
}
float CGameDataS::GetActorSkillDamages()
{
	return mActorSkillDamages;
}
//돈
void CGameDataS::SetMoney(unsigned int tMoney)
{
	mMoney = tMoney;
}
unsigned int CGameDataS::GetMoney()
{
	return mMoney;
}
