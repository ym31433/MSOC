SYSTEMC_HOME=/Users/cosine/systemc-2.3.1
target=simple_perf

$(target): main.cpp fifo.h fifo.cpp consumer.h consumer.cpp producer.h producer.cpp read_if.h write_if.h
	g++ -o $(target) main.cpp fifo.cpp consumer.cpp producer.cpp -I$(SYSTEMC_HOME)/include -L$(SYSTEMC_HOME)/lib-macosx64 -lsystemc
