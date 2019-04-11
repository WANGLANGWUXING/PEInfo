
// MyLordPEDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyLordPE.h"
#include "MyLordPEDlg.h"
#include "afxdialogex.h"
#include "PeInfo.h"
#include "SectionDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyLordPEDlg �Ի���



CMyLordPEDlg::CMyLordPEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYLORDPE_DIALOG, pParent)
	, m_strFilePath(_T(""))
	, m_strOEP(_T(""))
	, m_strSubSystem(_T(""))
	, m_strNumberOfSections(_T(""))
	, m_strSizeOfImage(_T(""))
	, m_strTimeDateStamp(_T(""))
	, m_strBaseOfCode(_T(""))
	, m_strSizeOfHeaders(_T(""))
	, m_strBaseOfData(_T(""))
	, m_strCharacteristics(_T(""))
	, m_strSectionAlignment(_T(""))
	, m_strCheckSum(_T(""))
	, m_strFileAlignment(_T(""))
	, m_strSizeOfOptionalHeader(_T(""))
	, m_strMagic(_T(""))
	, m_strNumberOfRvaAndSizes(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyLordPEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITFilePath, m_strFilePath);
	DDX_Text(pDX, IDC_EDITOEP, m_strOEP);
	DDX_Text(pDX, IDC_EDITSubSystem, m_strSubSystem);
	DDX_Text(pDX, IDC_EDITImageBase, m_strImageBase);
	DDX_Text(pDX, IDC_EDITNumberOfSections, m_strNumberOfSections);
	DDX_Text(pDX, IDC_EDITSizeOfImage, m_strSizeOfImage);
	DDX_Text(pDX, IDC_EDITTimeDateStamp, m_strTimeDateStamp);
	DDX_Text(pDX, IDC_BaseOfCode, m_strBaseOfCode);
	DDX_Text(pDX, IDC_EDITSizeOfHeaders, m_strSizeOfHeaders);
	DDX_Text(pDX, IDC_EDITBaseOfData, m_strBaseOfData);
	DDX_Text(pDX, IDC_EDITCharacteristics, m_strCharacteristics);
	DDX_Text(pDX, IDC_EDITSectionAlignment, m_strSectionAlignment);
	DDX_Text(pDX, IDC_EDITCheckSum, m_strCheckSum);
	DDX_Text(pDX, IDC_EDITFileAlignment, m_strFileAlignment);
	DDX_Text(pDX, IDC_EDITSizeOfOptionalHeader, m_strSizeOfOptionalHeader);
	DDX_Text(pDX, IDC_EDITMagic, m_strMagic);
	DDX_Text(pDX, IDC_EDITNumberOfRvaAndSizes, m_strNumberOfRvaAndSizes);
}

BEGIN_MESSAGE_MAP(CMyLordPEDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BTNSectionHeader, &CMyLordPEDlg::OnBnClickedBtnsectionheader)
END_MESSAGE_MAP()


// CMyLordPEDlg ��Ϣ�������

BOOL CMyLordPEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyLordPEDlg::OnPaint()
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
HCURSOR CMyLordPEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyLordPEDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	char szStr[MAX_PATH];
	DragQueryFileA(hDropInfo, 0, szStr, MAX_PATH);
	DragFinish(hDropInfo);
	pFileBuf = GetFileMemPointer(szStr);
	if (!pFileBuf)
	{
		return;

	}
	if (!IsPeFile(pFileBuf))
	{
		MessageBox("���ļ�����PE�ļ�");
		return;
	}
	pDos = (PIMAGE_DOS_HEADER)pFileBuf;
	pNt =(PIMAGE_NT_HEADERS)(pDos->e_lfanew + pFileBuf);

	UpdateData(TRUE);
	m_strFilePath = szStr;
	m_strOEP.Format("%08X", pNt->OptionalHeader.AddressOfEntryPoint);
	m_strSubSystem.Format("%04X", pNt->OptionalHeader.Subsystem);
	m_strImageBase.Format("%08X", pNt->OptionalHeader.ImageBase);
	m_strNumberOfSections.Format("%04X", pNt->FileHeader.NumberOfSections);
	m_strSizeOfImage.Format("%08X", pNt->OptionalHeader.SizeOfImage);
	m_strTimeDateStamp.Format("%08X", pNt->FileHeader.TimeDateStamp);
	m_strBaseOfCode.Format("%08X", pNt->OptionalHeader.BaseOfCode);
	m_strSizeOfHeaders.Format("%08X", pNt->OptionalHeader.SizeOfHeaders);
	m_strBaseOfData.Format("%08X", pNt->OptionalHeader.BaseOfData);
	m_strCharacteristics.Format("%04X", pNt->FileHeader.Characteristics);
	m_strSectionAlignment.Format("%08X", pNt->OptionalHeader.SectionAlignment);
	m_strCheckSum.Format("%08X", pNt->OptionalHeader.CheckSum);
	m_strFileAlignment.Format("%08X", pNt->OptionalHeader.FileAlignment);
	m_strSizeOfOptionalHeader.Format("%04X", pNt->FileHeader.SizeOfOptionalHeader);
	m_strMagic.Format("%04X", pNt->OptionalHeader.Magic);
	m_strNumberOfRvaAndSizes.Format("%08X", pNt->OptionalHeader.NumberOfRvaAndSizes);

	UpdateData(FALSE);

	CDialogEx::OnDropFiles(hDropInfo);
}

// NTͷ��������ʾ
void CMyLordPEDlg::ShowHeaderOfNt(char* pFileBuf)
{
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)pFileBuf;
	PIMAGE_NT_HEADERS pNt =
		(PIMAGE_NT_HEADERS)
		(pDos->e_lfanew + pFileBuf);

	printf("��ڵ㣺%08X\n", pNt->OptionalHeader.AddressOfEntryPoint);
	
}

void CMyLordPEDlg::OnBnClickedBtnsectionheader()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_strFilePath=="")
	{
		MessageBox("��������ЧPE�ļ�");
		return;
	}
	CSectionDlg section(pFileBuf,pNt);
	section.DoModal();

}
