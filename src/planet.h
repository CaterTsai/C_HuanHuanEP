#pragma once

#include "constParameter.h"
#include "ofxAnimatableFloat.h"

class planet {
public:
	planet() {};
	planet(float size, ofColor c, float selfSpeed, float revRadius, float revSpeed)
		:_color(c)
		, _selfSpeed(selfSpeed)
		, _selfSpeedBase(selfSpeed)
		, _revSpeedBase(revSpeed)
		, _revSpeed(revSpeed)
		, _revRadius(revRadius)
		, _selfDegree(0.0f)
		, _revDegree(0.0f)
	{
		_sphere.setResolution(8);
		_sphere.setRadius(size);

		_revDegree = ofRandom(0, 360);

		_arcDegree = (size / (revRadius * PI)) * 2.0f * 180;
		_animAlpha.reset(255);

		ofSetCircleResolution(50);
	}

	void update(float delta)
	{
		_animAlpha.update(delta);
		_selfDegree += delta * _selfSpeed;
		_revDegree += delta * _revSpeed;

		if (_selfDegree >= 360.0f)
		{
			_selfDegree -= 360.0f;
		}

		if (_revDegree >= 360.0f)
		{
			_revDegree -= 360.0f;
		}
	}

	void draw()
	{
		ofVec3f pos;
		pos.x = cos(_revDegree * DEG_TO_RAD) * _revRadius;
		pos.z = sin(_revDegree * DEG_TO_RAD) * -_revRadius;
		pos.y = 0;

		ofPushStyle();
			ofNoFill();
			ofSetLineWidth(3);
			ofSetColor(0, _animAlpha.getCurrentValue());
			ofPushMatrix();
			ofRotateX(-90);
			drawArc();
			ofPopMatrix();
		ofPopStyle();

		ofPushStyle();
			ofSetLineWidth(1);
			ofSetColor(_color, _animAlpha.getCurrentValue());
			ofPushMatrix();
			ofTranslate(pos);
			ofRotateY(_selfDegree);
			_sphere.drawWireframe();
			ofPopMatrix();
		ofPopStyle();
	}

	void setSpeedLevel(float s)
	{
		float amplification = ofMap(s, 0, 1, 1, cMaxAmplification);
		_selfSpeed = _selfSpeedBase * amplification;
		_revSpeed = _revSpeedBase * amplification;
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
	void drawArc()
	{
		ofVec3f begin;
		begin.x = cos((_revDegree + _arcDegree) * DEG_TO_RAD) * _revRadius;
		begin.y = sin( (_revDegree + _arcDegree) * DEG_TO_RAD) * _revRadius;
		begin.z = 0;

		ofPath arc;
		arc.setArcResolution(50);
		arc.setFilled(false);
		arc.setStrokeWidth(3);
		arc.setStrokeColor(ofColor(0, 0, 0, _animAlpha.getCurrentValue()));
		arc.moveTo(begin);
		arc.arc(ofVec3f(0, 0, 0), _revRadius, _revRadius, _revDegree + _arcDegree, _revDegree - _arcDegree);

		arc.draw();
	}

private:
	float _revRadius;
	float _selfDegree, _revDegree;
	float _selfSpeedBase, _revSpeedBase;
	float _selfSpeed, _revSpeed;
	ofColor _color;
	float _arcDegree;
	ofSpherePrimitive _sphere;

	ofxAnimatableFloat _animAlpha;
};