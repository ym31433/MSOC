/*****************************************************************************

The following code is derived, directly or indirectly, from the SystemC
source code Copyright (c) 1996-2006 by all Contributors.
All Rights reserved.

The contents of this file are subject to the restrictions and limitations
set forth in the SystemC Open Source License Version 2.4 (the "License");
You may not use this file except in compliance with such restrictions and
limitations. You may obtain instructions on how to receive a copy of the
License at http://www.systemc.org/. Software distributed by Contributors
under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
ANY KIND, either express or implied. See the License for the specific
language governing rights and limitations under the License.

*****************************************************************************/

/*****************************************************************************

simple_bus_master_blocking.h : The master using the blocking BUS interface.

Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11

*****************************************************************************/

/*****************************************************************************

MODIFICATION LOG - modifiers, enter your name, affiliation, date and
changes you are making here.

Name, Affiliation, Date:
Description of Modification:

*****************************************************************************/

#ifndef __simple_bus_master_blocking_h
#define __simple_bus_master_blocking_h

#include <systemc.h>

#include "simple_bus_types.h"
#include "simple_bus_blocking_if.h"
#include "Mem_if.h"
#include <iostream>
using namespace std;

class simple_bus_master_blocking
    : public Mem_if
    , public sc_module
{
public:
    // ports
    //sc_in_clk clock;
    sc_port<simple_bus_blocking_if> bus_port;

    //SC_HAS_PROCESS(simple_bus_master_blocking);

    // constructor
    simple_bus_master_blocking(sc_module_name name_
        , unsigned int unique_priority
        , unsigned int address
        , bool lock
        , int timeout
        , unsigned w)
        : sc_module(name_)
        , m_unique_priority(unique_priority)
        , m_address(address)
        , m_lock(lock)
        , m_timeout(timeout)
        , m_width(w)
    {
/*        // process declaration
        SC_THREAD(main_action);
        sensitive << clock.pos();
*/
    }
    ~simple_bus_master_blocking() {}

    // process
//    void main_action();
    void word_write(unsigned addrY, unsigned addrX, int data);
    void word_read(unsigned addrY, unsigned addrX, int& data);
    

private:
    unsigned int m_unique_priority;
    unsigned int m_address;
    bool m_lock;
    int m_timeout;
    unsigned m_width;
}; // end class simple_bus_master_blocking

inline void simple_bus_master_blocking::word_read(unsigned addrY, unsigned addrX, int& data) {
    simple_bus_status status;
    unsigned a = (addrY*m_width+addrX)*4;
//cout << "read address: " << a << endl;
    status = bus_port->burst_read(m_unique_priority, &data, a, 1, m_lock);
    if (status == SIMPLE_BUS_ERROR)
            sb_fprintf(stdout, "%g %s : blocking-read failed at address %x\n", sc_time_stamp().to_double(), name(), m_address);
}
inline void simple_bus_master_blocking::word_write(unsigned addrY, unsigned addrX, int data) {
    simple_bus_status status;
    unsigned a = (addrY*m_width+addrX)*4;
    status = bus_port->burst_write(m_unique_priority, &data, a, 1, m_lock);
//cout << "write address: " << a << endl;
    if (status == SIMPLE_BUS_ERROR)
            sb_fprintf(stdout, "%g %s : blocking-write failed at address %x\n", 
            sc_time_stamp().to_double(), name(), m_address);
}

#endif
