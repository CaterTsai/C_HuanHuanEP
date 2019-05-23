#pragma once

#include "constParameter.h"
#include "ctrlMap.h"
#include "midiCtrl.h"

#define CHECK_START if(!_isStart || !_isInit)return;

class baseScene {
public:
	baseScene(string name) 
		:_isInit(false)
		,_isStart(false)
	{
		_sName = name;
	}
	virtual void init() {};
	virtual void update(float delta) {};
	virtual void draw() {};

	virtual void showSceneMsg(int x, int y) {};

	virtual void start() {};
	virtual void stop() {};

	virtual void control(eCtrlType eType, int value) {};

protected:
	virtual void reset() {};
	string getBaseInfo() {
		return "Scene :" + _sName;
	}

protected:
	bool _isInit, _isStart;
	string _sName;
};