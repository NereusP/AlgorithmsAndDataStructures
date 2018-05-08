
// CRCToolDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <string>
#include "crc16.hpp"

typedef int (__cdecl *CalcCRCFunc)(FILE* fr, CRC16_TYPE crc16_type, uint16_t& crc16value);
typedef int (__cdecl *CalcCRCExFunc)(FILE* fr, uint16_t& crc16value, uint16_t crc_startvalue, uint16_t polyrepres);

// CCRCToolDlg 对话框
class CCRCToolDlg : public CDialogEx
{
// 构造
public:
	CCRCToolDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CCRCToolDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CRCTOOL_DIALOG };
#endif

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
	// 打开文件
	CButton m_BtnOpenFile;
	// 文件路径
	CEdit m_EditFilePath;
	// 选择CRC类型
	CComboBox m_ComboBoxSelCRCType;
	// 多项式
	CEdit m_EditPoly;
	// 异或值
	CEdit m_EditXORValue;
	// 初始值
	CEdit m_EditStartValue;
	// CRC计算值
	CStatic m_EditCalcValue;
	// 开始计算
	CButton m_BtnCalc;
	afx_msg void OnOpenFile();
	afx_msg void OnSelCRCType();
	afx_msg void OnCalcCRC();
	FILE* fread;
	std::string filename;
	HINSTANCE hInstCRC16Dll;
	CalcCRCFunc CalcCRCDllFunc;
	CalcCRCExFunc CalcCRCExDllFunc;
};

//计算CRC值的线程
void __stdcall CalcCRCThread(void* param);
