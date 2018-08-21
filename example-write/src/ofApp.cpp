#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(640,480);
    fbo.allocate(200,200);
    vwt.pipe_dir = "../../../../../example-read/bin/data/video_out";
    vwt.startThread(true);
}
//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    fbo.begin();
    grabber.draw(0,0,pix.getWidth(),pix.getHeight());
    fbo.end();
    fbo.readToPixels(pix);
    vwt.lock();
    vwt.pixels = pix;
    ofDrawBitmapStringHighlight(ofToString(vwt.fps),0,10);
    vwt.unlock();
}
//--------------------------------------------------------------
void ofApp::exit(){
    vwt.stopThread();
}

//--------------------------------------------------------------
void ofApp::draw(){
    grabber.draw(0,0);
    ofDrawBitmapStringHighlight("FPS: "+ofToString(vwt.fps,2),0,10);
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
