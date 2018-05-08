
// CRCToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <string>
#include "crc16.hpp"

typedef int (__cdecl *CalcCRCFunc)(FILE* fr, CRC16_TYPE crc16_type, uint16_t& crc16value);
typedef int (__cdecl *CalcCRCExFunc)(FILE* fr, uint16_t& crc16value, uint16_t crc_startvalue, uint16_t polyrepres);

// CCRCToolDlg �Ի���
class CCRCToolDlg : public CDialogEx
{
// ����
public:
	CCRCToolDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CCRCToolDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CRCTOOL_DIALOG };
#endif

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
	// ���ļ�
	CButton m_BtnOpenFile;
	// �ļ�·��
	CEdit m_EditFilePath;
	// ѡ��CRC����
	CComboBox m_ComboBoxSelCRCType;
	// ����ʽ
	CEdit m_EditPoly;
	// ���ֵ
	CEdit m_EditXORValue;
	// ��ʼֵ
	CEdit m_EditStartValue;
	// CRC����ֵ
	CStatic m_EditCalcValue;
	// ��ʼ����
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

//����CRCֵ���߳�
void __stdcall CalcCRCThread(void* param);
