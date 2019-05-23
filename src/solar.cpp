#include "solar.h"

solar::solar()
	:_isInit(false)
	, _eMode(eMainCamMode)
	, _isDrawPlanet(false)
{}

void solar::init(int w, int h)
{
	ofDisableArbTex();
	_width = w;
	_height = h;

	_post.init(w, h, true);
	_post.createPass<BloomPass>()->setEnabled(true);
	_post.setFlip(false);

	_sun = sun(_width * 0.05, 20);
	_sStar.init(500, 10, w, h, w);

	initHeart();
	initPlane();
	initCamNCanvas(w, h);
	_isInit = true;


	ofSetSphereResolution(5);
}

void solar::update(float delta)
{
	if (!_isInit)
	{
		return;
	}

	for (auto& iter : _planetList)
	{
		iter.update(delta);
	}
	

	if (_eMode == eFourCamMode)
	{
		_sun.update(delta);
		updateFourCam(delta);
	}
	else
	{
		_sStar.update(delta);
		updateMainCam();
	}
}

void solar::draw()
{
	if (!_isInit)
	{
		return;
	}

	ofSetColor(255);
	_canvas.draw(0, 0);
	
}

void solar::reset()
{
	_eMode = eMainCamMode;
	_isDrawPlanet = false;
	setSpeedLevel(0);
	setFourCamRotate(0);

	_animFourCamHeight.reset(0);
	_animFourCamHeight.setDuration(0.5f);

	_animFourCamDist.reset(350);
	_animFourCamDist.setDuration(0.5f);
	_fourRotateD = 30;
	_fourRotateV = 0;

	_sun.enter(0);

	for (auto& iter : _planetList)
	{
		iter.enter(0);
	}
	
}

void solar::setSpeedLevel(float v)
{
	float speedLevel = MAX(0, MIN(1.0f, v));
	setPlaneSpeedLevel(speedLevel);
	_sStar.setSpeedLevel(speedLevel);
	_sun.setSpeedLevel(speedLevel);
	
}

void solar::setFourCamRotate(float v)
{
	_fourRotateV = v;
}

void solar::setFourCamDist(float d)
{
	if (_eMode == eMode::eFourCamMode)
	{
		_animFourCamDist.animateTo(d);
	}
}

void solar::setFourCamHeight(float h)
{
	if (_eMode == eMode::eFourCamMode)
	{
		_animFourCamHeight.animateTo(h);
	}
}

void solar::setPlanetEnable(bool val)
{
	_isDrawPlanet = val;
}

void solar::setPlanetOut(float d)
{
	for (auto& iter : _planetList)
	{
		iter.exit(d);
	}
}

void solar::setSunOut(float d)
{
	_sun.exit(d);
	
}

void solar::changeMode()
{
	if (_eMode == eMode::eFourCamMode)
	{
		_eMode = eMode::eMainCamMode;
		setPlanetEnable(true);
	}
	else
	{
		_eMode = eMode::eFourCamMode;
		setPlanetEnable(false);
	}
}

void solar::getCamInfo()
{
	ofVec3f pos = _mainCam.getGlobalPosition();
	auto q = _mainCam.getGlobalOrientation();

	cout << "pos:" << pos << endl;
	cout << "Q:" << q << endl;
}


