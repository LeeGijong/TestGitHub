#pragma once

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;
using namespace std;

class CGameDataS 
{
	static CGameDataS *mpInstance;

private:

	CGameDataS();
	~CGameDataS();
	//주인공 HP
	float mActorMaxHP = 10;
	float mActorCurHP = 10;
	//주인공 MP
	unsigned int mActorMaxMP = 6;
	unsigned int mActorCurMP = 0;
	//주인공 XP
	float mActorMaxXP = 10;
	float mActorCurXP = 0;

	unsigned int mMoney = 0;

	float mActorDamages = 5;
	float mActorSkillDamages = 0;

public:
	static CGameDataS *GetInstance();

	void SetActorMaxHP(float tMaxHP);
	float GetActorMaxHP();

	void SetActorCurHP(float tCurHP);
	float GetActorCurHP();
	
	void SetActorCurMP(float tCurMP);
	unsigned int GetActorCurMP();

	unsigned int GetActorMaxMP();

	void SetActorCurXP(float tCurXP);
	float GetActorCurXP();

	void SetActorMaxXP(float tMaxXP);
	float GetActorMaxXP();

	void SetActorDamages(float tDamages);
	float GetActorDamages();

	void SetActorSkillDamages(float tSkillDamages);
	float GetActorSkillDamages();

	void SetMoney(unsigned int tMoney);
	unsigned int GetMoney();

	void SetActorData(float tMaxHP, float tMaxMP, float tMaxXP);


};