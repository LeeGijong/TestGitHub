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
//���ΰ� �ִ� HP
void CGameDataS::SetActorMaxHP(float tMaxHP)
{
	mActorMaxHP = tMaxHP;
}
float CGameDataS::GetActorMaxHP()
{
	return mActorMaxHP;
}
//���ΰ� ���� HP
void CGameDataS::SetActorCurHP(float tCurHP)
{
	mActorCurHP = tCurHP;
}
float CGameDataS::GetActorCurHP()
{
	return mActorCurHP;
}
//���ΰ� ���� MP
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
//���ΰ� �ִ� XP
void CGameDataS::SetActorMaxXP(float tMaxXP)
{
	mActorMaxXP = tMaxXP;
}
float CGameDataS::GetActorMaxXP()
{
	return mActorMaxXP;
}
//���ΰ� ���� XP
void CGameDataS::SetActorCurXP(float tCurXP)
{
	mActorCurXP = tCurXP;
}
float CGameDataS::GetActorCurXP()
{
	return mActorCurXP;
}
//���ΰ� ������
void CGameDataS::SetActorDamages(float tDamages)
{
	mActorDamages = tDamages;
}
float CGameDataS::GetActorDamages()
{
	return mActorDamages;
}
//���ΰ� ��ų ������
void CGameDataS::SetActorSkillDamages(float tSkillDamages)
{
	mActorSkillDamages = tSkillDamages;
}
float CGameDataS::GetActorSkillDamages()
{
	return mActorSkillDamages;
}
//��
void CGameDataS::SetMoney(unsigned int tMoney)
{
	mMoney = tMoney;
}
unsigned int CGameDataS::GetMoney()
{
	return mMoney;
}
