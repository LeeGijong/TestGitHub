#pragma once

#include "cocos2d.h"

USING_NS_CC;

class CGuageBar
{
protected:

	//data
	float mCurHP = 0.0f;
	float mMaxHP = 0.0f;

	float mHPUIRatio = 0.0f;


	Node *mpScene = NULL;

	Node *mpBody = NULL;

	//ui
	Node *mpParentNode = NULL;

	Sprite *mpSprGuageBar = NULL;
	ProgressTimer *mpProgressTimer = NULL;

public:
	CGuageBar();
	~CGuageBar();

	void Clear();
	void Clean();

	void Create(std::string tString, float tCurHP, float tMaxHP);
	void Destroy();

	void Build(int Zorder);
	void UnBuild();

	void SetScene(Node *tpScene);

	void SetPosition(Vec2 tVec);

	void SetScaleX(float tScale);
	void SetScaleY(float tScale);
	

	void Show();
	void Hide();

	bool IsShow();

	void BuildGuageWithDamage(float tDamage);
	void BuildGuageRev(float tRev);
};