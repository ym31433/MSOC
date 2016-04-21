
#ifndef MEM_RTL_H
#define MEM_RTL_H
//BEGIN: memory.h (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See hier_chan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


SC_MODULE(memory) {
    sc_in_clk                ck; // clock
    sc_in<bool>              ld; // load/execute command
    sc_in<bool>              rw; // read high/write low
    sc_in<unsigned>          x;  // address
    sc_in<unsigned>          y;
    sc_inout_rv<32>          d;  // data
    SC_HAS_PROCESS(memory);
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
        SC_THREAD(mem_thread);
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
    // Processes
    void mem_thread();
    sc_signal<bool> err; // for debug
private:
    // Local data
    unsigned      m_width;
    int**         m_mem;
    // Disabled methods
    memory(const memory&);
};
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: mem_bsyn.h,v 1.2 2004/04/15 17:40:48 dcblack Exp $
