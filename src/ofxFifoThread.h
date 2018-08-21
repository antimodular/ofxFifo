#pragma once
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>

using namespace std;
namespace ofxFifo{
    
    class vidWriteThread : public ofThread{
    protected:
        int did_frame = -1;
    public:
        ofPixels pixels;
        string pipe_dir;
        float fps = 0;
        void threadedFunction(){
            float t = ofGetElapsedTimef();
            while (isThreadRunning()){
                if (did_frame != ofGetFrameNum()){
                    lock();
                    write_image(pixels,pipe_dir);
                    did_frame = ofGetFrameNum();
                    float t1 = ofGetElapsedTimef();
                    fps = 1.0/(t1-t);
                    t = t1;
                    unlock();
                }
            }
        }
    };
    class vidReadThread : public ofThread{
    protected:
        int did_frame = -1;
    public:
        ofPixels pixels;
        unsigned char * arr;
        int w;
        int h;
        int c;
        string pipe_dir;
        float fps = 0;
        void threadedFunction(){
            float t = ofGetElapsedTimef();
            while (isThreadRunning()){
                if (did_frame != ofGetFrameNum()){
                    lock();
                    try{
                        tie(h,w,c,arr) = read_image_array(pipe_dir);
                        pixels.setFromPixels(arr,w,h,c);
                    }catch(const invalid_argument& ){
                        ofLogVerbose()<<"pipe not ready";
                    }catch(...){
                        ofLogVerbose()<<"unknown error";
                    }
                    did_frame = ofGetFrameNum();
                    float t1 = ofGetElapsedTimef();
                    fps = 1.0/(t1-t);
                    t = t1;
                    unlock();
                }
            }
        }
    };
}
