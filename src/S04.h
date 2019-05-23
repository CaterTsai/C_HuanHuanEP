#pragma once
#include "baseScene.h"

class S04 : public baseScene
{
public:

	S04() :baseScene("S04-Mask") { init(); }

	void init()
	{
		_isInit = true;
	};
	void update(float delta) override 
	{
		CHECK_START;
		for (auto& iter : _animAlphaList)
		{
			iter.update(delta);
		}
	};

	void draw() override 
	{

		CHECK_START;
		
		ofPushStyle();
		int posX = 0;
		for (auto& iter : _animAlphaList)
		{
			ofSetColor(0, iter.getCurrentValue());
			ofDrawRectangle(posX, 0, cDisplayUnitWidth, cDisplayUnitHeight);
			posX += cDisplayUnitWidth;
		}

		ofPopStyle();
	};

	void showSceneMsg(int x, int y) override
	{
		stringstream ss;
		ss << getBaseInfo() << endl;
		ss << "[T]1-4:Fade In/Out Mask" << endl;
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

		for (auto& iter : _animAlphaList)
		{
			iter.setDuration(1.0f);
			iter.reset(255);
		}
	};
	
	void stop() override 
	{
		_isStart = true;
		reset();
	};

	void control(eCtrlType eType, int value) override
	{
		if (value == cMidiButtonPress)
		{
			switch (eType)
			{
			case eCtrl_ViewTrigger1: {
				if (_animAlphaList[0].getCurrentValue() > 0)
				{
					_animAlphaList[0].animateTo(0);
				}
				else
				{
					_animAlphaList[0].animateTo(255);
				}
				break;
			}
			case eCtrl_ViewTrigger2: {
				if (_animAlphaList[1].getCurrentValue() > 0)
				{
					_animAlphaList[1].animateTo(0);
				}
				else
				{
					_animAlphaList[1].animateTo(255);
				}
				break;
			}
			case eCtrl_ViewTrigger3: {
				if (_animAlphaList[2].getCurrentValue() > 0)
				{
					_animAlphaList[2].animateTo(0);
				}
				else
				{
					_animAlphaList[2].animateTo(255);
				}
				break;
			}
			case eCtrl_ViewTrigger4: {
				if (_animAlphaList[3].getCurrentValue() > 0)
				{
					_animAlphaList[3].animateTo(0);
				}
				else
				{
					_animAlphaList[3].animateTo(255);
				}
				break;
			}
			}
		}

	}

private:
	void reset() override
	{
	};

private:

	array<bool, cDisplayNum> _flagList;
	array<ofxAnimatableFloat, cDisplayNum> _animAlphaList;
};