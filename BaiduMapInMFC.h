
// BaiduMapInMFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBaiduMapInMFCApp: 
// �йش����ʵ�֣������ BaiduMapInMFC.cpp
//

class CBaiduMapInMFCApp : public CWinApp
{
public:
	CBaiduMapInMFCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBaiduMapInMFCApp theApp;