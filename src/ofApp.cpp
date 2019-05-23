#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);

	_ctrlOF = true;
	midiCtrl::GetInstance()->init();
	midiCtrl::GetInstance()->addListener(this);

	arenaOSC::GetInstance()->setup("192.168.0.10", 7000);

	ofSetWindowPosition(960, 0);
	_outputMaskAlpha = 0;
	initScene();

	_isSpoutInit = false;
	initSpout();
	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	updateScnen(delta);

	beginSpout();
	drawScene();
	endSpout();

	updateSpout();
	updateMidi();
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
		
	drawSpoutPreview(0, 0, 480, 240);
	drawSceneMsg();

	string msg = (_ctrlOF ? "Control OF" : "Control Arena");
	ofDrawBitmapStringHighlight(msg, 0, 300);
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
	
	ofDrawBitmapStringHighlight(state, 10, 350);
	_sceneList[_sceneIdx]->showSceneMsg(10, 370);
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

	if (eType == eCtrl_ChangeMaskAlpha)
	{
		_outputMaskAlpha = ofMap(value, 0, cMidiValueMax, 0, 255);
	}
}

#pragma endregion

#pragma region Spout
void ofApp::initSpout()
{
	char sendername[] = { "[C_HuanHuan Spout]" };
	_isSpoutInit = _spoutSender.CreateSender(sendername, cDisplayUnitWidth * 4, cDisplayUnitHeight);
	_spoutCanvas.allocate(cDisplayUnitWidth * 4, cDisplayUnitHeight, GL_RGBA);
}
void ofApp::updateSpout()
{
	if (_isSpoutInit)
	{
		_spoutSender.SendTexture(
			_spoutCanvas.getTextureReference().getTextureData().textureID,
			_spoutCanvas.getTextureReference().getTextureData().textureTarget,
			_spoutCanvas.getWidth(),
			_spoutCanvas.getHeight()
		);
	}


}
void ofApp::beginSpout()
{
	_spoutCanvas.begin();
	ofClear(0);

	
}
void ofApp::endSpout()
{
	//Cover
	ofPushStyle();
	ofSetColor(0, 255 - _outputMaskAlpha);
	ofFill();
	ofDrawRectangle(0, 0, _spoutCanvas.getWidth(), _spoutCanvas.getHeight());
	ofPopStyle();

	_spoutCanvas.end();
}
void ofApp::drawSpoutPreview(int x, int y, int w, int h)
{
	ofPushStyle();
	ofSetColor(255);
	_spoutCanvas.draw(x, y, w, h);
	ofPopStyle();
}
#pragma endregion



//----------------------------------
void ofApp::updateMidi()
{
	if (_midiQueue.size() == 0)
	{
		return;
	}

	auto ctrl = _midiQueue.begin();

	if (_ctrlOF)
	{
		_sceneList[_sceneIdx]->control(ctrl->type, ctrl->value);
		sceneCtrl(ctrl->type, ctrl->value);
	}
	else
	{
		arenaOSC::GetInstance()->send(ctrl->code, ctrl->value);
	}
	
	_midiQueue.pop_front();
}

//----------------------------------
void ofApp::newMidiMessage(ofxMidiMessage & msg)
{
	if (msg.control == eMidiSetBtn)
	{
		if (msg.value == cMidiButtonPress)
		{
			_ctrlOF ^= true;
			_midiQueue.clear();
		}
	}
	else
	{
		midiCtrlData newCtrl;
		newCtrl.code = (eMidiCtrlCode)msg.control;
		newCtrl.type = ctrlMap::GetInstance()->midi2Ctrl[msg.control];
		newCtrl.value = msg.value;
		_midiQueue.push_back(newCtrl);
	}
	
	
}