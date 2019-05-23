#pragma once

#include "drawerParameter.h"
#include "ofxTrueTypeFontUC.h"
#include "../particleSys.h"

class DAichemicalSymbol {
public:
	DAichemicalSymbol();
	void update(float delta);
	void draw(ofColor c);
	void reset();

	void initUpper();
	void toggleUpper();

	void initFaller();
	void toggleFaller();

private:
	void initSymbolSet();
	string getRandomSymbol();
	void drawParticle(particleSys& psys, ofColor c);
private:
	array<string, cAlchemicalSymbolNum> _symbolSet;
	particleSys _psysUpper, _psysFaller;
	ofxTrueTypeFontUC _font;
	string _text;
};