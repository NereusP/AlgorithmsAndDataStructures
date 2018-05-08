
// CRCToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CRCTool.h"
#include "CRCToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCRCToolDlg �Ի���



CCRCToolDlg::CCRCToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CRCTOOL_DIALOG, pParent), 
	fread(nullptr),hInstCRC16Dll(nullptr),
	CalcCRCDllFunc(nullptr),
	CalcCRCExDllFunc(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CCRCToolDlg::~CCRCToolDlg()
{
	if (fread != nullptr)
	{
		fclose(fread);
		fread = nullptr;
	}
	if (hInstCRC16Dll != nullptr)
	{
		FreeLibrary(hInstCRC16Dll);
		hInstCRC16Dll = nullptr;
	}
}

void CCRCToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_OPENFILE, m_BtnOpenFile);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_EditFilePath);
	DDX_Control(pDX, IDC_COMBO_CRCTYPE_SEL, m_ComboBoxSelCRCType);
	DDX_Control(pDX, IDC_EDIT_POLY, m_EditPoly);
	DDX_Control(pDX, IDC_EDIT_XOR_VALUE, m_EditXORValue);
	DDX_Control(pDX, IDC_EDIT_START_VALUE, m_EditStartValue);
	DDX_Control(pDX, IDC_STATIC_CRC16, m_EditCalcValue);
	DDX_Control(pDX, IDC_BUTTON_CALC, m_BtnCalc);
}

BEGIN_MESSAGE_MAP(CCRCToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, &CCRCToolDlg::OnOpenFile)
	ON_CBN_SELCHANGE(IDC_COMBO_CRCTYPE_SEL, &CCRCToolDlg::OnSelCRCType)
	ON_BN_CLICKED(IDC_BUTTON_CALC, &CCRCToolDlg::OnCalcCRC)
END_MESSAGE_MAP()


// CCRCToolDlg ��Ϣ�������

BOOL CCRCToolDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_BtnCalc.EnableWindow(FALSE);
	m_ComboBoxSelCRCType.InsertString(0, L"CRC16_IBM");
	m_ComboBoxSelCRCType.InsertString(1, L"CRC16_CCITT");
	m_ComboBoxSelCRCType.InsertString(2, L"CRC16_CCITT_FALSE");
	m_ComboBoxSelCRCType.InsertString(3, L"CRC16_XMODEM");
	m_ComboBoxSelCRCType.InsertString(4, L"CRC16_X25");
	m_ComboBoxSelCRCType.InsertString(5, L"CRC16_MODBUS");
	m_ComboBoxSelCRCType.InsertString(6, L"CRC16_MAXIM");
	m_ComboBoxSelCRCType.InsertString(7, L"CRC16_USB");
	m_ComboBoxSelCRCType.SetCurSel(0);
	m_EditPoly.SetWindowTextW(L"8005");
	m_EditStartValue.SetWindowTextW(L"0000");
	m_EditXORValue.SetWindowTextW(L"0000");
	m_EditCalcValue.SetWindowTextW(L"");
#ifdef _DEBUG
	hInstCRC16Dll = LoadLibrary(L"crc16d.dll");
	if (hInstCRC16Dll == nullptr)
	{
		MessageBox(L"��ʧcrc16d.dll", L"����", MB_ICONERROR | MB_OK);
		return FALSE;
	}
#else
	hInstCRC16Dll = LoadLibrary(L"crc16.dll");
	if (hInstCRC16Dll == nullptr)
	{
		MessageBox(L"��ʧcrc16.dll", L"����", MB_ICONERROR | MB_OK);
		return FALSE;
	}
