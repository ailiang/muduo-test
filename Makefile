CC=g++ --std=c++11
INC=-I/home/dev/workspace/muduo-test/release-install-cpp11/include/ -I/usr/include/
LIB=-L/home/dev/workspace/muduo-test/release-install-cpp11/lib -lmuduo_base -lmuduo_http -lmuduo_inspect -lmuduo_net -lpthread

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

all: $(OBJ)
	$(CC) -o p $(OBJ) $(LIB)

$(OBJ): %.o:%.c
	$(CC) $(INC) -c $<

clean:
	rm -f *.o p




