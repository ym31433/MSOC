
#ifndef INTERCHANGE_H
#define INTERCHANGE_H
//BEGIN: interchange.h (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See hier_chan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SC_MODULE(interchange) {
    sc_out<bool> done;
    sc_in_clk                ck; // clock
    sc_out<bool>             ld; // load/execute command
    sc_out<bool>             rw; // read high/write low
    sc_out<unsigned>         x;  // address
    sc_out<unsigned>         y;
    sc_inout_rv<32>          d;  // data
    
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
