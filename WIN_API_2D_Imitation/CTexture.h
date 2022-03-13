#pragma once
#include "CResource.h"

class CTexture : public CResource
{
private:
	// �ؽ��ĸ� ������ ���� DC �ڵ�
	HDC		m_hDC;
	// �̹����� ������ ��Ʈ�� �ڵ�
	HBITMAP m_hBMP;
	// �̹����� ���� ����
	BITMAP	m_bmpInfo;

public:
	CTexture();
	virtual ~CTexture();

	HDC GetDC();
	HBITMAP GetBitMap();
	BITMAP	GetBmpInfo();

	int GetBmpWidth();
	int GetBmpHeight();

	// �ش� ����� �̹����� �ҷ�����
	void Load(const wstring& strFilePath);
	void Create(UINT width, UINT height);
};

