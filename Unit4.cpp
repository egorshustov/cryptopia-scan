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
// Эта нить крутит саму себя в цикле без интервалов, пока не будет отмены

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
	if (p==0)//если нету точки
	{
		//функция не отработает корректно, если  будет целое число меньше 1000 при n=3. Или меньше 10000 при n=4
		start=temp.Delete(temp.Length()-n+1,temp.Length());
		end=temp2.Delete(1,temp2.Length()-n);
		final=start+"."+end;
	}
	else
	{
		p=p-n;//передвинем точку на n знака влево (разделим число на n)
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

	memoline = "Начинаем сканировать рынки..."; Synchronize(AddLineMemo1);

	//описание api криптопии на https://www.cryptopia.co.nz/Forum/Thread/255
	if (Form1->RadioButton1->Checked==true)
	{
		getmarkets = "https://www.cryptopia.co.nz/api/GetMarkets/BTC/"+Form1->Edit4->Text;//все пары с биткойном за Edit4 часов.
	}
	if (Form1->RadioButton2->Checked==true)
	{
		getmarkets = "https://www.cryptopia.co.nz/api/GetMarkets/USDT/"+Form1->Edit4->Text;//все пары с USDT за Edit4 часов.
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

	while(!Terminated)//бесконечный цикл сканирования рынков
	{
		memoline = "отправляем Get-запрос \"GetMarkets\""; Synchronize(AddLineMemo1);
		markets_html = Form1->IdHTTP1->Get(getmarkets);//отправляем Get-запрос и получаем новую html страницу с рынками

		if (Form1->SearchText("{\"TradePairId\"", "}", markets_html, 0, 1) != "Error")//если страница с рынками, то зафиксируем время
		{
			previouspagetime=pagetime;
			pagetime=Now();
			difftime=pagetime-previouspagetime;

			pagetime_secs = Form1->DateTimeToUnixx(pagetime);
			previouspagetime_secs = Form1->DateTimeToUnixx(previouspagetime);
			difftime_secs = pagetime_secs-previouspagetime_secs;
		}

		while ((Form1->SearchText("{\"TradePairId\"", "}", markets_html, 0, 1) != "Error")&&(!Terminated))//пока рынки есть на html странице
		{
			market = Form1->SearchText("{\"TradePairId\"", "}", markets_html, 0, 1);//берём рынок market со страницы markets_html
			label = Form1->SearchText("\"Label\":\"", "\"", market, 0, 0);//получаем название рынка market
			st_basevolume = Form1->SearchText("\"BaseVolume\":", ",", market, 0, 0);//получаем BaseVolume рынка market
			st_buyvolume = Form1->SearchText("\"BuyVolume\":", ",", market, 0, 0);//получаем BuyVolume рынка market
			st_sellvolume = Form1->SearchText("\"SellVolume\":", ",", market, 0, 0);//получаем SellVolume рынка market
			st_askprice = Form1->SearchText("\"AskPrice\":", ",", market, 0, 0);//получаем AskPrice рынка market
			basevolume = StrToFloat(st_basevolume);
			/*String randdd=1000;
			move_dot_in_string(randdd, 3); */
			//buyvolume = StrToFloat(move_dot_in_string(st_buyvolume, 3));
			//sellvolume = StrToFloat(move_dot_in_string(st_sellvolume, 3));
			buyvolume = StrToFloat(st_buyvolume);
			sellvolume = StrToFloat(st_sellvolume);
			askprice = StrToFloat(st_askprice);

			memoline = "Проверяем рынок "+label; Synchronize(AddLineMemo1);

			//определим, присутствует ли уже рынок в таблице cryptopiamarkets:
			Form1->ADOQuery1->Close();
			Form1->ADOQuery1->SQL->Clear();
			Form1->ADOQuery1->SQL->Add("SELECT COUNT (*) AS countmarket FROM cryptopiamarkets WHERE cryptopiamarkets.label ='"+label+"';");
			Form1->ADOQuery1->Open();
			int countmarket = Form1->ADOQuery1->FieldByName("countmarket")->AsInteger;

			if (countmarket==0)//если рынка нет в таблице, занесём его
			{
				memoline = "Рынка не было в таблице, занесём его"; Synchronize(AddLineMemo1);

				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("Insert into cryptopiamarkets Values ('"+label+"','"+basevolume+"','"+buyvolume+"','"+sellvolume+"','"+askprice+"');");
				Form1->ADOQuery1->ExecSQL();
			}
			if (countmarket==1)//если рынок присутствует в таблице
			{
				memoline = "Рынок присутствует в таблице"; Synchronize(AddLineMemo1);
				//получим предудущее значение BaseVolume:
				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("SELECT cryptopiamarkets.basevolume AS previousbasevolume FROM cryptopiamarkets WHERE cryptopiamarkets.label='"+label+"';");
				Form1->ADOQuery1->Open();
				previousbasevolume = Form1->ADOQuery1->FieldByName("previousbasevolume")->AsFloat;
				//получим предудущее значение BuyVolume:
				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("SELECT cryptopiamarkets.buyvolume AS previousbuyvolume FROM cryptopiamarkets WHERE cryptopiamarkets.label='"+label+"';");
				Form1->ADOQuery1->Open();
				previousbuyvolume = Form1->ADOQuery1->FieldByName("previousbuyvolume")->AsFloat;
				//получим предудущее значение SellVolume:
				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("SELECT cryptopiamarkets.sellvolume AS previoussellvolume FROM cryptopiamarkets WHERE cryptopiamarkets.label='"+label+"';");
				Form1->ADOQuery1->Open();
				previoussellvolume = Form1->ADOQuery1->FieldByName("previoussellvolume")->AsFloat;

				//получим предудущее значение AskPrice:
				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("SELECT cryptopiamarkets.askprice AS previousaskprice FROM cryptopiamarkets WHERE cryptopiamarkets.label='"+label+"';");
				Form1->ADOQuery1->Open();
				previousaskprice = Form1->ADOQuery1->FieldByName("previousaskprice")->AsFloat;

				//проверка цены на покупку:
				if (previousaskprice/askprice>=(StrToFloat(Form1->Edit6->Text)))
				{
					memoline = "ПОДАЁМ СИГНАЛ! Цена упала в "+FloatToStr(previousaskprice/askprice)+" раза"; Synchronize(AddLineMemo1);
					label_url = StringReplace(label,"/","_", TReplaceFlags());
					memoline = "ЦЕНА НА ПОКУПКУ УПАЛА В "+FloatToStr(previousaskprice/askprice)+" раза! "+label+"!"+" (за "+IntToStr(difftime_secs)+" сек)"+"\r\n"
					+ "https://www.cryptopia.co.nz/Exchange/?market="+label_url+"\r\n"
					+ "Прошлая AskPrice: "+FloatToStr(previousaskprice)+"\r\n"
					+ "Текущая AskPrice: "+FloatToStr(askprice)+"\r\n"
					+ "Текущая BidPrice: "+Form1->SearchText("\"BidPrice\":", ",", market, 0, 0);
					Synchronize(AddLineMemo2);
					Form1->send_vk_message(0);
				}

				//проверка объёмов:
				passed=false;
				if (basevolume-previousbasevolume >= StrToFloat(Form1->Edit1->Text))//если разница BaseVolume больше указанного значения
				{
					memoline = "Разница BaseVolume "+FloatToStr(basevolume-previousbasevolume); Synchronize(AddLineMemo1);
					if (previousbasevolume!=0)//если предыдущий BaseVolume не равен нулю (самая вероятная ситуация)
					{
						if (basevolume/previousbasevolume >= StrToFloat(Form1->Edit3->Text))//то делаем ещё одну проверку на отношение BaseVolume
						{
							memoline = "Отношение BaseVolume "+FloatToStr(basevolume/previousbasevolume); Synchronize(AddLineMemo1);
							passed=true;
						}
					}
					else //если предыдущий BaseVolume не равен нулю, то не делаем проверку на отношение (т.к. делить на ноль нельзя)
					{
						passed=true;
					}

					if ((buyvolume-previousbuyvolume>0)&&(passed==true))//только если BuyVolume увеличился
					{
						memoline = "Объём на покупку увеличился"; Synchronize(AddLineMemo1);
						if ((sellvolume<=previoussellvolume)||(sellvolume==0))//если SellVolume уменьшился или равен 0
						{
							memoline = "Объём на продажу уменьшился или равен 0"; Synchronize(AddLineMemo1);
							memoline = "ПОДАЁМ СИГНАЛ!"; Synchronize(AddLineMemo1);
							label_url = StringReplace(label,"/","_", TReplaceFlags());
							memoline = "ВЫРОС ОБЪЁМ! "+label+"!"+" (за "+IntToStr(difftime_secs)+" сек)"+"\r\n"
							+ "https://www.cryptopia.co.nz/Exchange/?market="+label_url+"\r\n"
							+ "Прошлый объём "+FloatToStr(previousbasevolume)+"\r\n"
							+ "Текущий объём "+FloatToStr(basevolume)+"\r\n"
							+ "Изменение объёма покупки "+FloatToStr(buyvolume-previousbuyvolume)+"\r\n"
							+ "Изменение объёма продажи "+FloatToStr(sellvolume-previoussellvolume)+"\r\n"
							+ "Цена на покупку (Ask): "+Form1->SearchText("\"AskPrice\":", ",", market, 0, 0)+"\r\n"
							+ "Цена на продажу (Bid): "+Form1->SearchText("\"BidPrice\":", ",", market, 0, 0);
							Synchronize(AddLineMemo2);
							Form1->send_vk_message(0);
						}
						else//если SellVolume тоже увеличился
						{
							memoline = "Объём на продажу увеличился"; Synchronize(AddLineMemo1);
							//находить соотношение изменения BuyVolume к изменению SellVolume
							ratio=(buyvolume-previousbuyvolume)/(sellvolume-previoussellvolume);
							memoline = "Соотношение объёмов "+FloatToStr(ratio); Synchronize(AddLineMemo1);
							if (ratio>=StrToFloat(Form1->Edit2->Text))
							{
								memoline = "ПОДАЁМ СИГНАЛ!"; Synchronize(AddLineMemo1);
								label_url = StringReplace(label,"/","_", TReplaceFlags());
								memoline = "ВЫРОС ОБЪЁМ! "+label+"!"+" (за "+IntToStr(difftime_secs)+" сек)"+"\r\n"
								+ "https://www.cryptopia.co.nz/Exchange/?market="+label_url+"\r\n"
								+ "Прошлый объём "+FloatToStr(previousbasevolume)+"\r\n"
								+ "Текущий объём "+FloatToStr(basevolume)+"\r\n"
								+ "Изменение объёма покупки "+FloatToStr(buyvolume-previousbuyvolume)+"\r\n"
								+ "Изменение объёма продажи "+FloatToStr(sellvolume-previoussellvolume)+"\r\n"
								+ "Цена на покупку (Ask): "+Form1->SearchText("\"AskPrice\":", ",", market, 0, 0)+"\r\n"
								+ "Цена на продажу (Bid): "+Form1->SearchText("\"BidPrice\":", ",", market, 0, 0);
								Synchronize(AddLineMemo2);
								Form1->send_vk_message(0);
							}

						}

					}
				}
				//заносим новое значение объёмов для этого рынка в таблицу
				Form1->ADOQuery1->Close();
				Form1->ADOQuery1->SQL->Clear();
				Form1->ADOQuery1->SQL->Add("UPDATE cryptopiamarkets SET cryptopiamarkets.basevolume = '"+FloatToStr(basevolume)+"', cryptopiamarkets.buyvolume = '"+FloatToStr(buyvolume)+"', cryptopiamarkets.sellvolume = '"+FloatToStr(sellvolume)+"', cryptopiamarkets.askprice = '"+FloatToStr(askprice)+"' WHERE cryptopiamarkets.label='"+label+"';");
				Form1->ADOQuery1->ExecSQL();
			}
			if (countmarket>1)//если один и тот же рынок присутствует в 2 или более строчках таблицы, то это ошибка
			{
				memoline = "Ошибка: количество этого рынка в таблице больше 1"; Synchronize(AddLineMemo1);
				exit(1);//выход из программы
			}

			markets_html = StringReplace(markets_html,market,"", TReplaceFlags());//удалим отсканированный рынок с html страницы markets

			if (Terminated){memoline = "Остановка поиска"; Synchronize(AddLineMemo1);break;}//если была нажата кнопка "Остановить поиск", то выходим из этого цикла
		}

		if (Terminated){break;}//если была нажата кнопка "Остановить поиск", то выходим из этого цикла
		memoline = "----------------------------------------------------"; Synchronize(AddLineMemo1);
	}
}
//---------------------------------------------------------------------------
