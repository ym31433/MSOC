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
#include "mem2pca.h"
#include "memory.h"
#include "ea_heartbeat.h"

SC_MODULE(hier_chan) {
    // Pin-level model instances
    interchange               interchange_i;
    memory                    memory_i;
    // Pin-level model channels
    mem2pca                   mem2pca_i; // hierarchical transactor
    sc_signal<bool>           ld;
    sc_signal<bool>           rw;
    sc_signal<unsigned>       x;
    sc_signal<unsigned>       y;
    sc_signal_rv<32>          d;
    sc_signal<bool>           done;
    ea_heartbeat              clock;
    SC_CTOR(hier_chan) 
        : interchange_i("interchange_i",8)    
        , mem2pca_i("mem2pca_i")
        , memory_i("memory_i",8)
        , clock("clock",sc_time(2,SC_NS))
    {
        SC_METHOD(done_method);
        sensitive << done;
        dont_initialize();
        // Pin-level model connectivity
        mem2pca_i.mem(memory_i);
        interchange_i.done(done);
        mem2pca_i.ld(ld);
        mem2pca_i.rw(rw);
        mem2pca_i.x(x);
        mem2pca_i.y(y);
        mem2pca_i.d(d);
        mem2pca_i.ck(clock);
        interchange_i.ld(ld);
        interchange_i.rw(rw);
        interchange_i.x(x);
        interchange_i.y(y);
        interchange_i.d(d);
        interchange_i.ck(clock);
    }
    // This method waits for both tests to complete and then terminates SystemC
    void done_method() {
        if (done.read()) sc_stop();
    }
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: hier_chan.h,v 1.3 2004/05/05 19:46:21 dcblack Exp $
