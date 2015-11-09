
// BaiduMapInMFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BaiduMapInMFC.h"
#include "BaiduMapInMFCDlg.h"
#include "afxdialogex.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern const CString GetSystemErrorMessage(DWORD dwError);

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBaiduMapInMFCDlg �Ի���



CBaiduMapInMFCDlg::CBaiduMapInMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBaiduMapInMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBaiduMapInMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_web);
}

BEGIN_MESSAGE_MAP(CBaiduMapInMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_POLYLINE, &CBaiduMapInMFCDlg::OnBnClickedBtnPolyline)
END_MESSAGE_MAP()


// CBaiduMapInMFCDlg ��Ϣ�������

BOOL CBaiduMapInMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	TCHAR strCurDir[512];
	GetCurrentDirectory(sizeof(strCurDir), strCurDir);
	m_web.Navigate((CString)strCurDir+_T("\\map.html"), NULL, NULL, NULL, NULL);
	ifstream file("data/pos0.txt");
	if (!file.is_open())
	{
		CString strErr = GetSystemErrorMessage(GetLastError());
		MessageBox(_T("Read File FAILED:") + strErr);
		exit(1);
	}
	POS pos;
	while (!file.eof())
	{
		file >> pos.lat >> pos.lon;
		m_pos.push_back(pos);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBaiduMapInMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBaiduMapInMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBaiduMapInMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBaiduMapInMFCDlg::OnBnClickedBtnPolyline()
{
	CWebPage page;
	page.SetDocument(m_web.GetDocument());
	CComVariant varResult;
	CString strLon, strLat;
	static int i = -1;
	if (++i >= m_pos.size())
		i = 0;
	strLon.Format(_T("%f"), m_pos[i].lon);
	strLat.Format(_T("%f"), m_pos[i].lat);
	page.CallJScript(_T("onDrawLine"), (const CString)strLon, (const CString)strLat, &varResult);
}
