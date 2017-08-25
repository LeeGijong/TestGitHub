#pragma once
#include "GuageBar.h"
#include "GameDataS.h"

CGuageBar::CGuageBar()
{
	Clear();
}
CGuageBar::~CGuageBar()
{
	Destroy();
}
void CGuageBar::Clear()
{
	float mCurHP = 0.0f;
	float mMaxHP = 0.0f;

	float mHPUIRatio = 0.0f;

	Node *mpParentNode = NULL;

	Sprite *mpSprGuageBar = NULL;
	ProgressTimer *mpProgressTimer = NULL;
}
void CGuageBar::Clean()
{

}
void CGuageBar::Create(std::string tString, float tCurHP, float tMaxHP)
{
	mpParentNode = Node::create();
	//data
	mCurHP = tCurHP;
	mMaxHP = tMaxHP;

	//ui
	mpSprGuageBar = Sprite::create(tString + ".png");
	mpSprGuageBar->retain();

	mpProgressTimer = ProgressTimer::create(mpSprGuageBar);
	mpProgressTimer->retain();

	mpProgressTimer->setAnchorPoint(Vec2(0, 0));

	mpProgressTimer->setType(ProgressTimer::Type::BAR);
	mpProgressTimer->setMidpoint(Vec2(0, 0));
	mpProgressTimer->setBarChangeRate(Vec2(1, 0));

	mpProgressTimer->setReverseDirection(false);

	mpProgressTimer->setPercentage(100.0f);
}
void CGuageBar::Destroy()
{
	if (NULL != mpProgressTimer)
	{
		mpProgressTimer->release();
		mpProgressTimer = NULL;
	}

	Clear();
}
void CGuageBar::Build(int Zorder)
{
	mpParentNode->addChild(mpProgressTimer);
	mpScene->addChild(mpParentNode, Zorder);
}
void CGuageBar::UnBuild()
{
	mpScene->removeChild(mpParentNode);
	mpParentNode->removeChild(mpProgressTimer);
}
void CGuageBar::SetScene(Node *tpScene)
{
	mpScene = tpScene;
	mpScene->retain();
}
void CGuageBar::SetPosition(Vec2 tVec)
{
	mpParentNode->setPosition(tVec);
}
void CGuageBar::SetScaleX(float tScale)
{
	mpProgressTimer->setScaleX(tScale);
}
void CGuageBar::SetScaleY(float tScale)
{
	mpProgressTimer->setScaleY(tScale);
}
void CGuageBar::Show()
{
	mpProgressTimer->setVisible(true);
}
void CGuageBar::Hide()
{
	mpProgressTimer->setVisible(false);
}
bool CGuageBar::IsShow()
{
	return mpParentNode->isVisible();
}
void CGuageBar::BuildGuageWithDamage(float tDamage)
{
	mCurHP = mCurHP - tDamage;

	float tRatio = (100.0f*mCurHP) / mMaxHP;

	mpProgressTimer->setPercentage(tRatio);
}
void CGuageBar::BuildGuageRev(float tRev)
{
	mCurHP = tRev;

	float tRatio = (100.0f*mCurHP) / mMaxHP;

	mpProgressTimer->setPercentage(tRatio);
}