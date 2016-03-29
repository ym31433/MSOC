//BEGIN pcix.cpp (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See pcix.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "pcix.h"
#include "ea_pcix_trans.h"

#define repeat(VAR,N) for(int VAR=0;VAR<(N);VAR++)

void pcix::pcix_packet_thread(void) {
    ea_pcix_trans new_trans;
    repeat(pass,20) {
        // Create a new value with some random data;
        new_trans.devnum = rand();
        new_trans.addr = rand();
        new_trans.attr1 = rand();
        new_trans.attr2 = rand();
        new_trans.cmnd = rand();
        repeat(i,8) new_trans.data[i] = 0;
        repeat(i,rand()&7) {
            new_trans.data[i] = rand();
        }
        pcix_trans.write(new_trans); // signal assignment
        pcix_fifo.write(new_trans); // fifo push
        wait(2,SC_NS);
    }//endrepeat
    repeat(i,4) wait(1,SC_NS);
}//end pcix::pcix_packet_thread()

void pcix::pcix_packet_method(void) {
    cout << sc_time_stamp() << " New PCIX transaction " << pcix_trans << endl;
}//end pcix::pcix_packet_method()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: pcix.cpp,v 1.1 2004/02/12 12:27:50 dcblack Exp $
