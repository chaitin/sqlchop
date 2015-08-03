.PHONY: all clean

all:
	protoc --python_out=. preprocessio.proto
	echo 'Done!'

clean:
	rm -f sqlchop.pyc
	rm -f preprocessio_pb2.py{,c}