void solar::initCamNCanvas(int w, int h)
{
	_canvas.allocate(w, h, GL_RGBA);

	_mainCam.disableMouseInput();
	_mainCam.setAutoDistance(false);
	_mainCam.setGlobalOrientation(ofQuaternion(0.203401, 0.222349, -0.0502956, 0.952187));
	_mainCam.setGlobalPosition(41.8799, -147.576, 265.402);

	_animFourCamHeight.reset(0);
	_animFourCamHeight.setDuration(0.5f);

	_animFourCamDist.reset(350);
	_animFourCamDist.setDuration(0.5f);
	_fourRotateD = 30;
	_fourRotateV = 0;

	float width = (float)w / 4.0f;
	for (int i = 0; i < 4; i++)
	{
		float deg = _fourRotateD + i * 90;
		ofVec3f pos;
		pos.x = sin(deg * DEG_TO_RAD) * _animFourCamDist.getCurrentValue();
		pos.y = _animFourCamHeight.getCurrentValue();
		pos.z = cos(deg * DEG_TO_RAD) * _animFourCamDist.getCurrentValue();

		_fourCanvas[i].allocate(width, h, GL_RGBA);
		_fourCam[i].disableMouseInput();
		
		_fourCam[i].setAutoDistance(false);
		_fourCam[i].setGlobalPosition(pos);
		_fourCam[i].lookAt(ofVec3f(0));
		_fourCam[i].setVFlip(true);
	}

}

void solar::initHeart()
{
	_heartModel.loadModel("heart/heart.obj", true);
	_heartModel.setScale(0.15f, 0.15f, 0.15f);
	_heartModel.setPosition(0, 75, 0);
}

void solar::initPlane()
{
	float baseSize = _width * 0.015;
	float baseRadius = (_width * 0.5) / 10.0f + _width * 0.05;
	float baseRevSpeed = 6; //1-min
	float baseSelfSpeed = baseRevSpeed * 2;


	for (int i = 0; i < _planetList.size(); i++)
	{
		_planetList[i] = planet(baseSize, ofColor(0), baseSelfSpeed, baseRadius * (i + 1), baseRevSpeed / ofRandom(0.8, 5.0f));
	}
}

void solar::setPlaneSpeedLevel(float v)
{
	for (auto& iter : _planetList)
	{
		iter.setSpeedLevel(v);
	}
}

void solar::updateMainCam()
{
	_canvas.begin();
	ofBackground(60);
	_post.begin(_mainCam);
	ofSetDepthTest(true);
	
	_sStar.draw();
	
	drawHeart();

	for (auto& iter : _planetList)
	{
		iter.draw();
	}
	_post.end();
	_canvas.end();

}

void solar::updateFourCam(float delta)
{
	_animFourCamHeight.update(delta);
	_animFourCamDist.update(delta);
	_fourRotateD += _fourRotateV * delta;
	if (_fourRotateD > 360)
	{
		_fourRotateD -= 360;
	}
	for (int i = 0; i < 4; i++)
	{
		//Update Pos & Cam
		float deg = _fourRotateD + i * 90;
		ofVec3f pos;
		pos.x = sin(deg * DEG_TO_RAD) * _animFourCamDist.getCurrentValue();
		pos.y = -_animFourCamHeight.getCurrentValue();
		pos.z = cos(deg * DEG_TO_RAD) * _animFourCamDist.getCurrentValue();

		_fourCam[i].setGlobalPosition(pos);
		
		_fourCam[i].lookAt(ofVec3f(0));

		//Draw on Canvas
		_fourCanvas[i].begin();
		ofSetDepthTest(true);
		ofClear(0);
		_fourCam[i].begin();
		drawHeart();
		_sun.draw();

		if (_isDrawPlanet)
		{
			for (auto& iter : _planetList)
			{
				iter.draw();
			}
		}

		_fourCam[i].end();
		_fourCanvas[i].end();
	}

	ofVec2f pos(0);
	_canvas.begin();
	ofClear(0);
	ofBackground(60);
	_post.begin();
	
	for (int i = 0; i < 4; i++)
	{
		_fourCanvas[i].draw(pos);
		pos.x += _fourCanvas[i].getWidth();
	}
	_post.end();
	
	_canvas.end();
}

void solar::drawHeart()
{
	ofPushStyle();
	ofSetColor(0, 0, 0, 128);
	_heartModel.drawFaces();
	ofSetColor(255);
	ofSetLineWidth(3);
	_heartModel.drawWireframe();
	ofPopStyle();
}
