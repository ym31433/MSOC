
#ifndef MEMORY_H
#define MEMORY_H
//BEGIN: memory.h (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See hier_chan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Mem_if.h"
#include <iostream>
using namespace std;

extern unsigned errors;

struct memory: public sc_channel, Mem_if {
    // Constructors & destructor
    explicit memory(sc_module_name nm,
        unsigned w) 
        : sc_channel(nm), m_width(w)
    {
        int data;
        srand(0);
        m_mem = new int*[m_width];
        for(int i = 0; i != m_width; ++i) {
            m_mem[i] = new int[m_width];
        }
        cout << "-----Original data in Memory:" << endl; 
        for(int i = m_width-1; i >= 0; --i) {
            cout << "[ ";
            for(int j = 0; j != m_width; ++j) {
                data = rand();
                m_mem[i][j] = data;
                cout << data << " ";
            }
            cout << "]" << endl;
        }
    }
    ~memory() {
        cout << "-----New data in Memory:" << endl; 
        for(int i = m_width-1; i >= 0; --i) {
            cout << "[ ";
            for(int j = 0; j != m_width; ++j) {
                cout << m_mem[i][j] << " ";
            }
            cout << "]" << endl;
        }
        for(int i = 0; i != m_width; ++i) {
            delete [] m_mem[i];
        }
        delete [] m_mem;
    }
    // Interface implementations
    void direct_write(int** block) {
        for(int i = 0; i != m_width; ++i) {
            for(int j = 0; j != m_width; ++j) {
                m_mem[i][j] = block[i][j];
            }
        }
    }
    void direct_read(int** block) {
        for(int i = 0; i != m_width; ++i) {
            for(int j = 0; j != m_width; ++j) {
                block[i][j] = m_mem[i][j];
            }
        }
    }
private:
    unsigned      m_base;
    unsigned      m_width;
    int**        m_mem;
    memory(const memory&); // Disable
};
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: mem_arch.h,v 1.3 2004/05/05 19:46:22 dcblack Exp $
