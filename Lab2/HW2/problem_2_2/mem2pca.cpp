
//BEGIN: mem2pca.h (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See hier_chan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SC_USE_SC_STRING_OLD
#include <systemc.h>
#include "mem2pca.h"

#include <iostream>
using namespace std;

void mem2pca::mem2pca_thread() {
    unsigned addrX, addrY;
    for(;;) {
        while(ld->read() == false) {
            d->write(sc_lv<32>(SC_LOGIC_Z));
            wait(ld->value_changed_event());
        };
        addrX = x->read();
        addrY = y->read();
        int data;
        if(rw->read()) {
            mem->read(addrY, addrX, data);
            d->write(data);
            wait(ck->negedge_event());
        }
        else {
            data = d->read().to_int();
//cout << "mem2pca data: " << data << endl;
            mem->write(addrY, addrX, data);
            wait(ck->negedge_event());
        }
    }
}
/*
void mem2pca::write(unsigned addrY, unsigned addrX, int data) {
    cout << "INFO: " << name() << "::write starting @ " << sc_time_stamp() << " Addr (" << addrY << ", " << addrX << ")" << endl;
    wait(ck->posedge_event());
    ld->write(true);
    rw->write(WRITE);
    x->write(addrX);
    y->write(addrY);
    d->write(data);
    wait(ck->posedge_event());
    ld->write(false);
    d->write(sc_lv<32>(SC_LOGIC_Z));
}

void mem2pca::read(unsigned addrY, unsigned addrX, int& data) {
    cout << "INFO: " << name() << "::read starting @ " << sc_time_stamp() << " Addr (" << addrY << ", " << addrX << ")" << endl;
    wait(ck->posedge_event());
    ld->write(true);
    rw->write(READ);
    x->write(addrX);
    y->write(addrY);
    d->write(sc_lv<32>(SC_LOGIC_Z));
    wait(ck->posedge_event());
    ld->write(false);
    data = d->read().to_int();
}
*/
/*
void cpu2pca::burst_write(unsigned long addr, unsigned size, long* data) {
    for (unsigned i=0; i!=size; i++) {
        wait(ck->posedge_event());
        ld->write(true);
        rw->write(WRITE);
        a->write(addr++);
        d->write(data[i]);
    }//endfor i
    wait(ck->posedge_event());
    ld->write(false);
}

void cpu2pca::burst_read(unsigned long addr, unsigned size, long* data) {
    wait(ck->posedge_event());
    ld->write(true);
    rw->write(READ);
    a->write(addr++);
    for (unsigned i=0; i!=size; i++) {
        wait(ck->posedge_event());
        ld->write(i!=(size-1));
        a->write(addr++);
        data[i] = d->read().to_long();
    }//endfor i
    wait(ck->posedge_event());
}
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: cpu2pca.cpp,v 1.1 2004/03/03 03:18:36 dcblack Exp $
