#pragma once

#include "constParameter.h"
#include "ofxAnimatableFloat.h"

class sun {
private:
	struct sunUnit {
		float theta;
		float rD, rV;
		float baserV;
	};

public:
	sun():
		_splitNum(10)
		, _radius(100)
	{
	};

	sun(int radius, int splitNum)
		:_radius(radius)
		,_splitNum(splitNum)
	{
		initSunUnit();
		_animAlpha.reset(255);
		
	}

	void update(float delta) {
		_animAlpha.update(delta);

		if (_animAlpha.getCurrentValue() != 0)
		{
			updateSunUnit(delta);
		}
		
	}

	void draw() {
		if (_animAlpha.getCurrentValue() != 0)
		{
			drawSunUnit();
		}
	}

	void setSpeedLevel(float speedLevel)
	{
		float amplification = ofMap(speedLevel, 0, 1, 1, cMaxAmplification);
		for (auto& iter : _sunUnitList)
		{
			iter.rV = iter.baserV * amplification;
		}
	}

	void enter(float d)
	{
		_animAlpha.setDuration(d);
		_animAlpha.animateTo(255);
	}

	void exit(float d)
	{
		_animAlpha.setDuration(d);
		_animAlpha.animateTo(0);
	}

private:
	void initSunUnit()
	{
		int thetaDelta = 180.0f / (float)(_splitNum + 1);

		for (int i = 0; i <= _splitNum; i++)
		{
			sunUnit newUnit;
			newUnit.theta = (i + 1) * thetaDelta;
			newUnit.rD = ofRandom(0, 360);
			newUnit.rV = ofRandom(30, 60);
			newUnit.baserV = newUnit.rV;
			_sunUnitList.push_back(newUnit);
		}

		_unitRadius = (_radius / (float)_splitNum) * 0.5f;
	}

	void updateSunUnit(float delta)
	{
		for (auto& iter : _sunUnitList)
		{
			iter.rD += iter.rV * delta;
		}
	}

	void drawSunUnit()
	{
		ofPushStyle();
		ofSetColor(0, _animAlpha.getCurrentValue());
		
		for (auto& iter : _sunUnitList)
		{
			ofVec3f pos = ballToLocal(_radius, iter.theta * DEG_TO_RAD, iter.rD * DEG_TO_RAD);

			ofVec3f c(0, pos.y, 0);
			ofPushMatrix();
			ofRotateX(-90);
			ofNoFill();
			ofDrawCircle(c.x, c.z, c.y, pos.distance(c));
			ofPopMatrix();

			ofFill();
			ofDrawSphere(pos, _unitRadius);
		}

		ofPopStyle();
	}

	ofVec3f ballToLocal(float r, float theta, float sigma)
	{
		ofVec3f pos;
		pos.z = r * sin(theta) * cos(sigma);
		pos.x = r * sin(theta) * sin(sigma);
		pos.y = -r * cos(theta);

		return pos;
	}



private:
	int _splitNum;
	float _radius;
	float _unitRadius;
	vector<sunUnit> _sunUnitList;
	ofxAnimatableFloat _animAlpha;
};