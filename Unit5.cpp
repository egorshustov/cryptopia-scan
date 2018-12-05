//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit5.h"
#include "Unit1.h"
#pragma package(smart_init)
#include <fstream>
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TSearchThread1::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TSearchThread1::TSearchThread1(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}

__fastcall TSearchThread1::TSearchThread1(bool CreateSuspended, int t)
{
	type=t;
}

void __fastcall TSearchThread1::UpdateSignalTime(String label)//�������� � ���������� ������� ������� � ��
{
	__int64 signal_time, current_time, edit_time;
	edit_time = 1000*60*StrToInt(Form1->Edit17->Text);
	current_time = GetTickCount();
	bool spam_signal=false;

	if (type==1)
	{
		//������� ���������� �������� signal_time:
		Form1->ADOQuery1->Close();
		Form1->ADOQuery1->SQL->Clear();
		Form1->ADOQuery1->SQL->Add("SELECT cryptopiamarkets.signaltime AS signaltime FROM cryptopiamarkets WHERE cryptopiamarkets.label='"+label+"';");
		Form1->ADOQuery1->Open();
		signal_time = Form1->ADOQuery1->FieldByName("signaltime")->AsLargeInt;

		//���� � ������� ������� ������ ������� ������ ����� Form1->Edit17->Text ����� (��� ���� ������ ������ �� ���������, ����� signal_time=0), �� ������� ����� � ������� � �������� ��������� � ���������
		if ((current_time-signal_time) > edit_time)
		{
			Form1->ADOQuery1->Close();
			Form1->ADOQuery1->SQL->Clear();
			Form1->ADOQuery1->SQL->Add("UPDATE cryptopiamarkets SET cryptopiamarkets.signaltime = '"+IntToStr(current_time)+"' WHERE cryptopiamarkets.label='"+label+"';");
			Form1->ADOQuery1->ExecSQL();
			send_tg_message();
			Form1->Memo2->Clear();
		}
		else
		{
			spam_signal=true;
        }
	}
	if (type==2)
	{
		Form1->ADOQuery2->Close();
		Form1->ADOQuery2->SQL->Clear();
		Form1->ADOQuery2->SQL->Add("SELECT cryptopiamarkets2.signaltime AS signaltime FROM cryptopiamarkets2 WHERE cryptopiamarkets2.label='"+label+"';");
		Form1->ADOQuery2->Open();
		signal_time = Form1->ADOQuery2->FieldByName("signaltime")->AsLargeInt;

		if ((current_time-signal_time) > edit_time)
		{
			Form1->ADOQuery2->Close();
			Form1->ADOQuery2->SQL->Clear();
			Form1->ADOQuery2->SQL->Add("UPDATE cryptopiamarkets2 SET cryptopiamarkets2.signaltime = '"+IntToStr(current_time)+"' WHERE cryptopiamarkets2.label='"+label+"';");
			Form1->ADOQuery2->ExecSQL();
			send_tg_message();
			Form1->Memo2->Clear();
		}
		else
		{
			spam_signal=true;
        }
	}
	if (type==3)
	{
		Form1->ADOQuery3->Close();
		Form1->ADOQuery3->SQL->Clear();
		Form1->ADOQuery3->SQL->Add("SELECT cryptopiamarkets3.signaltime AS signaltime FROM cryptopiamarkets3 WHERE cryptopiamarkets3.label='"+label+"';");
		Form1->ADOQuery3->Open();
		signal_time = Form1->ADOQuery3->FieldByName("signaltime")->AsLargeInt;

		if ((current_time-signal_time) > edit_time)
		{
			Form1->ADOQuery3->Close();
			Form1->ADOQuery3->SQL->Clear();
			Form1->ADOQuery3->SQL->Add("UPDATE cryptopiamarkets3 SET cryptopiamarkets3.signaltime = '"+IntToStr(current_time)+"' WHERE cryptopiamarkets3.label='"+label+"';");
			Form1->ADOQuery3->ExecSQL();
			send_tg_message();
			Form1->Memo2->Clear();
		}
		else
		{
			spam_signal=true;
        }
	}

	if (spam_signal==true)
	{
		ofstream fout;
		fout.open("spam.txt",ios::app);
		fout<<(AnsiString(label)+" ��� ��������� "+IntToStr((current_time-signal_time)/1000)+" ������ �����!").c_str()<<std::endl;
		fout.close();
	}
}

