#include "DAlchemicalSymbol.h"

DAichemicalSymbol::DAichemicalSymbol()
{
	_font.setGlobalDpi(72);
	_font.loadFont("font/Symbola.ttf", 30);
	
	initUpper();
	initFaller();

	initSymbolSet();
}

void DAichemicalSymbol::update(float delta)
{
	_psysUpper.update(delta);
	_psysFaller.update(delta);
}


void DAichemicalSymbol::draw(ofColor c)
{
	drawParticle(_psysUpper, c);
	drawParticle(_psysFaller, c);
}

void DAichemicalSymbol::reset()
{
	_psysUpper.stopEmit();
	_psysUpper.clear();
	_psysFaller.stopEmit();
	_psysFaller.clear();
}

void DAichemicalSymbol::initUpper()
{
	_psysUpper.emitLifeTimeBegin = 2.0f;
	_psysUpper.emitLifeTimeEnd = 5.0f;
	_psysUpper.emitNum = 5;
	_psysUpper.maxNum = 100;
	_psysUpper.emitPosRangeBegin = ofVec3f(0, cDisplayUnitHeight, 300);
	_psysUpper.emitPosRangeEnd = ofVec3f(cDisplayUnitWidth, cDisplayUnitHeight, -300);
	_psysUpper.emitDirectionRangeBegin = _psysUpper.emitDirectionRangeEnd = ofVec3f(0, -1, 0);
	_psysUpper.emitSpeedRangeBegin = 200;
	_psysUpper.emitSpeedRangeEnd = 500;
	_psysUpper.emitRAxisBegin = ofVec3f(-1, -1, -1);
	_psysUpper.emitRAxisEnd = ofVec3f(1, 1, 1);
	_psysUpper.emitRotDRangeBegin = 0;
	_psysUpper.emitRotDRangeEnd = 360;
	_psysUpper.emitRotVRangeBegin = -60;
	_psysUpper.emitRotVRangeEnd = 60;

	_psysUpper.emitCustomIndexBegin = 0;
	_psysUpper.emitCustomIndexEnd = cAlchemicalSymbolNum - 1;
	_psysUpper.needFade = true;
}

void DAichemicalSymbol::toggleUpper()
{
	if (_psysUpper.getIsStart())
	{
		_psysUpper.stopEmit();
	}
	else
	{
		_psysUpper.startEmit();
	}
}

void DAichemicalSymbol::initFaller()
{
	_psysFaller.emitLifeTimeBegin = 2.0f;
	_psysFaller.emitLifeTimeEnd = 5.0f;
	_psysFaller.emitNum = 5;
	_psysFaller.maxNum = 100;
	_psysFaller.emitPosRangeBegin = ofVec3f(0, 0, 300);
	_psysFaller.emitPosRangeEnd = ofVec3f(cDisplayUnitWidth, 0, -300);
	_psysFaller.emitDirectionRangeBegin = _psysFaller.emitDirectionRangeEnd = ofVec3f(0, 1, 0);
	_psysFaller.emitSpeedRangeBegin = 50;
	_psysFaller.emitSpeedRangeEnd = 200;
	_psysFaller.emitRAxisBegin = ofVec3f(-1, -1, -1);
	_psysFaller.emitRAxisEnd = ofVec3f(1, 1, 1);
	_psysFaller.emitRotDRangeBegin = 0;
	_psysFaller.emitRotDRangeEnd = 360;
	_psysFaller.emitRotVRangeBegin = -60;
	_psysFaller.emitRotVRangeEnd = 60;

	_psysFaller.emitCustomIndexBegin = 0;
	_psysFaller.emitCustomIndexEnd = cAlchemicalSymbolNum - 1;
	_psysFaller.needFade = true;
}

void DAichemicalSymbol::toggleFaller()
{
	if (_psysFaller.getIsStart())
	{
		_psysFaller.stopEmit();
	}
	else
	{
		_psysFaller.startEmit();
	}
}

void DAichemicalSymbol::initSymbolSet()
{
	wstring ws(2, L' s');
	ws[0] = cAlchemicalSymbolPre;
	for (int i = 0; i < cAlchemicalSymbolNum; i++)
	{
		ws[1] = cAlchemicalSymbolMin + i;
		_symbolSet[i] = ws2s(ws);
	}
}

string DAichemicalSymbol::getRandomSymbol()
{
	wstring ws(2, L' s');
	ws[0] = cAlchemicalSymbolPre;
	ws[1] = cAlchemicalSymbolMin + rand() % cAlchemicalSymbolNum;

	return ws2s(ws);
}

void DAichemicalSymbol::drawParticle(particleSys & psys, ofColor c)
{
	auto pList = psys.getParticleList();

	for (auto & iter : pList)
	{
		ofSetColor(c);
		ofPushMatrix();
		ofTranslate(iter.param.pos);
		ofRotate(iter.param.deg, iter.param.rAxis.x, iter.param.rAxis.y, iter.param.rAxis.z);

		string symbol = _symbolSet[iter.param.cIdx];
		auto bound = _font.getStringBoundingBox(symbol, 0, 0);
		_font.drawString(symbol, bound.width * -0.5f, bound.height + 0.5f);

		ofPopMatrix();
	}
}
