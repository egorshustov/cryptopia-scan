//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit4.h"
#include "Unit1.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TSearchThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
// ��� ���� ������ ���� ���� � ����� ��� ����������, ���� �� ����� ������

__fastcall TSearchThread::TSearchThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TSearchThread::AddLineMemo1()
{
	Form1->Memo1->Lines->Add(memoline);
}
//---------------------------------------------------------------------------
void __fastcall TSearchThread::AddLineMemo2()
{
	Form1->Memo2->Lines->Add(memoline);
}
//---------------------------------------------------------------------------
String __fastcall TSearchThread::move_dot_in_string(String all, int n)
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
void __fastcall TSearchThread::Execute()
{
	FreeOnTerminate = true;
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

	String  st_basevolume,  st_buyvolume, st_sellvolume, st_askprice, label, label_url;
	float basevolume, buyvolume, sellvolume, askprice, ratio,
	previousbasevolume, previousbuyvolume, previoussellvolume, previousaskprice;

	TDateTime pagetime, previouspagetime, difftime;
	//int pages_count=0;
	bool passed;
	int pagetime_secs, previouspagetime_secs, difftime_secs;
	Form1->IdHTTP1->ReadTimeout=3000;
	Form1->IdHTTP1->ConnectTimeout=3000;

	while(!Terminated)//����������� ���� ������������ ������
	{
		memoline = "���������� Get-������ \"GetMarkets\""; Synchronize(AddLineMemo1);
		markets_html = Form1->IdHTTP1->Get(getmarkets);//���������� Get-������ � �������� ����� html �������� � �������

		if (Form1->SearchText("{\"TradePairId\"", "}", markets_html, 0, 1) != "Error")//���� �������� � �������, �� ����������� �����
		{
			previouspagetime=pagetime;
			pagetime=Now();
			difftime=pagetime-previouspagetime;

			pagetime_secs = Form1->DateTimeToUnixx(pagetime);
			previouspagetime_secs = Form1->DateTimeToUnixx(previouspagetime);
			difftime_secs = pagetime_secs-previouspagetime_secs;
		}

		while ((Form1->SearchText("{\"TradePairId\"", "}", markets_html, 0, 1) != "Error")&&(!Terminated))//���� ����� ���� �� html ��������
		{
			market = Form1->SearchText("{\"TradePairId\"", "}", markets_html, 0, 1);//���� ����� market �� �������� markets_html
			label = Form1->SearchText("\"Label\":\"", "\"", market, 0, 0);//�������� �������� ����� market
			st_basevolume = Form1->SearchText("\"BaseVolume\":", ",", market, 0, 0);//�������� BaseVolume ����� market
			st_buyvolume = Form1->SearchText("\"BuyVolume\":", ",", market, 0, 0);//�������� BuyVolume ����� market
			st_sellvolume = Form1->SearchText("\"SellVolume\":", ",", market, 0, 0);//�������� SellVolume ����� market
			st_askprice = Form1->SearchText("\"AskPrice\":", ",", market, 0, 0);//�������� AskPrice ����� market
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
			Form1->ADOQuery1->Close();
			Form1->ADOQuery1->SQL->Clear();
			Form1->ADOQuery1->SQL->Add("SELECT COUNT (*) AS countmarket FROM cryptopiamarkets WHERE cryptopiamarkets.label ='"+label+"';");
			Form1->ADOQuery1->Open();
			int countmarket = Form1->ADOQuery1->FieldByName("countmarket")->AsInteger;

			if (countmarket==0)//���� ����� ��� � �������, ������ ���
			{
				memoline = "����� �� ���� � �������, ������ ���"; Synchronize(AddLineMemo1);

				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("Insert into cryptopiamarkets Values ('"+label+"','"+basevolume+"','"+buyvolume+"','"+sellvolume+"','"+askprice+"');");
				Form1->ADOQuery1->ExecSQL();
			}
			if (countmarket==1)//���� ����� ������������ � �������
			{
				memoline = "����� ������������ � �������"; Synchronize(AddLineMemo1);
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

				//�������� ���� �� �������:
				if (previousaskprice/askprice>=(StrToFloat(Form1->Edit6->Text)))
				{
					memoline = "������ ������! ���� ����� � "+FloatToStr(previousaskprice/askprice)+" ����"; Synchronize(AddLineMemo1);
					label_url = StringReplace(label,"/","_", TReplaceFlags());
					memoline = "���� �� ������� ����� � "+FloatToStr(previousaskprice/askprice)+" ����! "+label+"!"+" (�� "+IntToStr(difftime_secs)+" ���)"+"\r\n"
					+ "https://www.cryptopia.co.nz/Exchange/?market="+label_url+"\r\n"
					+ "������� AskPrice: "+FloatToStr(previousaskprice)+"\r\n"
					+ "������� AskPrice: "+FloatToStr(askprice)+"\r\n"
					+ "������� BidPrice: "+Form1->SearchText("\"BidPrice\":", ",", market, 0, 0);
					Synchronize(AddLineMemo2);
					Form1->send_vk_message(0);
				}

				//�������� �������:
				passed=false;
				if (basevolume-previousbasevolume >= StrToFloat(Form1->Edit1->Text))//���� ������� BaseVolume ������ ���������� ��������
				{
					memoline = "������� BaseVolume "+FloatToStr(basevolume-previousbasevolume); Synchronize(AddLineMemo1);
					if (previousbasevolume!=0)//���� ���������� BaseVolume �� ����� ���� (����� ��������� ��������)
					{
						if (basevolume/previousbasevolume >= StrToFloat(Form1->Edit3->Text))//�� ������ ��� ���� �������� �� ��������� BaseVolume
						{
							memoline = "��������� BaseVolume "+FloatToStr(basevolume/previousbasevolume); Synchronize(AddLineMemo1);
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
							memoline = "����� ��ڨ�! "+label+"!"+" (�� "+IntToStr(difftime_secs)+" ���)"+"\r\n"
							+ "https://www.cryptopia.co.nz/Exchange/?market="+label_url+"\r\n"
							+ "������� ����� "+FloatToStr(previousbasevolume)+"\r\n"
							+ "������� ����� "+FloatToStr(basevolume)+"\r\n"
							+ "��������� ������ ������� "+FloatToStr(buyvolume-previousbuyvolume)+"\r\n"
							+ "��������� ������ ������� "+FloatToStr(sellvolume-previoussellvolume)+"\r\n"
							+ "���� �� ������� (Ask): "+Form1->SearchText("\"AskPrice\":", ",", market, 0, 0)+"\r\n"
							+ "���� �� ������� (Bid): "+Form1->SearchText("\"BidPrice\":", ",", market, 0, 0);
							Synchronize(AddLineMemo2);
							Form1->send_vk_message(0);
						}
						else//���� SellVolume ���� ����������
						{
							memoline = "����� �� ������� ����������"; Synchronize(AddLineMemo1);
							//�������� ����������� ��������� BuyVolume � ��������� SellVolume
							ratio=(buyvolume-previousbuyvolume)/(sellvolume-previoussellvolume);
							memoline = "����������� ������� "+FloatToStr(ratio); Synchronize(AddLineMemo1);
							if (ratio>=StrToFloat(Form1->Edit2->Text))
							{
								memoline = "������ ������!"; Synchronize(AddLineMemo1);
								label_url = StringReplace(label,"/","_", TReplaceFlags());
								memoline = "����� ��ڨ�! "+label+"!"+" (�� "+IntToStr(difftime_secs)+" ���)"+"\r\n"
								+ "https://www.cryptopia.co.nz/Exchange/?market="+label_url+"\r\n"
								+ "������� ����� "+FloatToStr(previousbasevolume)+"\r\n"
								+ "������� ����� "+FloatToStr(basevolume)+"\r\n"
								+ "��������� ������ ������� "+FloatToStr(buyvolume-previousbuyvolume)+"\r\n"
								+ "��������� ������ ������� "+FloatToStr(sellvolume-previoussellvolume)+"\r\n"
								+ "���� �� ������� (Ask): "+Form1->SearchText("\"AskPrice\":", ",", market, 0, 0)+"\r\n"
								+ "���� �� ������� (Bid): "+Form1->SearchText("\"BidPrice\":", ",", market, 0, 0);
								Synchronize(AddLineMemo2);
								Form1->send_vk_message(0);
							}

						}

					}
				}
				//������� ����� �������� ������� ��� ����� ����� � �������
				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("UPDATE cryptopiamarkets SET cryptopiamarkets.basevolume = '"+FloatToStr(basevolume)+"', cryptopiamarkets.buyvolume = '"+FloatToStr(buyvolume)+"', cryptopiamarkets.sellvolume = '"+FloatToStr(sellvolume)+"', cryptopiamarkets.askprice = '"+FloatToStr(askprice)+"' WHERE cryptopiamarkets.label='"+label+"';");
				Form1->ADOQuery1->ExecSQL();
			}
			if (countmarket>1)//���� ���� � ��� �� ����� ������������ � 2 ��� ����� �������� �������, �� ��� ������
			{
				memoline = "������: ���������� ����� ����� � ������� ������ 1"; Synchronize(AddLineMemo1);
				exit(1);//����� �� ���������
			}

			markets_html = StringReplace(markets_html,market,"", TReplaceFlags());//������ ��������������� ����� � html �������� markets

			if (Terminated){memoline = "��������� ������"; Synchronize(AddLineMemo1);break;}//���� ���� ������ ������ "���������� �����", �� ������� �� ����� �����
		}

		if (Terminated){break;}//���� ���� ������ ������ "���������� �����", �� ������� �� ����� �����
		memoline = "----------------------------------------------------"; Synchronize(AddLineMemo1);
	}
}
//---------------------------------------------------------------------------
