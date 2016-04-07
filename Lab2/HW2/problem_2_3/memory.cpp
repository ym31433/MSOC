
//BEGIN: mem_bsyn.cpp (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See hier_chan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SC_USE_SC_STRING_OLD
#include <systemc.h>
#include "memory.h"

void memory::mem_thread() {
    //bool                   reading = false;
    //bool                   m_rw;
    unsigned          addrX;
    unsigned          addrY;
    // Reset errors & float the data bus
    err.write(false);
    for(;;) {
        // Wait for a load instruction (active high) at a clock edge
        while (ld->read() == false) {
            d->write(sc_lv<32>(SC_LOGIC_Z));
            wait(ld->value_changed_event()); // wait here improves efficiency
        };
        addrX = x->read();
        addrY = y->read();
        if (rw->read()) { // reading
            // Allow for back-to-back reads. Verify legal addresses
            if (addrY < m_width && addrX < m_width) {
                d->write(m_mem[addrY][addrX]);
            }
            else {
                d->write(sc_lv<32>(SC_LOGIC_Z));
            }//endif
            // remove data and errors at next clock edge
            wait(ck->negedge_event());
        } else { // writing
            // Validate address and write
            if (addrY < m_width && addrX < m_width) {
                m_mem[addrY][addrX] = d->read().to_int();                
            }
            else {
                d->write(sc_lv<32>(SC_LOGIC_Z));
            }//endif
            wait(ck->negedge_event());
        }//endif
    }//endforever
}//end mem_bsyn::mem_thread

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: mem_bsyn.cpp,v 1.1 2004/03/03 03:18:36 dcblack Exp $
