
// BaiduMapInMFCDlg.h : ͷ�ļ�
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

// CBaiduMapInMFCDlg �Ի���
class CBaiduMapInMFCDlg : public CDialogEx
{
// ����
public:
	CBaiduMapInMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BAIDUMAPINMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
