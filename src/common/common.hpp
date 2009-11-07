
#ifndef _COMMON_HEADER_HPP_
#define _COMMON_HEADER_HPP_

#include <windows.h>
#include <wchar.h>
#if !defined(__GNUC__)
#include <crtdbg.h>
#else
#define _ASSERTE(f)
#endif

#include "usetodo.hpp"

//#define CONEMUPIPE      L"\\\\.\\pipe\\ConEmuPipe%u"
//#define CONEMUEVENTIN   L"ConEmuInEvent%u"
//#define CONEMUEVENTOUT  L"ConEmuOutEvent%u"
//#define CONEMUEVENTPIPE L"ConEmuPipeEvent%u"

#define MIN_CON_WIDTH 28
#define MIN_CON_HEIGHT 7
#define GUI_ATTACH_TIMEOUT 5000

// with line number
#if !defined(_MSC_VER)

    #define TODO(s)
    #define WARNING(s)
    #define PRAGMA_ERROR(s)

    //#define CONSOLE_APPLICATION_16BIT 1
    
    typedef struct _CONSOLE_SELECTION_INFO {
        DWORD dwFlags;
        COORD dwSelectionAnchor;
        SMALL_RECT srSelection;
    } CONSOLE_SELECTION_INFO, *PCONSOLE_SELECTION_INFO;

    #ifndef max
    #define max(a,b)            (((a) > (b)) ? (a) : (b))
    #endif

    #ifndef min
    #define min(a,b)            (((a) < (b)) ? (a) : (b))
    #endif

    #define _ASSERT(f)
    #define _ASSERTE(f)
    
#else

    #define STRING2(x) #x
    #define STRING(x) STRING2(x)
    #define FILE_LINE __FILE__ "(" STRING(__LINE__) "): "
    #ifdef HIDE_TODO
    #define TODO(s) 
    #define WARNING(s) 
    #else
    #define TODO(s) __pragma(message (FILE_LINE "TODO: " s))
    #define WARNING(s) __pragma(message (FILE_LINE "warning: " s))
    #endif
    #define PRAGMA_ERROR(s) __pragma(message (FILE_LINE "error: " s))

    #ifdef _DEBUG
    #include <crtdbg.h>
    #endif

#endif

#define countof(a) (sizeof((a))/(sizeof(*(a))))
#define ZeroStruct(s) memset(&(s), 0, sizeof(s))

#ifdef _DEBUG
extern wchar_t gszDbgModLabel[6];
#define CHEKCDBGMODLABEL if (gszDbgModLabel[0]==0) { \
	wchar_t szFile[MAX_PATH]; GetModuleFileName(NULL, szFile, MAX_PATH); \
	wchar_t* pszName = wcsrchr(szFile, L'\\'); \
	if (_wcsicmp(pszName, L"\\conemu.exe")==0) lstrcpyW(gszDbgModLabel, L"gui"); \
	else if (_wcsicmp(pszName, L"\\conemuc.exe")==0) lstrcpyW(gszDbgModLabel, L"srv"); \
	else lstrcpyW(gszDbgModLabel, L"dll"); \
}
#ifdef SHOWDEBUGSTR
#define DEBUGSTR(s) { MCHKHEAP; CHEKCDBGMODLABEL; SYSTEMTIME st; GetLocalTime(&st); wchar_t szDEBUGSTRTime[40]; wsprintf(szDEBUGSTRTime, L"%i:%02i:%02i.%03i(%s.%i) ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, gszDbgModLabel, GetCurrentThreadId()); OutputDebugString(szDEBUGSTRTime); OutputDebugString(s); }
#else
#define DEBUGSTR(s)
#endif
#else
#define DEBUGSTR(s)
#endif


#define CES_NTVDM 0x10
#define CEC_INITTITLE       L"ConEmu"
//#define CE_CURSORUPDATE     L"ConEmuCursorUpdate%u" // ConEmuC_PID - ��������� ������ (������ ��� ���������). ��������� ������� ����������� GUI

