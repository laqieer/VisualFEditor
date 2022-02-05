
// MFCApplication3.cpp : ����Ӧ�ó��������Ϊ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_SLU_NEW, &CMFCApplication3App::OnSluNew)
	ON_COMMAND(ID_SLU_OPEN, &CMFCApplication3App::OnSluOpen)
	ON_COMMAND(ID_SLU_SAVE, &CMFCApplication3App::OnSluSave)
	ON_COMMAND(ID_SLU_CLOSE, &CMFCApplication3App::OnSluClose)
	ON_COMMAND(ID_FILE_NEW, &CMFCApplication3App::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)             //�򿪶��������
	ON_COMMAND(ID_FILE_SAVE, &CMFCApplication3App::OnFileSave)
	ON_COMMAND(ID_FILE_CLOSE, &CMFCApplication3App::OnFileClose)
END_MESSAGE_MAP()


// CMFCApplication3App ����

CMFCApplication3App::CMFCApplication3App()
{
	IsSluOpened = false;//��ʼ������

	m_bHiColorIcons = TRUE;


	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MFCApplication3.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	SlutionEventFileList = _T("");
	SlutionTextFileList = _T("");
	SlutionUnitFileList = _T("");
	SlutionMapFileList = _T("");
}

// Ψһ��һ�� CMFCApplication3App ����

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

	Path��ʼ���� = DicList[1] + L"\\��ʼ����.eve";
	Path�������� = DicList[1] + L"\\��������.eve";
	Path��ɫ�¼� = DicList[0] + L"\\��ɫ�¼�������.peve";
	Path�غ��¼� = DicList[0] + L"\\�غ��¼�������.peve";
	Path��ͼ�¼� = DicList[0] + L"\\��ͼ�¼�������.peve";
	PathMisc�¼� = DicList[0] + L"\\Misc�¼�������.peve";
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
// CMFCApplication3App ��ʼ��

BOOL CMFCApplication3App::InitInstance()
{
	HANDLE m_hMutex = ::CreateMutex(NULL, TRUE, L"XXXOnlyOneInstance");
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		AfxMessageBox(L"���Ѿ������˱������ллʹ��");  //�Ѿ������˳���
		return FALSE;
	}
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣  �ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	pDocTemplate1 = new CMultiDocTemplate(IDR_EVENTTYPE,
		RUNTIME_CLASS(CEventDoc),
		RUNTIME_CLASS(CEventChildWnd), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CEventView));
	if (!pDocTemplate1)
		return FALSE;
	AddDocTemplate(pDocTemplate1);

	pDocTemplate2 = new CMultiDocTemplate(IDR_PREEVENTTYPE,
		RUNTIME_CLASS(CPreEventDoc),
		RUNTIME_CLASS(CPreEventChildWnd), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CPreEventView));
	if (!pDocTemplate2)
		return FALSE;
	AddDocTemplate(pDocTemplate2);
	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	m_pMainWnd->DragAcceptFiles(TRUE); //�ɽ����ļ�
	
	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	////////////////////////////////////////////////////
	IsSluOpened = false;
	SetOLEVisible(FALSE);
	////////////////////////////////////////////////////

	// ��������������ָ�������  ���
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

void CMFCApplication3App::SetComboxContent(int iType)
{
	
}

int CMFCApplication3App::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMFCApplication3App ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

// �������жԻ����Ӧ�ó�������
void CMFCApplication3App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMFCApplication3App �Զ������/���淽��

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

// CMFCApplication3App ��Ϣ�������

void CAboutDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
//////////////////////////////////////////////////////////////
void CMFCApplication3App::OnSluNew()
{
	if (IsSluOpened)
	{
		if (AfxMessageBox(L"�Ƿ�رյ�ǰ��Ŀ�Լ�����", MB_OKCANCEL) == IDOK)
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
		IsSluOpened = true;//���Ϊ�Ѵ���Ŀ
	}
	else
	{
		delete newSlu;
		return;
	}
	delete newSlu;

	if (PathFileExists(SlutionLocalDir))
	{
		AfxMessageBox(L"���ļ����Ѿ����ڣ���ѡ����ʵĹ�������", MB_OK);
		return;
	}
	if (!CreateDirectory(SlutionLocalDir, NULL))
	{
		AfxMessageBox(L"���������ļ���ʱʧ�ܣ�����", MB_OK);
		return;
	}

	setPath();

	for (int i = 0; i < 5; i++)
	{
		CreateDirectory(DicList[i], NULL);
	}

	CFile ��ʼ����File;
	CFile ��������File;
	CFile ��ɫ�¼�File;
	CFile �غ��¼�File;
	CFile ��ͼ�¼�File;
	CFile Misc�¼�File;

	CFile sluFile(SlutionPath, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	CArchive ar(&sluFile, CArchive::store);
	ar << SlutionPath << SlutionName << SlutionDictionary << SlutionLocalDir << SlutionEventFileList << SlutionTextFileList << SlutionUnitFileList << SlutionMapFileList;//��˳��д��
	ar.Close();
	sluFile.Close();
	��ʼ����File.Open(Path��ʼ����, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	��������File.Open(Path��������, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	��ɫ�¼�File.Open(Path��ɫ�¼�, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	�غ��¼�File.Open(Path�غ��¼�, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	��ͼ�¼�File.Open(Path��ͼ�¼�, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	Misc�¼�File.Open(PathMisc�¼�, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
	��ʼ����File.Close();
	��������File.Close();
	��ɫ�¼�File.Close();
	�غ��¼�File.Close();
	��ͼ�¼�File.Close();
	Misc�¼�File.Close();

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	pMain->m_wndFileView.SetAllString(SlutionEventFileList, SlutionTextFileList, SlutionUnitFileList, SlutionMapFileList);

	SetOLEVisible(IsSluOpened);
}

void CMFCApplication3App::OnSluOpen()
{
	if (IsSluOpened)
	{
		if (AfxMessageBox(L"�Ƿ�رյ�ǰ��Ŀ�Լ�����", MB_OKCANCEL) == IDOK)
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
		_T("FE�����ļ�(*.fe)|*.fe;)"),
		NULL);
	dlg.m_ofn.lpstrTitle = L"�򿪹���";
	//��ʾ�ļ��Ի��򣬻���ļ�������
	int retval = dlg.DoModal();
	if (retval == IDCANCEL)
		return;
	IsSluOpened = true;//���Ϊ�Ѵ���Ŀ
	CFile sluFile(dlg.GetPathName(), CFile::modeRead | CFile::shareDenyNone);
	CArchive ar(&sluFile, CArchive::load);
	ar >> SlutionPath >> SlutionName >> SlutionDictionary >> SlutionLocalDir >> SlutionEventFileList >> SlutionTextFileList >> SlutionUnitFileList >> SlutionMapFileList;
	sluFile.Close();
	ar.Close();
	setPath();
	//���ļ��б�д������FileView

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	pMain->m_wndFileView.SetAllString(SlutionEventFileList, SlutionTextFileList, SlutionUnitFileList, SlutionMapFileList);

	SetOLEVisible(IsSluOpened);
	////////////////////////////////////////
}

void CMFCApplication3App::OnSluSave()
{
	//д��fe�ļ������а������ļ�������OnSluOpen()����д���ʱ�ĺ���

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	SlutionEventFileList = pMain->m_wndFileView.GetAllString(1);
	SlutionTextFileList = pMain->m_wndFileView.GetAllString(2);
	SlutionUnitFileList = pMain->m_wndFileView.GetAllString(3);
	SlutionMapFileList = pMain->m_wndFileView.GetAllString(4);

	CFile sluFile(SlutionPath,CFile::modeReadWrite | CFile::shareDenyNone);
	CArchive ar(&sluFile, CArchive::store);
	ar << SlutionPath << SlutionName << SlutionDictionary << SlutionLocalDir << SlutionEventFileList << SlutionTextFileList << SlutionUnitFileList << SlutionMapFileList;//��˳��д��
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
		if (i == 1 || i >= 10) //��ý������ļ����ͣ�����·������
		{
			fPathName = DicList[1] + L"\\" + fName + L".eve";//1��event��2��text��3��unit��4��map
			if (PathFileExists(fPathName))
			{
				AfxMessageBox(L"���ļ��Ѿ����ڣ��볢�Ը����½����ļ����ƣ�");
				delete CDialognsw;
				return;
			}
			pMain->m_wndFileView.AddString(fName, 1);//��fileview�м�����ļ�
		}
		if (i == 2)
		{
		}
		CFile eventFile;//�½��հ��ļ�
		eventFile.Open(fPathName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
		eventFile.Close();
		theApp.OpenDocumentFile(fPathName);//�½�һ���հ��ĵ�
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
	if (sSelectParent == L"���¼�")
	{
		if (sSelect == L"��ʼ����")
		{
			theApp.OpenDocumentFile(Path��ʼ����);
		}
		if (sSelect == L"��������")
		{
			theApp.OpenDocumentFile(Path��������);
		}
	}
	if (sSelectParent == L"�������¼�")
	{
		if (sSelect == L"��ɫ�¼�")
		{
			theApp.OpenDocumentFile(Path��ɫ�¼�);
		}
		if (sSelect == L"��ͼ�¼�")
		{
			theApp.OpenDocumentFile(Path��ͼ�¼�);
		}
		if (sSelect == L"�غ��¼�")
		{
			theApp.OpenDocumentFile(Path�غ��¼�);
		}
		if (sSelect == L"Misc�¼�")
		{
			theApp.OpenDocumentFile(PathMisc�¼�);
		}
	}
	if (sSelectParent == L"�¼��ļ�")
	{
		theApp.OpenDocumentFile(DicList[1] + L"\\" + sSelect + L".eve");
	}
	if (sSelectParent == L"��������")
	{

	}
	if (sSelectParent == L"���ֶԻ�")
	{

	}
	if (sSelectParent == L"��ͼ")
	{

	}
	return true;
}

bool CMFCApplication3App::DeleteDocument(CString sSelectParent, CString sSelect)//ɾ��FileView�е��ļ�
{
	if (sSelectParent == L"�¼��ļ�")
	{
		DeleteFile(DicList[1] + L"\\" + sSelect);
	}
	if (sSelectParent == L"��������")
	{

	}
	if (sSelectParent == L"���ֶԻ�")
	{

	}
	if (sSelectParent == L"��ͼ")
	{

	}
	return true;
}
