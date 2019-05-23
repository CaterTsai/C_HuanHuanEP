#include "ctrlMap.h"
#include "midiCtrl.h"

//--------------------------------------------------------------
void ctrlMap::initKey2Ctrl()
{
	key2Ctrl['u'] = eCtrl_PrevScence;
	key2Ctrl['i'] = eCtrl_NextScence;
	key2Ctrl['o'] = eCtrl_Stop;
	key2Ctrl['p'] = eCtrl_Start;


	key2Ctrl['q'] = eCtrl_ViewTrigger1;
	key2Ctrl['w'] = eCtrl_ViewTrigger2;
	key2Ctrl['e'] = eCtrl_ViewTrigger3;
	key2Ctrl['r'] = eCtrl_ViewTrigger4;
	key2Ctrl['a'] = eCtrl_ViewTrigger5;
	key2Ctrl['s'] = eCtrl_ViewTrigger6;
	key2Ctrl['d'] = eCtrl_ViewTrigger7;
	key2Ctrl['f'] = eCtrl_ViewTrigger8;
	key2Ctrl['z'] = eCtrl_ViewTrigger9;
	key2Ctrl['x'] = eCtrl_ViewTrigger10;
	key2Ctrl['c'] = eCtrl_ViewTrigger11;
	key2Ctrl['v'] = eCtrl_ViewTrigger12;
}

//--------------------------------------------------------------
void ctrlMap::initMidi2Ctrl()
{
	midi2Ctrl[eMidiPlayBtn] = eCtrl_Start;
	midi2Ctrl[eMidiStopBtn] = eCtrl_Stop;
	midi2Ctrl[eMidiForward] = eCtrl_NextScence;
	midi2Ctrl[eMidiBackward] = eCtrl_PrevScence;

	
	midi2Ctrl[eMidiKnob8] = eCtrl_ChangeMaskAlpha;
	
	
	midi2Ctrl[eMidiTriggerS1] = eCtrl_ViewTrigger1;
	midi2Ctrl[eMidiTriggerS2] = eCtrl_ViewTrigger2;
	midi2Ctrl[eMidiTriggerS3] = eCtrl_ViewTrigger3;
	midi2Ctrl[eMidiTriggerS4] = eCtrl_ViewTrigger4;

	midi2Ctrl[eMidiTriggerM1] = eCtrl_ViewTrigger5;
	midi2Ctrl[eMidiTriggerM2] = eCtrl_ViewTrigger6;
	midi2Ctrl[eMidiTriggerM3] = eCtrl_ViewTrigger7;
	midi2Ctrl[eMidiTriggerM4] = eCtrl_ViewTrigger8;

	midi2Ctrl[eMidiTriggerR1] = eCtrl_ViewTrigger9;
	midi2Ctrl[eMidiTriggerR2] = eCtrl_ViewTrigger10;
	midi2Ctrl[eMidiTriggerR3] = eCtrl_ViewTrigger11;
	midi2Ctrl[eMidiTriggerR4] = eCtrl_ViewTrigger12;

	midi2Ctrl[eMidiSlider1] = eCtrl_ViewSlider1;
	midi2Ctrl[eMidiSlider2] = eCtrl_ViewSlider2;
	midi2Ctrl[eMidiSlider3] = eCtrl_ViewSlider3;

}

//--------------------------------------------------------------
ctrlMap::ctrlMap()
{
	initKey2Ctrl();
	initMidi2Ctrl();
}

//--------------------------------------------------------------
ctrlMap* ctrlMap::pInstance = 0;
ctrlMap* ctrlMap::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new ctrlMap();
	}
	return pInstance;
}

//--------------------------------------------------------------
void ctrlMap::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}