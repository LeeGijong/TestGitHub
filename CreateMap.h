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
	//¸Ê
	void CreateBackground(string tMapName, Layer *tpLayer);

	//¸Ê Ãæµ¹ °ü·Ã
	int GetAttributeWith(int tRow, int tCol);

};