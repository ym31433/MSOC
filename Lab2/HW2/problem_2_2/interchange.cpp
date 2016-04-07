
//BEGIN: interchange.cpp (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See hier_chan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SC_USE_SC_STRING_OLD
#include <systemc.h>
#include "interchange.h"

#include <iostream>
using namespace std;

enum operation {WRITE=false, READ=true};

void interchange::interchange_thread() {
    done->write(false);
    //cout << "INFO: "<< name() << " @ " << sc_time_stamp() << " Starting..." << endl;
    int** temp = new int*[m_width];
    for(int i = 0; i != m_width; ++i) {
        temp[i] = new int[m_width];
    }
    for(int i = 0; i != m_width; ++i) {
        for(int j = 0; j != m_width; ++j) {
            cout << "INFO: " << name() << "::read starting @ " << sc_time_stamp() << " Addr (" << i << ", " << j << ")" << endl;
            wait(ck->posedge_event());
            ld->write(true);
            rw->write(READ);
            x->write(j);
            y->write(i);
            d->write(sc_lv<32>(SC_LOGIC_Z));
            wait(ck->posedge_event());
            ld->write(false);
            temp[j][i] = d->read().to_int();
        }
    }
    cout << "INFO: Complete Memory read." << endl;
    for(int i = 0; i != m_width; ++i) {
        for(int j = 0; j != m_width; ++j) {
            cout << "INFO: " << name() << "::write starting @ " << sc_time_stamp() << " Addr (" << i << ", " << j << ")" << endl;
            wait(ck->posedge_event());
            ld->write(true);
            rw->write(WRITE);
            x->write(j);
            y->write(i);
            d->write(temp[i][j]);
//cout << "temp[" << i << "][" << j << "]=" << temp[i][j] << endl;
            wait(ck->posedge_event());
            ld->write(false);
            d->write(sc_lv<32>(SC_LOGIC_Z));
        }
    }
    cout << "INFO: Complete Memory write." << endl;
    //cout << "INFO: "<< name() << " @ " << sc_time_stamp() << " Finished!" << endl;
    for(int i = 0; i != m_width; ++i) {
        delete [] temp[i];
    }
    delete [] temp;
    done->write(true);
}//end testbench::test_thread()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: testbench.cpp,v 1.2 2004/05/05 19:46:22 dcblack Exp $