#define CESERVERPIPENAME    L"\\\\%s\\pipe\\ConEmuSrv%u"      // ConEmuC_PID
#define CESERVERINPUTNAME   L"\\\\%s\\pipe\\ConEmuSrvInput%u" // ConEmuC_PID
#define CEGUIPIPENAME       L"\\\\%s\\pipe\\ConEmuGui%u"      // GetConsoleWindow() // ����������, ����� ������ ��� �������� � GUI
#define CEPLUGINPIPENAME    L"\\\\%s\\pipe\\ConEmuPlugin%u"   // Far_PID
//#define CEGUIATTACHED       L"ConEmuGuiAttached.%u"
#define CEGUIRCONSTARTED    L"ConEmuGuiRConStarted.%u"
#define CEGUI_ALIVE_EVENT   L"ConEmuGuiStarted"
//#define CESIGNAL_C          L"ConEmuC_C_Signal.%u"
//#define CESIGNAL_BREAK      L"ConEmuC_Break_Signal.%u"
#define CECMD_GETSHORTINFO  1
#define CECMD_GETFULLINFO   2
#define CECMD_SETSIZE       3
#define CECMD_CMDSTARTSTOP  4 // 0 - ServerStart, 1 - ServerStop, 2 - ComspecStart, 3 - ComspecStop
#define CECMD_GETGUIHWND    5
//#define CECMD_RECREATE      6
#define CECMD_TABSCHANGED   7
#define CECMD_CMDSTARTED    8 // == CECMD_SETSIZE + ������������ ���������� ������� (���������� comspec)
#define CECMD_CMDFINISHED   9 // == CECMD_SETSIZE + ��������� ���������� ������� (���������� comspec)
#define CECMD_GETOUTPUTFILE 10 // �������� ����� ��������� ���������� ��������� �� ��������� ���� � ������� ��� ���
#define CECMD_GETOUTPUT     11
#define CECMD_LANGCHANGE    12
#define CECMD_NEWCMD        13 // ��������� � ���� ���������� ����� ������� � ���������� ��������
#define CECMD_TABSCMD       14 // 0: ��������/�������� ����, 1: ������� �� ���������, 2: ������� �� ����������, 3: commit switch
#define CECMD_RESOURCES     15 // ���������� �������� ��� ������������� (��������� ��������)
#define CECMD_GETNEWCONPARM 16 // ���.��������� ��� �������� ����� ������� (�����, ������,...)
#define CECMD_SETSIZESYNC   17 // ���������, ���� (�� �������), ���� FAR ���������� ��������� ������� (�� ���� ����������)
#define CECMD_ATTACH2GUI    18 // ��������� ����������� ������� (�����������) ������� � GUI. ��� ����������
#define CECMD_FARLOADED     19 // ���������� �������� � ������
#define CECMD_SHOWCONSOLE   20 // � Win7 ������ ������ �������� ���� �������, ���������� � ������ ��������������
#define CECMD_POSTCONMSG    21 // � Win7 ������ ������ �������� ��������� ���� �������, ���������� � ������ ��������������
#define CECMD_REQUESTFULLINFO 22

#define CESERVER_REQ_VER    19

#define PIPEBUFSIZE 4096



//#pragma pack(push, 1)
#include <pshpack1.h>

#define u64 unsigned __int64
typedef struct tag_HWND2 {
	u64 u;
	operator HWND() {
		return (HWND)u;
	};
	operator DWORD() {
		return (DWORD)u;
	};
	struct tag_HWND2& operator=(HWND h) {
		u = (u64)h;
		return *this;
	};
} HWND2;

TODO("Restrict CONEMUTABMAX to 128 chars. Only filename, and may be ellipsed...");
#define CONEMUTABMAX 0x400
typedef struct tag_ConEmuTab {
	int  Pos;
	int  Current;
	int  Type; // Panels=1, Viewer=2, Editor=3
	int  Modified;
	wchar_t Name[CONEMUTABMAX];
	//  int  Modified;
	//  int isEditor;
} ConEmuTab;

typedef struct tag_CESERVER_REQ_CONEMUTAB {
	DWORD nTabCount;
	BOOL  bMacroActive;
	BOOL  bMainThread;
	ConEmuTab tabs[1];
} CESERVER_REQ_CONEMUTAB;

typedef struct tag_CESERVER_REQ_CONEMUTAB_RET {
	BOOL  bNeedPostTabSend;
	BOOL  bNeedResize;
	COORD crNewSize;
} CESERVER_REQ_CONEMUTAB_RET;

typedef struct tag_ForwardedPanelInfo {
	RECT ActiveRect;
	RECT PassiveRect;
	int ActivePathShift; // ����� � ���� ��������� � ������
	int PassivePathShift; // ����� � ���� ��������� � ������
	union { //x64 ready
		WCHAR* pszActivePath/*[MAX_PATH+1]*/;
		u64 Reserved1;
	};
	union { //x64 ready
		WCHAR* pszPassivePath/*[MAX_PATH+1]*/;
		u64 Reserved2;
	};
} ForwardedPanelInfo;

typedef struct tag_FarVersion {
	union {
		DWORD dwVer;
		struct {
			WORD dwVerMinor;
			WORD dwVerMajor;
		};
	};
	DWORD dwBuild;
} FarVersion;

