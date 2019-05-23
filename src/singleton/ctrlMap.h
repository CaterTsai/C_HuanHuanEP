#pragma once

#include <map>
using namespace std;

enum eCtrlType : int
{
	//global
	eCtrl_Global = 0

	, eCtrl_BPM
	, eCtrl_Start
	, eCtrl_Stop
	, eCtrl_NextScence
	, eCtrl_PrevScence
	, eCtrl_ChangeMaskAlpha
	, eCtrl_GlobalNum

	//scence
	, eCtrl_Scence = 30
	, eCtrl_Trigger
	
	, eCtrl_ViewSpeed
	, eCtrl_ViewNext
	, eCtrl_ViewPrev
	, eCtrl_ScenceNum

	//View
	, eCtrl_View = 60
	, eCtrl_ViewTrigger1
	, eCtrl_ViewTrigger2
	, eCtrl_ViewTrigger3
	, eCtrl_ViewTrigger4
	, eCtrl_ViewTrigger5
	, eCtrl_ViewTrigger6
	, eCtrl_ViewTrigger7
	, eCtrl_ViewTrigger8
	, eCtrl_ViewTrigger9
	, eCtrl_ViewTrigger10
	, eCtrl_ViewTrigger11
	, eCtrl_ViewTrigger12
	, eCtrl_ViewSlider1
	, eCtrl_ViewSlider2
	, eCtrl_ViewSlider3
	, eCtrl_ViewNum
};

class ctrlMap
{
private:
	void initKey2Ctrl();
	void initMidi2Ctrl();

public:
	map<char, eCtrlType> key2Ctrl;
	map<int, eCtrlType> midi2Ctrl;

//-------------------
//Singleton
//-------------------
private:
	ctrlMap();
	~ctrlMap()
	{
		ctrlMap::Destroy();
	}
	ctrlMap(ctrlMap const&);
	void operator=(ctrlMap const&);

public:
	static ctrlMap* GetInstance();
	static void Destroy();

private:
	static ctrlMap *pInstance;
};
