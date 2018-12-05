//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
char * strrstr(const char * s1, const char * s2)//последнее вхождение подстроки в строку
{
	const char * p = s1 + strlen(s1) - strlen(s2) + 1;

	while ( p > s1 )
		if ( strstr(--p, s2) )
            return (char*)p;

	return NULL;
}

String SearchText(String begin, String end, String all, bool reverse, bool include)
{
   int p1, p2;
   String temp;
   if ((Pos(begin,all)==0) || (Pos(end,all)==0))
   {
	  return "Error";
   }
   else
   {
	  temp = all;
	  if (reverse==0)
	  {
		 if (include==0) {p1 = Pos(begin,all) + begin.Length() - 1;}
		 else {p1 = Pos(begin,all) - 1;}
		 temp.Delete(1,p1);
		 if (include==0) {p2 = Pos(end,temp);}
		 else {p2 = Pos(end,temp) + end.Length();}
		 temp.Delete(p2,all.Length());
	  }
	  else
	  {
		 if (include==0) {p2 = Pos(end,temp);}
		 else {p2 = Pos(end,temp) + end.Length();}

		 temp.Delete(p2,all.Length());
		 char* k;
		 if (include==0)
		 {
			k = strrstr(AnsiString(temp).c_str(),AnsiString(begin).c_str())+begin.Length();
		 }
		 else
		 {
			k = strrstr(AnsiString(temp).c_str(),AnsiString(begin).c_str());
		 }
		 temp = k;
	  }
	  return temp;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::WebBrowser1NavigateComplete2(TObject *ASender, IDispatch * const pDisp,
          const OleVariant &URL)
{
	String return_url = URL;
	String access_token;

	access_token=SearchText("#access_token=", "&expires_in", return_url, 0, 0);
	if (access_token != "Error")
	{
		return_url.operator +=("&end");
		Form1->ui=SearchText("user_id=", "&end", return_url, 0, 0);
		Form1->at=access_token;
		Form2->Close();
	}
}
//---------------------------------------------------------------------------



