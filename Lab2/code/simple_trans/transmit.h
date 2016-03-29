// transmit.h
#include "packet.h"

SC_MODULE (transmit) {
    sc_in<packet_type>	tpackin;
    sc_in<bool>	timeout;
    sc_out<packet_type>	tpackout;
    sc_out<bool>	start_timer;
    sc_in<bool>	clock;

    int buffer;
    int framenum;
    packet_type packin, tpackold;
    packet_type s;
    int retry;
    bool start;

    void send_data();
    int get_data_fromApp();

    // Constructor
    SC_CTOR(transmit) {
        SC_METHOD(send_data);
        sensitive << timeout;
        sensitive << clock.pos();
        framenum = 1;
        retry = 0;
        start = false;
        buffer = get_data_fromApp();
    }
};
