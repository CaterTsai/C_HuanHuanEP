#pragma once
#include "baseScene.h"
#include "solar.h"

class S03 : public baseScene
{
public:

	S03() :baseScene("S03-Planet") { init(); }

	void init()
	{
		_isInit = true;
		_solarSpace.init(cDisplayUnitWidth * 4, cDisplayUnitHeight);
	};
	void update(float delta) override 
	{
		CHECK_START;
		_solarSpace.update(delta);
	};

	void draw() override 
	{
		CHECK_START;
		_solarSpace.draw();
	};

	void showSceneMsg(int x, int y) override
	{
		stringstream ss;
		ss << getBaseInfo() << endl;
		ss << "[T]1-2:Slow/Fast Rotate" << endl;
		ss << "[T]3-4:Four Cam Rotate On/Off" << endl;
		ss << "[T]5-7:Change Four Cam Position" << endl;
		ss << "[T]9:Change Mode" << endl;
		ss << "[T]10:Show Planet" << endl;
		ss << "[T]11:Planet Fadeout" << endl;
		ss << "[T]12:Sun Fadeout" << endl;

		ofDrawBitmapStringHighlight(ss.str(), x, y);
	};

	void start() override 
	{
		if (!_isInit)
		{
			ofLog(OF_LOG_ERROR, "[start]Need init first");
			return;
		}
		_isStart = true;
		
	};
	
	void stop() override 
	{
		_isStart = false;
		reset();
	};

	void control(eCtrlType eType, int value) override
	{
		if (value == cMidiButtonPress)
		{
			switch (eType)
			{
			case eCtrl_ViewTrigger1: {
				_solarSpace.setSpeedLevel(0.0f);
				break;
			}
			case eCtrl_ViewTrigger2: {
				_solarSpace.setSpeedLevel(1.0f);
				break;
			}
			case eCtrl_ViewTrigger3: {
				_solarSpace.setFourCamRotate(0);
				break;
			}
			case eCtrl_ViewTrigger4: {
				_solarSpace.setFourCamRotate(60);
				break;
			}
			case eCtrl_ViewTrigger5: {
				_solarSpace.setFourCamDist(350);
				_solarSpace.setFourCamHeight(0);
				break;
			}
			case eCtrl_ViewTrigger6: {
				_solarSpace.setFourCamDist(600);
				_solarSpace.setFourCamHeight(150);
				break;
			}
			case eCtrl_ViewTrigger7: {
				_solarSpace.setFourCamDist(250);
				_solarSpace.setFourCamHeight(0);
				break;
			}
			case eCtrl_ViewTrigger9: {
				_solarSpace.changeMode();
				break;
			}
			case eCtrl_ViewTrigger10: {
				_solarSpace.setPlanetEnable(true);
				break;
			}
			case eCtrl_ViewTrigger11: {
				_solarSpace.setPlanetOut(3.0f);
				break;
			}
			case eCtrl_ViewTrigger12: {
				_solarSpace.setSunOut(3.0f);
				break;
			}
			}
		}

	}

private:
	void reset() override
	{
		_solarSpace.reset();
	};

private:
	solar _solarSpace;
};