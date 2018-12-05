//---------------------------------------------------------------------------

#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TSearchThread1 : public TThread
{
private:
	String memoline;
	int type;
protected:
	void __fastcall Execute();
public:
	__fastcall TSearchThread1(bool CreateSuspended);
	__fastcall TSearchThread1(bool CreateSuspended, int t);
	void __fastcall AddLineMemo1();
	void __fastcall AddLineMemo2();
	String __fastcall move_dot_in_string(String all, int n);
	void __fastcall MainFunction();
	void __fastcall send_tg_message();
	void __fastcall UpdateSignalTime(String label);
};
//---------------------------------------------------------------------------
#endif
