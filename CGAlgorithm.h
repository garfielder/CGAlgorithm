// CGAlgorithm.h : CGAlgorithm Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CCGAlgorithmApp:
// �йش����ʵ�֣������ CGAlgorithm.cpp
//

class CCGAlgorithmApp : public CWinApp
{
public:
	CCGAlgorithmApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCGAlgorithmApp theApp;