#pragma once
#include "afxcmn.h"


// CSectionDlg �Ի���

class CSectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSectionDlg)

public:
	CSectionDlg(char *pFileBuf, PIMAGE_NT_HEADERS pNt, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSectionDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SECTION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_sectionList;
	char *m_pFileBuf = NULL;
	PIMAGE_NT_HEADERS m_pNt;
	virtual BOOL OnInitDialog();
};
