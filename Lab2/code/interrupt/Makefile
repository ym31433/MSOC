SYSTEMC_HOME=/Users/cosine/systemc-2.3.1

TARGET=Lab2
L1=interrupt
L2=stim
L3=resp

$(TARGET): main.cpp $(L1).o $(L2).o $(L3).o 
	g++ -o $(TARGET) main.cpp $(L1).o $(L2).o $(L3).o -I$(SYSTEMC_HOME)/include -L$(SYSTEMC_HOME)/lib-macosx64 -lsystemc
$(L1).o: $(L1).cpp $(L1).h ea_interrupt.h stim.h resp.h
	g++ -c $(L1).cpp -I$(SYSTEMC_HOME)/include
$(L2).o: $(L2).cpp $(L2).h ea_interrupt_gen_if.h
	g++ -c $(L2).cpp -I$(SYSTEMC_HOME)/include
$(L3).o: $(L3).cpp $(L3).h ea_interrupt_evt_if.h
	g++ -c $(L3).cpp -I$(SYSTEMC_HOME)/include
