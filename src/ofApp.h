#pragma once

#include "ofMain.h"

struct planet {
    
    ofImage image;
    ofVec3f location;
    float rotationSpeed, rotationDegrees, orbitSpeed, orbitDegrees;
    string nameOfPlanet;
    ofSpherePrimitive sphere;
    ofMaterial material;
};

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void drawFboPlanets();
    void generateUniverse();
    
    vector <planet> universe;
    int maxPlanets, minRadius, maxRadius, universeWidth, universeHeight, universeDepth, pointSize, expansionSteps, expansionStep, currentExpandingPlanet;
    bool b_rotateCam, b_fullScreen, b_expanding, b_contracting;
    float camDist, maxRotationSpeed, maxOrbitSpeed, camRotationSpeed;
    ofEasyCam cam;
    ofLight worldLight;
    
    ofFbo rgbaFbo; // with alpha
};
