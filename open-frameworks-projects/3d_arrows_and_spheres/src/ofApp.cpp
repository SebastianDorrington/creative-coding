#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofSetCircleResolution(64);
    
    light.setup();
    light.enable();
    light.setPosition(300, 300, 300); // Position above and in front of the scene

    sphereCount = 1;
    drawSpheres = true;
    drawArrows = true;

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(213, 202, 205);

    // Settings
    float cloudSize = ofGetWidth() / 8;
    float maxSphereSize = 5;
    float spacing = 0.3;
    float sphereSpeed = 0.1;
    float arrowSpeed = 0.1;

    ofColor colorA = ofColor(208, 239, 177);
    ofColor colorB = ofColor(77, 114, 152);
    
    ofColor colorC = ofColor(234, 99, 140);
    ofColor colorD = ofColor(0, 42, 34);
    
    cam.begin();
    light.enable();

    for(int i = 0; i < sphereCount; i++) {
        ofPushMatrix();

        float t = (ofGetElapsedTimef() + i * spacing) * sphereSpeed;

        if (drawSpheres) {
            // ---- Spheres: use one noise function ----
            glm::vec3 spherePos(
                ofSignedNoise(t, 0, 0),
                ofSignedNoise(0, t, 0),
                ofSignedNoise(0, 0, t)
            );
            spherePos *= cloudSize;

            float lerpAmount1 = (sin(t) + 1.0f) / 2.0f; // Map sin(t) from [-1,1] to [0,1]
            ofColor currentColor1 = colorA.getLerped(colorB, lerpAmount1);
            
            ofSetColor(currentColor1);
            ofPushMatrix();
            ofTranslate(spherePos);
            ofDrawIcoSphere(glm::vec3(0), maxSphereSize);

        } if (drawArrows) {
            // ---- Arrows: use different noise offsets to generate unique positions ----
            float offset = 100.0; // ensure arrows don't overlap spheres' paths

            glm::vec3 arrowPos(
                ofSignedNoise(t + offset, 0, 0),
                ofSignedNoise(0, t + offset, 0),
                ofSignedNoise(0, 0, t + offset)
            );
            arrowPos *= cloudSize;

            float tNext = (ofGetElapsedTimef() + (i + 1) * spacing) * arrowSpeed;
            glm::vec3 arrowNextPos(
                ofSignedNoise(tNext + offset, 0, 0),
                ofSignedNoise(0, tNext + offset, 0),
                ofSignedNoise(0, 0, tNext + offset)
            );
            arrowNextPos *= cloudSize;

            glm::vec3 dir = glm::normalize(arrowNextPos - arrowPos);
            glm::vec3 end = arrowPos + dir * 20.0f;

            
            float lerpAmount2 = (sin(t) + 1.0f) / 2.0f; // Map sin(t) from [-1,1] to [0,1]
            ofColor currentColor2 = colorC.getLerped(colorD, lerpAmount2);
            ofSetColor(currentColor2);

            ofDrawArrow(arrowPos, end, 5.0f);
        }

        ofPopMatrix();
    }
    
    light.disable();
    cam.end();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '+' || key == '=') {
        sphereCount += 1;
    } else if (key == '-' || key == '_') {
        sphereCount = max(1, sphereCount - 1);
    } else if (key == 's' || key == 'S') {
        drawSpheres = !drawSpheres;
    } else if (key == 'a' || key == 'A') {
        drawArrows = !drawArrows;
    }
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
