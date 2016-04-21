SYSTEMC_HOME=/Users/cosine/systemc-2.3.1

TARGET=Edge_detection
L1=edge_detect
L2=simple_bus_arbiter
#L3=simple_bus_main
L4=simple_bus

$(TARGET): main.cpp $(L1).o $(L2).o $(L4).o simple_bus_tools.cpp simple_bus_types.cpp
	g++ -o $(TARGET) main.cpp $(L1).o $(L2).o  $(L4).o simple_bus_tools.cpp simple_bus_types.cpp -I$(SYSTEMC_HOME)/include -L$(SYSTEMC_HOME)/lib-macosx64 -lsystemc
$(L1).o: $(L1).cpp $(L1).h simple_bus_types.h
	g++ -c $(L1).cpp -I$(SYSTEMC_HOME)/include
$(L2).o: $(L2).cpp $(L2).h
	g++ -c $(L2).cpp -I$(SYSTEMC_HOME)/include
#$(L3).o: $(L3).cpp simple_bus_test.h
#	g++ -c $(L3).cpp -I$(SYSTEMC_HOME)/include
$(L4).o: $(L4).cpp $(L4).h
	g++ -c $(L4).cpp -I$(SYSTEMC_HOME)/include
