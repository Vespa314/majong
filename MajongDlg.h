// MajongDlg.h : 头文件
//

#pragma once
#include "Majong_Analyse.h"
const int Table_IDC[34] = {
	IDC_PIC1,IDC_PIC2,IDC_PIC3,IDC_PIC4,IDC_PIC5,IDC_PIC6,IDC_PIC7,
	IDC_PIC8,IDC_PIC9,IDC_PIC10,IDC_PIC11,IDC_PIC12,IDC_PIC13,IDC_PIC14,
	IDC_PIC15,IDC_PIC16,IDC_PIC17,IDC_PIC18,IDC_PIC19,IDC_PIC20,IDC_PIC21,
	IDC_PIC22,IDC_PIC23,IDC_PIC24,IDC_PIC25,IDC_PIC26,IDC_PIC27,IDC_PIC28,
	IDC_PIC29,IDC_PIC30,IDC_PIC31,IDC_PIC32,IDC_PIC33,IDC_PIC34
};

const int MajongPool_IDC[13] = {
	IDC_PIC35,IDC_PIC36,IDC_PIC37,IDC_PIC38,IDC_PIC39,IDC_PIC40,IDC_PIC41,
	IDC_PIC42,IDC_PIC43,IDC_PIC44,IDC_PIC45,IDC_PIC46,IDC_PIC47
};

const int MajongResult_IDC[13] = {
	IDC_PIC48,IDC_PIC49,IDC_PIC50,IDC_PIC51,IDC_PIC52,IDC_PIC53,IDC_PIC54,IDC_PIC55,IDC_PIC56
};

// CMajongDlg 对话框
class CMajongDlg : public CDialog
{
// 构造
public:
	CMajongDlg(CWnd* pParent = NULL);	// 标准构造函数
	void DrawJPG(int nID,char* pic_path );
	void ShowTable();
	void ShowCardPool();
	void SetResult();
	void ShowResult();
	CMajong_Card pool[13];
	CMajong_Card tp_result[9];
// 对话框数据
	enum { IDD = IDD_MAJONG_DIALOG };

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
	afx_msg void OnStnClickedTablePic(UINT uID);
	afx_msg void OnStnClickedPoolPic(UINT uID);
	afx_msg void OnBnClickedBeginAnalyse();
	afx_msg void OnBnClickedClearall();
};
