#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    pointSize = 4;
    camDist = 0.f;
    camRotationSpeed = 0.1;
   maxPlanets = ofRandom(100)+5;
    minRadius = 6;
    maxRadius = 200;
    maxRotationSpeed = 0.5;
    maxOrbitSpeed = 0.1;
    universeWidth = universeHeight = universeDepth = 6000;
    
    b_rotateCam = b_fullScreen = false;
    //cam.setPosition(0, 500 , -100000);
    cam.setFarClip(50000);
    
   // rgbaFbo.allocate(1024,768, GL_RGBA);
    
#ifdef TARGET_OPENGLES
    rgbaFbo.allocate(1024, 768, GL_RGBA ); // with alpha, 8 bits red, 8 bits green, 8 bits blue, 8 bits alpha, from 0 to 255 in 256 steps
    ofLogWarning("ofApp") << "GL_RGBA32F_ARB is not available for OPENGLES.  Using RGBA.";
#else
    rgbaFbo.allocate(1024, 768, GL_RGBA32F_ARB); // with alpha, 32 bits red, 32 bits green, 32 bits blue, 32 bits alpha, from 0 to 1 in 'infinite' steps
#endif
    rgbaFbo.begin();
    ofClear(255,255,255, 0);
    rgbaFbo.end();
    //generate a vector of planets of various sizes and locations
    for (int i=0; i< maxPlanets; i++){
        planet newPlanet;
        newPlanet.rotationSpeed = ofRandom(maxRotationSpeed);
        newPlanet.rotationDegrees =0.f;
        newPlanet.orbitSpeed = ofRandom(maxOrbitSpeed);
        newPlanet.orbitDegrees =0.f;
        newPlanet.location.x = (ofRandom(universeWidth) - universeWidth/2);
        newPlanet.location.y = (ofRandom(universeHeight)- universeHeight/2);
        newPlanet.location.z = (ofRandom(universeDepth) - universeDepth/2);
        newPlanet.sphere.setMode(OF_PRIMITIVE_POINTS);
        newPlanet.sphere.setRadius(ofRandom(minRadius, maxRadius));
        newPlanet.sphere.setResolution(newPlanet.sphere.getRadius()/10);
        newPlanet.material.setShininess( ofRandom(200) );
        ofColor diffuse(ofRandom(255), ofRandom(255), ofRandom(255));
        ofColor ambient(ofRandom(120), ofRandom(120), ofRandom(120));
        newPlanet.material.setDiffuseColor(diffuse);
        newPlanet.material.setAmbientColor(ambient);
        newPlanet.material.setSpecularColor(ofColor(255, 255, 255, 255));
        
        universe.push_back(newPlanet);
    }
    
    ofBackground(0);
    //ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){
//    ofEnableAlphaBlending();
//
//    rgbaFbo.begin();
//    drawFboPlanets();
//    rgbaFbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofEnableDepthTest();
    ofEnableLighting();
    worldLight.enable();
    ofSetColor(255);
    if (b_rotateCam) {
        camDist+=camRotationSpeed; // spin the universe in front of the camera
    }
    glPointSize(pointSize);
    for (int i=0; i< maxPlanets; i++){
        ofPushMatrix();


        ofRotateZDeg(camDist);
        ofRotateYDeg(universe[i].orbitDegrees); //rotate orbit
        ofTranslate(universe[i].location);
        ofRotateYDeg(-universe[i].rotationDegrees); // planetary spin
        universe[i].rotationDegrees += universe[i].rotationSpeed;
        universe[i].orbitDegrees += universe[i].orbitSpeed;

        universe[i].material.begin();
        //universe[i].sphere.draw();
       // universe[i].sphere.drawWireframe();
        universe[i].sphere.drawVertices();
        universe[i].material.end();
        ofPopMatrix();
        
    }
    cam.end();
    worldLight.disable();
    ofDisableDepthTest();
    
  // rgbaFbo.draw(0,0);
}

//--------------------------------------------------------------

void ofApp::drawFboPlanets(){
    
    ofFill();
    ofSetColor(255,255,255,40);
    ofDrawRectangle(0,0,1024,768);
    ofNoFill();
    
    cam.begin();
    ofEnableDepthTest();
    ofEnableLighting();
    worldLight.enable();
    ofSetColor(255);
    if (b_rotateCam) {
        camDist+=camRotationSpeed; // spin the universe in front of the camera
    }
    glPointSize(pointSize);
    for (int i=0; i< maxPlanets; i++){
        ofPushMatrix();
        
        ofRotateZDeg(camDist);
        ofRotateYDeg(universe[i].orbitDegrees); //rotate orbit
        ofTranslate(universe[i].location);
        ofRotateYDeg(-universe[i].rotationDegrees); // planetary spin
        universe[i].rotationDegrees += universe[i].rotationSpeed;
        universe[i].orbitDegrees += universe[i].orbitSpeed;
        
        universe[i].material.begin();
       // universe[i].sphere.draw();
        universe[i].sphere.drawWireframe();
        universe[i].sphere.drawVertices();
        universe[i].material.end();
        
        ofPopMatrix();
    }
    cam.end();
    worldLight.disable();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case OF_KEY_UP:
            
            cam.dolly(-10);
            break;
            
        case OF_KEY_DOWN:
            
            cam.dolly(10);
            break;
            
        case OF_KEY_LEFT:
            cam.truck(-10);
            break;
            
        case OF_KEY_RIGHT:
            cam.truck(10);
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    switch (key) {
        case ' ':            
            b_rotateCam = !b_rotateCam;
            break;
        case 'f':
            b_fullScreen = !b_fullScreen;
            ofSetFullscreen(b_fullScreen);
    }    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
