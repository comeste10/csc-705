#!/usr/bin/python

"""
	Author: Steven Comer
	Description: Generates testing files
	Updated: 20 Jul 16
"""

def main():
	for i in xrange(100, 100000, 100):
		fd = open("data/in_"+str(i),'w')
		fd.write('c'*i)
		fd.close()

if __name__ == "__main__":
	main()
