ofxFifo
=====================================
![](ofxaddons_thumbnail.png)

ofxFifo is an openFrameworks addon that enables different apps to exchange large amout of data in real time using named pipes (FIFO). For example, you can grab video from webcam in openFrameworks, send the frames to python for processing, and retrieve its output in real time. Another possible usage is having two openFramework apps communicating with each other.

Installation
------------
Drop the `ofxFifo` folder into the `openFrameworks/addons/` folder and that's it.
Tested on macOS 10.12 with OF 0.9.8, but should also work with other OS and OF versions.

Examples
------------

### OpenFrameworks x2
- Build the examples `example-write/` and `example-read/`
- Open both apps
- You will see a real-time video feed in one window. This is what your webcam sees. There's a smaller, scaled version of the same imagery in the other window. This is the image data being sent and received.
- Look into the code to explore the details.

### OpenFrameworks + python
There's also a built-in example for passing video between OF and python.

- To run this specific demo, you'll need `python` and `opencv-python` (e.g. `pip install numpy; pip install opencv-python`).
- Build `example-python/` and run
- You'll see an OF window displaying the webcam feed, and a python window displaying the image data transfered.
- The python window might be in the back, bring it to front by e.g. clicking on its icon in dock.
- Look into the code to explore the details

### OpenFrameworks + ???
You can also communicate with ofxFifo from your favorite language. Here's how to do it:

- The shell command for reading and writing named pipes are:

```
echo "Hello there" > my_awesome_pipe
cat my_awesome_pipe                   
# output: "Hello there"
```
- Since most languages has a `system()` function, you can simply call the above commands within your code. Or you can use your language-specific libraries to manage named pipes.
- `timeout` on linux and `gtimeout` from `coreutils` on macOS may be handy for making pipe operations non-blocking. Multi-threading may also be used for the same reason.

#### Image data format

For transfering images, the following format is used:

- The first 15 characters indicate the size of the image. They're string of integers left-padded with zero: [0:5] is height, [5:10] is width, [10:15] is number of channels. (e.g. `004800064000003` represents a 640x480 RGB image).
- All the rest characters are pixel information encoded as an array of `unsigned char`, in row-major, RGB order.

Known issues
------------
When receiving larger images in OpenFrameworks, some frames observe partial corruption. This is either due to data lost in pipe I/O, or C++'s problem with huge arrays. If you're a C++ pro and think you can fix this problem, pull requests are very welcome! 

