PORT=/dev/ttyUSB0

build: ./main/*
	idf.py build

clean:
	idf.py fullclean

config:
	idf.py menuconfig

upload:
	idf.py -p $(PORT) flash
