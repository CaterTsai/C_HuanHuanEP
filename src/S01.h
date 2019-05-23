#pragma once
#include "baseScene.h"
#include "drawer.h"

class S01 : public baseScene
{
public:

	S01() :baseScene("S01-Teshima")
	{
		init();
	}

	void init()
	{
		initSymbol();
		_isInit = true;
	};
	void update(float delta) override
	{
		CHECK_START;
		for (auto& iter : _symbolList)
		{
			iter.update(delta);
		}
		updateIcon(delta);
	};

	void draw() override
	{
		CHECK_START;
		ofPushStyle();
		for (auto& iter : _symbolList)
		{
			iter.draw();
		}
		ofPopStyle();
	};

	void showSceneMsg(int x, int y) override
	{
		stringstream ss;
		ss << getBaseInfo() << endl;
		ss << "[T]1-4:Icon Troggle" << endl;
		ss << "[T]5-8:Day-Night Play" << endl;
		ss << "[T]9,10:Upper & Faller Troggle" << endl;
		ss << "[T]11:Day-Night Troggle" << endl;
		ss << "[T]12:Icon Beat Troggle" << endl;

		ofDrawBitmapStringHighlight(ss.str(), x, y);
	};

	void start() override
	{
		if (!_isInit)
		{
			ofLog(OF_LOG_ERROR, "[start]Need init first");
			return;
		}
		_updateIcon = false;
		ofSetDepthTest(true);
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
				_symbolList[0]._icon.toggle(10.0f);
				break;
			}
			case eCtrl_ViewTrigger2: {
				_symbolList[1]._icon.toggle(10.0f);
				break;
			}
			case eCtrl_ViewTrigger3: {
				_symbolList[2]._icon.toggle(10.0f);
				break;
			}
			case eCtrl_ViewTrigger4: {
				_symbolList[3]._icon.toggle(10.0f);
				break;
			}
			case eCtrl_ViewTrigger5: {
				_symbolList[0]._dayNight.play(0.5f);
				break;
			}
			case eCtrl_ViewTrigger6: {
				_symbolList[1]._dayNight.play(0.5f);
				break;
			}
			case eCtrl_ViewTrigger7: {
				_symbolList[2]._dayNight.play(0.5f);
				break;
			}
			case eCtrl_ViewTrigger8: {
				_symbolList[3]._dayNight.play(0.5f);
				break;
			}
			case eCtrl_ViewTrigger9: {
				for (int i = 0; i < cDisplayNum; i++)
				{
					_symbolList[i]._symbol.toggleUpper();
				}
				break;
			}
			case eCtrl_ViewTrigger10: {
				for (int i = 0; i < cDisplayNum; i++)
				{
					_symbolList[i]._symbol.toggleFaller();
				}
				break;
			}
			case eCtrl_ViewTrigger11: {
				for (int i = 0; i < cDisplayNum; i++)
				{
					_symbolList[i]._dayNight.toggle(10.0f);
				}
				break;
			}
			case eCtrl_ViewTrigger12: {

				if (_updateIcon)
				{
					_animHandDrawLevel.reset();
					for (int i = 0; i < cDisplayNum; i++)
					{
						_symbolList[i]._icon.setHandDrawLevel(0.1f);
					}
				}
				else
				{
					_animHandDrawLevel.animateFromTo(1.0f, 0.1f);
					_animHandDrawLevel.setRepeatType(AnimRepeat::LOOP);
					_animHandDrawLevel.setCurve(AnimCurve::EASE_OUT);
					_animHandDrawLevel.setDuration(0.5f);
				}
				_updateIcon ^= true;
				break;
			}
			}
		}

	}
private:
	void reset() override
	{
		_updateIcon = false;
		for (auto& iter : _symbolList)
		{
			iter.reset();
		}
	};


private:
	void initSymbol()
	{
		//Fire
		ofVec2f v(0, -1);
		float x1, x2;
		ofPath path;
		path.moveTo(v);
		v.rotate(120);
		x1 = v.x;
		path.lineTo(v);
		v.rotate(120);
		x2 = v.x;
		path.lineTo(v);
		path.close();

		_symbolList[2].init(path, cDisplayUnitWidth * 2, 0, cDisplayUnitWidth, cDisplayUnitHeight);

		//Air
		path.moveTo(x1, -0.5);
		path.lineTo(x2, -0.5);
		_symbolList[0].init(path, cDisplayUnitWidth * 0, 0, cDisplayUnitWidth, cDisplayUnitHeight);

		//Water
		path.clear();
		v.set(0, 1);
		path.moveTo(v);
		v.rotate(120);
		x1 = v.x;
		path.lineTo(v);
		v.rotate(120);
		x2 = v.x;
		path.lineTo(v);
		path.close();
		_symbolList[1].init(path, cDisplayUnitWidth * 1, 0, cDisplayUnitWidth, cDisplayUnitHeight);

		//Soil
		path.moveTo(x1, 0.5);
		path.lineTo(x2, 0.5);
		_symbolList[3].init(path, cDisplayUnitWidth * 3, 0, cDisplayUnitWidth, cDisplayUnitHeight);
	}
	void updateIcon(float delta) {
		if (!_updateIcon)
		{
			return;
		}
		_animHandDrawLevel.update(delta);
		for (auto& iter : _symbolList)
		{
			iter._icon.setHandDrawLevel(_animHandDrawLevel.getCurrentValue());
		}
	}
private:
	class symbolUnit {
	public:
		void init(ofPath p, int x, int y, int w, int h)
		{
			_icon.setUpdateTime(0.1f);
			_icon.setIcon(p, w * 0.25);
			_icon.setHandDrawLevel(0.1f);
			_dayNight.init(w * 1.5, h * 1.5, 10, 20);
			_pos.set(x, y);

			_canvas.allocate(w, h, GL_RGBA);
			_color.set(255);
		}
		void update(float delta)
		{
			_dayNight.update(delta);
			if (_dayNight.getChangeColor())
			{
				_color = _dayNight.getColor();
			}
			_symbol.update(delta);
			_icon.update(delta);

		}
		void draw()
		{
			ofColor bg = _color;
			bg.invert();

			ofPushStyle();
			_canvas.begin();
			ofClear(0);

			ofFill();
			ofSetColor(bg);
			ofDrawRectangle(0, 0, _canvas.getWidth(), _canvas.getHeight());

			_dayNight.draw(_canvas.getWidth() * -0.25, _canvas.getHeight() * -0.25);
			_icon.draw(_canvas.getWidth() * 0.5, _canvas.getHeight() * 0.5, _color);
			_symbol.draw(_color);
			_canvas.end();

			ofSetColor(255);
			_canvas.draw(_pos);
			ofPopStyle();
		}
		void reset()
		{
			_icon.reset();
			_symbol.reset();
			_dayNight.reset();
			_icon.setHandDrawLevel(0.1f);
			_icon.setUpdateTime(0.1f);
			_color.set(255);
		}
	public:
		DAichemicalSymbol _symbol;
		DHandDrawIcon _icon;
		DAlchemicalDaynight _dayNight;
		ofColor _color;

		ofFbo _canvas;
		ofVec2f _pos;
	};

private:
	bool _updateIcon;
	ofxAnimatableFloat _animHandDrawLevel;
	array<symbolUnit, cDisplayNum> _symbolList;
};