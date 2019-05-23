#pragma once

#include "constParameter.h"


class spaceStar
{
public:
	spaceStar()
		:_isInit(false)
		, _rDeg(0)
	{
		_posList.setMode(ofPrimitiveMode::OF_PRIMITIVE_POINTS);
	}


	void init(int num, float baseRV, float width, float height, float depth)
	{
		_isInit = true;
		for (int i = 0; i < num; i++)
		{
			_posList.addVertex(ofVec3f(ofRandom(width*-0.5f, width*0.5f), ofRandom(height*-0.5f, height*0.5f), ofRandom(depth*-0.5f, depth*0.5f)));
		}
		_rDeg = 0;
		_rBaseVec = _rVec = baseRV;

		glPointSize(2);
	}

	void update(float delta)
	{
		if (!_isInit)
		{
			return;
		}
		_rDeg += _rVec * delta;
		if (_rDeg >= 360)
		{
			_rDeg -= 360;
		}
	}

	void draw()
	{
		if (!_isInit)
		{
			return;
		}
		ofPushStyle();
		ofSetColor(128);
		ofPushMatrix();
		ofRotateY(_rDeg);
		{
			_posList.draw();
		}
		ofPopMatrix();

		ofPopStyle();
	}

	void setSpeedLevel(float v)
	{
		float amplification = ofMap(v, 0, 1, 1, cMaxAmplification);
		_rVec = _rBaseVec * amplification;
	}
private:
	bool _isInit;
	
	float _rDeg;
	float _rVec, _rBaseVec;

	ofVboMesh _posList;
};