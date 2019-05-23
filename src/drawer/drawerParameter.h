#pragma once


#include "../constParameter.h"

static string ws2s(wstring wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, 0);
	string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, 0);
	return strTo;

}

//--------------------------------------------------------------
static wstring s2ws(const string & str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

const int cAlchemicalSymbolPre = 0xd83d;
const int cAlchemicalSymbolMin = 0xdf00;
const int cAlchemicalSymbolMax = 0xdf73;
const int cAlchemicalSymbolNum = cAlchemicalSymbolMax - cAlchemicalSymbolMin;
