#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(30);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofSetLineWidth(2);
	this->photo.loadImage("photo.png");

	for (int i = 0; i < 512 + 256; i++) {
		this->particles.push_back(shared_ptr<Particle>(new Particle()));
	}

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {
	ofPixels pixels = this->photo.getPixelsRef();
	ofColor pixel_color;

	for (int i = 0; i < this->particles.size(); i++) {
		this->particles[i]->update();
	}

	this->fbo.begin();
	if (ofGetMousePressed()) {
		ofClear(0);
	}

	for (int i = 0; i < this->particles.size(); i++) {
		vector<ofVec2f> near_point;
		pixel_color = pixels.getColor(this->particles[i]->get_location().x, this->particles[i]->get_location().y);
		if (pixel_color == ofColor(0, 0, 0, 0)) {
			pixel_color = ofColor(255);
		}
		ofSetColor(pixel_color, 128);
		for (int j = i + 1; j < this->particles.size(); j++) {
			if (this->particles[i]->get_location().distanceSquared(this->particles[j]->get_location()) < 1000) {
				near_point.push_back(this->particles[j]->get_location());
				//ofDrawLine(this->particles[i]->get_location(), this->particles[j]->get_location());
			}
		}

		if (near_point.size() > 2) {
			ofBeginShape();
			for (int k = 0; k < near_point.size(); k++) {
				ofVertex(near_point[k].x, near_point[k].y);
			}
			ofEndShape(true);
		}
	}

	this->fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {
	this->fbo.draw(0, 0);
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}