// MajongDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Majong.h"
#include "MajongDlg.h"
#include <afx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMajongDlg 对话框




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


// CMajongDlg 消息处理程序

BOOL CMajongDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMajongDlg::OnPaint()
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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

	CoInitialize(NULL); // COM 初始化
	
	CFile file;
	// 读入文件内容
	file.Open(pic_path,CFile::modeRead | CFile::shareDenyNone); 
	//获取长度
	DWORD dwSize = DWORD(file.GetLength());
	//给图片分配全局内存
	HGLOBAL hMem = GlobalAlloc( GMEM_MOVEABLE, dwSize );
	//锁定内存
	LPVOID lpBuf = GlobalLock( hMem );
	//读取图片到全局内存当中
	file.Read( lpBuf, dwSize );
	//关闭文件
	file.Close();
	//解锁内存
	GlobalUnlock( hMem );

	//IStream接口指针，用来保存图片流
	IStream* pStream = NULL;
	//图片对象
	IPicture* pPicture = NULL;
	//由HGLOBAL得到IStream，参数TRUE表示释放IStream的同时，释放内存
	HRESULT hr;
	//用全局内存初使化IStream接口指针
	hr = CreateStreamOnHGlobal( hMem, TRUE, &pStream );//ASSERT ( SUCCEEDED(hr) );
	//得到IPicture COM接口对象
	hr = OleLoadPicture( pStream, dwSize, TRUE, IID_IPicture, ( LPVOID * )&pPicture );
	//ASSERT(hr==S_OK);

	long nWidth,nHeight;
	//MM_HIMETRIC 模式  单位是0.01毫米
	pPicture->get_Width( &nWidth );
	pPicture->get_Height( &nHeight );

	////////原大显示//////
	CSize sz( nWidth, nHeight );
	//转换MM_HIMETRIC到MM_TEXT像素单位
	pDC->HIMETRICtoDP( &sz ); 


	//控件大小变成图片大小
	//GetDlgItem(IDC_PIC1)->MoveWindow(rect.left,rect.top,sz.cx,sz.cy);

	//左上角那个点对齐
	//pPicture->Render(pDC->m_hDC,rect.left,rect.top,sz.cx,sz.cy,
	//	0,nHeight,nWidth,-nHeight,NULL);

	//图片缩放至空间大小
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
	//找到牌池中未知的那个位置
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
	//条子
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
	// TODO: 在此添加控件通知处理程序代码
	
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
	// TODO: 在此添加控件通知处理程序代码
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
