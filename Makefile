CXX = g++ -Wall -std=c++0x
CXXFLAGS = -g -Wall -O2
LDFLAGS = `pkg-config --cflags --libs opencv4`

TARGET = Contour_Analysis
SOURCE = $(TARGET).cpp

TARGET:FreemanCode.o Path.o DigitalLineSegment.o DigitalTangent.o DigitalTangentPositive.o Contour_Analysis.o 
	$(CXX) -o $(TARGET) FreemanCode.o  Path.o DigitalLineSegment.o DigitalTangent.o DigitalTangentPositive.o  Contour_Analysis.o $(CXXFLAGS) $(LDFLAGS)

FreemanCode.o : FreemanCode.cpp
	$(CXX) -o FreemanCode.o -c FreemanCode.cpp $(CXXFLAGS) $(LDFLAGS)

Path.o : Path.cpp FreemanCode.o DigitalTangent.o DigitalTangentPositive.o 
	$(CXX) -o Path.o -c Path.cpp $(CXXFLAGS) $(LDFLAGS)

DigitalLineSegment.o: DigitalLineSegment.cpp
	$(CXX) -o DigitalLineSegment.o -c DigitalLineSegment.cpp $(CXXFLAGS) $(LDFLAGS)

DigitalTangent.o : DigitalTangent.cpp FreemanCode.o DigitalLineSegment.o
	$(CXX) -o DigitalTangent.o -c DigitalTangent.cpp $(CXXFLAGS) $(LDFLAGS)

DigitalTangentPositive.o : DigitalTangentPositive.cpp FreemanCode.o DigitalLineSegment.o
	$(CXX) -o DigitalTangentPositive.o -c DigitalTangentPositive.cpp $(CXXFLAGS) $(LDFLAGS)



Contour_Analysis.o : Contour_Analysis.cpp FreemanCode.o Path.o DigitalLineSegment.o DigitalTangent.o DigitalTangentPositive.o 
	$(CXX) -o Contour_Analysis.o -c $(SOURCE) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f *.o *~ $(TARGET)