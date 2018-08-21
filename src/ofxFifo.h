
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

using namespace std;
namespace ofxFifo{
    inline string exec(const char* cmd){
        std::array<char, 128> buffer;
        std::string result;
        std::shared_ptr<FILE> pipe(popen(cmd,"r"),pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (!feof(pipe.get())){
            if (fgets(buffer.data(), 128, pipe.get()) != nullptr){
                ofLogVerbose()<<"reading exec results...";
                result += buffer.data();
            }
        }
        return result;
    }
    
    inline void del(string pipe_dir="pipe"){
        string cmd ="rm -f "+pipe_dir;
        system(cmd.c_str());
    }
    inline void make(string pipe_dir="pipe"){
        string cmd ="mkfifo "+pipe_dir;
        system(cmd.c_str());
    }
    
    inline void write_str(string dat, string pipe_dir="pipe"){
        string cmd ="echo \""+dat+"\" > "+pipe_dir;
        ofLogVerbose()<<cmd;
        system(cmd.c_str());
    }

    inline string read_str(string pipe_dir="pipe"){
        if (!ofFile::doesFileExist(pipe_dir)){
            throw invalid_argument("file does not exist");
        }
        std::ifstream file;
        file.open(pipe_dir);
        std::string data;
        std::string line;
        while (std::getline(file, line)){
            data += line + "\n";
        }
        file.close();
        //ofLogVerbose()<<data;
        del(pipe_dir);
        return data;
    }
    
    inline void write_image(ofPixels img, string pipe_dir="pipe"){
        int w = img.getWidth();
        int h = img.getHeight();
        int c = img.getNumChannels();
        unsigned char* carr = img.getData();
        std::string dat = "";
        for (int i = 0; i < w*h*c; i++){
            dat += carr[i];
        }
        ofLogVerbose() << dat;
        std::ofstream file;
        file.open(pipe_dir);
        file << setw(5) << setfill('0') << h;
        file << setw(5) << setfill('0') << w;
        file << setw(5) << setfill('0') << c;
        file << dat;
        file.close();
        ofLogVerbose() << dat.size() << " written.";
    }
    inline void write_image(ofImage img, string pipe_dir="pipe"){
        write_image(img.getPixels(), pipe_dir);
    }
    inline tuple<int,int,int,unsigned char*> read_image_array(string pipe_dir="pipe"){
        string rec = read_str(pipe_dir);
        int h = ofToInt(rec.substr(0,5));
        int w = ofToInt(rec.substr(5,5));
        int c = ofToInt(rec.substr(10,5));
        string dat = rec.substr(15,h*w*c);

        ofLogVerbose()<<ofToString(h)<<","<<ofToString(w)<<","<<ofToString(c);
        ofLogVerbose()<<ofToString(dat.size())<<"/"<<ofToString(w*h*c);
        
        ofLogVerbose()<<"read complete.";
        return make_tuple(h,w,c,(unsigned char *)(dat.c_str()));
    }
    inline ofImage read_image(string pipe_dir="pipe"){
        tuple<int,int,int,unsigned char*> dat = read_image_array(pipe_dir);
        int h = get<0>(dat);
        int w = get<1>(dat);
        int c = get<2>(dat);
        unsigned char * carr = get<3>(dat);
        ofImage img;
        ofImageType typ;
        if (c == 4){
            typ = OF_IMAGE_COLOR_ALPHA;
        }else if (c == 3){
            typ = OF_IMAGE_COLOR;
        }else if (c == 1){
            typ = OF_IMAGE_GRAYSCALE;
        }
        img.setFromPixels(carr,w,h,typ);
        return img;
    }
    
    
}
