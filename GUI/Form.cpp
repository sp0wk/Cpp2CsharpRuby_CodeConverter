//---------------------------------------------------------------------------

#include <vcl.h>
#include <clipbrd.hpp>   	//clipboard help
#pragma hdrstop

#include "Form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SynEdit"
#pragma link "SynEditHighlighter"
#pragma link "SynHighlighterCpp"
#pragma link "SynHighlighterRuby"
#pragma link "SynEdit"
#pragma link "SynEditHighlighter"
#pragma link "SynHighlighterCpp"
#pragma link "SynHighlighterRuby"
#pragma resource "*.dfm"
TMainForm *MainForm;

//DLL function import
const wchar_t* ruby_libname = L"RubyConverterDLL.dll";
const wchar_t* csharp_libname = L"CsharpConverterDLL.dll";
extern "C" __declspec(dllimport) char* __stdcall convertCppToRuby(char** code_in);
extern "C" __declspec(dllimport) char* __stdcall convertCppToCsharp(char** code_in);

typedef void* (*VoidReturnFunc)(char**);


// public methods

bool TMainForm::testSaved()
{
	int ans = 0;
	if (currentCppFile != "" && cppFileSaved == false) {
		ans = MessageBox(NULL, L"Файл с кодом С++ не сохранён. Сохранить?", L"Сохранить", MB_YESNOCANCEL);
		switch (ans) {
			case IDYES: {
				CppEdit->Lines->SaveToFile(currentCppFile);
				cppFileSaved = true;
				return true;
			}
			case IDNO: {
				return true;
			}
			case IDCANCEL: {
				return false;
			}
			default: return false;
		}
	}
	else {
		return true;
	}
}


UnicodeString TMainForm::convertCode(UnicodeString code = "")
{
	AnsiString tmp = code;
	UnicodeString result = L"";

	if (convertMode == 1) {    // C# conversion
		if (csharpDLL_load == NULL) {
			csharpDLL_load = LoadLibrary(csharp_libname);
		}

		if (csharpDLL_load) {
			// GetProcAddress returns a pointer to the loaded method
			VoidReturnFunc convertFunc = (VoidReturnFunc) GetProcAddress(csharpDLL_load, "convertCppToCsharp");

			convertStr = tmp.c_str();
			result = (char*)convertFunc(&convertStr);
		}
		else {
			ShowMessage("Библиотека конвертера C# не найдена!");
			this->Close();
		}
	}
	else if (convertMode == 2) {     	// Ruby conversion
		if (rubyDLL_load == NULL) {
			rubyDLL_load = LoadLibrary(ruby_libname);
		}

		if (rubyDLL_load) {
			// GetProcAddress returns a pointer to the loaded method
			VoidReturnFunc convertFunc = (VoidReturnFunc) GetProcAddress(rubyDLL_load, "convertCppToRuby");

			convertStr = tmp.c_str();
			result = (char*)convertFunc(&convertStr);
		}
		else {
			ShowMessage("Библиотека конвертера Ruby не найдена!");
			this->Close();
		}
	}
	else {
		 MessageBox(NULL, L"Сперва необходимо выбрать режим", L"Режим не выбран", MB_OK + MB_ICONWARNING);
	}

	return result;
}


void TMainForm::convertAll()
{
	if (convertMode == 1) {    // C# conversion
		ConvEdit->Lines->Text = "using System.IO;\nusing System;\n\n"
								"class Converted\n{\n" +
								convertCode(CppEdit->Lines->Text) + "}";
	}
	else if (convertMode == 2) {     	// Ruby conversion
		ConvEdit->Lines->Text = require + convertCode(CppEdit->Lines->Text);
	}
	else {
		 MessageBox(NULL, L"Сперва необходимо выбрать режим", L"Режим не выбран", MB_OK + MB_ICONWARNING);
	}
}


