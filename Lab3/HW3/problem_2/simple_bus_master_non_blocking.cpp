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

simple_bus_master_non_blocking.cpp : The master using the non-blocking BUS
interface.

Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11

*****************************************************************************/

/*****************************************************************************

MODIFICATION LOG - modifiers, enter your name, affiliation, date and
changes you are making here.

Name, Affiliation, Date:
Description of Modification:

*****************************************************************************/

#include "simple_bus_master_non_blocking.h"
#include <iostream>
using namespace std;

void simple_bus_master_non_blocking::main_action()
{
    unsigned          addr;
    int               data;
//    wait(); // ... for the next rising clock edge
    while (true) {
        while (ld->read() == false) {
            d->write(sc_lv<32>(SC_LOGIC_Z));
            wait(ld->value_changed_event()); // wait here improves efficiency
        };
        addr = (x->read()+(y->read()*m_width))*4;
        

        if(rw->read()) { //read
            bus_port->read(m_unique_priority, &data, addr, m_lock);
            while ((bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK) && (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR))
                wait();
            if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR) 
                sb_fprintf(stdout, "%g %s : ERROR cannot read from %x\n", sc_time_stamp().to_double(), name(), addr);
//cout << "master writing data" << data << " @ " << sc_time_stamp() << endl;
            d->write(data);
        }
        else { //write
            data = d->read().to_int();
//cout << "data: " << data << endl;
            bus_port->write(m_unique_priority, &data, addr, m_lock);
            while ((bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK) && (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR))
                wait();
            if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR)
                sb_fprintf(stdout, "%g %s : ERROR cannot write to %x\n", sc_time_stamp().to_double(), name(), addr);
        }
//        wait(m_timeout, SC_NS);
        wait(); // ... for the next falling clock edge
        //wait();
        //wait();
    }
}

