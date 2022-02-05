
// MFCApplication3.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MFCApplication3.h"

#include "EventDoc.h"
#include "EventView.h"
#include "EventChildWnd.h"
#include "PreEventDoc.h"
#include "PreEventView.h"
#include "PreEventChildWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication3App

BEGIN_MESSAGE_MAP(CMFCApplication3App, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMFCApplication3App::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_SLU_NEW, &CMFCApplication3App::OnSluNew)
	ON_COMMAND(ID_SLU_OPEN, &CMFCApplication3App::OnSluOpen)
	ON_COMMAND(ID_SLU_SAVE, &CMFCApplication3App::OnSluSave)
	ON_COMMAND(ID_SLU_CLOSE, &CMFCApplication3App::OnSluClose)
	ON_COMMAND(ID_FILE_NEW, &CMFCApplication3App::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)             //打开而不是添加
	ON_COMMAND(ID_FILE_SAVE, &CMFCApplication3App::OnFileSave)
	ON_COMMAND(ID_FILE_CLOSE, &CMFCApplication3App::OnFileClose)
END_MESSAGE_MAP()


// CMFCApplication3App 构造

CMFCApplication3App::CMFCApplication3App()
{
	IsSluOpened = false;//初始化数据

	m_bHiColorIcons = TRUE;


	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MFCApplication3.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	SlutionEventFileList = _T("");
	SlutionTextFileList = _T("");
	SlutionUnitFileList = _T("");
	SlutionMapFileList = _T("");
}

// 唯一的一个 CMFCApplication3App 对象

CMFCApplication3App theApp;

void CMFCApplication3App::SetOLEVisible(bool bVisible)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (bVisible)
		pMain->SetControlEnable(SW_SHOW, SW_SHOW, SW_SHOW, SW_SHOW, SW_SHOW, SW_SHOW, SW_SHOW);
	else
		pMain->SetControlEnable(SW_HIDE, SW_HIDE, SW_HIDE, SW_HIDE, SW_HIDE, SW_HIDE, SW_HIDE);
}


void  CMFCApplication3App::setPath()
{
	DicList[0] = SlutionLocalDir + L"\\PreEvent";
	DicList[1] = SlutionLocalDir + L"\\Event";
	DicList[2] = SlutionLocalDir + L"\\Text";
	DicList[3] = SlutionLocalDir + L"\\UnitData";
	DicList[4] = SlutionLocalDir + L"\\Map";

	Path开始剧情 = DicList[1] + L"\\开始剧情.eve";
	Path结束剧情 = DicList[1] + L"\\结束剧情.eve";
	Path角色事件 = DicList[0] + L"\\角色事件启动子.peve";
	Path回合事件 = DicList[0] + L"\\回合事件启动子.peve";
	Path地图事件 = DicList[0] + L"\\地图事件启动子.peve";
	PathMisc事件 = DicList[0] + L"\\Misc事件启动子.peve";
}


CString CMFCApplication3App::To16(int iinput)
{
	CString s;
	s.Format(L"%x2", iinput);
	return s;
}
int CMFCApplication3App::To10(CString sinput)
{
	return _wtoi(sinput + L"X");
}

CString CMFCApplication3App::GetCXY(int X, int Y)
{
	int a = (X + (Y % 4) * 64);
	int b = Y / 4;
	CString s;
	s.Format(L"%x2 %x2", X, Y);
	return s;
}
// CMFCApplication3App 初始化

BOOL CMFCApplication3App::InitInstance()
{
	HANDLE m_hMutex = ::CreateMutex(NULL, TRUE, L"XXXOnlyOneInstance");
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		AfxMessageBox(L"您已经运行了本软件！谢谢使用");  //已经运行了程序
		return FALSE;
	}
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	pDocTemplate1 = new CMultiDocTemplate(IDR_EVENTTYPE,
		RUNTIME_CLASS(CEventDoc),
		RUNTIME_CLASS(CEventChildWnd), // 自定义 MDI 子框架
		RUNTIME_CLASS(CEventView));
	if (!pDocTemplate1)
		return FALSE;
	AddDocTemplate(pDocTemplate1);

	pDocTemplate2 = new CMultiDocTemplate(IDR_PREEVENTTYPE,
		RUNTIME_CLASS(CPreEventDoc),
		RUNTIME_CLASS(CPreEventChildWnd), // 自定义 MDI 子框架
		RUNTIME_CLASS(CPreEventView));
	if (!pDocTemplate2)
		return FALSE;
	AddDocTemplate(pDocTemplate2);
	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	m_pMainWnd->DragAcceptFiles(TRUE); //可接受文件
	
	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	////////////////////////////////////////////////////
	IsSluOpened = false;
	SetOLEVisible(FALSE);
	////////////////////////////////////////////////////

	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

