
#ifndef MEM_IF_H
#define MEM_IF_H
//BEGIN: Mem_if.h (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See hier_chan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

struct Mem_if: public sc_interface {
    virtual void direct_write(int** block)=0;
    virtual void direct_read(int** block)=0;
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: CPU_if.h,v 1.2 2004/04/15 17:40:18 dcblack Exp $
