#pragma once

#include "ofMain.h"
#include "ofxOscSender.h"
#include "midiCtrl.h"
class arenaOSC {

public:
	void setup(string ip, int port);
	void send(eMidiCtrlCode midi, int value);


private:
	void initMap();

private:
	enum eOscType {
		eOscBool = 0,
		eOscInt,
		eOscFloat,
	};
	map<eMidiCtrlCode, string> midi2Arena;
	map<eMidiCtrlCode, eOscType> midi2ArenaType;
	bool _isSetup;
	ofxOscSender _sender;
//-------------------
//Singleton
//-------------------
private:
	arenaOSC()
		:_isSetup(false)
	{
		initMap();
	};
	~arenaOSC()
	{
		arenaOSC::Destroy();
	}
	arenaOSC(arenaOSC const&);
	void operator=(arenaOSC const&);

public:
	static arenaOSC* GetInstance();
	static void Destroy();

private:
	static arenaOSC *pInstance;
};