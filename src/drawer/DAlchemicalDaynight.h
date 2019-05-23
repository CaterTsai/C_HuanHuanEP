#pragma once

#include "drawerParameter.h"
#include "ofxAnimatableFloat.h"

class DAlchemicalDaynight {
public:
	DAlchemicalDaynight();

	void init(int w, int h, int colNum, int rowNum);
	void update(float delta);
	void draw(int x, int y);
	void reset();
	void toggle(float duration);
	void play(float duration);

	ofColor getColor();

	inline void setChangeColor(bool val)
	{
		_changeColor = val;
	}
	inline bool getChangeColor()
	{
		return _changeColor;
	}

private:
	void stateCheck(float delta);
	void drawUnit();
	void updateLinePos();
	void updatePos();

	void alphaInit(int total, float duration);
	void alphaUpdate(float delta);
private:
	enum eAnimState {
		eAnimHide = 0,
		eAnimAlphaIn,
		eAnimCircle,
		eAnimSorceWait,
		eAnimLine,
		eAnimMove,
		eAnimWaitTwo,
		eAnimLineTwo,
		eAnimMoveTwo,
		eAnimOut,
	}_eState;
	bool _isStart, _isAuto, _changeColor;
	int _colNum, _rowNum;
	float _unitW, _unitH;
	float _timer, _duration;

	ofxAnimatableFloat _animColor;

	ofVec3f _leftPos, _rightPos;
	ofVec3f _leftLinePos, _rightLinePos;

	ofVec2f _leftSource, _rightSource;
	ofVec2f _leftMove, _rightMove;

	ofxAnimatableFloat	_animMove, _animAlpha;

	int _alphaIdx;
	float _alphaTimer, _alphaD;
	vector<int> _alphaIdxList;
	vector<float> _alphaList;
};