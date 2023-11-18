PORT=/dev/ttyUSB0

build:
	idf.py build

upload:
	idf.py -p $(PORT) flash