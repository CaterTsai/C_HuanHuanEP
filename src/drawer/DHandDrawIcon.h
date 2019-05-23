#pragma once

#include "ofMain.h"
#include "ofxAnimatableFloat.h"

class DHandDrawIcon {
public:
	DHandDrawIcon()
		:_drawTime(10)
		,_randomSize(0.1)
		,_timer(0.0f)
		,_updateTime(1.0f)
	{
		_iconPath.setFilled(false);
		_iconPath.setStrokeColor(ofColor(255));
		_iconPath.setStrokeWidth(1);

		_animAlpha.reset(0);
	}

	void update(float delta);
	void draw(int x, int y, ofColor c);

	void setIcon(ofPath path, float size);
	void setHandDrawLevel(float v);
	void setUpdateTime(float t);

	void toggle(float d);

	void reset();
private:
	void updateIcon();
	void drawIcon(ofPath& path);

private:
	int _drawTime;
	float _drawSize, _randomSize;
	float _timer, _updateTime;
	ofPath _iconPath;
	vector<ofPath::Command> _drawCommand;

	ofxAnimatableFloat _animAlpha;
};