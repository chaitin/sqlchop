uname=$$(uname | tr [:upper:] [:lower:])

all: ./cn/chaitin/sqlchop/protobuf/Sqlchopio.class ./jni/libSQLChopJni.jnilib ./cn/chaitin/sqlchop/SQLChop.class


./jni/libSQLChopJni.jnilib : ./jni/cn_chaitin_sqlchop_SQLChop.h ./jni/SQLChop.c
	gcc -shared -fPIC -I $(java_home)/include -I$(java_home)/include/$(uname) -L./jni -lsqlchop ./jni/SQLChop.c -o ./libSQLChopJni.jnilib

./jni/cn_chaitin_sqlchop_SQLChop.h : ./cn/chaitin/sqlchop/SQLChop.class
	javah -jni -classpath ./protobuf-java-2.6.1.jar:. -d ./jni cn.chaitin.sqlchop.SQLChop

./cn/chaitin/sqlchop/protobuf/Sqlchopio.class ./cn/chaitin/sqlchop/SQLChop.class : ./cn/chaitin/sqlchop/protobuf/Sqlchopio.java ./cn/chaitin/sqlchop/SQLChop.java
	javac -classpath ./protobuf-java-2.6.1.jar:. ./cn/chaitin/sqlchop/protobuf/Sqlchopio.java  ./cn/chaitin/sqlchop/SQLChop.java

./cn/chaitin/sqlchop/protobuf/Sqlchopio.java : sqlchopio.proto
	protoc --java_out="./" sqlchopio.proto

clean :
	rm -rf ./cn/chaitin/SQLchop/protobuf
	rm ./cn/chaitin/sqlchop/*.class
	rm ./jni/cn_chaitin_sqlchop_SQLChop_ClassifyResult.h
	rm ./jni/cn_chaitin_sqlchop_SQLChop.h
	rm ./libSQLChopJni.jnilib

test :
	@export DYLD_LIBRARY_PATH="$${DYLD_LIBRARY_PATH}:./jni:./jni/render";
	java -classpath ./protobuf-java-2.6.1.jar:. cn.chaitin.sqlchop.SQLChop
