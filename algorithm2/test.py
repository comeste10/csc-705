#!/usr/bin/python

from rle import encode,decode
from os import system,stat

"""
	File: test.py
	Author: Steven Comer
	Description: Testing suite for rle.py
	Updated: 25 Jul 2016
	Data of interest:
		runtime_enc.csv -- file size vs encode runtime
		runtime_dec.csv -- file size vs decode runtime
		compression.csv -- file size vs compression ratio (uncompressed/compressed)
"""

def main():
	d_run_enc = {}
	d_run_dec = {}
	d_comp = {}
	for i in xrange(21):
		system("head -c " + str(2**i) + " < /dev/urandom > test.data")		
		enc_time = encode("test.data","test.data.rle")
		dec_time = decode("test.data.rle","test.data.dec")
		file_size = stat("test.data").st_size
		enc_file_size = stat("test.data.rle").st_size
		d_run_enc[2**i] = round(enc_time,5)
		d_run_dec[2**i] = round(dec_time,5)
		d_comp[2**i] = round(float(file_size)/float(enc_file_size),5)
	f_run_enc = open("runtime_enc.csv","w")
	f_run_dec = open("runtime_dec.csv","w")
	f_comp = open("compression.csv","w")
	for item in d_run_enc:
		f_run_enc.write(str(item) + "," + str(d_run_enc[item]) + "\n")
		f_run_dec.write(str(item) + "," + str(d_run_enc[item]) + "\n")
		f_comp.write(str(item) + "," + str(d_comp[item]) + "\n")
	f_run_enc.close()
	f_run_dec.close()
	f_comp.close()

if __name__ == "__main__":
	main()
