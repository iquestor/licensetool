
#include "StdAfx.h"
#include "ActivationWizard.h"
#include "resource.h"

#include <string>

#include "../../generator/license.h"

std::wstring g_uniqueid;

#define KEY_SOFTWARE_IQAGENT L"Software\\iQagent"
#define KEY_SOFTWARE_MICROSOFT L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"

void SaveRegistry(const wchar_t * key, const wchar_t * name, const wchar_t * value);
void LoadRegistry(const wchar_t * key, const wchar_t * name, std::wstring & value);

bool is64bit()
{
	bool ret;
#if defined(_WIN64)
	ret = true;
#elif defined(_WIN32)
	BOOL f64 = false;
	ret = IsWow64Process(GetCurrentProcess(), &f64) && f64;
#else
	ret = false;
#endif
	return ret;
}

bool aero()
{
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);

	return osvi.dwMajorVersion >= 6;
}

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    std::wstring r(len, L'\0');
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, &r[0], len);
    return r;
}

std::string ws2s(const std::wstring& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0); 
    std::string r(len, '\0');
    WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, &r[0], len, 0, 0); 
    return r;
}

ActivationWizard::ActivationWizard(void)
{

}

ActivationWizard::~ActivationWizard(void)
{
}

void ActivationWizard::Launch(HINSTANCE hInst)
{
    ZeroMemory(&propsheetheader_, sizeof(propsheetheader_));

	PROPSHEETPAGE psp = { 0 };

	psp.dwSize = sizeof(psp);
	psp.hInstance = hInst;
	psp.lParam = 0;

    psp.dwFlags = PSP_DEFAULT | PSP_USEHEADERTITLE | PSP_USEHEADERSUBTITLE;
    psp.pszTemplate = (LPCWSTR)IDD_PROPPAGE_STEP_ONE;
	psp.pszHeaderTitle =
		aero() ? MAKEINTRESOURCE(IDS_STRING_HEADER_SUBTITLE_STEP_ONE) :
		MAKEINTRESOURCE(IDS_STRING_HEADER_TITLE_STEP_ONE)
	;
	psp.pszHeaderSubTitle = MAKEINTRESOURCE(IDS_STRING_HEADER_SUBTITLE_STEP_ONE);
	psp.pfnDlgProc = StepOneProc;

	propsheetpages_[0] = CreatePropertySheetPage(&psp);

    psp.dwFlags = PSP_DEFAULT | PSP_USEHEADERTITLE | PSP_USEHEADERSUBTITLE;
    psp.pszTemplate = (LPCWSTR)IDD_PROPPAGE_STEP_TWO;
	psp.pszHeaderTitle =
		aero() ? MAKEINTRESOURCE(IDS_STRING_HEADER_SUBTITLE_STEP_TWO) :
		MAKEINTRESOURCE(IDS_STRING_HEADER_TITLE_STEP_TWO)
	;
	psp.pszHeaderSubTitle = MAKEINTRESOURCE(IDS_STRING_HEADER_SUBTITLE_STEP_TWO);
	psp.pfnDlgProc = StepTwoProc;

	propsheetpages_[1] = CreatePropertySheetPage(&psp);

    psp.dwFlags = PSP_DEFAULT | PSP_USEHEADERTITLE | PSP_USEHEADERSUBTITLE;
    psp.pszTemplate = (LPCWSTR)IDD_PROPPAGE_STEP_THREE;
	psp.pszHeaderTitle =
		aero() ? MAKEINTRESOURCE(IDS_STRING_HEADER_SUBTITLE_STEP_THREE) :
		MAKEINTRESOURCE(IDS_STRING_HEADER_TITLE_STEP_THREE)
	;
	psp.pszHeaderSubTitle = MAKEINTRESOURCE(IDS_STRING_HEADER_SUBTITLE_STEP_THREE);
	psp.pfnDlgProc = StepThreeProc;

	propsheetpages_[2] = CreatePropertySheetPage(&psp);

	propsheetheader_.dwSize = sizeof(PROPSHEETHEADER);
	propsheetheader_.hwndParent = 0;
    propsheetheader_.dwFlags = aero() ? (PSH_WIZARD | PSH_AEROWIZARD) : (PSH_WIZARD97 | PSH_HEADER);
    propsheetheader_.hInstance = hInst;
    propsheetheader_.pszCaption = MAKEINTRESOURCE(IDS_APP_TITLE);
    propsheetheader_.nPages = 3;
    propsheetheader_.nStartPage = 0;
	propsheetheader_.phpage = propsheetpages_;
	propsheetheader_.pszbmHeader = MAKEINTRESOURCE(IDB_BITMAP_HEADER);

    PropertySheet(&propsheetheader_);
}

INT_PTR CALLBACK ActivationWizard::StepOneProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_ERASEBKGND:
		return 0;
		case WM_INITDIALOG:
		{

		}
		break;
		case WM_SHOWWINDOW:
		{

		}
		break;
		case WM_NOTIFY:
		{
			switch (((NMHDR *)lParam)->code)
			{
				case PSN_SETACTIVE:
				{
					PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_NEXT);

					std::wstring product_id;

					LoadRegistry(KEY_SOFTWARE_MICROSOFT, L"ProductId", product_id);

					g_uniqueid = product_id;

					SetWindowText(GetDlgItem(hDlg, IDC_EDIT_STEP_ONE_SYSTEM_ID), g_uniqueid.c_str());
				}
				break;
				case PSN_QUERYCANCEL:
				{
					SetWindowLong(hDlg, 0 /*DWL_MSGRESULT*/, false);
					exit(0);
				}
				break;
				case PSN_RESET:
				{

				}
				break;
				case PSN_WIZNEXT:
				{

				}
				break;
				case NM_CLICK:
				{
					if (wParam  == IDC_SYSLINK_CONTACT)
					{
						ShellExecute(NULL, L"open", L"http://www.iquestcorp.com/contact-us", 0, 0, SW_SHOWNORMAL);
					}
				}
				break;
			}
			break;
		}
		break;
		case WM_COMMAND:
		{

		}
		break;
		default:
			return 0;
	}
	return 0;
}

