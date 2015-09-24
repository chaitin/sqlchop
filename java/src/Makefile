java_home=$$(find / -name jni.h 2>/dev/null | grep -e 'include/jni.h$$' | tail -n 1 | sed 's/\/include\/jni.h//g')
uname=$$(uname | tr [:upper:] [:lower:])
lib_path=/usr/lib64

all : ./cn/chaitin/sqlchop/protobuf/Sqlchopio.class $(lib_path)/libSQLChopJni.so ./cn/chaitin/sqlchop/SQLChop.class


$(lib_path)/libSQLChopJni.so : ./jni/cn_chaitin_sqlchop_SQLChop.h ./jni/SQLChop.c
	cp ../../libsqlchop.so $(lib_path)/libsqlchop.so
	gcc -shared -fPIC -Wall -O3 -I $(java_home)/include -I$(java_home)/include/$(uname) -lsqlchop ./jni/SQLChop.c -o $(lib_path)/libSQLChopJni.so

./jni/cn_chaitin_sqlchop_SQLChop.h : ./cn/chaitin/sqlchop/SQLChop.class
	javah -jni -classpath ./protobuf-java-2.6.1.jar:. -d ./jni cn.chaitin.sqlchop.SQLChop

./cn/chaitin/sqlchop/protobuf/Sqlchopio.class ./cn/chaitin/sqlchop/SQLChop.class : ./cn/chaitin/sqlchop/protobuf/Sqlchopio.java ./cn/chaitin/sqlchop/SQLChop.java
	javac -classpath ./protobuf-java-2.6.1.jar:. ./cn/chaitin/sqlchop/protobuf/Sqlchopio.java  ./cn/chaitin/sqlchop/SQLChop.java

./cn/chaitin/sqlchop/protobuf/Sqlchopio.java : sqlchopio.proto
	protoc --java_out="./" sqlchopio.proto

clean :
	rm -rf ./cn/chaitin/sqlchop/protobuf
	rm -f ./cn/chaitin/sqlchop/*.class
	rm -f ./jni/cn_chaitin_sqlchop_SQLChop_ClassifyResult.h
	rm -f ./jni/cn_chaitin_sqlchop_SQLChop.h
	rm -f $(lib_path)/libSQLChopJni.so
	rm -f $(lib_path)/libsqlchop.so

test :
	java -classpath ./protobuf-java-2.6.1.jar:. cn.chaitin.sqlchop.SQLChop