#endif
	CalcCRCDllFunc = (CalcCRCFunc)GetProcAddress(hInstCRC16Dll, "CalcCRC16");
	CalcCRCExDllFunc = (CalcCRCExFunc)GetProcAddress(hInstCRC16Dll, "CalcCRC16Ex");
	if ((CalcCRCDllFunc == nullptr) || (CalcCRCExDllFunc == nullptr))
	{
		MessageBox(L"����crc16.dllʧ��", L"����", MB_ICONERROR | MB_OK);
		return FALSE;
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCRCToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCRCToolDlg::OnPaint()
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
HCURSOR CCRCToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCRCToolDlg::OnOpenFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_EditCalcValue.SetWindowTextW(L"");//����ϴμ�����
	BOOL isOpen = TRUE;
	CString defaultDir = L"D:\\";//Ĭ�ϴ򿪵�Ŀ¼
	CString defaultFileName = L"";//Ĭ�ϴ򿪵��ļ���
	CString filter = L"�ļ�(*.*)|*.*||";
	CFileDialog openFileDlg(isOpen, defaultDir, defaultFileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	if (result == IDOK)
	{
		CString filepath = openFileDlg.GetPathName();
		filepath.Replace(L"\\", L"/");
		m_EditFilePath.SetWindowTextW(filepath);
		USES_CONVERSION;
		filename = W2CA(filepath);
		if (fread != nullptr)
		{
			fclose(fread);
			fread = nullptr;
		}
		fread = fopen(filename.c_str(), "rb+");
		if (fread != nullptr)
		{
			m_BtnCalc.EnableWindow(TRUE);
		}
	}
}


void CCRCToolDlg::OnSelCRCType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int sel_index = m_ComboBoxSelCRCType.GetCurSel();
	if (sel_index >= 0)
	{
		switch (sel_index)
		{
		case 0:
			//CRC16_IBM
			m_EditPoly.SetWindowTextW(L"8005");
			m_EditStartValue.SetWindowTextW(L"0000");
			m_EditXORValue.SetWindowTextW(L"0000");
			m_EditCalcValue.SetWindowTextW(L"");
			break;
		case 1:
			//CRC16_CCITT
			m_EditPoly.SetWindowTextW(L"1021");
			m_EditStartValue.SetWindowTextW(L"0000");
			m_EditXORValue.SetWindowTextW(L"0000");
			m_EditCalcValue.SetWindowTextW(L"");
			break;
		case 2:
			//CRC16_CCITT_FALSE
			m_EditPoly.SetWindowTextW(L"1021");
			m_EditStartValue.SetWindowTextW(L"FFFF");
			m_EditXORValue.SetWindowTextW(L"0000");
			m_EditCalcValue.SetWindowTextW(L"");
			break;
		case 3:
			//CRC16_XMODEM
			m_EditPoly.SetWindowTextW(L"1021");
			m_EditStartValue.SetWindowTextW(L"0000");
			m_EditXORValue.SetWindowTextW(L"0000");
			m_EditCalcValue.SetWindowTextW(L"");
			break;
		case 4:
			//CRC16_X25
			m_EditPoly.SetWindowTextW(L"1021");
			m_EditStartValue.SetWindowTextW(L"0000");
			m_EditXORValue.SetWindowTextW(L"FFFF");
			m_EditCalcValue.SetWindowTextW(L"");
			break;
		case 5:
			//CRC16_MODBUS
			m_EditPoly.SetWindowTextW(L"8005");
			m_EditStartValue.SetWindowTextW(L"FFFF");
			m_EditXORValue.SetWindowTextW(L"0000");
			m_EditCalcValue.SetWindowTextW(L"");
			break;
		case 6:
			//CRC16_MAXIM
			m_EditPoly.SetWindowTextW(L"8005");
			m_EditStartValue.SetWindowTextW(L"0000");
			m_EditXORValue.SetWindowTextW(L"FFFF");
			m_EditCalcValue.SetWindowTextW(L"");
			break;
		case 7:
			//CRC16_USB
			m_EditPoly.SetWindowTextW(L"8005");
			m_EditStartValue.SetWindowTextW(L"FFFF");
			m_EditXORValue.SetWindowTextW(L"FFFF");
			m_EditCalcValue.SetWindowTextW(L"");
			break;
		default:
			break;
		}
	}
}


void CCRCToolDlg::OnCalcCRC()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_beginthreadex(nullptr, 0, (unsigned int(__stdcall *)(void *))&CalcCRCThread, (void *)this, 0, nullptr);
}

void __stdcall CalcCRCThread(void * param)
{
	CCRCToolDlg* pdlg = (CCRCToolDlg*)param;
	CString cstr;
	pdlg->m_EditPoly.GetWindowTextW(cstr);
	uint16_t polyrepres = wcstol(cstr, nullptr, 16);
	pdlg->m_EditStartValue.GetWindowTextW(cstr);
	uint16_t crc_startvalue = wcstol(cstr, nullptr, 16);
	uint16_t crc16_value = 0x00;
	int calc_res = (pdlg->CalcCRCExDllFunc)(pdlg->fread, crc16_value, crc_startvalue, polyrepres);
	if (calc_res != -1)
	{
		cstr.Empty();
		cstr.Format(_T("0x%04X"), crc16_value);
		pdlg->m_EditCalcValue.SetWindowTextW(cstr);
	}
}