void TMainForm::convertToClipboard(UnicodeString code)
{
	UnicodeString converted = convertCode(CppEdit->SelText);

	Clipboard()->AsText = converted;

	if (!Clipboard()->HasFormat(CF_TEXT)) {
		MessageBox(NULL, L"Ошибка при копировании в буфер", L"Ошибка", MB_OK + MB_ICONERROR);
	}
}


//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	convertMode = 0;

	stdFont = new TFont;

	convertStr = "";
	currentCppFile = "";
	currentConvFile = "";
	cppFileSaved = false;
	convFileSaved = false;

	ppath = GetCurrentDir();
	require = "require \'./ruby_help_methods.rb\'\n\n\n";
	help_file = ppath + "\\help.html";

	//cpp compiler
	cpp_path = "\"" + ppath + "\\cpp_OUT\\cpp_out.exe\"";
	cpp_param = "\"" + currentCppFile + "\"" + " -o " + cpp_path;
	cpp_compiler = "\"" + ppath + "\\cpp_compiler\\bin\\g++.exe\"";
	//csharp compiler
	csharp_path = "\"" + ppath + "\\csharp_OUT\\csharp_out.exe\"";
	csharp_param = "out:\"" + csharp_path + "\" \"" + currentConvFile + "\"";
	csharp_compiler = "\"%WINDIR%\\Microsoft.NET\\Framework\\v3.5\\csc.exe\"";
	//ruby compiler
	ruby_param = "\"" + currentConvFile + "\"";
	ruby_compiler = "\"" + ppath + "\\ruby_compiler\\bin\\ruby.exe\"";
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::mExitClick(TObject *Sender)
{
	if (testSaved())
		Application->Terminate();
}
//---------------------------------------------------------------------------

