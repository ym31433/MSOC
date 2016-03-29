//BEGIN ea_pcix_trans.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <systemc.h>
#include "ea_pcix_trans.h"

#include <string>
using std::string;

// Print a PCIX transaction packet out to a stream (usually just the terminal
// window), in a nice-looking format
ostream& operator<<(ostream& os, const ea_pcix_trans& trans) {
    os << "{" << endl
        << "  cmnd: " << trans.cmnd   << ", "
        << "attr1:" << trans.attr1  << ", "
        << "attr2:" << trans.attr2  << "," << endl
        << "  devnum:"<< trans.devnum << ", "
        << "addr:"  << trans.addr   << "," << endl
        << "  data: " << trans.data[0] << "." << trans.data[1] << "." << trans.data[2] << "." << trans.data[3]
    <<      "." << trans.data[4] << "." << trans.data[5] << "." << trans.data[6] << "." << trans.data[7]
    << "," << endl
        << "  done:"  << (trans.done?"true":"false")  << endl
        << "}";                       
    return os;
}//end operator<<

// trace function, only required if actually used
void sc_trace(sc_trace_file*& tf, const ea_pcix_trans& trans, std::string nm) {
    sc_trace(tf, trans.devnum,   nm + ".devnum");
    sc_trace(tf, trans.addr,     nm + ".addr");
    sc_trace(tf, trans.attr1,    nm + ".attr1");
    sc_trace(tf, trans.attr2,    nm + ".attr2");
    sc_trace(tf, trans.cmnd,     nm + ".cmnd");
    sc_trace(tf, trans.data[0],  nm + ".data[0]");
    sc_trace(tf, trans.data[1],  nm + ".data[1]");
    sc_trace(tf, trans.data[2],  nm + ".data[2]");
    sc_trace(tf, trans.data[3],  nm + ".data[3]");
    sc_trace(tf, trans.data[4],  nm + ".data[4]");
    sc_trace(tf, trans.data[5],  nm + ".data[5]");
    sc_trace(tf, trans.data[6],  nm + ".data[6]");
    sc_trace(tf, trans.data[7],  nm + ".data[7]");
    sc_trace(tf, trans.done,     nm + ".done");
}//end sc_trace

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: ea_pcix_trans.cpp,v 1.1 2004/02/12 12:27:50 dcblack Exp $
