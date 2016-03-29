//BEGIN main.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See pcix.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <iostream>
using std::cout;
using std::endl;

#include <systemc.h>
#include "pcix.h"

unsigned errors = 0;
char* simulation_name = "pcix";

int sc_main(int argc, char* argv[]) {
    cout << "INFO: Elaborating "<< simulation_name << endl;
    //sc_set_time_resolution(1,SC_PS);
    //sc_set_default_time_unit(1,SC_NS);
    pcix pcix_i("pcix_i");
    cout << "INFO: Simulating "<< simulation_name << endl;
    sc_start();
    cout << "INFO: Post-processing "<< simulation_name << endl;
    cout << "INFO: Simulation " << simulation_name
        << " " << (errors?"FAILED":"PASSED")
        << " with " << errors << " errors"
        << endl;
    return errors?1:0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: main.cpp,v 1.1 2004/02/12 12:27:50 dcblack Exp $
