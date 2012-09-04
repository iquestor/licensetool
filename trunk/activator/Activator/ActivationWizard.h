#pragma once

#include "Prsht.h"

#pragma comment(lib, "comctl32.lib")

class ActivationWizard
{
	public:
		ActivationWizard(void);
		~ActivationWizard(void);

		void Launch(HINSTANCE hInst);

	private:

		static INT_PTR CALLBACK StepOneProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static INT_PTR CALLBACK StepTwoProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static INT_PTR CALLBACK StepThreeProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:

		PROPSHEETHEADER propsheetheader_;

		HPROPSHEETPAGE propsheetpages_[3];
};

