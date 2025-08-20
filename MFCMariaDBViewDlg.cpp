
// MFCMariaDBViewDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCMariaDBView.h"
#include "MFCMariaDBViewDlg.h"

#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCMariaDBViewDlg 대화 상자



CMFCMariaDBViewDlg::CMFCMariaDBViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCMARIADBVIEW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMariaDBViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODEL_LIST, m_ModelList);
	DDX_Control(pDX, IDC_MODEL_LIST, m_ModelList);
	DDX_Control(pDX, IDC_PARAMS_LIST, m_ParamsList);
	DDX_Control(pDX, IDC_HOST, m_DBHOST);
	DDX_Control(pDX, IDC_NAME, m_DBNAME);
	DDX_Control(pDX, IDC_PORT, m_DBPORT);
	DDX_Control(pDX, IDC_PW, m_DBPW);
	DDX_Control(pDX, IDC_USER, m_DBUSER);
}

BEGIN_MESSAGE_MAP(CMFCMariaDBViewDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_NOTIFY(NM_CLICK, IDC_MODEL_LIST, &CMFCMariaDBViewDlg::ModelClick)
	ON_BN_CLICKED(IDC_DB, &CMFCMariaDBViewDlg::OnBnClickedDb)
END_MESSAGE_MAP()


// CMFCMariaDBViewDlg 메시지 처리기

BOOL CMFCMariaDBViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	InitCtrl();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCMariaDBViewDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCMariaDBViewDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCMariaDBViewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCMariaDBViewDlg::InitCtrl()
{
	m_ModelList.ModifyStyle(0, LVS_REPORT); // 컬럼 보이게 설정
	m_ModelList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ModelList.InsertColumn(1, _T("sRecipeName"), LVCFMT_CENTER, 280);
	m_ModelList.InsertColumn(2, _T("sFrontalPattern"), LVCFMT_CENTER, 280);

	m_ParamsList.ModifyStyle(0, LVS_REPORT); // 컬럼 보이게 설정
	m_ParamsList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ParamsList.InsertColumn(1, _T("sInspType"), LVCFMT_CENTER, 200);
	m_ParamsList.InsertColumn(2, _T("sRecipe"), LVCFMT_CENTER, 200);
	m_ParamsList.InsertColumn(3, _T("sPattern"), LVCFMT_CENTER, 200);
	m_ParamsList.InsertColumn(4, _T("sSubPattern"), LVCFMT_CENTER, 200);
	m_ParamsList.InsertColumn(5, _T("sFilterName"), LVCFMT_CENTER, 200);
	m_ParamsList.InsertColumn(6, _T("sFilterType"), LVCFMT_CENTER, 200);
	m_ParamsList.InsertColumn(7, _T("bItemUsage"), LVCFMT_CENTER, 150);
	
	m_DBHOST.SetWindowText(MariaDB.DB_Setting.DB_HOST);
	m_DBNAME.SetWindowText(MariaDB.DB_Setting.DB_NAME);
	m_DBPORT.SetWindowText(MariaDB.DB_Setting.DB_PORT);
	m_DBPW.SetWindowText(MariaDB.DB_Setting.DB_PASS);
	m_DBUSER.SetWindowText(MariaDB.DB_Setting.DB_USER);
}
void CMFCMariaDBViewDlg::GetEditCtrl()
{
	m_DBHOST.GetWindowText(MariaDB.DB_Setting.DB_HOST);
	m_DBNAME.GetWindowText(MariaDB.DB_Setting.DB_NAME);
	m_DBPORT.GetWindowText(MariaDB.DB_Setting.DB_PORT);
	m_DBUSER.GetWindowText(MariaDB.DB_Setting.DB_USER);
	m_DBPW.GetWindowText(MariaDB.DB_Setting.DB_PASS);
}
void CMFCMariaDBViewDlg::OnBnClickedDb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ModelList.DeleteAllItems();
	GetEditCtrl();
	MariaDB.m_fnInitDB();
	MariaDB.m_fnConnectDB();
	CString SELECT_query;
	SELECT_query.Format(L"SELECT sRecipeName,sFrontalParam FROM %s.tbl_setmodel;", MariaDB.DB_Setting.DB_NAME);
	MariaDB.GetDBData(CT2A(SELECT_query), tbl_setmodel, m_ModelList);
}
void CMFCMariaDBViewDlg::ModelClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_ParamsList.DeleteAllItems();

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nIndex = pNMItemActivate->iItem; 

	if (nIndex >= 0)
	{
		CString sRecipe = m_ModelList.GetItemText(nIndex, 1);  // 컬럼 인덱스는 실제 레이아웃에 따라 조정

		CString SELECT_query;
		SELECT_query.Format(L"SELECT sInspType, sRecipe, sPattern, sSubPattern, sFilterName, sFilterType, bItemUsage FROM %s.tbl_setparams WHERE sRecipe = '%s' AND sInspType = 'Frontal';", MariaDB.DB_Setting.DB_NAME, sRecipe);

		MariaDB.GetDBData(CT2A(SELECT_query), tbl_setparams, m_ParamsList);
	}

	*pResult = 0;

}