typedef struct tag_ForwardedFileInfo {
	WCHAR Path[MAX_PATH+1];
} ForwardedFileInfo;


typedef struct tag_CESERVER_REQ_HDR {
	DWORD   nSize;
	DWORD   nCmd;
	DWORD   nVersion;
	DWORD   nSrcThreadId;
	DWORD   nSrcPID;
#ifdef _DEBUG
	DWORD   nCreateTick;
#endif
} CESERVER_REQ_HDR;


typedef struct tag_CESERVER_CHAR_HDR {
	int   nSize;    // ������ ��������� ������������. ���� 0 - ������ ������������� is NULL
	COORD cr1, cr2; // WARNING: ��� ���������� ���������� (��� ����� ���������), � �� ��������.
} CESERVER_CHAR_HDR;

typedef struct tag_CESERVER_CHAR {
	CESERVER_CHAR_HDR hdr; // ������������� �����
	WORD  data[2];  // variable(!) length
} CESERVER_CHAR;

typedef struct tag_CESERVER_CONSAVE_HDR {
	CESERVER_REQ_HDR hdr; // ����������� ������ ����� �������� � ������
	CONSOLE_SCREEN_BUFFER_INFO sbi;
	DWORD cbMaxOneBufferSize;
} CESERVER_CONSAVE_HDR;

typedef struct tag_CESERVER_CONSAVE {
	CESERVER_CONSAVE_HDR hdr;
	wchar_t Data[1];
} CESERVER_CONSAVE;



typedef struct tag_CESERVER_REQ_RGNINFO {
	DWORD dwRgnInfoSize;
	CESERVER_CHAR RgnInfo;
} CESERVER_REQ_RGNINFO;

typedef struct tag_CESERVER_REQ_FULLCONDATA {
	DWORD dwRgnInfoSize_MustBe0; // must be 0
	DWORD dwOneBufferSize; // may be 0
	wchar_t Data[300]; // Variable length!!!
} CESERVER_REQ_FULLCONDATA;

typedef struct tag_CESERVER_REQ_CONINFO_HDR {
	/* 1*/HWND2 hConWnd;
	/* 2*/DWORD nPacketId;
	      DWORD nInputTID;
	/* 3*/DWORD nProcesses[20];
    /* 4*/DWORD dwCiSize;
	      CONSOLE_CURSOR_INFO ci;
    /* 5*/DWORD dwConsoleCP;
	/* 6*/DWORD dwConsoleOutputCP;
	/* 7*/DWORD dwConsoleMode;
	/* 8*/DWORD dwSbiSize;
	      CONSOLE_SCREEN_BUFFER_INFO sbi;
} CESERVER_REQ_CONINFO_HDR;

typedef struct tag_CESERVER_REQ_CONINFO {
	CESERVER_REQ_CONINFO_HDR inf;
    union {
	/* 9*/DWORD dwRgnInfoSize;
	      CESERVER_REQ_RGNINFO RgnInfo;
    /*10*/CESERVER_REQ_FULLCONDATA FullData;
	};
} CESERVER_REQ_CONINFO;

typedef struct tag_CESERVER_REQ_SETSIZE {
	USHORT nBufferHeight; // 0 ��� ������ ������ (����� � ����������)
	COORD  size;
	SHORT  nSendTopLine;  // -1 ��� 0based ����� ������ ��������������� � GUI (������ ��� ������ � ����������)
	SMALL_RECT rcWindow;  // ���������� ������� ������� ��� ������ � ����������
	DWORD  dwFarPID;      // ���� �������� - ������ ������ ��� ����������� �� FAR'� � �������� ��� ������ ����� ������ ����� ���������
} CESERVER_REQ_SETSIZE;

typedef struct tag_CESERVER_REQ_OUTPUTFILE {
	BOOL  bUnicode;
	WCHAR szFilePathName[MAX_PATH+1];
} CESERVER_REQ_OUTPUTFILE;

typedef struct tag_CESERVER_REQ_RETSIZE {
	DWORD nNextPacketId;
	CONSOLE_SCREEN_BUFFER_INFO SetSizeRet;
} CESERVER_REQ_RETSIZE;

typedef struct tag_CESERVER_REQ_NEWCMD {
	wchar_t szCurDir[MAX_PATH];
	wchar_t szCommand[MAX_PATH]; // �� ����� ���� - variable_size !!!
} CESERVER_REQ_NEWCMD;

