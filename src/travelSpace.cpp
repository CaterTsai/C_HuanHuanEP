#include "travelSpace.h"

#pragma region Basic Method
travelSpace::travelSpace()
	:_isInit(false)
	, _isStart(false)
	, _isDelay(false)
	, _sw(0)
	, _sh(0)
	, _sd(0)
	, _targetRotateV(0)
	, _targetRotateR(0)
	, _targetRadius(0)
	, _camRotateD(0)
	, _camRotateV(0)
{
	_camPos.set(0);
	_targetPos.set(0);
	

}

void travelSpace::init(int mw, int mh, int md, int windowW, int windowH)
{
	_sw = mw;
	_sh = mh;
	_sd = md;

	_canvas.allocate(mw, mh, GL_RGBA);
	_cam.disableMouseInput();
	_cam.setAutoDistance(false);

	_left.allocate(windowW, windowH, GL_RGBA);
	_right.allocate(windowW, windowH, GL_RGBA);
	_leftCam.disableMouseInput();
	_leftCam.setAutoDistance(false);
	_rightCam.disableMouseInput();
	_rightCam.setAutoDistance(false);

	_torus.set(mw * 0.1, mh * 0.005, 50, 5);

	_targetPos.set(0, 0, -md);
	_isInit = true;

}

void travelSpace::update(float delta)
{
	if (!_isStart)
	{
		return;
	}

	_animBGColor.update(delta);

	auto dPos = _animCamVec.getCurrentPosition() * delta;
	dPos.z = -_speed * delta;
	_camPos.x += dPos.x;
	_camPos.y += dPos.y;
	_tempPos.z -= dPos.z;
	targetUpdate(delta);
	checkList(dPos.z);
	updateList(dPos.z);
	updateCam(delta);
	updateParticle(delta, dPos.z);

	ofBackground(_animBGColor.getCurrentColor());
	

}

void travelSpace::draw()
{
	if (!_isStart)
	{
		return;
	}
	ofPushStyle();
	drawOnCam(_canvas, _cam);
	drawOnCam(_left, _leftCam);
	drawOnCam(_right, _rightCam);

	int posX = 0;
	_left.draw(0, 0, _left.getWidth(), _left.getHeight());
	posX += _left.getWidth();

	_canvas.draw(posX, 0, _canvas.getWidth(), _canvas.getHeight());
	posX += _canvas.getWidth();

	_right.draw(posX, 0, _left.getWidth(), _left.getHeight());
	
	ofPopStyle();
}

void travelSpace::reset()
{
	_isStart = false;
	_isDelay = false;

	_keyList.clear();
}

void travelSpace::debugDraw()
{
	if (!_isInit)
	{
		return;
	}
	ofSetColor(255);

	_cam.draw();

	ofBoxPrimitive box(5, 5, 5);
	box.setPosition(_targetPos);
	box.draw();

	drawTorus();
	drawParticle();
}

void travelSpace::start(float speed, float interDist)
{
	if (!_isInit || _isStart)
	{
		return;
	}

	_isStart = true;
	_isDelay = false;
	_speed = speed;
	_interDist = interDist;
	basicKey();
	_animCamVec.setCurve(AnimCurve::LINEAR);
	_animCamVec.setPosition((*_keyList.begin()) - _camPos);
	_animCamVec.setDuration((interDist * 0.4f) / speed);

	initParticle();

	_animBGColor.setColor(ofColor(100, 160, 255));

}

void travelSpace::stop()
{
	_isStart = false;
	_animCamVec.reset();
	_pSys.stopEmit();
}

#pragma endregion

#pragma region Control
void travelSpace::toggleDelay()
{
	_isDelay ^= true;
}

void travelSpace::setSpeed(float speed)
{

	_speed = speed;
	_animCamVec.setDuration((_interDist * 0.4f) / speed);
}

void travelSpace::targetRadius(float x)
{
	_targetRadius = ofMap(x, 0, 1.0f, 0, _sw * 0.5f);
}

void travelSpace::targetRotateV(float v)
{
	_targetRotateV = ofMap(v, 0.0f, 1.0f, 0, PI * 0.5f);
}

void travelSpace::camRotateV(float v)
{
	_camRotateV = ofMap(v, 0.0f, 1.0f, 0, 90.0f);
}
void travelSpace::toggleParticle()
{
	_pSys.getIsStart() ? _pSys.stopEmit() : _pSys.startEmit();
}
#pragma endregion

#pragma region Private Method
void travelSpace::basicKey()
{
	int num = _sd / _interDist;

	for (int i = -1; i < num; i++)
	{
		_keyList.push_back(ofVec3f(0, 0, (i + 1) * -_interDist));
	}
}

