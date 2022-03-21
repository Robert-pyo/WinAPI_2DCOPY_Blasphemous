#include "framework.h"
#include "CScene_Title.h"
#include "CBackground.h"
#include "CAnimator.h"
#include "CButtonUI.h"

CScene_Title::CScene_Title()
{
	m_pBackImgFront = CResourceManager::GetInst()->LoadD2DImage(L"Title_Background_Crisanta", L"texture\\UI\\Background\\Title\\MainMenu_Crisanta_Animation.png");
	m_pBackImgMiddle = CResourceManager::GetInst()->LoadD2DImage(L"Title_Background", L"texture\\UI\\Background\\Title\\MainMenu_BG_Animation.png");
	m_pBackImgBack = CResourceManager::GetInst()->LoadD2DImage(L"Title_Background_petals", L"texture\\UI\\Background\\Title\\MainMenu_Middle_petals.png");

	m_vecUI = {};
}

CScene_Title::~CScene_Title()
{
}

void ButtonStartClicked(DWORD_PTR param1, DWORD_PTR param2)
{
	ChangeToNextScene(GROUP_SCENE::STAGE_01);
}

void ButtonQuitClicked(DWORD_PTR param1, DWORD_PTR param2)
{
	PostQuitMessage(0);
}

void CScene_Title::update()
{
	CScene::update();

	if (PRESS_KEY_DOWN(VK_UP) || PRESS_KEY_DOWN('W'))
	{
		CSoundManager::GetInst()->Play(L"ChangeSelection");
		for (UINT i = 0; i < m_vecUI.size(); ++i)
		{
			if (m_vecUI[i]->IsMouseOn())
			{
				m_vecUI[i]->DeselectUI();
				m_vecUI[i]->MouseLBtnUp();
				
				if (i > 0)
				{
					m_vecUI[i - 1]->SelectUI();
					CUIManager::GetInst()->SetFocusedUI(m_vecUI[i - 1]);
				}
				else
				{
					m_vecUI[m_vecUI.size() - 1]->SelectUI();
					CUIManager::GetInst()->SetFocusedUI(m_vecUI[m_vecUI.size() - 1]);
				}
				break;
			}
		}
	}

	if (PRESS_KEY_DOWN(VK_DOWN) || PRESS_KEY_DOWN('S'))
	{
		CSoundManager::GetInst()->Play(L"ChangeSelection");
		for (UINT i = 0; i < m_vecUI.size(); ++i)
		{
			if (m_vecUI[i]->IsMouseOn())
			{
				m_vecUI[i]->DeselectUI();
				m_vecUI[i]->MouseLBtnUp();

				if (i < m_vecUI.size() - 1)
				{
					m_vecUI[i + 1]->SelectUI();
					CUIManager::GetInst()->SetFocusedUI(m_vecUI[i + 1]);
				}
				else
				{
					m_vecUI[0]->SelectUI();
					CUIManager::GetInst()->SetFocusedUI(m_vecUI[0]);
				}
				break;
			}
		}
	}

	if (PRESS_KEY_DOWN(VK_RETURN))
	{
		for (UINT i = 0; i < m_vecUI.size(); ++i)
		{
			if (m_vecUI[i]->IsMouseOn())
			{
				m_vecUI[i]->MouseLBtnClicked();
				break;
			}
		}
	}
}

