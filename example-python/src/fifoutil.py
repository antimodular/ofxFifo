# -*- coding: utf-8 -*-
import numpy as np
import os
import threading

def read_txt(pipe_dir="pipe"):
	with open(pipe_dir,'r') as f:
		return f.read()

def write_txt(dat, pipe_dir="pipe", wait=False, rm=False):
	if wait:
		if rm:
			try:
				os.system("rm "+pipe_dir)
			except:
				pass
		if not os.path.exists(pipe_dir):
			os.mkfifo(pipe_dir)
		with open(pipe_dir,'wb') as f:
			f.write(dat)
		# print("what was written is now read.")
	else:
		t = threading.Thread(target=write_txt, args=(dat,pipe_dir,True))
		t.daemon = True
		tcnt = threading.active_count()
		if tcnt > 10:
			for th in threading.enumerate():
				if (th.is_alive()):
					th._Thread__stop()
					# print("stopping:", th, "success?", not th.is_alive())
		# print(tcnt, threading.active_count())
		t.start()

def read_array(pipe_dir="pipe"):
	f = read_txt(pipe_dir = pipe_dir)
	h = int(f[:5])
	w = int(f[5:10])
	c = int(f[10:15])
	data = f[15:]
	im = np.frombuffer(data,dtype=np.uint8)
	imr = np.reshape(im,(h,w,c))
	return imr

def write_array(im, pipe_dir="pipe", wait=False):
	h, w, c = im.shape
	header = str(h).zfill(5)\
	       + str(w).zfill(5)\
	       + str(c).zfill(5)
	qkpipe.write_pipe(header + im.tobytes(), pipe_dir=pipe_dir, wait=wait)

