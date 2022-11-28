#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofSetColor(0);
	ofFill();
	ofSetLineWidth(1.5);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 90, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int y = -240 + 40; y < ofGetHeight() - 480; y += 120) {

		string word = "Every Day";
		auto path_list = font.getStringAsPoints(word, true, false);

		for (auto path : path_list) {

			auto outline = path.getOutline();

			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				outline[outline_index] = outline[outline_index].getResampledByCount(300);
				auto vertices = outline[outline_index].getVertices();
				for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

					auto location = glm::vec2(vertices[vertices_index].x - this->font.stringWidth(word) * 0.5, y + vertices[vertices_index].y + this->font.stringHeight(word) * 0.5);
					auto len = glm::length(location);

					auto noise_location = glm::normalize(location);

					for (int i = 0; i < 2; i++) {

						auto radius = (ofGetFrameNum() * 8 + i * 300) % 600 + ofMap(ofNoise(glm::vec3(noise_location, ofGetFrameNum() * 0.1)), 0, 1, -30, 30);

						if (len > radius - 35 && len < radius) {

							location = glm::normalize(location) * (radius + 35);
							break;
						}

						if (len < radius + 35 && len > radius) {

							location = glm::normalize(location) * (radius + 35);
							break;
						}
					}

					ofVertex(location);
				}
			}
			ofEndShape(true);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}