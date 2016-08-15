#!/usr/bin/python

import os
import time

"""
	Author: Steven Comer
	Description: Spritz empirical testing
	Updated: 20 Jul 16
"""

def main():
	d = {}
	for i in os.listdir("data"):
		start = time.time()
		os.system("./test < data/" + i)
		stop = time.time()
		d[int(i[3:])] = round(stop-start,5)
	for j in sorted(d):
		print str(j) + "," + str(d[j])

if __name__ == "__main__":
	main()