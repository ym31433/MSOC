#ifndef __edge_detect_h
#define __edge_detect_h

#include <systemc.h>

#include "simple_bus_direct_if.h"


SC_MODULE(edge_detect)
{
    // ports
    sc_in_clk clock;
    sc_port<simple_bus_direct_if> bus_port;

    SC_HAS_PROCESS(edge_detect);

    // constructor
    edge_detect(sc_module_name name_
        , bool verbose = true
        , int m_height = 512
        , int m_width  = 512)
        : sc_module(name_)
        , m_verbose(verbose)
        , height(m_height)
        , width(m_width)
    {
        // process declaration
        SC_THREAD(main_action);
    }

    // process
    void main_action();
    int edge_filtering(int* mydata);

private:
    bool m_verbose;
    int height;
    int width;

}; // end class

#endif
