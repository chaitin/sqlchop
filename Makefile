CXX := $(shell command -v clang++ || command -v g++)
CXXFLAGS := -O2
LDFLAGS += -L./ -lsqlchop `pkg-config --libs protobuf`

.PHONY: all clean

all: sqlchop_cpp sqlchop_python

sqlchop_cpp: sqlchop_test
sqlchop_python: sqlchopio_pb2.py

sqlchopio_pb2.py: 
	protoc --python_out=. sqlchopio.proto

sqlchopio.pb.cc: 
	protoc --cpp_out=. sqlchopio.proto

sqlchop_test: sqlchopio.pb.cc
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ test.cc sqlchopio.pb.cc

clean:
	rm -f sqlchop_test
	rm -f sqlchop.pyc
	rm -f sqlchopio_pb2.py{,c}
	rm -f sqlchopio.pb.{cc,h,o}
