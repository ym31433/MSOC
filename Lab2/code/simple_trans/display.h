// display.h
#include "packet.h"

SC_MODULE(display) {
    sc_in<long> din;

    void print_data();
    // Constructor
    SC_CTOR(display) {
        SC_METHOD(print_data);
        sensitive << din;
    }
};
