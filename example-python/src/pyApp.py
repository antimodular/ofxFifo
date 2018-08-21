# pyApp.py
# example usage for comunnicating with ofxFifo
# Lingdong@antimodular 2018

# python modules required to run this demo:
# - cv2   (pip install opencv-python)
# - numpy (pip install numpy)

import cv2
import fifoutil
import time


def main():
    t0 = time.time()
    while True:
        im = None
        try:
            im = fifoutil.read_array("../bin/data/video_out") # read data as image from pipe
        except:
            pass # possibly corrupted data, ignore

        if im is not None:
            im = cv2.cvtColor(im, cv2.COLOR_RGB2BGR) # cv2 uses BGR colorspace

            # calculate and draw the fps
            t = time.time(); fps = 1/(t-t0); t0 = t
            im[0:15,0:90] = im[0:15,0:90]*0.5 # dark background for text
            cv2.putText(im, "FPS: "+str(int(fps*100)/100.0), (0, 11), 
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,255,255), 1)

            cv2.imshow("I'm a python window!", im) # display the frame

        if cv2.waitKey(1) & 0xFF == ord('q'): # press 'q' to quit
            break


if __name__ == "__main__":
    main()