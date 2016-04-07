SYSTEMC_HOME=/Users/cosine/systemc-2.3.1

TARGET=Problem_1_1
L1=interchange

$(TARGET): main.cpp $(L1).o hier_chan.h memory.h
	g++ -o $(TARGET) main.cpp $(L1).o -I$(SYSTEMC_HOME)/include -L$(SYSTEMC_HOME)/lib-macosx64 -lsystemc
$(L1).o: $(L1).cpp $(L1).h Mem_if.h
	g++ -c $(L1).cpp -I$(SYSTEMC_HOME)/include
