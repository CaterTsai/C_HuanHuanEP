#pragma once

#include "constParameter.h"
#include "planet.h"
#include "sun.h"
#include "spaceStar.h"
#include "ofxPostProcessing.h"
#include "ofxAssimpModelLoader.h"

class solar {
public:
	solar();
	void init(int w, int h);

	void update(float delta);
	void draw();

	void reset();

	void setSpeedLevel(float v);

	void setFourCamRotate(float v);
	void setFourCamDist(float d);
	void setFourCamHeight(float h);

	void setPlanetEnable(bool val);
	
	void setPlanetOut(float d);
	void setSunOut(float d);

	void changeMode();

	void getCamInfo();
private:
	void initCamNCanvas(int w, int h);
	void initHeart();
	void initPlane();
	void setPlaneSpeedLevel(float v);

	void updateMainCam();
	void updateFourCam(float delta);

	void drawHeart();

private:
	enum eMode {
		eMainCamMode = 0,
		eFourCamMode
	}_eMode;
	int _width, _height;
	bool _isInit;
	
	bool _isDrawPlanet;
	sun _sun;
	array<planet, 8> _planetList;
	spaceStar _sStar;

	ofxPostProcessing _post;
	ofFbo _canvas;
	ofEasyCam _mainCam;

	array<ofFbo, 4> _fourCanvas;
	array<ofEasyCam, 4> _fourCam;
	ofxAnimatableFloat _animFourCamDist, _animFourCamHeight;

	float _fourRotateD, _fourRotateV;

	ofxAssimpModelLoader _heartModel;
};