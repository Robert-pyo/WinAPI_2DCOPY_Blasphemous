#include "framework.h"
#include "CScene_Start.h"
#include "CScene_Stage1.h"
#include "CTextObject.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update();

	if (PRESS_KEY_DOWN(VK_TAB))
	{
		CHANGE_SCENE(GROUP_SCENE::STAGE_01);
	}
	if (PRESS_KEY_DOWN(VK_ESCAPE))
	{
		CHANGE_SCENE(GROUP_SCENE::TOOL);
	}
}

void CScene_Start::Enter()
{
	CTextObject* textObj = new CTextObject(TEXT("!Press the Space to TAB!"));
	AddObject(textObj, GROUP_GAMEOBJ::DEFAULT);
}

void CScene_Start::Exit()
{
	ClearAll();
}
