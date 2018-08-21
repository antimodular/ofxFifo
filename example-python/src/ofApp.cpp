#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(640,480);
    fbo.allocate(200,200);
    vwt.pipe_dir = "../../../data/video_out";
    vwt.startThread(true);
    
    // run the python script
    // use "&" to fork the process so it's non-blocking
    system("cd ../../../../src; /usr/local/bin/python pyApp.py &");
    // python window typically tend to hide in the back
    // bring it to front by eg. clicking its icon in dock
    
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
    ofxFifo::del(vwt.pipe_dir);
    system("killall python"); // Make sure that you don't have any
                              // other processes called python!
                              // One workaround is duplicate the
                              // python binary and rename it into
                              // something like "my_special_python",
                              // and use it specifically for this task.
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
