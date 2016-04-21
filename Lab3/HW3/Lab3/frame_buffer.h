#ifndef __frame_buffer_h
#define __frame_buffer_h

#include <systemc.h>

#include "simple_bus_types.h"
#include "simple_bus_slave_if.h"


class frame_buffer
    : public simple_bus_slave_if
    , public sc_module
{
public:
    // constructor
    frame_buffer(sc_module_name name_
        , unsigned int start_address
        , unsigned int end_address)
        : sc_module(name_)
        , m_start_address(start_address)
        , m_end_address(end_address)
    {
        sc_assert(m_start_address <= m_end_address);
        sc_assert((m_end_address-m_start_address+1)%4 == 0);
        unsigned int size = (m_end_address-m_start_address+1)/4;
        ImagePtr= fopen("LenaY.raw","rb");
        MEM = new unsigned char [size];
        fread(MEM, 1, size, ImagePtr);
        fclose(ImagePtr);
    }

    // destructor
    ~frame_buffer();

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
    unsigned char *MEM;
    unsigned int m_start_address;
    unsigned int m_end_address;

}; // end class simple_bus_fast_mem

inline bool frame_buffer::direct_read(int *data, unsigned int address)
{
    return (read(data, address) == SIMPLE_BUS_OK);
}

inline bool frame_buffer::direct_write(int *data, unsigned int address)
{
    return (write(data, address) == SIMPLE_BUS_OK);
}

inline simple_bus_status frame_buffer::read(int *data
    , unsigned int address)
{
    // *** complete the behavior of read ***
    *data = (int)MEM[(address-m_start_address)/4];
    return SIMPLE_BUS_OK;
}

inline simple_bus_status frame_buffer::write(int *data
    , unsigned int address)
{
    // *** complete the behavior of write ***
    MEM[(address-m_start_address)/4] = (unsigned char)*data;
    return SIMPLE_BUS_OK;
}

inline  frame_buffer::~frame_buffer()
{
    delete [] MEM;
}

inline unsigned int frame_buffer::start_address() const
{
    return m_start_address;
}

inline unsigned int frame_buffer::end_address() const
{
    return m_end_address;
}

#endif
