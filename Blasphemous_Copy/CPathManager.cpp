#include "framework.h"
#include "CPathManager.h"

CPathManager::CPathManager()
{
	m_szContentPath[0] = {};
}

CPathManager::~CPathManager()
{
}

void CPathManager::init()
{
	// 경로 : (게임 솔루션 경로)\Output\Debug
	// 경로 : (게임 솔루션 경로)\Output\Release
	GetCurrentDirectory(MAXSIZE_PATH, m_szContentPath);		// 프로그램 경로를 확인하는 함수

	// 경로 문자열 길이
	int strSize = (int)wcslen(m_szContentPath);

	// === *경로를 상위 폴더로 바꿔주기* ===
	// 경로 문자열의 맨 뒤에서부터
	for (int i = strSize - 1; i > 0; --i)
	{
		// 처음으로 \\을 찾았다면
		if ('\\' == m_szContentPath[i])
		{
			// \\을 NULL문자로 바꿔줘서 문자열을 끊음
			m_szContentPath[i] = '\0';
			// 더 이상 찾을 필요 없으므로 break
			break;
		}
	}
	// 바뀐 경로 : (게임 솔루션 경로)\Output

	wcscat_s(m_szContentPath, MAXSIZE_PATH, L"\\Release\\Content\\");
	// 최종경로 : "(게임 솔루션 경로)\Output\Release\\Content\\"
}

const WCHAR* CPathManager::GetContentPath()
{
	return m_szContentPath;
}

const WCHAR* CPathManager::GetRelativeContentPath()
{
	return L"..\\Release\\Content\\";
}
