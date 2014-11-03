executable:=./src/main

build:=./build
src:=./src

objects:=$(build)/archivo.o $(build)/md5.o
sources:=$(src)/archivo.cpp $(src)/md5.cpp

cxx:=g++

includes:=-I./src/include 

main: $(objects)
	$(cxx) $(includes) $(objects)  -o $(build)/laboratorio3 $(executable).cpp -lpthread

$(build)/%.o: $(src)/%.cpp 
	test -d $(build) || mkdir $(build)
	$(cxx) $(includes) -c -o $(build)/$(*).o $(src)/$(*).cpp

clean:
	rm $(build)/*;
