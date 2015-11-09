
// BaiduMapInMFCDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CBaiduMapInMFCDlg 对话框



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


// CBaiduMapInMFCDlg 消息处理程序

BOOL CBaiduMapInMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBaiduMapInMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
