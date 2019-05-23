#include "DAlchemicalDaynight.h"

DAlchemicalDaynight::DAlchemicalDaynight()
	:_isStart(false)
	, _isAuto(false)
	, _changeColor(true)
	, _eState(eAnimHide)
	, _duration(0.0f)
	, _colNum(0)
	, _rowNum(0)
{


}

void DAlchemicalDaynight::init(int w, int h, int colNum, int rowNum)
{
	_colNum = colNum;
	_rowNum = rowNum;
	int total = _colNum * _rowNum;

	_animColor.reset(255);

	_unitW = (float)w / colNum;
	_unitH = (float)h / rowNum;
	_leftSource.set(0, 0);
	_rightSource.set(_unitW, 0);
	_leftPos = _leftLinePos = _leftSource;
	_rightPos = _rightLinePos = _rightSource;

	_leftMove.set(_unitW, _unitH * -0.5f);
	_rightMove.set(-_unitW, _unitH * 0.5f);

	
}

void DAlchemicalDaynight::update(float delta)
{
	if (!_isStart)
	{
		return;
	}

	_animAlpha.update(delta);
	_animMove.update(delta);
	_animColor.update(delta);

	alphaUpdate(delta);
	stateCheck(delta);
}

void DAlchemicalDaynight::draw(int x, int y)
{
	if (!_isStart)
	{
		return;
	}

	ofPushMatrix();
	ofTranslate(x + _unitW * 0.5, y + _unitH * 0.5);

	int cy = ceil(_rowNum / 2.0f);
	float delta = TWO_PI / (_rowNum * 0.5f);

	float animR = _animAlpha.getCurrentValue();

	for (int y = 0; y < _rowNum; y++)
	{
		float rowAlpha = 55 + (sin(abs(y - cy) * delta + animR) + 1.0f) * 0.5 * 200;
		
		for (int x = 0; x < _colNum; x+=2)
		{
			int index = y * _colNum + x;
			ofSetColor(_animColor.getCurrentValue(), _alphaList[index] * rowAlpha);
			ofPushMatrix();
			ofTranslate(x * _unitW, y * _unitH);
			
			drawUnit();
			ofPopMatrix();

		}
	}
	ofPopMatrix();
}

void DAlchemicalDaynight::reset()
{
	_eState = eAnimHide;
	_isStart = false;
}

void DAlchemicalDaynight::toggle(float duration)
{
	if (_eState == eAnimHide)
	{
		_isStart = true;
		_eState = eAnimAlphaIn;
		int total = _colNum * _rowNum;

		_animAlpha.setDuration(5.0f);
		_animAlpha.setRepeatType(AnimRepeat::LOOP);
		_animAlpha.setCurve(AnimCurve::LINEAR);
		_animAlpha.animateFromTo(0, TWO_PI);

		alphaInit(total, duration);
	}
	else
	{
		_eState = eAnimOut;

		_animAlpha.setRepeatType(AnimRepeat::PLAY_ONCE);
		_animAlpha.setDuration(duration);
		_animAlpha.animateTo(0);

		_animColor.setDuration(duration);
		_animColor.animateTo(255);
	}
}

void DAlchemicalDaynight::play(float duration)
{
	if (_eState != eAnimCircle)
	{
		return;
	}
	_duration = duration;
	_timer = _duration;
	_animMove.setDuration(duration);
	_animColor.setDuration(duration);

	_eState = eAnimSorceWait;
}


ofColor DAlchemicalDaynight::getColor()
{
	if(_changeColor)
	{
		return ofColor(_animColor.getCurrentValue());
	}
	else
	{
		return ofColor(_animColor.getCurrentValue());
	}
	
}

