//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm6::CheckBox1Click(TObject *Sender)
{
	if (CheckBox1->Checked)//использовать прокси
	{
		Form1->IdHTTP5->ProxyParams->ProxyServer = Edit1->Text;
		Form1->IdHTTP5->ProxyParams->ProxyPort = StrToInt(Edit2->Text);
		Form1->IdHTTP5->ProxyParams->ProxyUsername = Edit3->Text;
		Form1->IdHTTP5->ProxyParams->ProxyPassword = Edit4->Text;
	}
	else
	{
		Form1->IdHTTP5->ProxyParams->ProxyServer = "";
		Form1->IdHTTP5->ProxyParams->ProxyPort = 0;
		Form1->IdHTTP5->ProxyParams->ProxyUsername = "";
		Form1->IdHTTP5->ProxyParams->ProxyPassword = "";
	}
}
//---------------------------------------------------------------------------
