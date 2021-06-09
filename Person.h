#pragma once
#include<map>
using namespace std;
class Person
{
public:
	Person();
	~Person();
	Person(CString name,
		CString gender,
		CString sid,
		long money);
	CString name;
	CString gender;
	CString sid;
	long money;
	map<CString, long> personGift;
};
