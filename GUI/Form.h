//---------------------------------------------------------------------------

#ifndef FormH
#define FormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>
#include "SynEdit.hpp"
#include "SynEditHighlighter.hpp"
#include "SynHighlighterCpp.hpp"
#include "SynHighlighterRuby.hpp"
#include <Vcl.Imaging.pngimage.hpp>

#include <string>

#include "SynEdit.hpp"
#include "SynEditHighlighter.hpp"
#include "SynHighlighterCpp.hpp"
#include "SynHighlighterRuby.hpp"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *mFile;
	TMenuItem *mNew;
	TMenuItem *mOpen;
	TMenuItem *mSave;
	TMenuItem *mSaveAs;
	TMenuItem *N6;
	TMenuItem *N9;
	TMenuItem *mExit;
	TMenuItem *mCode;
	TMenuItem *mConvert;
	TMenuItem *mSaveConverted;
	TMenuItem *mRunC;
	TMenuItem *mRunConverted;
	TMenuItem *N16;
	TMenuItem *N17;
	TMenuItem *mFontUp;
	TMenuItem *mFontDown;
	TMenuItem *mFontReset;
	TMenuItem *mFontChange;
	TMenuItem *mHelp;
	TMenuItem *mOpenHelp;
	TMenuItem *mAbout;
	TMenuItem *N25;
	TMenuItem *mEdit;
	TMenuItem *mReset;
	TMenuItem *mSelectAll;
	TBitBtn *CsharpModeBtn;
	TFontDialog *FontDialog1;
	TSynEdit *CppEdit;
	TSynCppSyn *SynCppSyn1;
	TSynRubySyn *SynRubySyn1;
	TSynEdit *ConvEdit;
	TFileOpenDialog *OpenFileDlg;
	TFileSaveDialog *SaveFileDlg;
	TMenuItem *mUndo;
	TFileSaveDialog *ConvSaveDlg;
	TSplitter *Splitter1;
	TPanel *Panel1;
	TPanel *UpperPanel;
	TMenuItem *mRedo;
	TMenuItem *N1;
	TMenuItem *mCut;
	TMenuItem *mCopy;
	TMenuItem *mPaste;
	TStatusBar *StatusBar1;
	TMenuItem *mCCompile;
	TMenuItem *mConvertSelected;
	TBitBtn *RubyModeBtn;
	TLabel *Label1;
	TBitBtn *ConvertBtn;
	TImage *ConvertImg;
	TPopupMenu *CppPopupMenu;
	TMenuItem *pmCut;
	TMenuItem *pmCopy;
	TMenuItem *pmPaste;
	TPopupMenu *ConvPopupMenu;
	TMenuItem *pmCutConv;
	TMenuItem *pmCopyConv;
	TMenuItem *pmPasteConv;
	TMenuItem *pmConvert;
	TSynCppSyn *SynCSharpSyn1;
	void __fastcall mExitClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall mNewClick(TObject *Sender);
	void __fastcall mOpenClick(TObject *Sender);
	void __fastcall mSaveClick(TObject *Sender);
	void __fastcall mSaveAsClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall mResetClick(TObject *Sender);
	void __fastcall mUndoClick(TObject *Sender);
	void __fastcall mSelectAllClick(TObject *Sender);
	void __fastcall mSaveConvertedClick(TObject *Sender);
	void __fastcall CppEditChange(TObject *Sender);
	void __fastcall Panel1Resize(TObject *Sender);
	void __fastcall mRedoClick(TObject *Sender);
	void __fastcall mCutClick(TObject *Sender);
	void __fastcall mCopyClick(TObject *Sender);
	void __fastcall mPasteClick(TObject *Sender);
	void __fastcall CsharpModeBtnClick(TObject *Sender);
	void __fastcall mConvertClick(TObject *Sender);
	void __fastcall mRunCClick(TObject *Sender);
	void __fastcall mRunConvertedClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall ConvEditChange(TObject *Sender);
	void __fastcall mCCompileClick(TObject *Sender);
	void __fastcall mFontUpClick(TObject *Sender);
	void __fastcall mFontDownClick(TObject *Sender);
	void __fastcall mFontResetClick(TObject *Sender);
	void __fastcall mFontChangeClick(TObject *Sender);
	void __fastcall OpenFileDlgFileOkClick(TObject *Sender, bool &CanClose);
	void __fastcall SaveFileDlgFileOkClick(TObject *Sender, bool &CanClose);
	void __fastcall ConvSaveDlgFileOkClick(TObject *Sender, bool &CanClose);
	void __fastcall FontDialog1Apply(TObject *Sender, HWND Wnd);
	void __fastcall mAboutClick(TObject *Sender);
	void __fastcall mOpenHelpClick(TObject *Sender);
	void __fastcall ConvertBtnClick(TObject *Sender);
	void __fastcall RubyModeBtnClick(TObject *Sender);
	void __fastcall pmCutClick(TObject *Sender);
	void __fastcall pmCopyClick(TObject *Sender);
	void __fastcall pmPasteClick(TObject *Sender);
	void __fastcall pmCutConvClick(TObject *Sender);
	void __fastcall pmCopyConvClick(TObject *Sender);
	void __fastcall pmPasteConvClick(TObject *Sender);
	void __fastcall mConvertSelectedClick(TObject *Sender);
	void __fastcall pmConvertClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);

	HINSTANCE csharpDLL_load;		// csharp dll load var
	HINSTANCE rubyDLL_load;			// ruby dll load var
	int convertMode;				// C#(1) or Ruby(2) mode

	TFont* stdFont;					//standard font for editors
	char* convertStr;               //string with converted code

	UnicodeString currentCppFile;  	//path to current cpp file
	UnicodeString currentConvFile;  //path to current cs/rb file
	bool cppFileSaved;       		//cpp file saved check
	bool convFileSaved;             //converted file saved check

	UnicodeString ppath; 			//program path
	UnicodeString require;  		//include help methods in ruby code
	UnicodeString help_file;		//location of help.html file

	UnicodeString cpp_path;  		//path to cpp_out.exe
	UnicodeString cpp_param;    	//cpp compiler parameters
	UnicodeString cpp_compiler;		//cpp compiler path

	UnicodeString csharp_path;  	//path to csharp_out.exe
	UnicodeString csharp_param;		//csc compiler parameters
	UnicodeString csharp_compiler;	//csc compiler path

	UnicodeString ruby_param; 		//ruby compiler parameters
	UnicodeString ruby_compiler; 	//ruby compiler path

	bool testSaved();
	UnicodeString convertCode(UnicodeString code);
    void convertAll();
	void convertToClipboard(UnicodeString code);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