typedef struct tag_CESERVER_REQ_STARTSTOP {
	DWORD nStarted; // 0 - ServerStart, 1 - ServerStop, 2 - ComspecStart, 3 - ComspecStop
	HWND2 hWnd; // ��� �������� � GUI - �������, ��� �������� � ������� - GUI
	DWORD dwPID, dwInputTID;
	DWORD nSubSystem; // 255 ��� DOS ��������, 0x100 - ����� �� FAR �������
	BOOL  bRootIsCmdExe;
	// � ��� �������� �� �������, ������ ���������� ��������� ������ �������� ������ ������
	CONSOLE_SCREEN_BUFFER_INFO sbi;
} CESERVER_REQ_STARTSTOP;

typedef struct tag_CESERVER_REQ_STARTSTOPRET {
	BOOL  bWasBufferHeight;
	HWND2 hWnd; // ��� �������� � GUI - �������, ��� �������� � ������� - GUI
	DWORD dwPID;
	DWORD nBufferHeight, nWidth, nHeight;
} CESERVER_REQ_STARTSTOPRET;

typedef struct tag_CESERVER_REQ_POSTMSG {
	BOOL    bPost;
	UINT    nMsg;
	// ��������� �� ���������� x86 & x64
	u64     wParam, lParam;
} CESERVER_REQ_POSTMSG;

typedef struct tag_CESERVER_REQ {
    CESERVER_REQ_HDR hdr;
	union {
		BYTE    Data[1]; // variable(!) length
		WORD    wData[1];
		DWORD   dwData[1];
		u64     qwData[1];
		CESERVER_REQ_CONINFO ConInfo; // Informational only! Some fields ARE VARIABLE LENGTH
		CESERVER_REQ_SETSIZE SetSize;
		CESERVER_REQ_RETSIZE SetSizeRet;
		CESERVER_REQ_OUTPUTFILE OutputFile;
		CESERVER_REQ_NEWCMD NewCmd;
		CESERVER_REQ_STARTSTOP StartStop;
		CESERVER_REQ_STARTSTOPRET StartStopRet;
		CESERVER_REQ_CONEMUTAB Tabs;
		CESERVER_REQ_CONEMUTAB_RET TabsRet;
		CESERVER_REQ_POSTMSG Msg;
	};
} CESERVER_REQ;


//#pragma pack(pop)
#include <poppack.h>


#define CONEMUMSG_ATTACH L"ConEmuMain::Attach"            // wParam == hConWnd, lParam == ConEmuC_PID
#define CONEMUMSG_SRVSTARTED L"ConEmuMain::SrvStarted"    // wParam == hConWnd, lParam == ConEmuC_PID
#define CONEMUMSG_SETFOREGROUND L"ConEmuMain::SetForeground"            // wParam == hConWnd, lParam == ConEmuC_PID
#define CONEMUMSG_FLASHWINDOW L"ConEmuMain::FlashWindow"
//#define CONEMUCMDSTARTED L"ConEmuMain::CmdStarted"    // wParam == hConWnd, lParam == ConEmuC_PID (as ComSpec)
//#define CONEMUCMDSTOPPED L"ConEmuMain::CmdTerminated" // wParam == hConWnd, lParam == ConEmuC_PID (as ComSpec)

//#define CONEMUMAPPING    L"ConEmuPluginData%u"
//#define CONEMUDRAGFROM   L"ConEmuDragFrom%u"
//#define CONEMUDRAGTO     L"ConEmuDragTo%u"
//#define CONEMUREQTABS    L"ConEmuReqTabs%u"
//#define CONEMUSETWINDOW  L"ConEmuSetWindow%u"
//#define CONEMUPOSTMACRO  L"ConEmuPostMacro%u"
//#define CONEMUDEFFONT    L"ConEmuDefFont%u"
//#define CONEMULANGCHANGE L"ConEmuLangChange%u"
//#define CONEMUEXIT       L"ConEmuExit%u"
//#define CONEMUALIVE      L"ConEmuAlive%u"
//#define CONEMUREADY      L"ConEmuReady%u"
#define CONEMUTABCHANGED L"ConEmuTabsChanged"
#define CMD_DRAGFROM     0
#define CMD_DRAGTO       1
#define CMD_REQTABS      2
#define CMD_SETWINDOW    3
#define CMD_POSTMACRO    4 // ���� ������ ������ ������� '@' � ����� ���� �� ������ - ������ ����������� � DisabledOutput
//#define CMD_DEFFONT    5
#define CMD_LANGCHANGE   6
#define CMD_SETENVVAR    7 // ���������� ���������� ��������� (FAR plugin)
#define CMD_SETSIZE      8
// +2
#define MAXCMDCOUNT      10
#define CMD_EXIT         MAXCMDCOUNT-1

//#define GWL_TABINDEX     0
//#define GWL_LANGCHANGE   4