//---------------------------------------------------------------------------
void __fastcall TSearchThread1::send_tg_message()//������� ��������� � tg
{
	String messages_send="https://api.telegram.org/bot672161629:AAGdGgdDATn5Ghl7yFp9_jnNEj_jeq5EDZA/sendMessage?chat_id=-1001163041414&text=";
	messages_send.operator +=(Form1->Memo2->Text);
	Form1->Memo2->Clear();
	try
	{
		Form1->IdHTTP5->ReadTimeout=30000;
		Form1->IdHTTP5->ConnectTimeout=30000;
		String buf=Form1->IdHTTP5->Get(TIdURI::URLEncode(messages_send));
		ofstream fout2;
		fout2.open("log_tg.txt",ios::app);
		fout2<<AnsiString(buf).c_str()<<std::endl<<std::endl;
		fout2.close();
		if ((Pos("error",buf)!=0))
		{
			//Application->ProcessMessages();
			Sleep(30000);
			buf = Form1->IdHTTP5->Get(TIdURI::URLEncode(messages_send));
		}
	}
	catch (EIdException &E)
	{
		String buf=Form1->IdHTTP5->Get(TIdURI::URLEncode(messages_send));
		ofstream fout3;
		fout3.open("log_exception.txt",ios::app);
		fout3<<AnsiString(E.Message+" ----- "+buf).c_str()<<std::endl<<std::endl;
		fout3.close();
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TSearchThread1::AddLineMemo1()
{
	if (type==1)
	{
		Form1->Memo1->Lines->Add(memoline);
	}
	if (type==2)
	{
		Form1->Memo3->Lines->Add(memoline);
	}
	if (type==3)
	{
		Form1->Memo4->Lines->Add(memoline);
	}
}
//---------------------------------------------------------------------------
void __fastcall TSearchThread1::AddLineMemo2()
{
	Form1->Memo2->Lines->Add(memoline);
}
//---------------------------------------------------------------------------
String __fastcall TSearchThread1::move_dot_in_string(String all, int n)
{
	int p=Pos('.',all);

	String temp=StringReplace(all,".","", TReplaceFlags());
	String temp2=temp;
	String start,end,final;
	if (p==0)//���� ���� �����
	{
		//������� �� ���������� ���������, ����  ����� ����� ����� ������ 1000 ��� n=3. ��� ������ 10000 ��� n=4
		start=temp.Delete(temp.Length()-n+1,temp.Length());
		end=temp2.Delete(1,temp2.Length()-n);
		final=start+"."+end;
	}
	else
	{
		p=p-n;//���������� ����� �� n ����� ����� (�������� ����� �� n)
		if (p<=0)
		{
			start="0.";
			while (p!=0)
			{
				start=start+"0";
				++p;
			}
			end=temp;
			final=start+end;
		}
		else
		{
			if (p==1)
			{
				start="0.";
				end=temp;
				final=start+end;
			}
			if (p>=2)
			{
				start=temp.Delete(p,temp.Length());
				end=temp2.Delete(1,p-1);
				final=start+"."+end;
			}
		}
	}

	return final;
}
//---------------------------------------------------------------------------
void __fastcall TSearchThread1::MainFunction()
{
	String getmarkets, markets_html, market, check_result;

	memoline = "�������� ����������� �����..."; Synchronize(AddLineMemo1);

	//�������� api ��������� �� https://www.cryptopia.co.nz/Forum/Thread/255
	if (Form1->RadioButton1->Checked==true)
	{
		getmarkets = "https://www.cryptopia.co.nz/api/GetMarkets/BTC/"+Form1->Edit4->Text;//��� ���� � ��������� �� Edit4 �����.
	}
	if (Form1->RadioButton2->Checked==true)
	{
		getmarkets = "https://www.cryptopia.co.nz/api/GetMarkets/USDT/"+Form1->Edit4->Text;//��� ���� � USDT �� Edit4 �����.
	}

	bool passed;
	String  st_basevolume,  st_buyvolume, st_sellvolume, st_askprice, label, label_url;
	float basevolume, buyvolume, sellvolume, askprice, ratio,
	previousbasevolume, previousbuyvolume, previoussellvolume, previousaskprice,
	edit_basevolumediff, edit_basevolumeratio, edit_buyratiosell, edit_askpricedump, edit_time;

	if (type==1)
	{
		edit_basevolumediff=StrToFloat(Form1->Edit1->Text);
		edit_basevolumeratio=StrToFloat(Form1->Edit3->Text);
		edit_buyratiosell=StrToFloat(Form1->Edit2->Text);
		edit_askpricedump=StrToFloat(Form1->Edit6->Text);
		edit_time=StrToFloat(Form1->Edit5->Text);
	}
	if (type==2)
	{
		edit_basevolumediff=StrToFloat(Form1->Edit8->Text);
		edit_basevolumeratio=StrToFloat(Form1->Edit10->Text);
		edit_buyratiosell=StrToFloat(Form1->Edit9->Text);
		edit_askpricedump=StrToFloat(Form1->Edit11->Text);
		edit_time=StrToFloat(Form1->Edit7->Text);
	}
	if (type==3)
	{
		edit_basevolumediff=StrToFloat(Form1->Edit13->Text);
		edit_basevolumeratio=StrToFloat(Form1->Edit15->Text);
		edit_buyratiosell=StrToFloat(Form1->Edit14->Text);
		edit_askpricedump=StrToFloat(Form1->Edit16->Text);
		edit_time=StrToFloat(Form1->Edit12->Text);
	}

	memoline = "���������� Get-������ \"GetMarkets\""; Synchronize(AddLineMemo1);
	if (type==1)
	{
		try
		{
			markets_html = Form1->IdHTTP1->Get(getmarkets);//���������� Get-������ � �������� ����� html �������� � �������
		}
		catch (EIdException &E)
		{
			ofstream fout3;
			fout3.open("log_getmarkets_exception.txt");
			fout3<<markets_html.c_str()<<std::endl;
			fout3<<AnsiString(E.Message).c_str()<<std::endl<<std::endl;
			fout3.close();

			Form1->IdHTTP1->Socket->Close();
			Sleep(10000);
			Form1->IdHTTP1->Socket->Open();
			markets_html=Form1->IdHTTP1->Get(getmarkets);
		}
	}
	if (type==2)
	{
        try
		{
			markets_html = Form1->IdHTTP2->Get(getmarkets);//���������� Get-������ � �������� ����� html �������� � �������
		}
		catch (EIdException &E)
		{
			ofstream fout3;
			fout3.open("log_getmarkets_exception.txt");
			fout3<<markets_html.c_str()<<std::endl;
			fout3<<AnsiString(E.Message).c_str()<<std::endl<<std::endl;
			fout3.close();

			Form1->IdHTTP2->Socket->Close();
			Sleep(10000);
			Form1->IdHTTP1->Socket->Open();
			markets_html=Form1->IdHTTP1->Get(getmarkets);
		}
	}
	if (type==3)
	{
		try
		{
			markets_html = Form1->IdHTTP3->Get(getmarkets);//���������� Get-������ � �������� ����� html �������� � �������
		}
		catch (EIdException &E)
		{
			ofstream fout3;
			fout3.open("log_getmarkets_exception.txt");
			fout3<<markets_html.c_str()<<std::endl;
			fout3<<AnsiString(E.Message).c_str()<<std::endl<<std::endl;
			fout3.close();

			Form1->IdHTTP3->Socket->Close();
			Sleep(10000);
			Form1->IdHTTP3->Socket->Open();
			markets_html=Form1->IdHTTP1->Get(getmarkets);
		}}

	while (Form1->SearchText("{\"TradePairId\"", "}", markets_html, 0, 1) == "Error")//������� ����, ���� �� ������� �������� � �������
	{
		if (type==1)
		{
			markets_html = Form1->IdHTTP1->Get(getmarkets);//���������� Get-������ � �������� ����� html �������� � �������
		}
		if (type==2)
		{
			markets_html = Form1->IdHTTP2->Get(getmarkets);//���������� Get-������ � �������� ����� html �������� � �������
		}
		if (type==3)
		{
			markets_html = Form1->IdHTTP3->Get(getmarkets);//���������� Get-������ � �������� ����� html �������� � �������
		}
	}

	while ((Form1->SearchText("{\"TradePairId\"", "}", markets_html, 0, 1) != "Error")&&(!Terminated))//���� ����� ���� �� html ��������
	{
		market = Form1->SearchText("{\"TradePairId\"", "}", markets_html, 0, 1);//���� ����� market �� �������� markets_html
		label = Form1->SearchText("\"Label\":\"", "\"", market, 0, 0);//�������� �������� ����� market
		st_basevolume = Form1->SearchText("\"BaseVolume\":", ",", market, 0, 0);//�������� BaseVolume ����� market
		st_buyvolume = Form1->SearchText("\"BuyVolume\":", ",", market, 0, 0);//�������� BuyVolume ����� market
		st_sellvolume = Form1->SearchText("\"SellVolume\":", ",", market, 0, 0);//�������� SellVolume ����� market
		st_askprice = Form1->SearchText("\"AskPrice\":", ",", market, 0, 0);//�������� AskPrice ����� market
		if (Form1->RadioButton4->Checked==true)//��������� �����
		{
			st_basevolume = StringReplace(st_basevolume,".",",", TReplaceFlags()<<rfReplaceAll);
			st_buyvolume = StringReplace(st_buyvolume,".",",", TReplaceFlags()<<rfReplaceAll);
			st_sellvolume = StringReplace(st_sellvolume,".",",", TReplaceFlags()<<rfReplaceAll);
			st_askprice = StringReplace(st_askprice,".",",", TReplaceFlags()<<rfReplaceAll);
		}
		basevolume = StrToFloat(st_basevolume);
		/*String randdd=1000;
		move_dot_in_string(randdd, 3); */
		//buyvolume = StrToFloat(move_dot_in_string(st_buyvolume, 3));
		//sellvolume = StrToFloat(move_dot_in_string(st_sellvolume, 3));
		buyvolume = StrToFloat(st_buyvolume);
		sellvolume = StrToFloat(st_sellvolume);
		askprice = StrToFloat(st_askprice);

		memoline = "��������� ����� "+label; Synchronize(AddLineMemo1);

		//���������, ������������ �� ��� ����� � ������� cryptopiamarkets:
		int countmarket;
        if (type==1)
		{
            Form1->ADOQuery1->Close();
			Form1->ADOQuery1->SQL->Clear();
			Form1->ADOQuery1->SQL->Add("SELECT COUNT (*) AS countmarket FROM cryptopiamarkets WHERE cryptopiamarkets.label ='"+label+"';");
			Form1->ADOQuery1->Open();
			countmarket = Form1->ADOQuery1->FieldByName("countmarket")->AsInteger;
		}
		if (type==2)
		{
			Form1->ADOQuery2->Close();
			Form1->ADOQuery2->SQL->Clear();
			Form1->ADOQuery2->SQL->Add("SELECT COUNT (*) AS countmarket FROM cryptopiamarkets2 WHERE cryptopiamarkets2.label ='"+label+"';");
			Form1->ADOQuery2->Open();
			countmarket = Form1->ADOQuery2->FieldByName("countmarket")->AsInteger;
		}
		if (type==3)
		{
			Form1->ADOQuery3->Close();
			Form1->ADOQuery3->SQL->Clear();
			Form1->ADOQuery3->SQL->Add("SELECT COUNT (*) AS countmarket FROM cryptopiamarkets3 WHERE cryptopiamarkets3.label ='"+label+"';");
			Form1->ADOQuery3->Open();
			countmarket = Form1->ADOQuery3->FieldByName("countmarket")->AsInteger;
		}

		if (countmarket==0)//���� ����� ��� � �������, ������ ���
		{
			memoline = "����� �� ���� � �������, ������ ���"; Synchronize(AddLineMemo1);
			if (type==1)
			{
				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("Insert into cryptopiamarkets Values ('"+label+"','"+basevolume+"','"+buyvolume+"','"+sellvolume+"','"+askprice+"','0');");
				Form1->ADOQuery1->ExecSQL();
			}
			if (type==2)
			{
				Form1->ADOQuery2->Close();
				Form1->ADOQuery2->SQL->Clear();
				Form1->ADOQuery2->SQL->Add("Insert into cryptopiamarkets2 Values ('"+label+"','"+basevolume+"','"+buyvolume+"','"+sellvolume+"','"+askprice+"','0');");
				Form1->ADOQuery2->ExecSQL();
			}
			if (type==3)
			{
				Form1->ADOQuery3->Close();
				Form1->ADOQuery3->SQL->Clear();
				Form1->ADOQuery3->SQL->Add("Insert into cryptopiamarkets3 Values ('"+label+"','"+basevolume+"','"+buyvolume+"','"+sellvolume+"','"+askprice+"','0');");
				Form1->ADOQuery3->ExecSQL();
			}
		}
		if (countmarket==1)//���� ����� ������������ � �������
		{
			memoline = "����� ������������ � �������"; Synchronize(AddLineMemo1);
            if (type==1)
			{
				//������� ���������� �������� BaseVolume:
				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("SELECT cryptopiamarkets.basevolume AS previousbasevolume FROM cryptopiamarkets WHERE cryptopiamarkets.label='"+label+"';");
				Form1->ADOQuery1->Open();
				previousbasevolume = Form1->ADOQuery1->FieldByName("previousbasevolume")->AsFloat;
				//������� ���������� �������� BuyVolume:
				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("SELECT cryptopiamarkets.buyvolume AS previousbuyvolume FROM cryptopiamarkets WHERE cryptopiamarkets.label='"+label+"';");
				Form1->ADOQuery1->Open();
				previousbuyvolume = Form1->ADOQuery1->FieldByName("previousbuyvolume")->AsFloat;
				//������� ���������� �������� SellVolume:
				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("SELECT cryptopiamarkets.sellvolume AS previoussellvolume FROM cryptopiamarkets WHERE cryptopiamarkets.label='"+label+"';");
				Form1->ADOQuery1->Open();
				previoussellvolume = Form1->ADOQuery1->FieldByName("previoussellvolume")->AsFloat;
				//������� ���������� �������� AskPrice:
				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("SELECT cryptopiamarkets.askprice AS previousaskprice FROM cryptopiamarkets WHERE cryptopiamarkets.label='"+label+"';");
				Form1->ADOQuery1->Open();
				previousaskprice = Form1->ADOQuery1->FieldByName("previousaskprice")->AsFloat;
			}
			if (type==2)
			{
				//������� ���������� �������� BaseVolume:
				Form1->ADOQuery2->Close();
				Form1->ADOQuery2->SQL->Clear();
				Form1->ADOQuery2->SQL->Add("SELECT cryptopiamarkets2.basevolume AS previousbasevolume FROM cryptopiamarkets2 WHERE cryptopiamarkets2.label='"+label+"';");
				Form1->ADOQuery2->Open();
				previousbasevolume = Form1->ADOQuery2->FieldByName("previousbasevolume")->AsFloat;
				//������� ���������� �������� BuyVolume:
				Form1->ADOQuery2->Close();
				Form1->ADOQuery2->SQL->Clear();
				Form1->ADOQuery2->SQL->Add("SELECT cryptopiamarkets2.buyvolume AS previousbuyvolume FROM cryptopiamarkets2 WHERE cryptopiamarkets2.label='"+label+"';");
				Form1->ADOQuery2->Open();
				previousbuyvolume = Form1->ADOQuery2->FieldByName("previousbuyvolume")->AsFloat;
				//������� ���������� �������� SellVolume:
				Form1->ADOQuery2->Close();
				Form1->ADOQuery2->SQL->Clear();
				Form1->ADOQuery2->SQL->Add("SELECT cryptopiamarkets2.sellvolume AS previoussellvolume FROM cryptopiamarkets2 WHERE cryptopiamarkets2.label='"+label+"';");
				Form1->ADOQuery2->Open();
				previoussellvolume = Form1->ADOQuery2->FieldByName("previoussellvolume")->AsFloat;
				//������� ���������� �������� AskPrice:
				Form1->ADOQuery2->Close();
				Form1->ADOQuery2->SQL->Clear();
				Form1->ADOQuery2->SQL->Add("SELECT cryptopiamarkets2.askprice AS previousaskprice FROM cryptopiamarkets2 WHERE cryptopiamarkets2.label='"+label+"';");
				Form1->ADOQuery2->Open();
				previousaskprice = Form1->ADOQuery2->FieldByName("previousaskprice")->AsFloat;
			}
			if (type==3)
			{
				//������� ���������� �������� BaseVolume:
				Form1->ADOQuery3->Close();
				Form1->ADOQuery3->SQL->Clear();
				Form1->ADOQuery3->SQL->Add("SELECT cryptopiamarkets3.basevolume AS previousbasevolume FROM cryptopiamarkets3 WHERE cryptopiamarkets3.label='"+label+"';");
				Form1->ADOQuery3->Open();
				previousbasevolume = Form1->ADOQuery3->FieldByName("previousbasevolume")->AsFloat;
				//������� ���������� �������� BuyVolume:
				Form1->ADOQuery3->Close();
				Form1->ADOQuery3->SQL->Clear();
				Form1->ADOQuery3->SQL->Add("SELECT cryptopiamarkets3.buyvolume AS previousbuyvolume FROM cryptopiamarkets3 WHERE cryptopiamarkets3.label='"+label+"';");
				Form1->ADOQuery3->Open();
				previousbuyvolume = Form1->ADOQuery3->FieldByName("previousbuyvolume")->AsFloat;
				//������� ���������� �������� SellVolume:
				Form1->ADOQuery3->Close();
				Form1->ADOQuery3->SQL->Clear();
				Form1->ADOQuery3->SQL->Add("SELECT cryptopiamarkets3.sellvolume AS previoussellvolume FROM cryptopiamarkets3 WHERE cryptopiamarkets3.label='"+label+"';");
				Form1->ADOQuery3->Open();
				previoussellvolume = Form1->ADOQuery3->FieldByName("previoussellvolume")->AsFloat;
				//������� ���������� �������� AskPrice:
				Form1->ADOQuery3->Close();
				Form1->ADOQuery3->SQL->Clear();
				Form1->ADOQuery3->SQL->Add("SELECT cryptopiamarkets3.askprice AS previousaskprice FROM cryptopiamarkets3 WHERE cryptopiamarkets3.label='"+label+"';");
				Form1->ADOQuery3->Open();
				previousaskprice = Form1->ADOQuery3->FieldByName("previousaskprice")->AsFloat;
			}

			//�������� ���� �� �������:
			if ((previousaskprice/askprice>=edit_askpricedump)&&(askprice>=0.00000003))
			{
				memoline = "������ ������! ���� ����� � "+FloatToStr(RoundTo(previousaskprice/askprice,-3))+" ����"; Synchronize(AddLineMemo1);
				label_url = StringReplace(label,"/","_", TReplaceFlags());
				memoline = "���� �� ������� ����� � "+FloatToStr(RoundTo(previousaskprice/askprice,-3))+" ����! "+label+"!"+" (�� "+FloatToStr(RoundTo(edit_time,-3))+" ���)"+"\r\n"
				+ "https://www.cryptopia.co.nz/Exchange/?market="+label_url+"\r\n"
				+ "������� AskPrice: "+FloatToStr(previousaskprice)+"\r\n"
				+ "������� AskPrice: "+FloatToStr(askprice)+"\r\n"
				+ "������� BidPrice: "+Form1->SearchText("\"BidPrice\":", ",", market, 0, 0);
				Synchronize(AddLineMemo2);
				//Form1->send_vk_message(0);
				UpdateSignalTime(label);
			}

			//�������� �������:
			passed=false;
			if (basevolume-previousbasevolume >= edit_basevolumediff)//���� ������� BaseVolume ������ ���������� ��������
			{
				memoline = "������� BaseVolume "+FloatToStr(RoundTo(basevolume-previousbasevolume,-3)); Synchronize(AddLineMemo1);
				if (previousbasevolume!=0)//���� ���������� BaseVolume �� ����� ���� (����� ��������� ��������)
				{
					if (basevolume/previousbasevolume >= edit_basevolumeratio)//�� ������ ��� ���� �������� �� ��������� BaseVolume
					{
						memoline = "��������� BaseVolume "+FloatToStr(RoundTo(basevolume/previousbasevolume,-3)); Synchronize(AddLineMemo1);
						passed=true;
					}
				}
				else //���� ���������� BaseVolume �� ����� ����, �� �� ������ �������� �� ��������� (�.�. ������ �� ���� ������)
				{
					passed=true;
				}

				if ((buyvolume-previousbuyvolume>0)&&(passed==true))//������ ���� BuyVolume ����������
				{
					memoline = "����� �� ������� ����������"; Synchronize(AddLineMemo1);
					if ((sellvolume<=previoussellvolume)||(sellvolume==0))//���� SellVolume ���������� ��� ����� 0
					{
						memoline = "����� �� ������� ���������� ��� ����� 0"; Synchronize(AddLineMemo1);
						memoline = "������ ������!"; Synchronize(AddLineMemo1);
						label_url = StringReplace(label,"/","_", TReplaceFlags());
						memoline = "����� ��ڨ�! "+label+"!"+" (�� "+FloatToStr(RoundTo(edit_time,-3))+" ���)"+"\r\n"
						+ "https://www.cryptopia.co.nz/Exchange/?market="+label_url+"\r\n"
						+ "������� ����� "+FloatToStr(RoundTo(previousbasevolume,-3))+"\r\n"
						+ "������� ����� "+FloatToStr(RoundTo(basevolume,-3))+"\r\n"
						+ "��������� ������ ������� "+FloatToStr(RoundTo(buyvolume-previousbuyvolume,-3))+"\r\n"
						+ "��������� ������ ������� "+FloatToStr(RoundTo(sellvolume-previoussellvolume,-3))+"\r\n"
						+ "���� �� ������� (Ask): "+Form1->SearchText("\"AskPrice\":", ",", market, 0, 0)+"\r\n"
						+ "���� �� ������� (Bid): "+Form1->SearchText("\"BidPrice\":", ",", market, 0, 0);
						Synchronize(AddLineMemo2);
						//Form1->send_vk_message(0);
						UpdateSignalTime(label);
					}
					else//���� SellVolume ���� ����������
					{
						memoline = "����� �� ������� ����������"; Synchronize(AddLineMemo1);
						//�������� ����������� ��������� BuyVolume � ��������� SellVolume
						ratio=(buyvolume-previousbuyvolume)/(sellvolume-previoussellvolume);
						memoline = "����������� ������� "+FloatToStr(RoundTo(ratio,-3)); Synchronize(AddLineMemo1);
						if (ratio>=edit_buyratiosell)
						{
							memoline = "������ ������!"; Synchronize(AddLineMemo1);
							label_url = StringReplace(label,"/","_", TReplaceFlags());
							memoline = "����� ��ڨ�! "+label+"!"+" (�� "+FloatToStr(RoundTo(edit_time,-3))+" ���)"+"\r\n"
							+ "https://www.cryptopia.co.nz/Exchange/?market="+label_url+"\r\n"
							+ "������� ����� "+FloatToStr(RoundTo(previousbasevolume,-3))+"\r\n"
							+ "������� ����� "+FloatToStr(RoundTo(basevolume,-3))+"\r\n"
							+ "��������� ������ ������� "+FloatToStr(RoundTo(buyvolume-previousbuyvolume,-3))+"\r\n"
							+ "��������� ������ ������� "+FloatToStr(RoundTo(sellvolume-previoussellvolume,-3))+"\r\n"
							+ "���� �� ������� (Ask): "+Form1->SearchText("\"AskPrice\":", ",", market, 0, 0)+"\r\n"
							+ "���� �� ������� (Bid): "+Form1->SearchText("\"BidPrice\":", ",", market, 0, 0);
							Synchronize(AddLineMemo2);
							//Form1->send_vk_message(0);
							UpdateSignalTime(label);
						}

					}

				}
			}
			//������� ����� �������� ������� ��� ����� ����� � �������
			if (type==1)
			{
				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("UPDATE cryptopiamarkets SET cryptopiamarkets.basevolume = '"+FloatToStr(basevolume)+"', cryptopiamarkets.buyvolume = '"+FloatToStr(buyvolume)+"', cryptopiamarkets.sellvolume = '"+FloatToStr(sellvolume)+"', cryptopiamarkets.askprice = '"+FloatToStr(askprice)+"' WHERE cryptopiamarkets.label='"+label+"';");
				Form1->ADOQuery1->ExecSQL();
			}
			if (type==2)
			{
				Form1->ADOQuery2->Close();
				Form1->ADOQuery2->SQL->Clear();
				Form1->ADOQuery2->SQL->Add("UPDATE cryptopiamarkets2 SET cryptopiamarkets2.basevolume = '"+FloatToStr(basevolume)+"', cryptopiamarkets2.buyvolume = '"+FloatToStr(buyvolume)+"', cryptopiamarkets2.sellvolume = '"+FloatToStr(sellvolume)+"', cryptopiamarkets2.askprice = '"+FloatToStr(askprice)+"' WHERE cryptopiamarkets2.label='"+label+"';");
				Form1->ADOQuery2->ExecSQL();
			}
			if (type==3)
			{
				Form1->ADOQuery3->Close();
				Form1->ADOQuery3->SQL->Clear();
				Form1->ADOQuery3->SQL->Add("UPDATE cryptopiamarkets3 SET cryptopiamarkets3.basevolume = '"+FloatToStr(basevolume)+"', cryptopiamarkets3.buyvolume = '"+FloatToStr(buyvolume)+"', cryptopiamarkets3.sellvolume = '"+FloatToStr(sellvolume)+"', cryptopiamarkets3.askprice = '"+FloatToStr(askprice)+"' WHERE cryptopiamarkets3.label='"+label+"';");
				Form1->ADOQuery3->ExecSQL();
			}
		}
		if (countmarket>1)//���� ���� � ��� �� ����� ������������ � 2 ��� ����� �������� �������, �� ��� ������
		{
			memoline = "������: ���������� ����� ����� � ������� ������ 1"; Synchronize(AddLineMemo1);
			exit(1);//����� �� ���������
		}

		markets_html = StringReplace(markets_html,market,"", TReplaceFlags());//������ ��������������� ����� � html �������� markets

		if (Terminated){memoline = "��������� ������"; Synchronize(AddLineMemo1);break;}//���� ���� ������ ������ "���������� �����", �� ������� �� ����� �����
	}

	memoline = "----------------------------------------------------"; Synchronize(AddLineMemo1);
}

//---------------------------------------------------------------------------
void __fastcall TSearchThread1::Execute()
{
	FreeOnTerminate = true;
	/*while (!Terminated)
	{
		MainFunction();
		Sleep(1000*60*StrToFloat(Form1->Edit5->Text));
		if (Terminated){memoline = "��������� ������"; Synchronize(AddLineMemo1);}
	}*/
	__int64 time;
	__int64 time_temp1, time_temp2=1488;
	__int64 time_edit;
    if (type==1)
	{
		time_edit=1000*60*StrToFloat(Form1->Edit5->Text);
	}
	if (type==2)
	{
		time_edit=1000*60*StrToFloat(Form1->Edit7->Text);
	}
	if (type==3)
	{
		time_edit=1000*60*StrToFloat(Form1->Edit12->Text);
	}
	bool seconds_countdown = false;
	if (time_edit<=1000*60){seconds_countdown = true;}
	while (!Terminated)
	{
		MainFunction();
		time = GetTickCount();
		while(((GetTickCount()-time)<time_edit)&&(!Terminated))
		{
			time_temp1=GetTickCount()-time;
			if ((time_temp1!=time_temp2)&&(time_temp1%1000==0)&&(seconds_countdown==true))
			{
				memoline = "��� "+IntToStr((time_edit-time_temp1)/1000)+" ���..."; Synchronize(AddLineMemo1);
			}
			if ((time_temp1!=time_temp2)&&((time_temp1%(1000*60))==0)&&(seconds_countdown==false))
			{
				memoline = "��� "+IntToStr((time_edit-time_temp1)/(1000*60))+" ���..."; Synchronize(AddLineMemo1);
			}
			time_temp2=time_temp1;
		}
	}
}
//---------------------------------------------------------------------------
