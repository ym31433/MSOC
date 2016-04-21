#ifndef HIER_CHAN_H
#define HIER_CHAN_H
//BEGIN hier_chan.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   This design contains two examples of custom hierarchical channels.
//   First, mem_arch is a architectural model of a memory using the
//   custom CPU_if interface. Second, cpu2pca is a transactor that
//   adapts the CPU_if to a pin-cycle-accurate interface using signals.
//   mem_bsyn is a pin-cycle accurate behavioral model that may be
//   synthesizable.
//
//   To simplify understanding, we've put two sets of simulations in the
//   same model, one architectural and one with pin-level behavior. As
//   detour, the ea_heartbeat model is used for a clock.
//
//   Notice that the memories and testbench are instantiated with
//   parameters that affect their configuration.
//
// DESIGN HIERARCHY
//   sc_main()
//   +- hier_chan_i
//      +- testbench_arch_i
//      |     v
//      +- mem_arch_i (hierarchical channel)
//      |
//      +- testbench_bsyn_i
//      |     v
//      |  cpu2pca_i (transactor)
//      |     v
//      +- mem_bsyn_i
//      +- clock
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>
#include "interchange.h"
#include "memory.h"
#include "simple_bus.h"
#include "simple_bus_master_blocking.h"
#include "simple_bus_fast_mem.h"
#include "simple_bus_arbiter.h"

SC_MODULE(hier_chan) {
    sc_clock                    clk;
    // Architectural model instances
    interchange               interchange_i;
    // Architectural model channels
    memory                    memory_i; // hierarchical channel
    //bus
    simple_bus_master_blocking  master_b;
    simple_bus                  bus;
    simple_bus_fast_mem         mem_fast;
    simple_bus_arbiter          arbiter;

    sc_signal<bool>           done;
    SC_CTOR(hier_chan) 
        : interchange_i("interchange_i",8)
        , memory_i("memory_i",8)
        , master_b("master_b", 4, 0x4c, false, 300, 8)
        , mem_fast("mem_fast", 0x00, 0xff, 8) //not sure the size of the mem_fast yet
        , bus("bus")
        , arbiter("arbiter")
    {
        SC_METHOD(done_method);
        sensitive << done;
        dont_initialize();
        // Architectural model connectivity
        interchange_i.master(master_b);
        interchange_i.done(done);
        master_b.bus_port(bus);
        bus.clock(clk);
        bus.arbiter_port(arbiter);
        bus.slave_port(mem_fast);
        mem_fast.mem(memory_i);
    }
    // This method waits for both tests to complete and then terminates SystemC
    void done_method() {
        if (done.read()) sc_stop();
    }
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: hier_chan.h,v 1.3 2004/05/05 19:46:21 dcblack Exp $