//form create event
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	*stdFont = *CppEdit->Font;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (testSaved())
		Action = caFree;
	else
		Action = caNone;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mNewClick(TObject *Sender)
{
	if (testSaved()) {
		//clear
    	CppEdit->Clear();
		ConvEdit->Clear();
    	convertStr = "";
    	currentCppFile = "";
		currentConvFile = "";
		StatusBar1->Panels[0][0]->Text = "Cpp File:";
		StatusBar1->Panels[0][1]->Text = "Converted File:";
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mOpenClick(TObject *Sender)
{
	if (testSaved()) {
		OpenFileDlg->Execute();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mSaveClick(TObject *Sender)
{
	if (currentCppFile == "") {
		SaveFileDlg->Execute();
	}
	else {
		CppEdit->Lines->SaveToFile(currentCppFile);
		StatusBar1->Panels[0][0]->Text = "Cpp File:  " + currentCppFile;
		cppFileSaved = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mSaveAsClick(TObject *Sender)
{
	SaveFileDlg->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::mResetClick(TObject *Sender)
{
	// load content from cpp file
	if (currentCppFile != "" && CppEdit->Focused()) {
		CppEdit->Lines->LoadFromFile(currentCppFile);
		StatusBar1->Panels[0][0]->Text = "Cpp File:  " + currentCppFile;
		cppFileSaved = true;
	}
	else {// load content from converted file
		if (currentConvFile != "" && ConvEdit->Focused()) {
			ConvEdit->Lines->LoadFromFile(currentConvFile);
			StatusBar1->Panels[0][1]->Text = "Converted File:  " + currentConvFile;
			convFileSaved = true;
     	}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mUndoClick(TObject *Sender)
{
	if (CppEdit->Focused()) {
		CppEdit->Undo();
	}
	else if (ConvEdit->Focused()) {
		ConvEdit->Undo();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mSelectAllClick(TObject *Sender)
{
	if (CppEdit->Focused()) {
		CppEdit->SelectAll();
	}
	else if (ConvEdit->Focused()) {
		ConvEdit->SelectAll();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mSaveConvertedClick(TObject *Sender)
{
	ConvSaveDlg->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CppEditChange(TObject *Sender)
{
	cppFileSaved = false;
	if (currentCppFile != "")
		StatusBar1->Panels[0][0]->Text = "Cpp File:  * " + currentCppFile;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Panel1Resize(TObject *Sender)
{
	ConvEdit->Width = Panel1->Width * 0.49;
	CppEdit->Width = Panel1->Width * 0.49;
	Splitter1->Width = Panel1->Width * 0.02;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::mRedoClick(TObject *Sender)
{
	if (CppEdit->Focused()) {
		CppEdit->Redo();
	}
	else if (ConvEdit->Focused()) {
		ConvEdit->Redo();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mCutClick(TObject *Sender)
{
	if (CppEdit->Focused()) {
		CppEdit->CutToClipboard();
	}
	else if (ConvEdit->Focused()) {
		ConvEdit->CutToClipboard();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mCopyClick(TObject *Sender)
{
	if (CppEdit->Focused()) {
		CppEdit->CopyToClipboard();
	}
	else if (ConvEdit->Focused()) {
		ConvEdit->CopyToClipboard();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mPasteClick(TObject *Sender)
{
	if (CppEdit->Focused()) {
		CppEdit->PasteFromClipboard();
	}
	else if (ConvEdit->Focused()) {
		ConvEdit->PasteFromClipboard();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CsharpModeBtnClick(TObject *Sender)
{
    if (convertMode != 1) currentConvFile = "";
	convertMode = 1;
	CsharpModeBtn->Glyph->LoadFromResourceName(0, "Bitmap_csON");
	RubyModeBtn->Glyph->LoadFromResourceName(0, "Bitmap_rubyOFF");
	ConvEdit->Highlighter = SynCSharpSyn1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RubyModeBtnClick(TObject *Sender)
{
	if (convertMode != 2) currentConvFile = "";
	convertMode = 2;
	CsharpModeBtn->Glyph->LoadFromResourceName(0, "Bitmap_csOFF");
	RubyModeBtn->Glyph->LoadFromResourceName(0, "Bitmap_rubyON");
	ConvEdit->Highlighter = SynRubySyn1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mConvertClick(TObject *Sender)
{
	convertAll();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mRunCClick(TObject *Sender)
{
try {
	UnicodeString command = " /k "+cpp_path;
	ShellExecute(Handle, NULL, L"cmd.exe", command.w_str(), NULL, SW_SHOW);
} catch (Exception* e) {
	UnicodeString errormsg = "Error: " + e->Message;
	MessageBox(NULL, errormsg.w_str(), L"Error", MB_OK + MB_ICONERROR);
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mRunConvertedClick(TObject *Sender)
{
UnicodeString command = L"";

try {
	if (currentConvFile != "") {
		ConvEdit->Lines->SaveToFile(currentConvFile);
		StatusBar1->Panels[0][1]->Text = "Converted File:  " + currentConvFile;

		switch (convertMode)
		{
			case 1: {
					csharp_param = "/out:\"" + csharp_path + "\" \"" + currentConvFile + "\"";
					command = " /k \"" + csharp_compiler + " " + csharp_param + "\"";
					break;
			}
			case 2: {
					ruby_param = "\"" + currentConvFile + "\"";
					command = " /k \"" + ruby_compiler + " " + ruby_param + "\"";
					break;
			}
			default: MessageBox(NULL, L"Сперва необходимо выбрать режим", L"Режим не выбран", MB_OK + MB_ICONWARNING);
		}
		// execute compiling
		ShellExecute(Handle, NULL, L"cmd.exe", command.w_str(), NULL, SW_SHOW);
	}
	else {
		if (MessageBox(NULL, L"Сперва необходимо сохранить файл. Сохранить?", L"Предупреждение", MB_YESNO) == IDYES) {
			ConvSaveDlg->Execute();
		}
	}
} catch (Exception* e) {
	UnicodeString errormsg = "Error: " + e->Message;
	MessageBox(NULL, errormsg.w_str(), L"Error", MB_OK + MB_ICONERROR);
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormResize(TObject *Sender)
{
	StatusBar1->Panels[0][0]->Width = this->Width * 0.5;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ConvEditChange(TObject *Sender)
{
	convFileSaved = false;
	if (currentConvFile != "")
		StatusBar1->Panels[0][1]->Text = "Converted File: * " + currentConvFile;
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::mCCompileClick(TObject *Sender)
{
try {
	if (currentCppFile != "") {
		CppEdit->Lines->SaveToFile(currentCppFile);
		StatusBar1->Panels[0][0]->Text = "Cpp File:  " + currentCppFile;

		cpp_param = "\"" + currentCppFile + "\"" + " -o "+cpp_path;

		UnicodeString command = " /k \"" + cpp_compiler + " "+cpp_param+"\"";
		ShellExecute(Handle, NULL, L"cmd.exe", command.w_str(), NULL, SW_SHOW);
	}
	else {
		if (MessageBox(NULL, L"Сперва необходимо сохранить файл. Сохранить?", L"Предупреждение", MB_YESNO) == IDYES) {
			SaveFileDlg->Execute();
		}
	}
} catch (Exception* e) {
	UnicodeString errormsg = "Error: " + e->Message;
	MessageBox(NULL, errormsg.w_str(), L"Error", MB_OK + MB_ICONERROR);
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mFontUpClick(TObject *Sender)
{
	CppEdit->Font->Size += 1;
	ConvEdit->Font->Size += 1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mFontDownClick(TObject *Sender)
{
	CppEdit->Font->Size -= 1;
	ConvEdit->Font->Size -= 1;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::mFontResetClick(TObject *Sender)
{
	CppEdit->Font = stdFont;
	ConvEdit->Font = stdFont;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mFontChangeClick(TObject *Sender)
{
	FontDialog1->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenFileDlgFileOkClick(TObject *Sender, bool &CanClose)
{
	currentCppFile = OpenFileDlg->FileName;
	StatusBar1->Panels[0][0]->Text = "Cpp File:  " + currentCppFile;
	//load code
	CppEdit->Lines->LoadFromFile(currentCppFile);
	cppFileSaved = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveFileDlgFileOkClick(TObject *Sender, bool &CanClose)
{
	currentCppFile = SaveFileDlg->FileName;
	CppEdit->Lines->SaveToFile(currentCppFile);
	StatusBar1->Panels[0][0]->Text = "Cpp File:  " + currentCppFile;
	cppFileSaved = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ConvSaveDlgFileOkClick(TObject *Sender, bool &CanClose)
{
	currentConvFile = ConvSaveDlg->FileName;
	StatusBar1->Panels[0][1]->Text = "Converted File:  " + currentConvFile;
	ConvEdit->Lines->SaveToFile(currentConvFile);
	convFileSaved = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FontDialog1Apply(TObject *Sender, HWND Wnd)
{
	CppEdit->Font = FontDialog1->Font;
	ConvEdit->Font = FontDialog1->Font;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mAboutClick(TObject *Sender)
{
MessageBox(NULL, L"Название:  C++ To C#/Ruby Code Converter\n"
	L"Версия:   1.00\n\n"
	L"Автор программы:   Волошин Дмитрий \n\n"
	L"© ДНУЖТ, 2016"
, L"О программе", MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mOpenHelpClick(TObject *Sender)
{
	ShellExecute(NULL, L"open", help_file.w_str(), NULL, NULL, SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ConvertBtnClick(TObject *Sender)
{
	convertAll();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pmCutClick(TObject *Sender)
{
CppEdit->CutToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pmCopyClick(TObject *Sender)
{
CppEdit->CopyToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pmPasteClick(TObject *Sender)
{
CppEdit->PasteFromClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pmCutConvClick(TObject *Sender)
{
ConvEdit->CutToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pmCopyConvClick(TObject *Sender)
{
ConvEdit->CopyToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pmPasteConvClick(TObject *Sender)
{
ConvEdit->PasteFromClipboard();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::mConvertSelectedClick(TObject *Sender)
{
convertToClipboard(CppEdit->SelText);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pmConvertClick(TObject *Sender)
{
convertToClipboard(CppEdit->SelText);
}
//---------------------------------------------------------------------------


