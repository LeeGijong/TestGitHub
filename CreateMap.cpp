#pragma once

#include "CreateMap.h"
#include <stdio.h>

void CTileMap::CreateBackground(string tMapName, Layer *tpLayer)
{
	mpMap = TMXTiledMap::create(tMapName + ".tmx");
	mpMap->setAnchorPoint(Vec2(0, 0));

	auto tpNode = ParallaxNode::create();
	tpNode->addChild(mpMap, 1, Vec2(1.0f, 1.0f), Vec2(0, 0));


	tpLayer->addChild(tpNode, 0);
}
//¸Ê Ãæµ¹ °ü·Ã
int CTileMap::GetAttributeWith(int tRow, int tCol)
{
	int tResult = 0;

	int tGID = mpMap->getLayer("layerTile")->getTileGIDAt(Vec2(tCol, tRow));
	Value tValue = mpMap->getPropertiesForGID(tGID);

	if (false == tValue.isNull())
	{
		tResult = tValue.asValueMap()["mAttribute"].asInt();
	}

	return tResult;
}