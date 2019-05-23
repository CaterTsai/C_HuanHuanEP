#pragma once
#include "ofxMidi.h"


enum eMidiCtrlCode : int
{
	//-------------------
	eMidiPlayBtn = 41
	,eMidiStopBtn = 42
	,eMidiForward = 44
	,eMidiBackward = 43
	//-------------------
	,eMidiNextBtn = 62
	,eMidiPrevBtn = 61
	,eMidiSetBtn = 60

	//-------------------
	,eMidiTriggerS1 = 32
	,eMidiTriggerS2
	, eMidiTriggerS3
	, eMidiTriggerS4
	, eMidiTriggerS5
	, eMidiTriggerS6
	, eMidiTriggerS7
	, eMidiTriggerS8
	
	,eMidiTriggerM1 = 48
	, eMidiTriggerM2
	, eMidiTriggerM3
	, eMidiTriggerM4
	, eMidiTriggerM5
	, eMidiTriggerM6
	, eMidiTriggerM7
	, eMidiTriggerM8

	, eMidiTriggerR1 = 64
	, eMidiTriggerR2
	, eMidiTriggerR3
	, eMidiTriggerR4
	, eMidiTriggerR5
	, eMidiTriggerR6
	, eMidiTriggerR7
	, eMidiTriggerR8

	//-------------------
	,eMidiSlider1 = 0
	, eMidiSlider2
	, eMidiSlider3
	, eMidiSlider4
	, eMidiSlider5
	, eMidiSlider6
	, eMidiSlider7
	, eMidiSlider8

	//-------------------
	, eMidiKnob1 = 16
	, eMidiKnob2
	, eMidiKnob3
	, eMidiKnob4
	, eMidiKnob5
	, eMidiKnob6
	, eMidiKnob7
	, eMidiKnob8

	//-------------------
	, eMidiTrackNext = 59
	, eMidiTrackPrev = 58
};

const int cMidiButtonPress = 127;
const int cMidiValueMin = 0;
const int cMidiValueMax = 127;
class midiCtrl
{
public:
	void init();
	void release();
	void addListener(ofxMidiListener* listener);
	void removeListener(ofxMidiListener* listener);
private:
	bool _isSetup;
	ofxMidiIn	_midiIn;

//-------------------
//Singleton
//-------------------
private:
	midiCtrl()
		:_isSetup(false)
	{};
	~midiCtrl()
	{
		midiCtrl::Destroy();
	}
	midiCtrl(midiCtrl const&);
	void operator=(midiCtrl const&);

public:
	static midiCtrl* GetInstance();
	static void Destroy();

private:
	static midiCtrl *pInstance;
};
