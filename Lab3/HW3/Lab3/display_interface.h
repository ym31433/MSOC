#ifndef __display_interface_h
#define __display_interface_h

#include <systemc.h>

#include "simple_bus_types.h"
#include "simple_bus_slave_if.h"

class display_interface
    : public simple_bus_slave_if
    , public sc_module
{
public:
    // constructor
    display_interface(sc_module_name name_
        , unsigned int start_address
        , unsigned int end_address)
        : sc_module(name_)
        , m_start_address(start_address)
        , m_end_address(end_address)
    {
        sc_assert(m_start_address <= m_end_address);
        sc_assert((m_end_address-m_start_address+1)%4 == 0);
        idx = 0;
    }

    // direct Slave Interface
    bool direct_read(int *data, unsigned int address);
    bool direct_write(int *data, unsigned int address);

    // Slave Interface
    simple_bus_status read(int *data, unsigned int address);
    simple_bus_status write(int *data, unsigned int address);

    unsigned int start_address() const;
    unsigned int end_address() const;

private:
    FILE *ImagePtr;
    unsigned char  MEM[512*512];
    int idx;
    unsigned int m_start_address;
    unsigned int m_end_address;

}; // end class simple_bus_fast_mem

inline bool display_interface::direct_read(int *data, unsigned int address)
{
    return (read(data, address) == SIMPLE_BUS_OK);
}

inline bool display_interface::direct_write(int *data, unsigned int address)
{
    return (write(data, address) == SIMPLE_BUS_OK);
}

inline simple_bus_status display_interface::read(int *data
    , unsigned int address)
{
    *data = MEM[(address - m_start_address)/4];
    return SIMPLE_BUS_OK;
}

inline simple_bus_status display_interface::write(int *data
    , unsigned int address)
{
    MEM[idx] = (unsigned char)(*data);
    idx++;
    if(idx == 262144) {
        ImagePtr=fopen("EdgeDetect.raw","wb");
        fwrite(MEM, 1, 512*512, ImagePtr);
        fclose(ImagePtr);
        idx = 0;
    }
    return SIMPLE_BUS_OK;
}

inline unsigned int display_interface::start_address() const
{
    return m_start_address;
}

inline unsigned int display_interface::end_address() const
{
    return m_end_address;
}

#endif