void CMFCApplication3App::SetComboxContent(int iType)
{
	
}

int CMFCApplication3App::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMFCApplication3App 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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
public:
	afx_msg void OnBnClickedOk();
//	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
//	ON_WM_MDIACTIVATE()
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CMFCApplication3App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMFCApplication3App 自定义加载/保存方法

void CMFCApplication3App::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
	bNameValid = strName.LoadString(IDS_EXPLORER1);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER1);
}

void CMFCApplication3App::LoadCustomState()
{
}

void CMFCApplication3App::SaveCustomState()
{
}

// CMFCApplication3App 消息处理程序

void CAboutDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
//////////////////////////////////////////////////////////////
void CMFCApplication3App::OnSluNew()
{
	if (IsSluOpened)
	{
		if (AfxMessageBox(L"是否关闭当前项目以继续？", MB_OKCANCEL) == IDOK)
		{
			OnSluClose();
		}
		else
		{
			return;
		}
	}
	CNewSlu newSlu = new CNewSlu();
	if (newSlu.DoModal() == IDOK)
	{
		SlutionDictionary = newSlu.m_sluPath;
		SlutionName = newSlu.m_sluName;
		SlutionLocalDir = SlutionDictionary + +L"\\" + SlutionName;
		SlutionPath = SlutionDictionary + L"\\" + SlutionName + L".fe";
		SlutionEventFileList = L"";
		SlutionTextFileList = L"";	
		SlutionUnitFileList = L"";
		SlutionMapFileList = L"";
		IsSluOpened = true;//标记为已打开项目
	}
	else
	{
		delete newSlu;
		return;
	}
	delete newSlu;

	if (PathFileExists(SlutionLocalDir))
	{
		AfxMessageBox(L"该文件夹已经存在！请选择合适的工程名。", MB_OK);
		return;
	}
	if (!CreateDirectory(SlutionLocalDir, NULL))
	{
		AfxMessageBox(L"创建工程文件夹时失败！！！", MB_OK);
		return;
	}

	setPath();

	for (int i = 0; i < 5; i++)
	{
		CreateDirectory(DicList[i], NULL);
	}

	CFile 开始剧情File;
	CFile 结束剧情File;
	CFile 角色事件File;
	CFile 回合事件File;
	CFile 地图事件File;
	CFile Misc事件File;

	CFile sluFile(SlutionPath, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	CArchive ar(&sluFile, CArchive::store);
	ar << SlutionPath << SlutionName << SlutionDictionary << SlutionLocalDir << SlutionEventFileList << SlutionTextFileList << SlutionUnitFileList << SlutionMapFileList;//按顺序写入
	ar.Close();
	sluFile.Close();
	开始剧情File.Open(Path开始剧情, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	结束剧情File.Open(Path结束剧情, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	角色事件File.Open(Path角色事件, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	回合事件File.Open(Path回合事件, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	地图事件File.Open(Path地图事件, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	Misc事件File.Open(PathMisc事件, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	开始剧情File.Close();
	结束剧情File.Close();
	角色事件File.Close();
	回合事件File.Close();
	地图事件File.Close();
	Misc事件File.Close();

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	pMain->m_wndFileView.SetAllString(SlutionEventFileList, SlutionTextFileList, SlutionUnitFileList, SlutionMapFileList);

	SetOLEVisible(IsSluOpened);
}

void CMFCApplication3App::OnSluOpen()
{
	if (IsSluOpened)
	{
		if (AfxMessageBox(L"是否关闭当前项目以继续？", MB_OKCANCEL) == IDOK)
		{
			OnSluClose();
		}
		else
		{
			return;
		}
	}
	CFileDialog dlg(TRUE,
		L"DEM Files (*DEM)",
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ENABLESIZING,
		_T("FE工程文件(*.fe)|*.fe;)"),
		NULL);
	dlg.m_ofn.lpstrTitle = L"打开工程";
	//显示文件对话框，获得文件名集合
	int retval = dlg.DoModal();
	if (retval == IDCANCEL)
		return;
	IsSluOpened = true;//标记为已打开项目
	CFile sluFile(dlg.GetPathName(), CFile::modeRead | CFile::shareDenyNone);
	CArchive ar(&sluFile, CArchive::load);
	ar >> SlutionPath >> SlutionName >> SlutionDictionary >> SlutionLocalDir >> SlutionEventFileList >> SlutionTextFileList >> SlutionUnitFileList >> SlutionMapFileList;
	sluFile.Close();
	ar.Close();
	setPath();
	//将文件列表写入左侧的FileView

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	pMain->m_wndFileView.SetAllString(SlutionEventFileList, SlutionTextFileList, SlutionUnitFileList, SlutionMapFileList);

	SetOLEVisible(IsSluOpened);
	////////////////////////////////////////
}

void CMFCApplication3App::OnSluSave()
{
	//写入fe文件工程中包含的文件。并在OnSluOpen()里面写入打开时的函数

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	SlutionEventFileList = pMain->m_wndFileView.GetAllString(1);
	SlutionTextFileList = pMain->m_wndFileView.GetAllString(2);
	SlutionUnitFileList = pMain->m_wndFileView.GetAllString(3);
	SlutionMapFileList = pMain->m_wndFileView.GetAllString(4);

	CFile sluFile(SlutionPath,CFile::modeReadWrite | CFile::shareDenyNone);
	CArchive ar(&sluFile, CArchive::store);
	ar << SlutionPath << SlutionName << SlutionDictionary << SlutionLocalDir << SlutionEventFileList << SlutionTextFileList << SlutionUnitFileList << SlutionMapFileList;//按顺序写入
	ar.Close();
	sluFile.Close(); 

	CWinApp::SaveAllModified();
}
void CMFCApplication3App::OnSluClose()
{
	OnSluSave();
	theApp.CloseAllDocuments(FALSE);
	IsSluOpened = false;
	SetOLEVisible(IsSluOpened);
}
////////////////////////////////////////////////////////////////
void CMFCApplication3App::OnFileNew()
{
	CNewSlutionWizad CDialognsw = new CNewSlutionWizad();
	if (CDialognsw.DoModal() == IDOK)
	{
		CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
		int i = CDialognsw.m_iFileType;
		CString fName = CDialognsw.m_sFileName;
		CString fPathName;
		if (i == 1 || i >= 10) //获得建立的文件类型，并将路径复制
		{
			fPathName = DicList[1] + L"\\" + fName + L".eve";//1是event，2是text，3是unit，4是map
			if (PathFileExists(fPathName))
			{
				AfxMessageBox(L"该文件已经存在，请尝试更换新建的文件名称！");
				delete CDialognsw;
				return;
			}
			pMain->m_wndFileView.AddString(fName, 1);//在fileview中加入该文件
		}
		if (i == 2)
		{
		}
		CFile eventFile;//新建空白文件
		eventFile.Open(fPathName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
		eventFile.Close();
		theApp.OpenDocumentFile(fPathName);//新建一个空白文档
	}
	delete CDialognsw;
	return;
}

void CMFCApplication3App::OnFileAdd()
{

}
void CMFCApplication3App::OnFileSave()
{

}
void CMFCApplication3App::OnFileClose()
{

}


void CMFCApplication3App::SetCreateFileType(int iType)
{
	iCreateFileType = iType;
}

int CMFCApplication3App::GetCreateFileType()
{
	return iCreateFileType;
}


bool CMFCApplication3App::OpenDocument(CString sSelectParent, CString sSelect)
{
	if (sSelectParent == L"主事件")
	{
		if (sSelect == L"开始剧情")
		{
			theApp.OpenDocumentFile(Path开始剧情);
		}
		if (sSelect == L"结束剧情")
		{
			theApp.OpenDocumentFile(Path结束剧情);
		}
	}
	if (sSelectParent == L"启动子事件")
	{
		if (sSelect == L"角色事件")
		{
			theApp.OpenDocumentFile(Path角色事件);
		}
		if (sSelect == L"地图事件")
		{
			theApp.OpenDocumentFile(Path地图事件);
		}
		if (sSelect == L"回合事件")
		{
			theApp.OpenDocumentFile(Path回合事件);
		}
		if (sSelect == L"Misc事件")
		{
			theApp.OpenDocumentFile(PathMisc事件);
		}
	}
	if (sSelectParent == L"事件文件")
	{
		theApp.OpenDocumentFile(DicList[1] + L"\\" + sSelect + L".eve");
	}
	if (sSelectParent == L"人物配置")
	{

	}
	if (sSelectParent == L"文字对话")
	{

	}
	if (sSelectParent == L"地图")
	{

	}
	return true;
}

bool CMFCApplication3App::DeleteDocument(CString sSelectParent, CString sSelect)//删除FileView中的文件
{
	if (sSelectParent == L"事件文件")
	{
		DeleteFile(DicList[1] + L"\\" + sSelect);
	}
	if (sSelectParent == L"人物配置")
	{

	}
	if (sSelectParent == L"文字对话")
	{

	}
	if (sSelectParent == L"地图")
	{

	}
	return true;
}
