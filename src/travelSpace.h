#pragma once

#include "constParameter.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"
#include "ofxTorus.h"
#include "particleSys.h"

class travelSpace {
public:
#pragma region Basic Method
	travelSpace();
	void init(int mw, int mh, int md, int windowW, int windowH);

	void update(float delta);
	void draw();
	void reset();
	void debugDraw();

	void start(float speed, float interDist);
	void stop();
#pragma endregion

#pragma region Control
	//Control
	void toggleDelay();
	void setSpeed(float speed);
	void targetRadius(float x);
	void targetRotateV(float v);

	void camRotateV(float v);

	void toggleParticle();
	void setColor(ofColor c, float d);
#pragma endregion
	
#pragma region Private Method
private:
	void basicKey();
	void drawTorus();
	void drawOnCam(ofFbo& canvas, ofEasyCam& cam);
	void updateCam(float delta);
	void updateList(float deltaZ);
	void checkList(float deltaZ);

	void targetUpdate(float delta);

	
#pragma endregion

#pragma region Particle
private:
	void initParticle();
	void updateParticle(float delta, float moveD);
	void drawParticle();
#pragma endregion


private:
	bool _isInit, _isStart;
	int _sw, _sh, _sd;
	ofxAnimatableOfColor _animBGColor;
	
	ofFbo _canvas, _left, _right;

	float _speed, _interDist;
	ofEasyCam _cam, _leftCam, _rightCam;
	ofVec3f _camPos, _tempPos;
	float _camRotateD, _camRotateV;

	ofxAnimatableOfPoint _animCamVec;
	list<ofVec3f> _keyList;
	ofxTorusPrimitive _torus;
	
	//Target
	ofVec3f _targetPos;
	int _targetRadius;
	float _targetRotateR, _targetRotateV;

	//Effect
	bool _isDelay;

	//Particle
	particleSys _pSys;
};