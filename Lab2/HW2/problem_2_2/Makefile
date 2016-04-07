SYSTEMC_HOME=/Users/cosine/systemc-2.3.1

TARGET=Problem_2_2
L2=mem2pca
L3=interchange
L4=ea_heartbeat

$(TARGET): main.cpp $(L2).o $(L3).o $(L4).o memory.h hier_chan.h
	g++ -o $(TARGET) main.cpp $(L2).o $(L3).o $(L4).o -I$(SYSTEMC_HOME)/include -L$(SYSTEMC_HOME)/lib-macosx64 -lsystemc
$(L2).o: $(L2).cpp $(L2).h ea_heartbeat_if.h Mem_if.h
	g++ -c $(L2).cpp -I$(SYSTEMC_HOME)/include
$(L3).o: $(L3).cpp $(L3).h ea_heartbeat_if.h
	g++ -c $(L3).cpp -I$(SYSTEMC_HOME)/include
$(L4).o: $(L4).cpp $(L4).h ea_heartbeat_if.h
	g++ -c $(L4).cpp -I$(SYSTEMC_HOME)/include