#ifdef _DEBUG
    #define CONEMUALIVETIMEOUT INFINITE
    #define CONEMUREADYTIMEOUT INFINITE
    #define CONEMUFARTIMEOUT   120000 // ������� �������, ���� ��� ���������� �� ����� �������
#else
    #define CONEMUALIVETIMEOUT 1000  // ������� ������� ���� �������
    #define CONEMUREADYTIMEOUT 10000 // � �� ���������� ������� - 10s max
    #define CONEMUFARTIMEOUT   10000 // ������� �������, ���� ��� ���������� �� ����� �������
#endif



/*enum PipeCmd
{
    SetTabs=0,
    DragFrom,
    DragTo
};*/

// ConEmu.dll ������������ ��������� �������
//HWND WINAPI GetFarHWND();
//void WINAPI _export GetFarVersion ( FarVersion* pfv );

//#if defined(__GNUC__)
////typedef DWORD   HWINEVENTHOOK;
//#define WINEVENT_OUTOFCONTEXT   0x0000  // Events are ASYNC
//// User32.dll
//typedef HWINEVENTHOOK (WINAPI* FSetWinEventHook)(DWORD eventMin, DWORD eventMax, HMODULE hmodWinEventProc, WINEVENTPROC pfnWinEventProc, DWORD idProcess, DWORD idThread, DWORD dwFlags);
//typedef BOOL (WINAPI* FUnhookWinEvent)(HWINEVENTHOOK hWinEventHook);
//#endif


#ifdef __cplusplus


#define CERR_CMDLINEEMPTY 200
#define CERR_CMDLINE      201

#define MOUSE_EVENT_MOVE      (WM_APP+10)
#define MOUSE_EVENT_CLICK     (WM_APP+11)
#define MOUSE_EVENT_DBLCLICK  (WM_APP+12)
#define MOUSE_EVENT_WHEELED   (WM_APP+13)
#define MOUSE_EVENT_HWHEELED  (WM_APP+14)
#define MOUSE_EVENT_FIRST MOUSE_EVENT_MOVE
#define MOUSE_EVENT_LAST MOUSE_EVENT_HWHEELED

#define INPUT_THREAD_ALIVE_MSG (WM_APP+100)

#define MAX_INPUT_QUEUE_EMPTY_WAIT 100


int NextArg(const wchar_t** asCmdLine, wchar_t* rsArg/*[MAX_PATH+1]*/);
BOOL PackInputRecord(const INPUT_RECORD* piRec, MSG* pMsg);
BOOL UnpackInputRecord(const MSG* piMsg, INPUT_RECORD* pRec);
SECURITY_ATTRIBUTES* NullSecurity();
wchar_t* GetShortFileNameEx(LPCWSTR asLong);

//------------------------------------------------------------------------
///| Section |////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
class MSectionLock;

