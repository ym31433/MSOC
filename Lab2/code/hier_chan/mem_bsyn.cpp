//BEGIN: mem_bsyn.cpp (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See hier_chan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SC_USE_SC_STRING_OLD
#include <systemc.h>
#include "mem_bsyn.h"

void mem_bsyn::mem_thread() {
    bool                   reading = false;
    bool                   m_rw;
    unsigned long          addr;
    // Reset errors & float the data bus
    err.write(false);
    for(;;) {
        // Wait for a load instruction (active high) at a clock edge
        while (ld->read() == false) {
            d->write(sc_lv<32>(SC_LOGIC_Z));
            wait(ld->value_changed_event()); // wait here improves efficiency
        };
        addr = a->read();
        if (rw->read()) { // reading
            // Allow for back-to-back reads. Verify legal addresses
            if (m_base <= addr && addr < m_base+m_size) {
                d->write(m_mem[addr-m_base]);
            }
            else {
                d->write(sc_lv<32>(SC_LOGIC_Z));
            }//endif
            // remove data and errors at next clock edge
            wait(ck->posedge_event());
        } else { // writing
            // Validate address and write
            if (m_base <= addr && addr < m_base+m_size) {
                m_mem[addr-m_base] = d->read().to_long();                
            }
            else {
                d->write(sc_lv<32>(SC_LOGIC_Z));
            }//endif
            wait(ck->posedge_event());
        }//endif
    }//endforever
}//end mem_bsyn::mem_thread

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: mem_bsyn.cpp,v 1.1 2004/03/03 03:18:36 dcblack Exp $
