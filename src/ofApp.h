#pragma once


#include "ofMain.h"
#include "Spout/Spout.h"
#include "scene.h"
#include "ctrlMap.h"
#include "midiCtrl.h"
#include "arenaOSC.h"

class ofApp : public ofBaseApp, public ofxMidiListener {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	

private:
	float _mainTimer;

private:
	void initScene();
	void updateScnen(float delta);
	void drawScene();
	void drawSceneMsg();

	void playScene();
	void nextScene();
	void prevScene();
	void stopScene();

	void sceneCtrl(eCtrlType eType, int value);
private:
	bool _isPlay;
	int _sceneIdx;
	
	vector<ofPtr<baseScene>> _sceneList;


private:
	void initSpout();
	void updateSpout();
	void beginSpout();
	void endSpout();
	void drawSpoutPreview(int x, int y, int w, int h);

private:
	bool _isSpoutInit;
	SpoutSender _spoutSender;
	int _outputMaskAlpha;
	ofFbo _spoutCanvas;

	//Midi
public:
	void updateMidi();
	void newMidiMessage(ofxMidiMessage& msg) override;

private:
	bool _ctrlOF;
	struct midiCtrlData
	{
		eMidiCtrlCode code;
		eCtrlType type;
		int value;
	};
	list<midiCtrlData> _midiQueue;

};
