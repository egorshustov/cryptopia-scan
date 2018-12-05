//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TSearchThread : public TThread
{
private:
	String memoline;
protected:
	void __fastcall Execute();
public:
	__fastcall TSearchThread(bool CreateSuspended);
	void __fastcall AddLineMemo1();
	void __fastcall AddLineMemo2();
    String __fastcall move_dot_in_string(String all, int n);
};
//---------------------------------------------------------------------------
#endif
