CXX=g++

CXXSTANDARD=-std=c++11

CXXWARNINGS=-Wall -Wextra -Werror

INCLUDES=-I include/

LIBS=-I/sw/easybuild/software/MPI/GCC/5.4.0-2.26/OpenMPI/1.10.3/ROOT/6.10.02-Python-2.7.12/include -L/sw/easybuild/software/MPI/GCC/5.4.0-2.26/OpenMPI/1.10.3/ROOT/6.10.02-Python-2.7.12/lib -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -pthread -lm -ldl -rdynamic

CXXFLAGS=$(CXXSTANDARD) $(CXXWARNINGS)

EXECUTABLE=reg

OPTIMIZE=-O3

FILES=build/main.o build/csvregex.o build/Gregorian.o build/WeatherDataVec.o build/command_line.o build/avg_periodtemp.o build/global_temperature_regression.o build/project.o build/corona.o build/monthly.o

reg: build $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(EXECUTABLE) $(LIBS)

build/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(OPTIMIZE) $(INCLUDES) -c main.cpp -o build/main.o

build/csvregex.o: main.cpp
	$(CXX) $(CXXFLAGS) $(OPTIMIZE) $(INCLUDES) -c src/csvregex.cpp -o build/csvregex.o

build/Gregorian.o: main.cpp
	$(CXX) $(CXXFLAGS) $(OPTIMIZE) $(INCLUDES) -c src/Gregorian.cpp -o build/Gregorian.o

build/WeatherDataVec.o: main.cpp
	$(CXX) $(CXXFLAGS) $(OPTIMIZE) $(INCLUDES) -c src/WeatherDataVec.cpp -o build/WeatherDataVec.o

build/command_line.o: main.cpp
	$(CXX) $(CXXFLAGS) $(OPTIMIZE) $(INCLUDES) -c src/command_line.cpp -o build/command_line.o

build/avg_periodtemp.o: main.cpp
	$(CXX) $(CXXFLAGS) $(OPTIMIZE) $(INCLUDES) -c src/avg_periodtemp.C -o build/avg_periodtemp.o

build/project.o: main.cpp
	$(CXX) $(CXXFLAGS) $(OPTIMIZE) $(INCLUDES) -c src/project.cpp -o build/project.o

build/global_temperature_regression.o: main.cpp
	$(CXX) $(CXXFLAGS) $(OPTIMIZE) $(INCLUDES) -c src/global_temperature_regression.C -o build/global_temperature_regression.o

build/corona.o: main.cpp
	$(CXX) $(CXXFLAGS) $(OPTIMIZE) $(INCLUDES) -c src/corona.C -o build/corona.o

build/monthly.o: main.cpp
	$(CXX) $(CXXFLAGS) $(OPTIMIZE) $(INCLUDES) -c src/monthly.C -o build/monthly.o

build:
	@mkdir build