class MSection
{
protected:
	CRITICAL_SECTION m_cs;
	DWORD mn_TID; // ��������������� ������ ����� EnterCriticalSection
	int mn_Locked;
	BOOL mb_Exclusive;
	HANDLE mh_ReleaseEvent;
	friend class MSectionLock;
	DWORD mn_LockedTID[10];
	int   mn_LockedCount[10];
public:
	MSection() {
		mn_TID = 0; mn_Locked = 0; mb_Exclusive = FALSE;
		ZeroStruct(mn_LockedTID); ZeroStruct(mn_LockedCount);
		InitializeCriticalSection(&m_cs);
		mh_ReleaseEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		_ASSERTE(mh_ReleaseEvent!=NULL);
		if (mh_ReleaseEvent) ResetEvent(mh_ReleaseEvent);
	};
	~MSection() {
		DeleteCriticalSection(&m_cs);
		if (mh_ReleaseEvent) {
			CloseHandle(mh_ReleaseEvent); mh_ReleaseEvent = NULL;
		}
	};
public:
	void ThreadTerminated(DWORD dwTID) {
		for (int i=1; i<10; i++) {
			if (mn_LockedTID[i] == dwTID) {
				mn_LockedTID[i] = 0;
				if (mn_LockedCount[i] != 0) {
					_ASSERTE(mn_LockedCount[i] == 0);
				}
				break;
			}
		}
	};
protected:
	void AddRef(DWORD dwTID) {
		mn_Locked ++; // ����������� ������� nonexclusive locks
		_ASSERTE(mn_Locked>0);
		ResetEvent(mh_ReleaseEvent); // �� ������ ������ ������� Event
		int j = -1; // ����� -2, ���� ++ �� ������������, ����� - +1 �� ������
		for (int i=1; i<10; i++) {
			if (mn_LockedTID[i] == dwTID) {
				mn_LockedCount[i] ++; 
				j = -2; 
				break;
			} else if (j == -1 && mn_LockedTID[i] == 0) {
				mn_LockedTID[i] = dwTID;
				mn_LockedCount[i] ++; 
				j = i;
				break;
			}
		}
		if (j == -1) { // ����� ���� �� ������
			_ASSERTE(j != -1);
		}
	};
	int ReleaseRef(DWORD dwTID) {
		_ASSERTE(mn_Locked>0);
		int nInThreadLeft = 0;
		if (mn_Locked > 0) mn_Locked --;
		if (mn_Locked == 0)
			SetEvent(mh_ReleaseEvent); // ������ nonexclusive locks �� ��������
		for (int i=1; i<10; i++) {
			if (mn_LockedTID[i] == dwTID) {
				mn_LockedCount[i] --; 
				if ((nInThreadLeft = mn_LockedCount[i]) == 0)
					mn_LockedTID[i] = 0; // ����� ��� ����������� ����������� ����� - 10 ����� � ������ ������������
				break;
			}
		}
		return nInThreadLeft;
	};
	void WaitUnlocked(DWORD dwTID, DWORD anTimeout) {
		DWORD dwStartTick = GetTickCount();
		int nSelfCount = 0;
		for (int i=1; i<10; i++) {
			if (mn_LockedTID[i] == dwTID) {
				nSelfCount = mn_LockedCount[i];
				break;
			}
		}
		while (mn_Locked > nSelfCount) {
			#ifdef _DEBUG
			DEBUGSTR(L"!!! Waiting for exclusive access\n");

			DWORD nWait = 
			#endif

			WaitForSingleObject(mh_ReleaseEvent, 10);

			DWORD dwCurTick = GetTickCount();
			DWORD dwDelta = dwCurTick - dwStartTick;

			if (anTimeout != (DWORD)-1) {
				if (dwDelta > anTimeout) {
					#ifndef CSECTION_NON_RAISE
					_ASSERTE(dwDelta<=anTimeout);
					#endif
					break;
				}
			}
			#ifdef _DEBUG
			else if (dwDelta > 3000) {
				#ifndef CSECTION_NON_RAISE
				_ASSERTE(dwDelta <= 3000);
				#endif
				break;
			}
			#endif
		}
	};
	bool MyEnterCriticalSection(DWORD anTimeout) {
		//EnterCriticalSection(&m_cs); 
		// ��������� ���� ������ ��������

		// ����. �.�. ����� ���� ����� nTimeout (��� DC)
		DWORD dwTryLockSectionStart = GetTickCount(), dwCurrentTick;

		if (!TryEnterCriticalSection(&m_cs)) {
			Sleep(10);
			while (!TryEnterCriticalSection(&m_cs)) {
				Sleep(10);
				DEBUGSTR(L"TryEnterCriticalSection failed!!!\n");

				dwCurrentTick = GetTickCount();
				if (anTimeout != (DWORD)-1) {
					if (((dwCurrentTick - dwTryLockSectionStart) > anTimeout)) {
						#ifndef CSECTION_NON_RAISE
						_ASSERTE((dwCurrentTick - dwTryLockSectionStart) <= anTimeout);
						#endif
						return false;
					}
				}
				#ifdef _DEBUG
				else if ((dwCurrentTick - dwTryLockSectionStart) > 3000) {
					#ifndef CSECTION_NON_RAISE
					_ASSERTE((dwCurrentTick - dwTryLockSectionStart) <= 3000);
					#endif
					dwTryLockSectionStart = GetTickCount();
				}
				#endif
			}
		}

		return true;
	}
	BOOL Lock(BOOL abExclusive, DWORD anTimeout=-1/*, BOOL abRelockExclusive=FALSE*/) {
		DWORD dwTID = GetCurrentThreadId();
		
		// ����� ��� ���� ��� ��������� �������������?
		if (mb_Exclusive && dwTID == mn_TID) {
			return FALSE; // ���, �� Unlock ������ �� �����!
		}
		
		if (!abExclusive) {
			// ������� ����������, �� ����������� ������ ������ �����.
			// ��������� ������ ��������� (������������ ������ ��������)
			AddRef(dwTID);
			
			// ���� ������ ���� ��� ��������� exclusive
			if (mb_Exclusive) {
				int nLeft = ReleaseRef(dwTID); // ����� ����� ������� �� �������� ����������
				if (nLeft > 0) {
					_ASSERTE(nLeft == 0);
				}

				DEBUGSTR(L"!!! Failed non exclusive lock, trying to use CriticalSection\n");
				bool lbEntered = MyEnterCriticalSection(anTimeout); // ��������� ���� ������ ��������
				_ASSERTE(!mb_Exclusive); // ����� LeaveCriticalSection mb_Exclusive ��� ������ ���� �������

				AddRef(dwTID); // ���������� ����������

				// �� ��������� ��� ����� ������ nonexclusive lock
				if (lbEntered)
					LeaveCriticalSection(&m_cs);
			}
		} else {
			// ��������� Exclusive Lock

			#ifdef _DEBUG
			if (mb_Exclusive) {
				// ����� ���� ��������� ��������
				DEBUGSTR(L"!!! Exclusive lock found in other thread\n");
			}
			#endif
			
			// ���� ���� ExclusiveLock (� ������ ����) - �������� ���� EnterCriticalSection
			#ifdef _DEBUG
			BOOL lbPrev = mb_Exclusive;
			DWORD nPrevTID = mn_TID;
			#endif
			mb_Exclusive = TRUE; // �����, ����� � nonexclusive �� ���������
			TODO("Need to check, if MyEnterCriticalSection failed on timeout!\n");
			MyEnterCriticalSection(anTimeout);
			_ASSERTE(!(lbPrev && mb_Exclusive)); // ����� LeaveCriticalSection mb_Exclusive ��� ������ ���� �������
			mb_Exclusive = TRUE; // ���� ����� �������� ������ ����, ����������� Leave
			mn_TID = dwTID; // � ��������, � ����� ���� ��� ���������
			_ASSERTE(mn_LockedTID[0] == 0 && mn_LockedCount[0] == 0);
			mn_LockedTID[0] = dwTID;
			mn_LockedCount[0] ++;

			/*if (abRelockExclusive) {
				ReleaseRef(dwTID); // ���� �� ����� ��� nonexclusive lock
			}*/

			// B ���� ���� nonexclusive locks - ��������� �� ����������
			if (mn_Locked) {
				//WARNING: ��� ���� ���� ����������, ���� ������� ��� NonExclusive, � ����� � ���� �� ���� - Exclusive
				// � ����� ������� ����� �������� � ���������� abRelockExclusive
				WaitUnlocked(dwTID, anTimeout);
			}
		}
		
		return TRUE;
	};
	void Unlock(BOOL abExclusive) {
		DWORD dwTID = GetCurrentThreadId();
		if (abExclusive) {
			_ASSERTE(dwTID == dwTID && mb_Exclusive);
			_ASSERTE(mn_LockedTID[0] == dwTID);
			mb_Exclusive = FALSE; mn_TID = 0;
			mn_LockedTID[0] = 0; mn_LockedCount[0] --;
			LeaveCriticalSection(&m_cs);
		} else {
			ReleaseRef(dwTID);
		}
	};
};

