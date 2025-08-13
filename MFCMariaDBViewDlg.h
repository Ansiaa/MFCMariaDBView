
// MFCMariaDBViewDlg.h: 헤더 파일
//

#pragma once
#include <vector>
#include "CCtrlMariaDB.h"
// CMFCMariaDBViewDlg 대화 상자
class CMFCMariaDBViewDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCMariaDBViewDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCMARIADBVIEW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CCtrlMariaDB MariaDB;
	void InitCtrl();
	std::vector<std::vector<CString>> tbl_setmodel;
	std::vector<std::vector<CString>> tbl_setparams;
		
	CListCtrl m_ModelList;
	CListCtrl m_ParamsList;
	afx_msg void ModelClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedDb();
	CEdit m_DBHOST;
	CEdit m_DBNAME;
	CEdit m_DBPORT;
	CEdit m_DBPW;
	CEdit m_DBUSER;
};
