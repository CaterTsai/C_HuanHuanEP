#pragma once
#include "baseScene.h"
#include "travelSpace.h"

class S02 : public baseScene
{
public:

	S02() :baseScene("S02-Slow Dive")
	{
		init();
	}

	void init()
	{
		_isInit = true;
		_ts.init(cDisplayUnitWidth * 2, cDisplayUnitHeight, 3000, cDisplayUnitWidth, cDisplayUnitHeight);
	};
	void update(float delta) override
	{
		CHECK_START;
		_ts.update(delta);
	};

	void draw() override
	{
		CHECK_START;
		_ts.draw();
	};

	void showSceneMsg(int x, int y) override
	{
		stringstream ss;
		ss << getBaseInfo() << endl;
		ss << "[T]1-4:Change Color" << endl;
		ss << "[T]5:Delay Troggle" << endl;
		ss << "[T]6:Particle Troggle" << endl;
		ss << "[T]9-11:Change Speed" << endl;
		ss << "[S]1:Cam Rotate V" << endl;
		ss << "[S]2:Target Rotate R" << endl;
		ss << "[S]3:Target Rotate V" << endl;

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
		ofSetDepthTest(false);

		_ts.start(400, 200);
		_ts.toggleDelay();
	};

	void stop() override
	{
		_isStart = false;
		_ts.stop();
		reset();
	};

	void control(eCtrlType eType, int value) override
	{
		if (value == cMidiButtonPress)
		{
			switch (eType)
			{
			case eCtrl_ViewTrigger1: {
				_ts.setColor(ofColor(100, 160, 255), 5.0f);
				break;
			}
			case eCtrl_ViewTrigger2: {
				_ts.setColor(ofColor(0, 82, 217), 15.0f);
				break;
			}
			case eCtrl_ViewTrigger3: {
				_ts.setColor(ofColor(0, 46, 121), 15.0f);
				break;
			}
			case eCtrl_ViewTrigger4: {
				_ts.setColor(ofColor(0, 24, 66), 15.0f);
				break;
			}
			case eCtrl_ViewTrigger5: {
				_ts.toggleDelay();
				break;
			}
			case eCtrl_ViewTrigger6: {
				_ts.toggleParticle();
				break;
			}
			case eCtrl_ViewTrigger9: {
				_ts.setSpeed(100);
				break;
			}
			case eCtrl_ViewTrigger10: {
				_ts.setSpeed(400);
				break;
			}
			case eCtrl_ViewTrigger11: {
				_ts.setSpeed(800);
				break;
			}
			}
		}

		switch (eType) {
		case eCtrl_ViewSlider1: {
			_ts.camRotateV((float)value/cMidiButtonPress);
			break;
		}
		case eCtrl_ViewSlider2: {
			_ts.targetRadius((float)value / cMidiButtonPress);
			break;
		}
		case eCtrl_ViewSlider3: {
			_ts.targetRotateV((float)value / cMidiButtonPress);
			break;
		}
		}
		
	}

private:
	void reset() override
	{
		_ts.reset();
		ofBackground(0);
	};

private:
	travelSpace _ts;
};