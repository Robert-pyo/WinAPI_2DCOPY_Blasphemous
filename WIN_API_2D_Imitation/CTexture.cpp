#include "framework.h"
#include "CTexture.h"

CTexture::CTexture()
{
	m_hDC		= 0;
	m_hBMP		= 0;
	m_bmpInfo	= {};
}

CTexture::~CTexture()
{
	// �ؽ��İ� ����� �� �޾ƿԴ� HDC, HBITMAP�� ��ȯ����
	DeleteDC(m_hDC);
	DeleteObject(m_hBMP);
}

HDC CTexture::GetDC()
{
	return m_hDC;
}

HBITMAP CTexture::GetBitMap()
{
	return m_hBMP;
}

BITMAP CTexture::GetBmpInfo()
{
	return m_bmpInfo;
}

int CTexture::GetBmpWidth()
{
	return m_bmpInfo.bmWidth;
}

int CTexture::GetBmpHeight()
{
	return m_bmpInfo.bmHeight;
}

void CTexture::Load(const wstring& strFilePath)
{
	m_hBMP = (HBITMAP)LoadImage(
		nullptr,				// hInstance -> nullptr : �ٸ� �ν��Ͻ��� �ִ� �̹����� ���������°� �ƴ�
		strFilePath.c_str(),	// ���� ��� -> c_str() : wstring�� C��Ÿ�� ���ڿ��� �ٲ���
		IMAGE_BITMAP,			// PNG, JPG ���� ���ĵ��� ����ν� ó���ϱ� �����(����Ǿ��ִ� ����̶�)
		0, 0,					// 0, 0 -> �˾Ƽ� �̹����� �ҷ����� �� �� ũ�⿡ �°� ������
		LR_CREATEDIBSECTION | LR_LOADFROMFILE	// ��Ʈ����ŷ OR������ ���� �Ӽ��� ����
	);

	if (0 == m_hBMP)			// �̹����� �ҷ����µ� ���� �ߴٸ�
		assert(nullptr);

	// ��Ʈ���� �ٷ� DC�����
	m_hDC = CreateCompatibleDC(CCore::getInst()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hOldBitMap = (HBITMAP)SelectObject(m_hDC, m_hBMP);

	// bmpInfo ����
	GetObject(m_hBMP, sizeof(BITMAP), &m_bmpInfo);
}

void CTexture::Create(UINT width, UINT height)
{
	HDC mainDC = CCore::getInst()->GetMainDC();
	m_hBMP = CreateCompatibleBitmap(mainDC, width, height);
	m_hDC = CreateCompatibleDC(mainDC);

	HBITMAP hOldBmp = (HBITMAP)SelectObject(m_hDC, m_hBMP);
	DeleteObject(hOldBmp);

	GetObject(m_hBMP, sizeof(BITMAP), &m_bmpInfo);
}