INT_PTR CALLBACK ActivationWizard::StepTwoProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_ERASEBKGND:
		return 0;
		case WM_INITDIALOG:
		{

		}
		break;
		case WM_SHOWWINDOW:
		{

		}
		break;
		case WM_NOTIFY:
		{
			switch (((NMHDR *)lParam)->code)
			{
				case PSN_SETACTIVE:
				{
					PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK | PSWIZB_NEXT);

					std::wstring license;

					LoadRegistry(KEY_SOFTWARE_IQAGENT, L"license", license);

					SetWindowText(GetDlgItem(hDlg, IDC_EDIT_STEP_TWO_LICENSE_KEY), license.c_str());
				}
				break;
				case PSN_QUERYCANCEL:
				{
					SetWindowLong(hDlg, 0 /*DWL_MSGRESULT*/, false);
					exit(0);
				}
				break;
				case PSN_RESET:
				{

				}
				break;
				case PSN_WIZBACK:
				{

				}
				break;
				case PSN_WIZNEXT:
				{
					wchar_t license[4096] = { 0 };

					GetWindowText(GetDlgItem(hDlg, IDC_EDIT_STEP_TWO_LICENSE_KEY), license, 4096);

					std::string narrow = ws2s(license);

					unsigned limit = 0;
#if 0
					if (validate_license("GYXUWBBVKEAEQUAJJJDVSCSHKRFHGQASIICBAVSH", &limit, "p@$$w0rd") == 0)
#else
					if (validate_license(narrow.c_str(), &limit, ws2s(g_uniqueid).c_str()) == 0)
#endif
					{
						wchar_t buf[512] = { 0 };

						wsprintf(buf, L"License limit: %d.\n", limit);

						OutputDebugString(buf);

						SaveRegistry(KEY_SOFTWARE_IQAGENT, L"license", license);
					}
					else
					{
						MessageBox(0, L"The product license you have entered is invalid.", L"Error", MB_OK | MB_ICONERROR);

						SetWindowLong(hDlg, 0 /*DWL_MSGRESULT*/, -1);

						return true;
					}
				}
				break;
			}
			break;
		}
		break;
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				default:
				break;
			}
			break;
		}
		break;
		default:
			return 0;
	}
	return 0;
}

INT_PTR CALLBACK ActivationWizard::StepThreeProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ERASEBKGND:
		  return 0;
		case WM_INITDIALOG:
		{

		}
		break;
		case WM_SHOWWINDOW:
		{

		}
		break;
		case WM_NOTIFY:
		{
			switch (((NMHDR *)lParam)->code)
			{
				case PSN_SETACTIVE:
				{
					PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_FINISH);
				}
				break;
				case PSN_QUERYCANCEL:
				{
					SetWindowLong(hDlg, 0 /*DWL_MSGRESULT*/, false);
					exit(0);
				}
				break;
				case PSN_WIZFINISH:
				{
					SetWindowLong(hDlg, 0 /*DWL_MSGRESULT*/, false);
					exit(0);
				}
				break;
				case PSN_RESET:
				{

				}
				break;
			}
			break;
		}
		break;
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				default:
				break;
			}
			break;
		}
		break;
		default:
			return 0;
	}
	return 0;
}

void SaveRegistry(const wchar_t * key, const wchar_t * name, const wchar_t * value)
{
    DWORD rc; 
    HKEY dmKey; 

    rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, key, 0, KEY_ALL_ACCESS, &dmKey); 

    if (rc != ERROR_SUCCESS)
    { 
        DWORD dwDisposition;

        rc = RegCreateKeyEx(
            HKEY_LOCAL_MACHINE, key, 0, NULL, REG_OPTION_NON_VOLATILE, 
            KEY_ALL_ACCESS, NULL, &dmKey, &dwDisposition
        );

		if (rc != ERROR_SUCCESS)
		{
			MessageBox(0, L"Failed accessing registry.", L"Error", MB_OK | MB_ICONERROR);
		}
    } 

    RegSetValueEx(
        dmKey, name, 0, REG_SZ, (LPBYTE)value, (lstrlen(value) + 1) *
        sizeof(wchar_t)
    );
}

void LoadRegistry(const wchar_t * key, const wchar_t * name, std::wstring & value)
{
	DWORD rc; 
	HKEY dmKey; 
	DWORD len; 
	DWORD dwType; 
	wchar_t sTemp[2048];

	len = sizeof(sTemp);

	rc = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE, key, 0, KEY_QUERY_VALUE | (is64bit() ? KEY_WOW64_64KEY : 0) , &dmKey
	); 

	if (rc != ERROR_SUCCESS)
	{ 
#ifndef NDEBUG
		MessageBox(0, L"Failed accessing registry.", L"Error", MB_OK | MB_ICONERROR);
#endif
	} 

	rc = RegQueryValueEx(dmKey, name, 0, &dwType, (LPBYTE)sTemp, &len);

	if (rc == ERROR_SUCCESS)
	{
		value = sTemp;
	}
}
