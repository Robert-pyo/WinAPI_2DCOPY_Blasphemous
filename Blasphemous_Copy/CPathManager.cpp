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
	// ��� : (���� �ַ�� ���)\Output\Debug
	// ��� : (���� �ַ�� ���)\Output\Release
	GetCurrentDirectory(MAXSIZE_PATH, m_szContentPath);		// ���α׷� ��θ� Ȯ���ϴ� �Լ�

	// ��� ���ڿ� ����
	int strSize = (int)wcslen(m_szContentPath);

	// === *��θ� ���� ������ �ٲ��ֱ�* ===
	// ��� ���ڿ��� �� �ڿ�������
	for (int i = strSize - 1; i > 0; --i)
	{
		// ó������ \\�� ã�Ҵٸ�
		if ('\\' == m_szContentPath[i])
		{
			// \\�� NULL���ڷ� �ٲ��༭ ���ڿ��� ����
			m_szContentPath[i] = '\0';
			// �� �̻� ã�� �ʿ� �����Ƿ� break
			break;
		}
	}
	// �ٲ� ��� : (���� �ַ�� ���)\Output

	wcscat_s(m_szContentPath, MAXSIZE_PATH, L"\\Release\\Content\\");
	// ������� : "(���� �ַ�� ���)\Output\Release\\Content\\"
}

const WCHAR* CPathManager::GetContentPath()
{
	return m_szContentPath;
}

const WCHAR* CPathManager::GetRelativeContentPath()
{
	return L"..\\Release\\Content\\";
}
