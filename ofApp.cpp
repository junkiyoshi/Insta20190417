#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(1.5);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofFill();

	int span = 144;
	int len = 120;
	int radius = 60;
	bool flag = true;
	for (int location_y = span * 0.5; location_y < ofGetHeight(); location_y += span) {

		for (int location_x = span * 0.5; location_x < ofGetWidth(); location_x += span) {

			ofPushMatrix();
			ofTranslate(location_x, location_y);

			vector<glm::vec2> top, noise, bottom;
			for (int deg = 0; deg <= 180; deg++) {

				auto point = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
				bottom.push_back(point);
				noise.push_back(glm::vec2(point.x, ofMap(ofNoise(location_y, (location_x + point.x) * 0.03, ofGetFrameNum() * 0.008), 0, 1, -point.y * 0.5, point.y * 0.5) + 2));
			}
			this->draw_shape(bottom, noise);

			ofGetFill() ? ofNoFill() : ofFill();

			for (int deg = 180; deg <= 360; deg++) {

				auto point = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
				top.push_back(point);
				noise.push_back(glm::vec2(point.x, ofMap(ofNoise(location_y, (location_x + point.x) * 0.03, ofGetFrameNum() * 0.008), 0, 1, point.y * 0.5, -point.y * 0.5) - 2));
			}
			this->draw_shape(top, noise);

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_shape(vector<glm::vec2>& side, vector<glm::vec2>& noise) {

	std::reverse(noise.begin(), noise.end());

	ofBeginShape();
	ofVertices(side);
	ofVertices(noise);
	ofEndShape(true);

	side.clear();
	noise.clear();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}