class MSectionThread
{
protected:
	MSection* mp_S;
	DWORD mn_TID;
public:
	MSectionThread(MSection* apS) {
		mp_S = apS; mn_TID = GetCurrentThreadId();
	};
	~MSectionThread() {
		if (mp_S && mn_TID)
			mp_S->ThreadTerminated(mn_TID);
	};
};

class MSectionLock
{
protected:
	MSection* mp_S;
	BOOL mb_Locked, mb_Exclusive;
public:
	BOOL Lock(MSection* apS, BOOL abExclusive=FALSE, DWORD anTimeout=-1) {
		if (mb_Locked && apS == mp_S && (abExclusive == mb_Exclusive || mb_Exclusive))
			return FALSE; // ��� ������������
		_ASSERTE(!mb_Locked);
		mb_Exclusive = abExclusive;
		mp_S = apS;
		mb_Locked = mp_S->Lock(mb_Exclusive, anTimeout);
		return mb_Locked;
	};
	BOOL RelockExclusive(DWORD anTimeout=-1) {
		if (mb_Locked && mb_Exclusive) return FALSE; // ���
		// ������ ReLock ������ ������. ������ ������ ����, ������� ���� ��������� ReLock
		Unlock();
		mb_Exclusive = TRUE;
		mb_Locked = mp_S->Lock(mb_Exclusive, anTimeout);
		return mb_Locked;
	};
	void Unlock() {
		if (mp_S && mb_Locked) {
			mp_S->Unlock(mb_Exclusive);
			mb_Locked = FALSE;
		}
	};
	BOOL isLocked() {
		return (mp_S!=NULL) && mb_Locked;
	};
public:
	MSectionLock() {
		mp_S = NULL; mb_Locked = FALSE; mb_Exclusive = FALSE;
	};
	~MSectionLock() {
		if (mb_Locked) Unlock();
	};
};


