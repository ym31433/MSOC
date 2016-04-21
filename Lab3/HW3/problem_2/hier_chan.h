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
#include "simple_bus_master_non_blocking.h"
#include "simple_bus_fast_mem.h"
#include "simple_bus_arbiter.h"
#include "simple_bus.h"

SC_MODULE(hier_chan) {
    // Pin-level model instances
    interchange                     interchange_i;
    memory                          memory_i;
    simple_bus_master_non_blocking  master_nb;
    simple_bus                      bus;
    simple_bus_fast_mem             mem_fast;
    simple_bus_arbiter              arbiter;
    // Pin-level model channels
    sc_signal<bool>           ld_m, ld_s;
    sc_signal<bool>           rw_m, rw_s;
    sc_signal<unsigned>       x_m, x_s;
    sc_signal<unsigned>       y_m, y_s;
    sc_signal_rv<32>          d_m, d_s;
    sc_signal<bool>           done;
    sc_clock                  clock;
    SC_CTOR(hier_chan) 
        : interchange_i("interchange_i",8)    
        , memory_i("memory_i",8)
        , master_nb("master_nb", 4, 0x4c, false, 300, 8)
        , bus("bus")
        , mem_fast("mem_fast", 0x00, 0xff, 8)
        , arbiter("arbiter")
        , clock("clock",sc_time(2,SC_NS))
    {
        SC_METHOD(done_method);
        sensitive << done;
        dont_initialize();
        // Pin-level model connectivity
        interchange_i.done(done);
        memory_i.ld(ld_s);
        memory_i.rw(rw_s);
        memory_i.x(x_s);
        memory_i.y(y_s);
        memory_i.d(d_s);
        memory_i.ck(clock);
        interchange_i.ld(ld_m);
        interchange_i.rw(rw_m);
        interchange_i.x(x_m);
        interchange_i.y(y_m);
        interchange_i.d(d_m);
        interchange_i.ck(clock);

        master_nb.clock(clock);
        master_nb.bus_port(bus);
        master_nb.ld(ld_m);
        master_nb.rw(rw_m);
        master_nb.x(x_m);
        master_nb.y(y_m);
        master_nb.d(d_m);
        bus.clock(clock);
        bus.arbiter_port(arbiter);
        bus.slave_port(mem_fast);
        mem_fast.ck(clock);
        mem_fast.ld(ld_s);
        mem_fast.rw(rw_s);
        mem_fast.x(x_s);
        mem_fast.y(y_s);
        mem_fast.d(d_s);
    }
    // This method waits for both tests to complete and then terminates SystemC
    void done_method() {
        if (done.read()) sc_stop();
    }
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: hier_chan.h,v 1.3 2004/05/05 19:46:21 dcblack Exp $
