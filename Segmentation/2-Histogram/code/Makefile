CXX = g++ -Wall -std=c++0x
CXXFLAGS = -g -Wall -O2
LDFLAGS = `pkg-config --cflags --libs opencv4`

TARGET = main 
SOURCE = functions.cpp main.cpp

TARGET:
	$(CXX) -o $(TARGET) $(SOURCE) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f *.o *~ $(TARGET)