void travelSpace::drawTorus()
{
	for (auto iter = _keyList.begin(); iter != _keyList.end(); iter++)
	{
		auto pos = *iter;
		ofVec3f target;
		if (iter == _keyList.begin())
		{
			target = _tempPos;
		}
		else
		{
			auto prevIter = iter;
			prevIter--;
			target = *prevIter;

		}
		_torus.setPosition(pos);
		_torus.lookAt(target);

		ofSetColor(255);
		_torus.drawWireframe();
	}
}

void travelSpace::drawOnCam(ofFbo & canvas, ofEasyCam & cam)
{
	canvas.begin();

	if (_isDelay)
	{
		ofFill();
		ofSetColor(_animBGColor.getCurrentColor(), 20);
		ofDrawRectangle(0, 0, canvas.getWidth(), canvas.getHeight());
	}
	else
	{
		ofClear(255);
		ofSetColor(_animBGColor.getCurrentColor());
		ofDrawRectangle(0, 0, canvas.getWidth(), canvas.getHeight());
	}
	cam.begin();

	drawParticle();
	drawTorus();


	cam.end();
	canvas.end();
}

void travelSpace::updateCam(float delta)
{
	_animCamVec.update(delta);
	_cam.setPosition(_camPos);
	_cam.lookAt(_camPos + _animCamVec.getCurrentPosition());

	

	_camRotateD += _camRotateV * delta;
	if (_camRotateD > 360.0f)
	{
		_camRotateD -= 360.0f;
	}
	_cam.rotate(_camRotateD, 0, 0, -1);

	_leftCam.setPosition(_camPos);
	_rightCam.setPosition(_camPos);

	ofVec3f v = _cam.getXAxis();
	_leftCam.lookAt(_camPos + v);
	_rightCam.lookAt(_camPos - v);

}

void travelSpace::updateList(float deltaZ)
{
	for (auto& iter : _keyList)
	{
		iter.z -= deltaZ;
	}
}

void travelSpace::checkList(float deltaZ)
{
	auto pos = *_keyList.begin();
	auto nextZ = (deltaZ - pos.z);
	if (nextZ <= (-_interDist))
	{
		_tempPos = pos;
		_keyList.pop_front();
		_keyList.push_back(_targetPos);
	}
	else if (nextZ < _interDist * 0.2f)
	{
		if (!_animCamVec.isAnimating())
		{
			auto nextIter = _keyList.begin();
			nextIter++;
			auto nextVec = *nextIter - pos;
			nextVec /= nextVec.z;
			nextVec *= -_speed;
			_animCamVec.animateTo(nextVec);
		}
	}
}

void travelSpace::targetUpdate(float delta)
{
	_targetRotateR += _targetRotateV * delta;
	if (_targetRotateR > TWO_PI)
	{
		_targetRotateR -= TWO_PI;
	}

	float dx = (sin(_targetRotateR)) * _targetRadius;
	float dy = (cos(_targetRotateR)) * _targetRadius;
	_targetPos.x = dx;
	_targetPos.y = dy;
}

void travelSpace::setColor(ofColor c, float d)
{
	_animBGColor.setDuration(d);
	_animBGColor.animateTo(c);
}

#pragma endregion

#pragma region Particle
void travelSpace::initParticle()
{
	_pSys.emitLifeTimeBegin = 10.0f;
	_pSys.emitLifeTimeEnd = 15.0f;
	_pSys.emitNum = 10;
	_pSys.maxNum = 500;
	_pSys.emitPosRangeBegin = ofVec3f(_sw * -0.5, _sh * -0.5f, -_sd);
	_pSys.emitPosRangeEnd = ofVec3f(_sw * 0.5, _sh * 0.5f, -_sd);
	_pSys.emitDirectionRangeBegin = _pSys.emitDirectionRangeEnd = ofVec3f(0, 0, 1);
	_pSys.emitSizeBegin = 5;
	_pSys.emitSizeEnd = 15;
	_pSys.emitSpeedRangeBegin = 50;
	_pSys.emitSpeedRangeEnd = 200;
	_pSys.emitRAxisBegin = ofVec3f(-1, -1, -1);
	_pSys.emitRAxisEnd = ofVec3f(1, 1, 1);
	_pSys.emitRotDRangeBegin = 0;
	_pSys.emitRotDRangeEnd = 360;
	_pSys.emitRotVRangeBegin = -60;
	_pSys.emitRotVRangeEnd = 60;


	_pSys.needFade = true;

	
}

void travelSpace::updateParticle(float delta, float moveD)
{
	_pSys.update(delta);
	auto pList = _pSys.getParticleList();
	for (auto& iter : pList)
	{
		iter.param.pos.z -= moveD;
	}
	_pSys.getParticleList() = pList;
}

void travelSpace::drawParticle()
{
	ofPushStyle();
	ofNoFill();
	auto pList = _pSys.getParticleList();
	for (auto& iter : pList)
	{
		ofSetColor(iter.param.color);
		
		ofDrawSphere(iter.param.pos, iter.param.size);
	}
	ofPopStyle();
}
#pragma endregion