void CScene_Title::Enter()
{
	// ���� �� Ŀ�� ���ֱ�
	ShowCursor(false);

	CSoundManager::GetInst()->AddSound(L"ChangeSelection", L"sound\\SoundEffects\\UI\\CHANGE_SELECTION.wav", false);
	CSoundManager::GetInst()->AddSound(L"ChangeTab", L"sound\\SoundEffects\\UI\\CHANGE_TAB.wav", false);
	CSoundManager::GetInst()->AddSound(L"MainMenu_BGM", L"sound\\SoundEffects\\UI\\MainMenu_BGM\\Stairs_MASTER.wav", false);

	CSoundManager::GetInst()->Play(L"MainMenu_BGM");

#pragma region SetBackgroundAnimation
	CBackground* background_Crisanta = new CBackground;
	background_Crisanta->SetPos(fPoint(WINSIZE_X, WINSIZE_Y));
	background_Crisanta->SetImage(m_pBackImgFront);
	background_Crisanta->GetAnimator()->CreateAnimation(L"TitleBackground_Crisanta",
		m_pBackImgFront, 
		fPoint(0.f, 0.f), 
		fPoint(640.f, 360.f), 
		fPoint(640.f, 0.f), 
		4, 0.2f, 14, true, false);
	background_Crisanta->GetAnimator()->Play(L"TitleBackground_Crisanta");
	background_Crisanta->SetName(L"TitleBackground_Crisanta");
	AddObject(background_Crisanta, GROUP_GAMEOBJ::BACKGROUND_FRONT);

	CBackground* background_altar = new CBackground;
	background_altar->SetPos(fPoint(WINSIZE_X, WINSIZE_Y));
	background_altar->SetImage(m_pBackImgMiddle);
	background_altar->GetAnimator()->CreateAnimation(L"TitleBackground_altar",
		m_pBackImgMiddle,
		fPoint(0.f, 0.f),
		fPoint(640.f, 360.f),
		fPoint(640.f, 0.f),
		5, 0.2f, 15, true, false);
	background_altar->GetAnimator()->Play(L"TitleBackground_altar");
	background_altar->SetName(L"TitleBackground_altar");
	AddObject(background_altar, GROUP_GAMEOBJ::BACKGROUND_BACK);

	CBackground* background_petals = new CBackground;
	background_petals->SetPos(fPoint(WINSIZE_X, WINSIZE_Y));
	background_petals->SetImage(m_pBackImgBack);
	background_petals->GetAnimator()->CreateAnimation(L"TitleBackground_petals",
		m_pBackImgBack,
		fPoint(0.f, 0.f),
		fPoint(640.f, 360.f),
		fPoint(640.f, 0.f),
		11, 0.1f, 44, true, false);
	background_petals->GetAnimator()->Play(L"TitleBackground_petals");
	background_petals->SetName(L"TitleBackground_petals");
	AddObject(background_petals, GROUP_GAMEOBJ::BACKGROUND_MIDDLE);
#pragma endregion

	CCameraManager::GetInst()->SetLookAt(background_petals->GetPos());
	CCameraManager::GetInst()->InitCameraPos(background_petals->GetPos());

	CButtonUI* pBtn_start = new CButtonUI;
	pBtn_start->SetScale(fPoint(100.f, 50.f));
	pBtn_start->SetPos(fPoint(WINSIZE_X - 210.f, WINSIZE_Y / 2.f + 90.f));
	pBtn_start->SetText(L"����");
	pBtn_start->SetClickCallBack(ButtonStartClicked, 0, 0);
	m_vecUI.push_back(pBtn_start);
	AddObject(pBtn_start, GROUP_GAMEOBJ::UI);

	CButtonUI* pBtn_option = new CButtonUI;
	pBtn_option->SetScale(fPoint(100.f, 50.f));
	pBtn_option->SetPos(fPoint(WINSIZE_X - 210.f, WINSIZE_Y / 2.f + 140.f));
	pBtn_option->SetText(L"�ɼ�");
	m_vecUI.push_back(pBtn_option);
	AddObject(pBtn_option, GROUP_GAMEOBJ::UI);

	CButtonUI* pBtn_quit = new CButtonUI;
	pBtn_quit->SetScale(fPoint(100.f, 50.f));
	pBtn_quit->SetPos(fPoint(WINSIZE_X - 210.f, WINSIZE_Y / 2.f + 190.f));
	pBtn_quit->SetText(L"������");
	pBtn_quit->SetClickCallBack(ButtonQuitClicked, 0, 0);
	m_vecUI.push_back(pBtn_quit);
	AddObject(pBtn_quit, GROUP_GAMEOBJ::UI);

	pBtn_start->SelectUI();
	CUIManager::GetInst()->SetFocusedUI(pBtn_start);
}

void CScene_Title::Exit()
{
	CSoundManager::GetInst()->Stop(L"MainMenu_BGM");
}