//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdFTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdAntiFreezeBase.hpp>
#include <Vcl.IdAntiFreeze.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.Menus.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <IdAntiFreeze.hpp>
#include <IdHTTP.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TMemo *Memo1;
	TButton *Button2;
	TIdAntiFreeze *IdAntiFreeze1;
	TADOConnection *ADOConnection1;
	TADOTable *ADOTable1;
	TDataSource *DataSource1;
	TADOQuery *ADOQuery1;
	TDataSource *DataSource2;
	TADOQuery *ADOQuery2;
	TADOTable *ADOTable2;
	TGroupBox *GroupBox1;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMemo *Memo2;
	TGroupBox *GroupBox3;
	TLabel *Label1;
	TEdit *Edit1;
	TEdit *Edit2;
	TIdFTP *IdFTP1;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TMenuItem *N3;
	TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL1;
	TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL2;
	TIdHTTP *IdHTTP1;
	TIdHTTP *IdHTTP2;
	TLabel *Label6;
	TLabel *Label2;
	TEdit *Edit3;
	TLabel *Label3;
	TEdit *Edit4;
	TLabel *Label5;
	TLabel *Label7;
	TEdit *Edit5;
	TLabel *Label4;
	TLabel *Label8;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox4;
	TLabel *Label9;
	TEdit *Edit6;
	TLabel *Label10;
	TGroupBox *GroupBox5;
	TLabel *Label11;
	TLabel *Label12;
	TEdit *Edit7;
	TMemo *Memo3;
	TGroupBox *GroupBox6;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TEdit *Edit8;
	TEdit *Edit9;
	TEdit *Edit10;
	TGroupBox *GroupBox7;
	TLabel *Label17;
	TLabel *Label18;
	TEdit *Edit11;
	TADOTable *ADOTable3;
	TDataSource *DataSource3;
	TADOQuery *ADOQuery3;
	TGroupBox *GroupBox8;
	TLabel *Label19;
	TLabel *Label20;
	TEdit *Edit12;
	TMemo *Memo4;
	TGroupBox *GroupBox9;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TEdit *Edit13;
	TEdit *Edit14;
	TEdit *Edit15;
	TGroupBox *GroupBox10;
	TLabel *Label25;
	TLabel *Label26;
	TEdit *Edit16;
	TIdHTTP *IdHTTP3;
	TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL3;
	TButton *Button3;
	TGroupBox *GroupBox11;
	TRadioButton *RadioButton3;
	TRadioButton *RadioButton4;
	TMemo *Memo5;
	TIdHTTP *IdHTTP5;
	TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL4;
	TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL5;
	TIdHTTP *IdHTTP4;
	TMenuItem *N4;
	TGroupBox *GroupBox12;
	TEdit *Edit17;
	TLabel *Label27;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall RadioButton1Click(TObject *Sender);
	void __fastcall RadioButton2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall RadioButton4Click(TObject *Sender);
	void __fastcall RadioButton3Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	String at, ui, di;
	void TForm1::EnableComponents(bool state);
	void TForm1::check_market(String market_name);
	void TForm1::send_vk_message(bool to_user);
	String TForm1::SearchText(String begin, String end, String all, bool reverse, bool include);
	TDateTime TForm1::UnixToDateTime(long int USec);
	long int TForm1::DateTimeToUnixx(TDateTime ConvDate);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
