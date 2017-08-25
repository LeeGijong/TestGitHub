#include "AnimationBox.h"
#include <stdio.h>
#include "Actor.h"

using namespace std;
USING_NS_CC;

AnimationBox::AnimationBox()
{

}

AnimationBox::~AnimationBox()
{
	
}
//�ݺ� �ִϸ��̼�
void AnimationBox::Create(string tAniName, int tTotalFrameCount, float tDelayTime, float AnchorPtX, float AnchorPtY)
{
	mpBody = Sprite::create();

	tSpriteC = Sprite::create(tAniName + "00.png");


	mRectCollision = tSpriteC->getBoundingBox();

	auto tAnimation = Animation::create();
	tAnimation->setDelayPerUnit(tDelayTime);

	char tStr[512];
	memset(tStr, 0, 512);

	for (int i = 0; i < tTotalFrameCount; i++)
	{
		sprintf(tStr, "%s%02d.png", tAniName.c_str(), i);
		tAnimation->addSpriteFrameWithFile(tStr);
	}

	auto tAnimate = Animate::create(tAnimation);
	tRepeatForeverC = RepeatForever::create(tAnimate);
	tRepeatForeverC->retain();

	mpBody->setAnchorPoint(Vec2(AnchorPtX, AnchorPtY));
	tSpriteC->setAnchorPoint(Vec2(AnchorPtX, AnchorPtY));

}
//�ѹ� ���� �ִϸ��̼�
void AnimationBox::Create_Repeat_One(string tAniName, int tTotalFrameCount, float tDelayTime, float AnchorPtX, float AnchorPtY)
{
	mpBody = Sprite::create();

	tSpriteC = Sprite::create(tAniName + "00.png");

	mpActor = new CActor();

	mRectCollision = tSpriteC->getBoundingBox();

	auto tAnimation = Animation::create();
	tAnimation->setDelayPerUnit(tDelayTime);

	char tStr[512];
	memset(tStr, 0, 512);

	for (int i = 0; i < tTotalFrameCount; i++)
	{
		sprintf(tStr, "%s%02d.png", tAniName.c_str(), i);
		tAnimation->addSpriteFrameWithFile(tStr);
	}

	auto tAnimate = Animate::create(tAnimation);
	tRepeatC = Repeat::create(tAnimate, 1);
	tRepeatC->retain();

	mpBody->setAnchorPoint(Vec2(AnchorPtX, AnchorPtY));
	tSpriteC->setAnchorPoint(Vec2(AnchorPtX, AnchorPtY));
}
void AnimationBox::Destroy()
{
	if (tSpriteC != NULL)
	{
		tSpriteC->release();
		tSpriteC = NULL;
	}
	if (tRepeatForeverC != NULL)
	{
		tRepeatForeverC->release();
		tRepeatForeverC = NULL;

	}
	if (mpScene != NULL)
	{
		mpScene->release();
		mpScene = NULL;
	}

}

void AnimationBox::Build(int Zorder)
{
	mpBody->addChild(tSpriteC);
	mpScene->addChild(mpBody, Zorder);
}
void AnimationBox::UnBuild()
{
	mpBody->removeChild(tSpriteC);
	mpScene->removeChild(mpBody);
}

//�� �� ������
void AnimationBox::SetScene(Node *tpScene)
{
	mpScene = tpScene;
	mpScene->retain();
}

void AnimationBox::SetPosition(Vec2 tVec)
{
	mpBody->setPosition(tVec);
}
Vec2 AnimationBox::GetPosition()
{
	return mpBody->getPosition();
}

//���� �ݺ� �ִϸ��̼�
void AnimationBox::RunAni()
{
	tSpriteC->retain();
	tSpriteC->runAction(tRepeatForeverC);
}

//�ѹ��� �����ϴ� �ִϸ��̼�
void AnimationBox::RunAni_Repeat_One()
{
	tSpriteC->retain();
	tSpriteC->runAction(tRepeatC);
}

//�� �׼�
void AnimationBox::RunAction(Action *tpAction)
{
	tSpriteC->runAction(tpAction);
}

//��ž �ִ�
void AnimationBox::StopAni()
{
	tSpriteC->stopAction(tRepeatForeverC);
}

void AnimationBox::StopAni_Repeat_One()
{
	tSpriteC->stopAction(tRepeatC);
}

//�� ���̵�
void AnimationBox::Show()
{
	tSpriteC->setVisible(true);
}
void AnimationBox::Hide()
{
	tSpriteC->setVisible(false);
}
//������
void AnimationBox::SetScale(float tScale)
{
	mpBody->setScale(tScale);
}
void AnimationBox::SetScaleY(float tScale)
{
	mpBody->setScaleY(tScale);
}
void AnimationBox::SetScaleX(float tScale)
{
	mpBody->setScaleX(tScale);
}

void AnimationBox::SetAnchorPoint(Vec2 tAnchor)
{
	tSpriteC->setAnchorPoint(tAnchor);
}

void AnimationBox::SetOpacity(float tOpacity)
{
	tSpriteC->setOpacity(tOpacity);
}

bool AnimationBox::IsShow()
{
	return tSpriteC->isVisible();
}

Rect AnimationBox::GetBoundingBox()
{
	Rect tRect;

	tRect = mpBody->getBoundingBox();

	

	tRect.setRect(tRect.origin.x, tRect.origin.y,
		mRectCollision.size.width, mRectCollision.size.height);


	return tRect;
}
Size AnimationBox::GetContentSize()
{	
	Size tSize;

	tSize.setSize(mRectCollision.size.width, mRectCollision.size.height);

	return tSize;
}
Vec2 AnimationBox::ConvertToNodeSpace(const Vec2& worldPoint)
{
	return mpBody->convertToNodeSpace(worldPoint);
}
void AnimationBox::SetFlipX(bool tFlipX)
{
	tSpriteC->setFlippedX(tFlipX);
}

Sprite *AnimationBox::GetSprite()
{
	//�� ������ �ڵ���. �����ʿ�.
	return (Sprite *)mpBody;
}