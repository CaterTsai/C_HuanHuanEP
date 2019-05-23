#pragma once

#include "ofMain.h"



#include "scene.h"
#include "ctrlMap.h"
#include "midiCtrl.h"

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
	ofEasyCam _cam;

	//Midi
public:
	void updateMidi();
	void newMidiMessage(ofxMidiMessage& msg) override;

private:
	struct midiCtrlData
	{
		eCtrlType type;
		int value;
	};
	list<midiCtrlData> _midiQueue;

};
