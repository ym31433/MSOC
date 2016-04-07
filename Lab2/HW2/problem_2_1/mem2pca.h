
#ifndef MEM2PCA_H
#define MEM2PCA_H
//BEGIN: mem2pca.h (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See hier_chan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Mem_if.h"
#include "ea_heartbeat_if.h"

SC_MODULE(mem2pca), Mem_if {
    // Ports
    sc_port<ea_heartbeat_if> ck; // clock
    sc_out<bool>             ld; // load/execute command
    sc_out<bool>             rw; // read high/write low
    sc_out<unsigned>         x;  // address
    sc_out<unsigned>         y;
    sc_inout_rv<32>          d;  // data
    // Constructor
    SC_CTOR(mem2pca) {}
    // Processes
    // Interface implementations
    void write(unsigned addrY, unsigned addrX, int data);
    void read(unsigned addrY, unsigned addrX, int& data);
/*    void burst_write(unsigned long addr, unsigned size, long* data);
    void burst_read(unsigned long addr, unsigned size, long* data);
    bool nb_write(unsigned long addr, long& data);
    bool nb_read(unsigned long addr, long& data);
*/
private:
    mem2pca(const mem2pca&); // Disable
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: cpu2pca.h,v 1.2 2004/04/15 17:40:22 dcblack Exp $
