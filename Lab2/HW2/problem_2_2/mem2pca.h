
#ifndef MEM2PCA_H
#define MEM2PCA_H
//BEGIN: mem2pca.h (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See hier_chan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "ea_heartbeat_if.h"
#include "Mem_if.h"

SC_MODULE(mem2pca) {
    // Ports
    sc_port<Mem_if>         mem;
    sc_port<ea_heartbeat_if> ck; // clock
    sc_in<bool>             ld; // load/execute command
    sc_in<bool>             rw; // read high/write low
    sc_in<unsigned>         x;  // address
    sc_in<unsigned>         y;
    sc_inout_rv<32>          d;  // data
    // Constructor
    SC_CTOR(mem2pca) {
        SC_THREAD(mem2pca_thread);
    }
    // Processes
    // Interface implementations
    void mem2pca_thread();
//    void write(unsigned addrY, unsigned addrX, int data);
//    void read(unsigned addrY, unsigned addrX, int& data);
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
