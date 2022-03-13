#pragma once
#include "CResource.h"

class CTexture : public CResource
{
private:
	// 텍스쳐를 입히기 위한 DC 핸들
	HDC		m_hDC;
	// 이미지를 저장할 비트맵 핸들
	HBITMAP m_hBMP;
	// 이미지에 대한 정보
	BITMAP	m_bmpInfo;

public:
	CTexture();
	virtual ~CTexture();

	HDC GetDC();
	HBITMAP GetBitMap();
	BITMAP	GetBmpInfo();

	int GetBmpWidth();
	int GetBmpHeight();

	// 해당 경로의 이미지를 불러오기
	void Load(const wstring& strFilePath);
	void Create(UINT width, UINT height);
};

