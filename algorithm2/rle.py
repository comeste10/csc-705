#!/usr/bin/python

import pickle
import time

"""
	File: rle.py
	Author: Steven Comer
	Description: Run Length Encoding
	Source: https://en.wikipedia.org/wiki/Run-length_encoding
	Updated: 24 Jul 2016
"""

def encode(input_file,output_file):
	start_time = time.time()
	f = open(input_file,"rb")
	count = 1
	output_list = []
	prev = ""
	curr = f.read(1)
	while curr != "":
		if curr == prev:
			count += 1
		else:
			if prev:
				output_list.append((prev,count))
			count = 1
			prev = curr
		curr = f.read(1)
	output_list.append((prev,count))
	f.close()
	stop_time = time.time()
	f = open(output_file,"wb")
	pickle.dump(output_list, f)
	f.close()
	return stop_time - start_time

def decode(input_file,output_file):
	f = open(input_file,"rb")
	input_list = pickle.load(f)
	f.close()
	start_time = time.time()
	output = bytearray("")
	for b,count in input_list:
		output += b*count
	f = open(output_file,"wb")
	f.write(output)
	f.close()
	stop_time = time.time()
	return stop_time - start_time

def main():
	print "Run Length Encoding (RLE) Example"
	print "Encoding file test.data"
	encode("test.data","test.data.rle")
	decode("test.data.rle","test.data.dec")
	print "Done"

if __name__ == "__main__":
	main()