void DAlchemicalDaynight::stateCheck(float delta)
{
	switch (_eState)
	{
	case eAnimSorceWait:
	{
		_timer -= delta;
		if (_timer <= 0.0f)
		{
			_eState = eAnimLine;
			_animMove.animateFromTo(0.0f, 1.0f);
		}
		break;
	}
	case eAnimLine:
	{
		if (_animMove.hasFinishedAnimating() && _animMove.getPercentDone() == 1.0f)
		{
			_eState = eAnimMove;
			_animMove.animateFromTo(0.0f, 1.0f);
			if (_changeColor)
			{
				_animColor.animateFromTo(255, 0);
			}
			
		}
		else {
			updateLinePos();
		}
		break;
	}
	case eAnimMove:
	{
		if (_animMove.hasFinishedAnimating() && _animMove.getPercentDone() == 1.0f)
		{
			_eState = eAnimWaitTwo;
			_timer = _duration;
		}
		else
		{
			updatePos();
		}
		break;
	}
	case eAnimWaitTwo:
	{
		_timer -= delta;
		if (_timer <= 0.0f)
		{
			_eState = eAnimLineTwo;
			_animMove.animateFromTo(0.0f, 1.0f);
		}

		break;
	}
	case eAnimLineTwo:
	{
		if (_animMove.hasFinishedAnimating() && _animMove.getPercentDone() == 1.0f)
		{
			_eState = eAnimMoveTwo;
			_animMove.animateFromTo(0.0f, 1.0f);

			if (_changeColor)
			{
				_animColor.animateFromTo(0, 255);
			}
			
		}
		else
		{
			updateLinePos();
		}
		break;
	}
	case eAnimMoveTwo:
	{
		if (_animMove.hasFinishedAnimating() && _animMove.getPercentDone() == 1.0f)
		{
			_eState = eAnimSorceWait;
			_timer = _duration;

			_leftPos = _leftLinePos = _leftSource;
			_rightPos = _rightLinePos = _rightSource;
		}
		else
		{
			updatePos();
		}
		break;
	}
	case eAnimOut:
	{
		if (_animAlpha.hasFinishedAnimating() && _animAlpha.getPercentDone() == 1.0f)
		{
			_eState = eAnimHide;
			_isStart = false;
		}
		break;
	}
	}
}

void DAlchemicalDaynight::drawUnit()
{
	ofSetLineWidth(1);
	ofLine(_leftPos, _leftLinePos);
	ofLine(_rightPos, _rightLinePos);

	ofNoFill();
	ofSetLineWidth(2);
	ofDrawCircle(_leftPos, _unitW * 0.08);
	ofDrawCircle(_rightPos, _unitW * 0.08);
}

void DAlchemicalDaynight::updateLinePos()
{
	float p = _animMove.getCurrentValue();
	ofVec2f o(0, 0);
	_leftLinePos = _leftPos + o.getInterpolated(_leftMove, p);
	_rightLinePos = _rightPos + o.getInterpolated(_rightMove, p);
}

void DAlchemicalDaynight::updatePos()
{
	float p = _animMove.getCurrentValue();
	ofVec2f o(0, 0);
	_leftPos = _leftLinePos - _leftMove.getInterpolated(o, p);
	_rightPos = _rightLinePos - _rightMove.getInterpolated(o, p);
}

void DAlchemicalDaynight::alphaInit(int total, float duration)
{
	_alphaIdx = 0;
	_alphaD = duration / total;
	_alphaTimer = _alphaD;
	_alphaIdxList.resize(total);
	_alphaList.resize(total);
	for (int i = 0; i < total; i++)
	{
		_alphaIdxList[i] = i;
		_alphaList[i] = 0.0f;
	}

	random_shuffle(_alphaIdxList.begin(), _alphaIdxList.end());
}

void DAlchemicalDaynight::alphaUpdate(float delta)
{
	if (_eState == eAnimAlphaIn)
	{
		_alphaTimer -= delta;
		if (_alphaTimer <= 0.0f)
		{
			_alphaList[_alphaIdxList[_alphaIdx]] = 1.0f;
			_alphaIdx++;
			if (_alphaIdx >= _alphaIdxList.size())
			{
				_eState = eAnimCircle;
				ofLog(OF_LOG_NOTICE, "[alphaUpdate]All In");
			}
			else
			{
				_alphaTimer = _alphaD;
			}
		}
		else
		{
			_alphaList[_alphaIdxList[_alphaIdx]] = 1.0f - (_alphaTimer / _alphaD);
		}
		return;
	}
	else if (_eState == eAnimOut)
	{
		for (auto &iter : _alphaList)
		{
			iter = _animAlpha.getCurrentValue() / TWO_PI;
		}
	}
}
