SYSTEMC_HOME=/Users/cosine/systemc-2.3.1

TARGET=problem_2
L1=interchange
L2=simple_bus_arbiter
L3=memory
L4=simple_bus
L5=simple_bus_master_non_blocking

all:$(TARGET)
	rm *.o
	./$(TARGET)

clean:
	rm *.o

$(TARGET): main.cpp $(L1).o $(L2).o $(L3).o $(L4).o $(L5).o simple_bus_tools.cpp simple_bus_types.cpp
	g++ -o $(TARGET) main.cpp $(L1).o $(L2).o $(L3).o $(L4).o $(L5).o simple_bus_tools.cpp simple_bus_types.cpp -I$(SYSTEMC_HOME)/include -L$(SYSTEMC_HOME)/lib-macosx64 -lsystemc
$(L1).o: $(L1).cpp $(L1).h
	g++ -c $(L1).cpp -I$(SYSTEMC_HOME)/include
$(L2).o: $(L2).cpp $(L2).h
	g++ -c $(L2).cpp -I$(SYSTEMC_HOME)/include
$(L3).o: $(L3).cpp $(L3).h
	g++ -c $(L3).cpp -I$(SYSTEMC_HOME)/include
$(L4).o: $(L4).cpp $(L4).h
	g++ -c $(L4).cpp -I$(SYSTEMC_HOME)/include
$(L5).o: $(L5).cpp $(L5).h
	g++ -c $(L5).cpp -I$(SYSTEMC_HOME)/include