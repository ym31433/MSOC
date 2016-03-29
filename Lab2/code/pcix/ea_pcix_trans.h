#ifndef EA_PCIX_TRANS_H
#define EA_PCIX_TRANS_H
//BEGIN ea_pcix_trans.h (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <string>
using std::string;
// This defines a PCIX transaction packet
struct ea_pcix_trans {

    int  devnum;
    int  addr;
    int  attr1;
    int  attr2; 
    int  cmnd;
    int  data[8];
    bool done;

    // Constructors
    ea_pcix_trans()
        : devnum(-1) , addr(-1)   
        , cmnd(-1)   , attr1(-1)  
        , attr2(-1)  , done(false)
    {
        for (unsigned i=0;i!=8;i++) {
            data[i] = 0;
        }//endfor
    }
    ea_pcix_trans(
        int _devnum, int  _addr, 
        int _attr1,  int  _attr2,
        int _cmnd,   int* _data,
        int _done
        )
        : devnum(_devnum) , addr(_addr)  
        , cmnd(_cmnd)     , attr1(_attr1)
        , attr2(_attr2)   , done(_done)  
    {
        for (unsigned i=0;i!=8;i++) {
            data[i] = _data[i];
        }//endfor
    }

    // Required by sc_signal<> and sc_fifo<>
    ea_pcix_trans& operator= (const ea_pcix_trans& rhs) {
        devnum = rhs.devnum;
        addr   = rhs.addr;
        attr1  = rhs.attr1;
        attr2  = rhs.attr2;
        cmnd   = rhs.cmnd;
        for (unsigned i=0; i!=8; i++) {
            data[i] = rhs.data[i];
        }//endfor
        done   = rhs.done;
        return *this;
    }//end operator=

    // Required by sc_signal<>
    bool operator== (const ea_pcix_trans& rhs) const {
        return (
            devnum  == rhs.devnum  &&
            addr    == rhs.addr    &&
            attr1   == rhs.attr1   &&
            attr2   == rhs.attr2   &&
            cmnd    == rhs.cmnd    &&
            data[0] == rhs.data[0] &&
            data[1] == rhs.data[1] &&
            data[2] == rhs.data[2] &&
            data[3] == rhs.data[3] &&
            data[4] == rhs.data[4] &&
            data[5] == rhs.data[5] &&
            data[6] == rhs.data[6] &&
            data[7] == rhs.data[7] &&
            done    == rhs.done
            );
    }//end operator==

};

// Required functions by SystemC
//
// Stream operator to output a PCIX transaction packet to terminal
ostream& operator<<(ostream& file, const ea_pcix_trans& trans);

// Trace a PCIX transaction packet in case it is used in an sc_signal
void sc_trace(sc_trace_file*& tf, const ea_pcix_trans& trans, string nm);

#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: ea_pcix_trans.h,v 1.2 2004/04/15 17:42:53 dcblack Exp $
