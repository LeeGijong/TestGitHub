#pragma once

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;
using namespace std;

class CTileMap 
{
private:
	

public:

	TMXTiledMap *mpMap = NULL;
	

public:
	//��
	void CreateBackground(string tMapName, Layer *tpLayer);

	//�� �浹 ����
	int GetAttributeWith(int tRow, int tCol);

};