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
	// 텍스쳐가 사라질 시 받아왔던 HDC, HBITMAP을 반환해줌
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
		nullptr,				// hInstance -> nullptr : 다른 인스턴스에 있는 이미지를 가져오려는게 아님
		strFilePath.c_str(),	// 파일 경로 -> c_str() : wstring을 C스타일 문자열로 바꿔줌
		IMAGE_BITMAP,			// PNG, JPG 같은 형식들은 현재로썬 처리하기 어려움(압축되어있는 방식이라)
		0, 0,					// 0, 0 -> 알아서 이미지를 불러왔을 때 그 크기에 맞게 조정됨
		LR_CREATEDIBSECTION | LR_LOADFROMFILE	// 비트마스킹 OR연산을 통해 속성을 설정
	);

	if (0 == m_hBMP)			// 이미지를 불러오는데 실패 했다면
		assert(nullptr);

	// 비트맵을 다룰 DC만들기
	m_hDC = CreateCompatibleDC(CCore::getInst()->GetMainDC());

	// 비트맵과 DC 연결
	HBITMAP hOldBitMap = (HBITMAP)SelectObject(m_hDC, m_hBMP);

	// bmpInfo 추출
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
