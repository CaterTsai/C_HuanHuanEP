#pragma once

#include "ofMain.h"


class ofxTorusPrimitive : public of3dPrimitive {
public:
	ofxTorusPrimitive() {
		texCoords = ofVec4f(0, 0, 1, 1);
		set(100, 10, 20, 10);
	};
	ofxTorusPrimitive(float rIn, float rOut, int inResolution, int outResolution) {
		texCoords = ofVec4f(0, 0, 1, 1);
		set(rIn, rOut, inResolution, outResolution);
	}

	void set(float rIn, float rOut, int inResolution, int outResolution)
	{
		_rIn = rIn;
		_rOut = rOut;
		_inResolution = inResolution;
		_outResolution = outResolution;

		createTorusMesh();

		normalizeAndApplySavedTexCoords();
	}

protected:
	void createTorusMesh()
	{
		ofMesh mesh;
		mesh.clear();
		mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

		float unitIn = TWO_PI / (float)_inResolution;
		float unitOut = TWO_PI / (float)_outResolution;
		for (int in = 0; in < _inResolution; in++)
		{
			float u = unitIn * in;
			for (int out = 0; out < _outResolution; out++)
			{
				float v = unitOut * out;

				ofVec3f vert;
				vert.x = (_rIn + _rOut * cos(v)) * cos(u);
				vert.y = (_rIn + _rOut * cos(v)) * sin(u);
				vert.z = _rOut * sin(v);

				mesh.addVertex(vert);
			}
		}

		for (int in = 0; in < _inResolution; in++)
		{
			for (int out = 0; out < _outResolution; out++)
			{
				int idx1, idx2, idx3, idx4;
				idx1 = in * _outResolution + out;
				idx2 = ((in + 1) % _inResolution) * _outResolution + out;
				idx3 = in * _outResolution + ((out + 1) % _outResolution);
				idx4 = ((in + 1) % _inResolution) * _outResolution + ((out + 1) % _outResolution);
				mesh.addTriangle(idx1, idx2, idx3);
				mesh.addTriangle(idx2, idx4, idx3);
			}
		}

		getMesh() = mesh;
	}

protected:
	int _inResolution, _outResolution;
	float _rIn, _rOut;
};