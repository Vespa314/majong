// MajongDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Majong.h"
#include "MajongDlg.h"
#include <afx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMajongDlg �Ի���




CMajongDlg::CMajongDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMajongDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMajongDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMajongDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(STN_CLICKED,IDC_PIC1,IDC_PIC34,OnStnClickedTablePic)
	ON_CONTROL_RANGE(STN_CLICKED,IDC_PIC35,IDC_PIC47,OnStnClickedPoolPic)
	ON_BN_CLICKED(IDC_BEGIN_ANALYSE, &CMajongDlg::OnBnClickedBeginAnalyse)
	ON_BN_CLICKED(IDC_ClEARALL, &CMajongDlg::OnBnClickedClearall)
END_MESSAGE_MAP()


// CMajongDlg ��Ϣ�������

BOOL CMajongDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	for(int i = 0;i < 34;i++)
	{
		GetDlgItem(Table_IDC[i])->ModifyStyle(0,SS_NOTIFY);
	}
	for(int i = 0;i < 13;i++)
	{
		GetDlgItem(MajongPool_IDC[i])->ModifyStyle(0,SS_NOTIFY);
	}
	for(int i = 0;i < 13;i++)
	{
		pool[i].Type = TYPE_UNKNOWN;
		pool[i].Num = TYPE_UNKNOWN;
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMajongDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMajongDlg::OnPaint()
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
		CDialog::OnPaint();
	}

	/*CDC* pDC = GetDC();
	CDC MemDC;

	CRect rect;
	GetWindowRect(&rect);
	int nWidth = rect.Width();
	int nHeight = rect.Height();
	CBitmap MemBitmap;
	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));
	ShowTable(&MemDC);
	ShowCardPool(&MemDC);
	pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();*/

	ShowTable();
	ShowCardPool();
	ShowResult();
	int idx = -1;
	for(int i = 0;i < 13;i++)
	{
		if (pool[i].Type == TYPE_UNKNOWN)
		{
			idx = i;
			break;
		}
	}
	CButton* Analyse_Button = (CButton*)GetDlgItem(IDC_BEGIN_ANALYSE);
	Analyse_Button->EnableWindow(-1==idx);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMajongDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMajongDlg::DrawJPG(int nID,char* pic_path )
{
	if (!pic_path)
		return;

	CDC *pDC = this->GetDC();
	CRect rect;
	//CDC memDC; 
	GetDlgItem(nID)->GetWindowRect(&rect);
	GetDlgItem(nID)->GetParent()->ScreenToClient(rect);
	//memDC.CreateCompatibleDC(NULL);    

	CoInitialize(NULL); // COM ��ʼ��
	
	CFile file;
	// �����ļ�����
	file.Open(pic_path,CFile::modeRead | CFile::shareDenyNone); 
	//��ȡ����
	DWORD dwSize = DWORD(file.GetLength());
	//��ͼƬ����ȫ���ڴ�
	HGLOBAL hMem = GlobalAlloc( GMEM_MOVEABLE, dwSize );
	//�����ڴ�
	LPVOID lpBuf = GlobalLock( hMem );
	//��ȡͼƬ��ȫ���ڴ浱��
	file.Read( lpBuf, dwSize );
	//�ر��ļ�
	file.Close();
	//�����ڴ�
	GlobalUnlock( hMem );

	//IStream�ӿ�ָ�룬��������ͼƬ��
	IStream* pStream = NULL;
	//ͼƬ����
	IPicture* pPicture = NULL;
	//��HGLOBAL�õ�IStream������TRUE��ʾ�ͷ�IStream��ͬʱ���ͷ��ڴ�
	HRESULT hr;
	//��ȫ���ڴ��ʹ��IStream�ӿ�ָ��
	hr = CreateStreamOnHGlobal( hMem, TRUE, &pStream );//ASSERT ( SUCCEEDED(hr) );
	//�õ�IPicture COM�ӿڶ���
	hr = OleLoadPicture( pStream, dwSize, TRUE, IID_IPicture, ( LPVOID * )&pPicture );
	//ASSERT(hr==S_OK);

	long nWidth,nHeight;
	//MM_HIMETRIC ģʽ  ��λ��0.01����
	pPicture->get_Width( &nWidth );
	pPicture->get_Height( &nHeight );

	////////ԭ����ʾ//////
	CSize sz( nWidth, nHeight );
	//ת��MM_HIMETRIC��MM_TEXT���ص�λ
	pDC->HIMETRICtoDP( &sz ); 


	//�ؼ���С���ͼƬ��С
	//GetDlgItem(IDC_PIC1)->MoveWindow(rect.left,rect.top,sz.cx,sz.cy);

	//���Ͻ��Ǹ������
	//pPicture->Render(pDC->m_hDC,rect.left,rect.top,sz.cx,sz.cy,
	//	0,nHeight,nWidth,-nHeight,NULL);

	//ͼƬ�������ռ��С
	pPicture->Render(pDC->m_hDC,rect.left,rect.top,rect.Width(),rect.Height(),
			0,nHeight,nWidth,-nHeight,NULL);

	if (pPicture) 
		pPicture->Release();
	if (pStream) 
		pStream->Release(); 

	//pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);
	//this->ReleaseDC(pDC);
	//memDC.DeleteDC();

	CoUninitialize();
}

void CMajongDlg::ShowTable()
{
	char* path = new char[1024];
	for(int i = 0;i < 34;i++)
	{
		if (i < 9)
		{
			sprintf(path,"./image/m%d.JPG",i+1);
			DrawJPG(Table_IDC[i],path);
		}
		else if(i < 18)
		{
			sprintf(path,"./image/t%d.JPG",i+1-9);
			DrawJPG(Table_IDC[i],path);
		}
		else if(i < 27)
		{
			sprintf(path,"./image/w%d.JPG",i+1-18);
			DrawJPG(Table_IDC[i],path);
		}
		else if(i<31)
		{
			sprintf(path,"./image/zf%d.JPG",i+1-27);
			DrawJPG(Table_IDC[i],path);
		}
		else
		{
			sprintf(path,"./image/zj%d.JPG",i+1-31);
			DrawJPG(Table_IDC[i],path);
		}
	}
}



