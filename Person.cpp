#include "pch.h"
#include "Person.h"
Person::Person()
{
}
Person::Person(CString name,
	           CString gender,
	           CString sid,
	           long money):name(name),gender(gender),sid(sid),money(money){}
Person::~Person()
{
}