/* Console Handles */
class MConHandle {
private:
	wchar_t   ms_Name[10];
	HANDLE    mh_Handle;
	MSection  mcs_Handle;

public:
	operator const HANDLE()
	{
		if (mh_Handle == INVALID_HANDLE_VALUE)
		{
			// ����� �������� �� ������� ����� ��������� ��� � ������ �������
			MSectionLock CS; CS.Lock(&mcs_Handle, TRUE);
			// �� ����� �������� ����� ��� ��� ������ � ������ ������
			if (mh_Handle == INVALID_HANDLE_VALUE) {
				mh_Handle = CreateFile(ms_Name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_READ,
					0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
				if (mh_Handle == INVALID_HANDLE_VALUE) {
					DWORD dwErr = GetLastError();
					wprintf(L"CreateFile(%s) failed, ErrCode=0x%08X\n", ms_Name, dwErr); 
				}
			}
		}
		return mh_Handle;
	};

public:
	void Close()
	{
		if (mh_Handle != INVALID_HANDLE_VALUE) {
			HANDLE h = mh_Handle;
			mh_Handle = INVALID_HANDLE_VALUE;
			CloseHandle(h);
		}
	};

public:
	MConHandle(LPCWSTR asName)
	{
		mh_Handle = INVALID_HANDLE_VALUE;
		lstrcpynW(ms_Name, asName, 9);
	};

	~MConHandle()
	{
		Close();
	};

};


//class CSection
//{
//protected:
//	CRITICAL_SECTION* mp_cs;
//	DWORD* mp_TID;
//public:
//	void Leave()
//	{
//		if (mp_cs) {
//			*mp_TID = 0;
//			mp_TID = NULL;
//			//OutputDebugString(_T("LeaveCriticalSection\n"));
//			LeaveCriticalSection(mp_cs);
//			#ifdef _DEBUG
//			#ifndef CSECTION_NON_RAISE
//			_ASSERTE(mp_cs->LockCount==-1);
//			#endif
//			#endif
//			mp_cs = NULL;
//		}
//	}
//	bool Enter(CRITICAL_SECTION* pcs, DWORD* pTID, DWORD nTimeout=(DWORD)-1)
//	{
//		#ifdef _DEBUG
//		if (*((DWORD_PTR*)pcs) == NULL) {
//			_ASSERTE(*((DWORD_PTR*)pcs) != NULL);
//		}
//		#endif
//		Leave(); // ���� ����
//
//		mp_TID = pTID;
//		DWORD dwTID = GetCurrentThreadId();
//		if (dwTID == *pTID)
//			return true; // � ���� ���� ��� �������������
//
//		mp_cs = pcs;
//		if (mp_cs) {
//			//OutputDebugString(_T("TryEnterCriticalSection\n"));
//			
//			// ����. �.�. ����� ���� ����� nTimeout (��� DC)
//			DWORD dwTryLockSectionStart = GetTickCount(), dwCurrentTick;
//			
//			if (!TryEnterCriticalSection(mp_cs)) {
//				Sleep(50);
//				while (!TryEnterCriticalSection(mp_cs)) {
//					Sleep(50);
//					DEBUGSTR(L"TryEnterCriticalSection failed!!!\n");
//					
//					dwCurrentTick = GetTickCount();
//					if ((nTimeout != (DWORD)-1) && ((dwCurrentTick - dwTryLockSectionStart) > nTimeout)) {
//						mp_TID = NULL; mp_cs = NULL;
//						DEBUGSTR(L"TryEnterCriticalSection Timeout!!!\n");
//						return false;
//					}
//					
//					#ifdef _DEBUG
//					if ((dwCurrentTick - dwTryLockSectionStart) > 3000) {
//						#ifndef CSECTION_NON_RAISE
//						_ASSERTE((dwCurrentTick - dwTryLockSectionStart) <= 3000);
//						#endif
//						dwTryLockSectionStart = GetTickCount();
//					}
//					#endif
//				}
//			}
//			//EnterCriticalSection(mp_cs);
//			*mp_TID = dwTID;
//		}
//		return true;
//	}
//	bool isLocked()
//	{
//		if (mp_cs)
//			return true;
//		// ��� ���� ������������ �� ������ ���� � ���� �� �������
//		if (mp_TID) {
//			DWORD dwTID = GetCurrentThreadId();
//			if (*mp_TID == dwTID)
//				return true;
//		}
//		return false;
//	}
//	CSection (CRITICAL_SECTION* pcs, DWORD* pTID) : mp_cs(NULL), mp_TID(NULL)
//	{
//		if (pcs) Enter(pcs, pTID);
//	}
//	~CSection()
//	{
//		Leave();
//	}
//};
#endif // __cplusplus



// This must be the end line
#endif // _COMMON_HEADER_HPP_
