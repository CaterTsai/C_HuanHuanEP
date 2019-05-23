#include "arenaOSC.h"

void arenaOSC::setup(string ip, int port)
{
	_sender.setup(ip, port);
	_isSetup = true;
}
void arenaOSC::send(eMidiCtrlCode midi, int value)
{
	if (!_isSetup)
	{
		return;
	}

	auto key = midi2Arena.find(midi);
	if (key == midi2Arena.end())
	{
		return;
	}

	auto type = midi2ArenaType[midi];

	ofxOscMessage m;
	m.setAddress(key->second);
	switch (type)
	{
	case eOscBool:
	{
		if (value == cMidiButtonPress)
		{
			m.addIntArg(1);
		}
		break;
	}
	case eOscInt:
	{
		m.addIntArg(value);
		break;
	}
	case eOscFloat:
	{
		float v = (float)value / cMidiButtonPress;
		m.addFloatArg(v);
		break;
	}
	}
	_sender.sendMessage(m, false);
}
void arenaOSC::initMap()
{
	midi2Arena[eMidiTriggerS1] = "/composition/layers/3/clips/1/connect";
	midi2ArenaType[eMidiTriggerS1] = eOscBool;
	midi2Arena[eMidiTriggerS2] = "/composition/layers/3/clips/2/connect";
	midi2ArenaType[eMidiTriggerS2] = eOscBool;
	midi2Arena[eMidiTriggerS3] = "/composition/layers/3/clips/3/connect";
	midi2ArenaType[eMidiTriggerS3] = eOscBool;
	midi2Arena[eMidiTriggerS4] = "/composition/layers/3/clips/4/connect";
	midi2ArenaType[eMidiTriggerS4] = eOscBool;
	midi2Arena[eMidiTriggerS5] = "/composition/layers/3/clips/5/connect";
	midi2ArenaType[eMidiTriggerS5] = eOscBool;
	midi2Arena[eMidiTriggerS6] = "/composition/layers/3/clips/6/connect";
	midi2ArenaType[eMidiTriggerS6] = eOscBool;
	midi2Arena[eMidiTriggerS7] = "/composition/layers/3/clips/7/connect";
	midi2ArenaType[eMidiTriggerS7] = eOscBool;

	midi2Arena[eMidiTriggerM1] = "/composition/layers/2/clips/1/connect";
	midi2ArenaType[eMidiTriggerM1] = eOscBool;
	midi2Arena[eMidiTriggerM2] = "/composition/layers/2/clips/2/connect";
	midi2ArenaType[eMidiTriggerM2] = eOscBool;
	midi2Arena[eMidiTriggerM3] = "/composition/layers/2/clips/3/connect";
	midi2ArenaType[eMidiTriggerM3] = eOscBool;
	midi2Arena[eMidiTriggerM4] = "/composition/layers/2/clips/4/connect";
	midi2ArenaType[eMidiTriggerM4] = eOscBool;
	midi2Arena[eMidiTriggerM5] = "/composition/layers/2/clips/5/connect";
	midi2ArenaType[eMidiTriggerM5] = eOscBool;
	midi2Arena[eMidiTriggerM6] = "/composition/layers/2/clips/6/connect";
	midi2ArenaType[eMidiTriggerM6] = eOscBool;
	midi2Arena[eMidiTriggerM7] = "/composition/layers/2/clips/7/connect";
	midi2ArenaType[eMidiTriggerM7] = eOscBool;

	midi2Arena[eMidiTriggerR1] = "/composition/layers/1/clips/1/connect";
	midi2ArenaType[eMidiTriggerR1] = eOscBool;
	midi2Arena[eMidiTriggerR2] = "/composition/layers/1/clips/2/connect";
	midi2ArenaType[eMidiTriggerR2] = eOscBool;
	midi2Arena[eMidiTriggerR3] = "/composition/layers/1/clips/3/connect";
	midi2ArenaType[eMidiTriggerR3] = eOscBool;
	midi2Arena[eMidiTriggerR4] = "/composition/layers/1/clips/4/connect";
	midi2ArenaType[eMidiTriggerR4] = eOscBool;
	midi2Arena[eMidiTriggerR5] = "/composition/layers/1/clips/5/connect";
	midi2ArenaType[eMidiTriggerR5] = eOscBool;
	midi2Arena[eMidiTriggerR6] = "/composition/layers/1/clips/6/connect";
	midi2ArenaType[eMidiTriggerR6] = eOscBool;
	midi2Arena[eMidiTriggerR7] = "/composition/layers/1/clips/7/connect";
	midi2ArenaType[eMidiTriggerR7] = eOscBool;

	midi2Arena[eMidiStopBtn] = "/composition/columns/8/connect";
	midi2ArenaType[eMidiStopBtn] = eOscBool;

	midi2Arena[eMidiSlider1] = "/composition/layers/3/transition/duration";
	midi2ArenaType[eMidiSlider1] = eOscFloat;
	midi2Arena[eMidiSlider2] = "/composition/layers/2/transition/duration";
	midi2ArenaType[eMidiSlider2] = eOscFloat;
	midi2Arena[eMidiSlider3] = "/composition/layers/1/transition/duration";
	midi2ArenaType[eMidiSlider3] = eOscFloat;

	midi2Arena[eMidiSlider4] = "/composition/master";
	midi2ArenaType[eMidiSlider4] = eOscFloat;

	midi2Arena[eMidiKnob1] = "/composition/layers/3/dashboard/link1";
	midi2ArenaType[eMidiKnob1] = eOscFloat;
	midi2Arena[eMidiKnob2] = "/composition/layers/3/dashboard/link2";
	midi2ArenaType[eMidiKnob2] = eOscFloat;
	midi2Arena[eMidiKnob3] = "/composition/layers/3/dashboard/link3";
	midi2ArenaType[eMidiKnob3] = eOscFloat;

	midi2Arena[eMidiKnob4] = "/composition/layers/2/dashboard/link1";
	midi2ArenaType[eMidiKnob4] = eOscFloat;
	midi2Arena[eMidiKnob5] = "/composition/layers/2/dashboard/link2";
	midi2ArenaType[eMidiKnob5] = eOscFloat;
	midi2Arena[eMidiKnob6] = "/composition/layers/2/dashboard/link3";
	midi2ArenaType[eMidiKnob6] = eOscFloat;

	midi2Arena[eMidiKnob7] = "/composition/layers/1/dashboard/link1";
	midi2ArenaType[eMidiKnob7] = eOscFloat;
	midi2Arena[eMidiKnob8] = "/composition/layers/1/dashboard/link2";
	midi2ArenaType[eMidiKnob8] = eOscFloat;

	midi2Arena[eMidiPrevBtn] = "/composition/selectprevdeck";
	midi2ArenaType[eMidiPrevBtn] = eOscBool;

	midi2Arena[eMidiNextBtn] = "/composition/selectnextdeck";
	midi2ArenaType[eMidiNextBtn] = eOscBool;
}

//--------------------------------------------------------------
arenaOSC* arenaOSC::pInstance = 0;

arenaOSC* arenaOSC::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new arenaOSC();
	}
	return pInstance;
}

//--------------------------------------------------------------
void arenaOSC::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}