
//BEGIN: interchange.cpp (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See hier_chan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SC_USE_SC_STRING_OLD
#include <systemc.h>
#include "interchange.h"

void interchange::interchange_thread() {
    done->write(false);
    //cout << "INFO: "<< name() << " @ " << sc_time_stamp() << " Starting..." << endl;
    long** temp = new long*[m_width];
    for(int i = 0; i != m_width; ++i) {
        temp[i] = new long[m_width];
    }
    for(int i = 0; i != m_width; ++i) {
        for(int j = 0; j != m_width; ++j) {
            temp[j][i] = mem->read(i, j);
        }
    }
    cout << "INFO: Complete Memory read." << endl;
    for(int i = 0; i != m_width; ++i) {
        for(int j = 0; j != m_width; ++j) {
            mem->write(i, j, temp[i][j]);
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