
// BaiduMapInMFCDlg.h : 头文件
//

#pragma once
#include "webbrowser2.h"
#include "WebPage.h"
#include <vector>
using namespace std;

typedef struct
{
	double lon;
	double lat;
}POS;

// CBaiduMapInMFCDlg 对话框
class CBaiduMapInMFCDlg : public CDialogEx
{
// 构造
public:
	CBaiduMapInMFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BAIDUMAPINMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CWebBrowser2 m_web;
	vector<POS> m_pos;
	afx_msg void OnBnClickedBtnPolyline();
};
