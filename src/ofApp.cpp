#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);

	//midiCtrl::GetInstance()->init();
	//midiCtrl::GetInstance()->addListener(this);

	initScene();
	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	updateScnen(delta);

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	drawScene();

	drawSceneMsg();

	ofSetDepthTest(false);
	ofPushStyle();
	ofNoFill();
	ofSetLineWidth(2);
	ofVec2f pos(0);
	for (int i = 0; i < 4; i++)
	{
		ofDrawRectangle(pos, cDisplayUnitWidth, cDisplayUnitHeight);
		pos.x += cDisplayUnitWidth;
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	auto ctrl = ctrlMap::GetInstance()->key2Ctrl[key];
	_sceneList[_sceneIdx]->control(ctrl, cMidiButtonPress);

	sceneCtrl(ctrl, cMidiButtonPress);
}

#pragma region Scene
void ofApp::initScene()
{
	_sceneIdx = 0;
	_isPlay = false;

	_sceneList.push_back(ofPtr<S01>(new S01()));
	_sceneList.push_back(ofPtr<S02>(new S02()));
	_sceneList.push_back(ofPtr<S03>(new S03()));
	_sceneList.push_back(ofPtr<S04>(new S04()));

}

void ofApp::updateScnen(float delta)
{
	if (!_isPlay)
	{
		return;
	}

	_sceneList[_sceneIdx]->update(delta);
}

void ofApp::drawScene()
{
	if (!_isPlay)
	{
		return;
	}
	_sceneList[_sceneIdx]->draw();
}

void ofApp::drawSceneMsg()
{
	string state = "Scene State:"; 
	state += (_isPlay ? "Play" : "Stop");
	ofDrawBitmapStringHighlight(state, 10, 15);
	_sceneList[_sceneIdx]->showSceneMsg(10, 35);
}

void ofApp::playScene()
{
	_isPlay = true;
	_sceneList[_sceneIdx]->start();
}

void ofApp::nextScene()
{
	if (_isPlay)
	{
		_sceneList[_sceneIdx]->stop();
	}
	_sceneIdx = (_sceneIdx + 1) % _sceneList.size();
	if (_isPlay)
	{
		_sceneList[_sceneIdx]->start();
	}
}

void ofApp::prevScene()
{
	if (_isPlay)
	{
		_sceneList[_sceneIdx]->stop();
	}
	_sceneIdx--;
	if (_sceneIdx < 0)_sceneIdx = _sceneList.size() - 1;

	if (_isPlay)
	{
		_sceneList[_sceneIdx]->start();
	}
}

void ofApp::stopScene()
{
	_isPlay = false;
	_sceneList[_sceneIdx]->stop();
}

void ofApp::sceneCtrl(eCtrlType eType, int value)
{
	if (value == cMidiButtonPress)
	{
		switch (eType)
		{
		case eCtrl_Start:
		{
			playScene();
			break;
		}
		case eCtrl_Stop:
		{
			stopScene();
			break;
		}
		case eCtrl_NextScence:
		{
			nextScene();
			break;
		}
		case eCtrl_PrevScence:
		{
			prevScene();
			break;
		}
		}
	}
}
#pragma endregion



//----------------------------------
void ofApp::updateMidi()
{
	for (int i = 0; i < _midiQueue.size(); i++)
	{
		auto ctrl = _midiQueue.begin();
		_sceneList[_sceneIdx]->control(ctrl->type, ctrl->value);
		sceneCtrl(ctrl->type, ctrl->value);
		_midiQueue.pop_front();
	}
}

//----------------------------------
void ofApp::newMidiMessage(ofxMidiMessage & msg)
{
	cout << msg.control << endl;
	
	midiCtrlData newCtrl;
	newCtrl.type = ctrlMap::GetInstance()->midi2Ctrl[msg.control];
	newCtrl.value = msg.value;
	_midiQueue.push_back(newCtrl);
}