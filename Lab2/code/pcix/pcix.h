#ifndef PCIX_PACKET_H
#define PCIX_PACKET_H
//BEGIN pcix.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   This is an example of a custom data type that is enabled
//   to be used as an sc_signal or an sc_fifo.
//
// DESIGN HIERARCHY
//   sc_main()
//   +- pcix_packet_i
//    +- pcix_packet_thread # generates random packets
//    +- pcix_packet_method # recieves and displays packets
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>
#include "ea_pcix_trans.h"

SC_MODULE(pcix) {
    sc_signal<ea_pcix_trans> pcix_trans;
    sc_fifo<ea_pcix_trans> pcix_fifo;
    SC_CTOR(pcix)
    {
        SC_THREAD(pcix_packet_thread);
        SC_METHOD(pcix_packet_method);
        sensitive << pcix_trans;
        dont_initialize();
    }
    void pcix_packet_thread(void);
    void pcix_packet_method(void);
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: pcix.h,v 1.2 2004/04/15 17:42:58 dcblack Exp $
