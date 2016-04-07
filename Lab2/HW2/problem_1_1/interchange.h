
#ifndef INTERCHANGE_H
#define INTERCHANGE_H
//BEGIN: interchange.h (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See hier_chan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Mem_if.h"

SC_MODULE(interchange) {
    sc_port<Mem_if> mem;
    sc_out<bool> done;
    SC_HAS_PROCESS(interchange);
    interchange(
        sc_module_name nm,
        unsigned       w
        )
        : sc_module(nm)
        , m_width(w)
    {
        SC_THREAD(interchange_thread);
    }
    void interchange_thread();
private:
    unsigned      m_width;
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: testbench.h,v 1.3 2004/05/05 19:46:22 dcblack Exp $