void CMajongDlg::OnStnClickedTablePic(UINT uID)
{
	//�ҵ��Ƴ���δ֪���Ǹ�λ��
	int idx = -1;
	for(int i = 0;i < 13;i++)
	{
		if (pool[i].Type == TYPE_UNKNOWN)
		{
			idx = i;
			break;
		}
	}
	if(idx == -1)
		return;
	//����
	if(uID >= Table_IDC[0] && uID < Table_IDC[9])
	{
		pool[idx].Num = uID - Table_IDC[0]+1;
		pool[idx].Type = TIAO;
	}
	else if(uID >= Table_IDC[9] && uID < Table_IDC[18])
	{
		pool[idx].Num = uID - Table_IDC[9]+1;
		pool[idx].Type = BING;
	}
	else if(uID >= Table_IDC[18] && uID < Table_IDC[27])
	{
		pool[idx].Num = uID - Table_IDC[18]+1;
		pool[idx].Type = WAN;
	}
	else 
	{
		pool[idx].Type = DONG + uID - Table_IDC[27];
		pool[idx].Num = 0;
	}
	//Invalidate(TRUE);
	CRect rect;
	GetDlgItem(MajongPool_IDC[idx])->GetWindowRect(&rect);
	GetDlgItem(MajongPool_IDC[idx])->GetParent()->ScreenToClient(rect);
	InvalidateRect(&rect);

}

void CMajongDlg::ShowCardPool()
{
	char* path = new char[1024];
	for(int i = 0;i < 13;i++)
	{
		if (pool[i].Type == TYPE_UNKNOWN)
			continue;
		else switch (pool[i].Type)
		{
		case TIAO:
			sprintf(path,"./image/m%d.JPG",pool[i].Num);
			break;
		case BING:
			sprintf(path,"./image/t%d.JPG",pool[i].Num);
			break;
		case WAN:
			sprintf(path,"./image/w%d.JPG",pool[i].Num);
			break;
		case DONG:
		case NAN:
		case XI:
		case BEI:
			sprintf(path,"./image/zf%d.JPG",pool[i].Type - DONG + 1);
			break;
		case ZHONG:
		case FA:
		case BAI:
			sprintf(path,"./image/zj%d.JPG",pool[i].Type - ZHONG + 1);
			break;
		default:
			return;
		}
		DrawJPG(MajongPool_IDC[i],path);
	}
}

void CMajongDlg::OnBnClickedBeginAnalyse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CMajong_Analyse Analyse;
	for(int i = 0;i < 13;i++)
	{
		Analyse.pool[i] = pool[i];
	}
	Analyse.Analyse();

	SetResult();
	Invalidate(TRUE);

}

void CMajongDlg::OnStnClickedPoolPic( UINT uID )
{
	pool[uID-IDC_PIC35].Type = TYPE_UNKNOWN;
	CRect rect;
	GetDlgItem(MajongPool_IDC[uID-IDC_PIC35])->GetWindowRect(&rect);
	GetDlgItem(MajongPool_IDC[uID-IDC_PIC35])->GetParent()->ScreenToClient(rect);
	InvalidateRect(&rect);
}

void CMajongDlg::ShowResult()
{
	char* path = new char[1024];
	for(int i = 0;i < 9;i++)
	{
		if (tp_result[i].Type == TYPE_UNKNOWN)
			continue;
		else switch (tp_result[i].Type)
		{
		case TIAO:
			sprintf(path,"./image/m%d.JPG",tp_result[i].Num);
			break;
		case BING:
			sprintf(path,"./image/t%d.JPG",tp_result[i].Num);
			break;
		case WAN:
			sprintf(path,"./image/w%d.JPG",tp_result[i].Num);
			break;
		case DONG:
		case NAN:
		case XI:
		case BEI:
			sprintf(path,"./image/zf%d.JPG",tp_result[i].Type - DONG + 1);
			break;
		case ZHONG:
		case FA:
		case BAI:
			sprintf(path,"./image/zj%d.JPG",tp_result[i].Type - ZHONG + 1);
			break;
		default:
			return;
		}
		DrawJPG(MajongResult_IDC[i],path);
	}
}

void CMajongDlg::SetResult()
{
	for(int i = 0;i < 9;i++)
	{
		tp_result[i].Type = TYPE_UNKNOWN;
	}

	int cc = 0;
	for(int i = 0;i < 34;i++)
	{
		if(CMajong_Analyse::TingPaiResult & 0x01<<i)
		{
			if(i<9)
			{
				tp_result[cc].Num = i+1;
				tp_result[cc].Type = WAN;
			}
			else if(i<18)
			{
				tp_result[cc].Num = i+1-9;
				tp_result[cc].Type = TIAO;
			}
			else if(i<27)
			{
				tp_result[cc].Num = i+1-18;
				tp_result[cc].Type = BING;
			}
			else
			{
				tp_result[cc].Num = 0;
				tp_result[cc].Type = i-27+DONG;
			}
			cc++;
		}
	}
}

void CMajongDlg::OnBnClickedClearall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i = 0;i < 9;i++)
	{
		tp_result[i].Type = TYPE_UNKNOWN;
	}
	for(int i = 0;i < 13;i++)
	{
		pool[i].Type = TYPE_UNKNOWN;
	}

	Invalidate(TRUE);
}
