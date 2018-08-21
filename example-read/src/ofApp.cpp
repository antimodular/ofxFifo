#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    vrt.pipe_dir = "../../../data/video_out";
    vrt.startThread(true);
}
//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
}
//--------------------------------------------------------------
void ofApp::exit(){
    vrt.stopThread();
}

//--------------------------------------------------------------
void ofApp::draw(){
    vrt.lock();
    img.setFromPixels(vrt.pixels);
    img.draw(0,0);
    ofDrawBitmapStringHighlight("FPS: "+ofToString(vrt.fps,2),0,10);
    vrt.unlock();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
