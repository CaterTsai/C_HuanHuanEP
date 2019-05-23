#include "DHandDrawIcon.h"

void DHandDrawIcon::update(float delta)
{
	_animAlpha.update(delta);
	_timer -= delta;
	if (_timer < 0.0f)
	{
		updateIcon();
		_timer = _updateTime;
	}
	
}

void DHandDrawIcon::draw(int x, int y, ofColor c)
{
	if (_drawCommand.size() < 0)
	{
		return;
	}

	ofColor iconColor(c.r, c.g, c.b, _animAlpha.getCurrentValue());
	ofPushMatrix();
	ofTranslate(x, y);
	_iconPath.setStrokeColor(iconColor);
	_iconPath.draw();
	ofPopMatrix();
}

void DHandDrawIcon::setIcon(ofPath path, float size)
{
	_drawCommand = path.getCommands();
	_drawSize = size;
}

void DHandDrawIcon::setHandDrawLevel(float v)
{	
	_randomSize = ofMap(v, 0.0f, 1.0f, 0.0f, 0.3f, true);
}

void DHandDrawIcon::setUpdateTime(float t)
{
	_updateTime = t;
}

void DHandDrawIcon::toggle(float d)
{
	_animAlpha.setDuration(d);
	if (_animAlpha.getCurrentValue() == 255)
	{
		_animAlpha.animateTo(0);
	}
	else if(_animAlpha.getCurrentValue() == 0)
	{
		_animAlpha.animateTo(255);
	}
}

void DHandDrawIcon::reset()
{
	_animAlpha.reset(0);
}


void DHandDrawIcon::updateIcon()
{
	_iconPath.clear();
	for (int i = 0; i < _drawTime; i++)
	{
		drawIcon(_iconPath);
	}
}

void DHandDrawIcon::drawIcon(ofPath & path)
{
	for (auto& iter : _drawCommand)
	{
		auto to = iter.to;
		to.x += ofRandom(-_randomSize, _randomSize);
		to.y += ofRandom(-_randomSize, _randomSize);
		to.z += ofRandom(-_randomSize, _randomSize);
		to *= _drawSize;
		switch (iter.type)
		{
		case ofPath::Command::Type::moveTo:
		{
			path.moveTo(to);
			break;
		}
		case ofPath::Command::Type::lineTo:
		{
			path.lineTo(to);
			break;
		}
		case ofPath::Command::Type::curveTo:
		{
			path.curveTo(to);
			break;
		}
		case ofPath::Command::Type::bezierTo:
		{
			path.bezierTo(iter.cp1, iter.cp2, to);
			break;
		}
		case ofPath::Command::Type::quadBezierTo:
		{
			path.quadBezierTo(iter.cp1, iter.cp2, to);
			break;
		}
		case ofPath::Command::Type::arc:
		{
			path.arc(to, iter.radiusX, iter.radiusY, iter.angleBegin, iter.angleEnd);
			break;
		}
		case ofPath::Command::Type::arcNegative:
		{
			path.arcNegative(to, iter.radiusX, iter.radiusY, iter.angleBegin, iter.angleEnd);
			break;
		}
		case ofPath::Command::Type::close:
		{
			path.close();
			break;
		}
		}
	}
}
