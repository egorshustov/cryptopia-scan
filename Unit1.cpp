//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include <IdHTTP.hpp>
#include <IdSSLOpenSSL.hpp>
#include <fstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
using namespace std;

TForm1 *Form1;
//TSearchThread *myThread;
TSearchThread1 *myThread1;
TSearchThread1 *myThread2;
TSearchThread1 *myThread3;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Memo1->Clear();
	Memo3->Clear();
	Memo4->Clear();
}
//---------------------------------------------------------------------------
char * strrstr(const char * s1, const char * s2)//последнее вхождение подстроки в строку (используется в функции SearchText)
{
	const char * p = s1 + strlen(s1) - strlen(s2) + 1;

	while ( p > s1 )
		if ( strstr(--p, s2) )
			return (char*)p;

	return NULL;
}

String TForm1::SearchText(String begin, String end, String all, bool reverse, bool include)//функция поиска текста
{//если include==true, то begin и end включаются в возвращаемое значение
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
TDateTime TForm1::UnixToDateTime(long int USec)
{
	TDateTime dt(((double)USec / 86400) + 25569.0);
	return  dt;
}
//---------------------------------------------------------------------------
long int TForm1::DateTimeToUnixx(TDateTime ConvDate)
{
	return floor((ConvDate.Val - 25569.0) * 86400);
}
//---------------------------------------------------------------------------
void TForm1::EnableComponents(bool state)
{
	GroupBox1->Enabled = state;
	GroupBox3->Enabled = state;
	GroupBox5->Enabled = state;
	GroupBox8->Enabled = state;

	Button1->Enabled = state;
	Button2->Enabled = (!state);
}
//---------------------------------------------------------------------------
void TForm1::send_vk_message(bool to_user)//послать сообщение в вк
{
	String access_token = at;
	String user_id;
	String messages_send="https://api.vk.com/method/messages.send?";

	if (to_user == true)//пользователю
	{
		user_id = Form1->ui;//id получателя
		messages_send.operator +=("user_id=");
		messages_send.operator +=(user_id);
	}
	if (to_user == false)//в беседу
	{
		user_id = Form1->di;//id беседы
		messages_send.operator +=("chat_id=");
		messages_send.operator +=(user_id);
	}
	messages_send.operator +=("&message=");
	messages_send.operator +=(Memo2->Text);
    //Memo2->Clear();

	messages_send.operator +=("&access_token=");
	messages_send.operator +=(access_token);

	messages_send.operator +=("&v=5.73");
	try
	{
		IdHTTP4->ReadTimeout=30000;
		IdHTTP4->ConnectTimeout=30000;
		String buf=IdHTTP4->Get(TIdURI::URLEncode(messages_send));
		ofstream fout1;
		fout1.open("log_vk.txt",ios::app);
		fout1<<AnsiString(buf).c_str()<<endl<<endl;
		fout1.close();
		while ((Pos("error",buf)!=0))
		{
			//Application->ProcessMessages();
			Sleep(10000);
			buf = IdHTTP4->Get(TIdURI::URLEncode(messages_send));
		}
	}
	catch (EIdException &E)
	{
		ofstream fout3;
		fout3.open("log_exception.txt",ios::app);
		fout3<<AnsiString(E.Message).c_str()<<endl<<endl;
		fout3.close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	ADOQuery1->SQL->Clear();
	ADOQuery1->SQL->Add("DELETE * from cryptopiamarkets;");
	ADOQuery1->ExecSQL();

	ADOQuery2->SQL->Clear();
	ADOQuery2->SQL->Add("DELETE * from cryptopiamarkets2;");
	ADOQuery2->ExecSQL();

	ADOQuery3->SQL->Clear();
	ADOQuery3->SQL->Add("DELETE * from cryptopiamarkets3;");
	ADOQuery3->ExecSQL();

	Memo1->Clear();
	Memo2->Clear();
	Memo3->Clear();
	Memo4->Clear();

	EnableComponents(0);

	//myThread = new TSearchThread(false);
	myThread1 = new TSearchThread1(false, 1);
	myThread2 = new TSearchThread1(false, 2);
	myThread3 = new TSearchThread1(false, 3);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)//остановить поиск
{
	//myThread->Terminate();
	myThread1->Terminate();
	myThread2->Terminate();
	myThread3->Terminate();
	EnableComponents(1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
	char settings_line[100];
	memset(settings_line,'\0', 300);

	ifstream f("settings.txt", ios::in);
	if (f!=0)
	{
		f.getline(settings_line, 300); Form1->Edit1->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit2->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit3->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit4->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit5->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit6->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit7->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit8->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit9->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit10->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit11->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit12->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit13->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit14->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit15->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300); Form1->Edit16->Text=settings_line; memset(settings_line,'\0', 300);
		f.getline(settings_line, 300);
		if (strcmp(settings_line, "RadioButton1")==0){Form1->RadioButton1->Checked=true;}
		if (strcmp(settings_line, "RadioButton2")==0){Form1->RadioButton2->Checked=true;}
        f.getline(settings_line, 300);
		if (strcmp(settings_line, "RadioButton3")==0){Form1->RadioButton3->Checked=true;}
		if (strcmp(settings_line, "RadioButton4")==0){Form1->RadioButton4->Checked=true;}
	}

	AnsiString ansi_at, ansi_ui, ansi_di;
	char txt_line[100],txt_line2[100],txt_line3[100];

	ifstream f_auth("auth.txt", ios::in);
	memset(txt_line,'\0', 300);
	memset(txt_line2,'\0', 300);
	memset(txt_line3,'\0', 300);
	f_auth.getline(txt_line, 300);
	f_auth.getline(txt_line2, 300);
	f_auth.getline(txt_line3, 300);
	Form1->at=txt_line;
	Form1->ui=txt_line2;
	Form1->di=txt_line3;
	f_auth.clear(); f_auth.seekg(0);f_auth.close();

	if ((Form1->at=="")||(Form1->ui=="")||(Form1->di==""))
	{
		//Form2 = new TForm2(NULL);
		Form2->WebBrowser1->Navigate("https://oauth.vk.com/authorize?client_id=6423904&scope=messages,offline,photos&redirect_uri=http://vk.com/&display=page&response_type=token&v=5.73");
		Form2->ShowModal();
		if ((Form1->at!="")||(Form1->ui!=""))
		{
			Form3->ShowModal();
		}
		//delete Form2;
		//Form2 = NULL;

		if ((Form1->at=="")||(Form1->ui=="")||(Form1->di==""))
		{
			Form1->Close();
			return;
		}
		ofstream fout_auth;
		fout_auth.open("auth.txt"/*,ios::app*/);

		ansi_at=Form1->at;
		ansi_ui=Form1->ui;
		ansi_di=Form1->di;
		fout_auth<<(ansi_at.c_str())<<endl;
		fout_auth<<(ansi_ui.c_str())<<endl;
		fout_auth<<(ansi_di.c_str())<<endl;
		fout_auth.close();
	}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::N3Click(TObject *Sender)
{
	ADOQuery1->SQL->Clear();
	ADOQuery1->SQL->Add("DELETE * from cryptopiamarkets;");
	ADOQuery1->ExecSQL();

	ADOQuery2->SQL->Clear();
	ADOQuery2->SQL->Add("DELETE * from cryptopiamarkets2;");
	ADOQuery2->ExecSQL();

	ADOQuery3->SQL->Clear();
	ADOQuery3->SQL->Add("DELETE * from cryptopiamarkets3;");
	ADOQuery3->ExecSQL();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
	Label3->Caption = "BTC";
	Edit1->Text = "0.05";

	Label15->Caption = "BTC";
	Edit8->Text = "0.25";

	Label23->Caption = "BTC";
	Edit13->Text = "0.75";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
	Label3->Caption = "USDT";
	Edit1->Text = "500";

	Label15->Caption = "USDT";
	Edit8->Text = "2500";

	Label23->Caption = "USDT";
	Edit13->Text = "7500";
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)//недописанная функция - пробовал сделать скрин и отправить файл
{
	Graphics::TBitmap *FormImage = GetFormImage();
	TJPEGImage *jp = new TJPEGImage();
	try
	{
		jp->Assign(FormImage);
		Form1->Tag++;
		jp->SaveToFile("screenshot.jpg");
	}
	__finally
	{
		delete FormImage;
		delete jp;
	}

	String buf, request, upload_url;
	request = "https://api.vk.com/method/photos.getMessagesUploadServer?access_token="+Form1->at+"&v=5.73";
	IdHTTP1->ReadTimeout=30000;
	IdHTTP1->ConnectTimeout=30000;
	buf = Form1->IdHTTP1->Get(request);
	Memo1->Text=buf;
	upload_url=SearchText("\"upload_url\":\"", "\"", buf, 0, 0);//получаем BaseVolume рынка market
	upload_url = StringReplace(upload_url,"\\/","/", TReplaceFlags()<< rfReplaceAll);

	TStringList *params = new TStringList;
	//params->Add("access_token="+at);
	params->Add("name=photo");
	params->Add("filename=screenshot.jpg");
	//auth->Add("remember_login=1");
	IdHTTP1->Request->ContentType="multipart/form-data";
	IdHTTP1->Request->ContentDisposition="form-data";

	buf = IdHTTP1->Post(upload_url,params);
	//Memo1->Text=buf;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
	Edit1->Text = StringReplace(Edit1->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit2->Text = StringReplace(Edit2->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit3->Text = StringReplace(Edit3->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit4->Text = StringReplace(Edit4->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit5->Text = StringReplace(Edit5->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit6->Text = StringReplace(Edit6->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit7->Text = StringReplace(Edit7->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit8->Text = StringReplace(Edit8->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit9->Text = StringReplace(Edit9->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit10->Text = StringReplace(Edit10->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit11->Text = StringReplace(Edit11->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit12->Text = StringReplace(Edit12->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit13->Text = StringReplace(Edit13->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit14->Text = StringReplace(Edit14->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit15->Text = StringReplace(Edit15->Text,",",".", TReplaceFlags()<<rfReplaceAll);
	Edit16->Text = StringReplace(Edit16->Text,",",".", TReplaceFlags()<<rfReplaceAll);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton4Click(TObject *Sender)
{
	Edit1->Text = StringReplace(Edit1->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit2->Text = StringReplace(Edit2->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit3->Text = StringReplace(Edit3->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit4->Text = StringReplace(Edit4->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit5->Text = StringReplace(Edit5->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit6->Text = StringReplace(Edit6->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit7->Text = StringReplace(Edit7->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit8->Text = StringReplace(Edit8->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit9->Text = StringReplace(Edit9->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit10->Text = StringReplace(Edit10->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit11->Text = StringReplace(Edit11->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit12->Text = StringReplace(Edit12->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit13->Text = StringReplace(Edit13->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit14->Text = StringReplace(Edit14->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit15->Text = StringReplace(Edit15->Text,".",",", TReplaceFlags()<<rfReplaceAll);
	Edit16->Text = StringReplace(Edit16->Text,".",",", TReplaceFlags()<<rfReplaceAll);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	ofstream fout;
	fout.open("settings.txt"/*,ios::app*/);
	fout<<AnsiString(Edit1->Text).c_str()<<endl;
	fout<<AnsiString(Edit2->Text).c_str()<<endl;
	fout<<AnsiString(Edit3->Text).c_str()<<endl;
	fout<<AnsiString(Edit4->Text).c_str()<<endl;
	fout<<AnsiString(Edit5->Text).c_str()<<endl;
	fout<<AnsiString(Edit6->Text).c_str()<<endl;
	fout<<AnsiString(Edit7->Text).c_str()<<endl;
	fout<<AnsiString(Edit8->Text).c_str()<<endl;
	fout<<AnsiString(Edit9->Text).c_str()<<endl;
	fout<<AnsiString(Edit10->Text).c_str()<<endl;
	fout<<AnsiString(Edit11->Text).c_str()<<endl;
	fout<<AnsiString(Edit12->Text).c_str()<<endl;
	fout<<AnsiString(Edit13->Text).c_str()<<endl;
	fout<<AnsiString(Edit14->Text).c_str()<<endl;
	fout<<AnsiString(Edit15->Text).c_str()<<endl;
	fout<<AnsiString(Edit16->Text).c_str()<<endl;
	if (RadioButton1->Checked==true){fout<<AnsiString("RadioButton1").c_str()<<endl;}
	if (RadioButton2->Checked==true){fout<<AnsiString("RadioButton2").c_str()<<endl;}
	if (RadioButton3->Checked==true){fout<<AnsiString("RadioButton3").c_str()<<endl;}
	if (RadioButton4->Checked==true){fout<<AnsiString("RadioButton4").c_str()<<endl;}
	fout.close();
}
//---------------------------------------------------------------------------






void __fastcall TForm1::N4Click(TObject *Sender)
{
	Form6->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormActivate(TObject *Sender)
{
	if (Form6->CheckBox1->Checked)//использовать прокси
	{
		IdHTTP5->ProxyParams->ProxyServer = Form6->Edit1->Text;
		IdHTTP5->ProxyParams->ProxyPort = StrToInt(Form6->Edit2->Text);
		IdHTTP5->ProxyParams->ProxyUsername = Form6->Edit3->Text;
		IdHTTP5->ProxyParams->ProxyPassword = Form6->Edit4->Text;
	}
	else
	{
		IdHTTP5->ProxyParams->ProxyServer = "";
		IdHTTP5->ProxyParams->ProxyPort = 0;
		IdHTTP5->ProxyParams->ProxyUsername = "";
		IdHTTP5->ProxyParams->ProxyPassword = "";
	}
}
//---------------------------------------------------------------------------


