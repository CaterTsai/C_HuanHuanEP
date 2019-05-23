#include "midiCtrl.h"

//--------------------------------------------------------------
void midiCtrl::init()
{
	if (_isSetup)
	{
		return;
	}
	if (!_midiIn.openPort())
	{
		ofLog(OF_LOG_ERROR, "[MIDI] open midi in port failed");
		return;
	}
	_midiIn.ignoreTypes(false, false, false);

	_isSetup = true;
}

//--------------------------------------------------------------
void midiCtrl::release()
{
	if (_isSetup && _midiIn.isOpen())
	{
		_midiIn.closePort();

	}
}

//--------------------------------------------------------------
void midiCtrl::addListener(ofxMidiListener * listener)
{
	if (!_isSetup)
	{
		return;
	}
	_midiIn.addListener(listener);
}

//--------------------------------------------------------------
void midiCtrl::removeListener(ofxMidiListener * listener)
{
	if (!_isSetup)
	{
		return;
	}
	_midiIn.removeListener(listener);
}


//--------------------------------------------------------------
midiCtrl* midiCtrl::pInstance = 0;
midiCtrl* midiCtrl::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new midiCtrl();
	}
	return pInstance;
}

//--------------------------------------------------------------
void midiCtrl::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}