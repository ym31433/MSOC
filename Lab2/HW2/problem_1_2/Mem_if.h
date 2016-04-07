
#ifndef MEM_IF_H
#define MEM_IF_H
//BEGIN: Mem_if.h (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See hier_chan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

struct Mem_if: public sc_interface {
    virtual void word_write(unsigned addrY, unsigned addrX, int data)=0;
    virtual int word_read(unsigned addrY, unsigned addrX)=0;
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: CPU_if.h,v 1.2 2004/04/15 17:40:18 dcblack Exp $
