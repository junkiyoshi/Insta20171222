#pragma once
#include "ofMain.h"

class Particle
{
public:
	Particle();
	~Particle() {};

	void apply_force(ofVec2f force);
	void update();
	void draw();
	
	ofVec2f get_location();
private:
	ofVec2f location;
	ofVec2f velocity;
	ofVec2f acceleration;
};