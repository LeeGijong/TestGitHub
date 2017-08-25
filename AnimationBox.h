#pragma once

#include "cocos2d.h"
#include <iostream>

using namespace cocos2d;
using namespace std;

class CActor;

class AnimationBox
{

protected:

	CActor *mpActor = NULL;

	Node *mpScene = NULL;


	Node *mpBody = NULL;

	string mAniName = "";

	int mTotalFrameCount = 0;
	float mDelayTime = 0.0f;

	//ÄÚÄÚ½º°´Ã¼
	Sprite *tSpriteC = NULL;
	RepeatForever *tRepeatForeverC = NULL;
	Repeat *tRepeatC = NULL;

	Vec2 mVec;

	cocos2d::Vector<SpriteFrame *> tSpriteFrameVec;

	Rect mRectCollision;


public:
	AnimationBox();
	~AnimationBox();
	
	void Create(string tAniName, int tTotalFrameCount, float tDelayTime, float AnchorPtX, float AnchorPtY);
	void Create_Repeat_One(string tAniName, int tTotalFrameCount, float tDelayTime, float AnchorPtX, float AnchorPtY);
	void Destroy();

	void Build(int Zorder);
	void UnBuild();


	void SetScene(Node *tpScene);

	void SetPosition(Vec2 tVec);
	Vec2 GetPosition();
	
	void SetScale(float tScale);
	void SetScaleY(float tScale);
	void SetScaleX(float tScale);

	void SetAnchorPoint(Vec2 tAnchor);

	void SetOpacity(float tOpacity);

	void SetFlipX(bool tFlipX);

	void RunAni();
	void RunAni_Repeat_One();
	void RunAction(Action *tpAction);
	
	void StopAni();
	void StopAni_Repeat_One();
	
	void Show();
	void Hide();

	bool IsShow();

	

	Rect GetBoundingBox();

	Size GetContentSize();

	Vec2 ConvertToNodeSpace(const Vec2& worldPoint);

	Sprite *GetSprite();

};
