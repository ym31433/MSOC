#include <systemc.h>

#include "simple_bus.h"
#include "simple_bus_arbiter.h"
#include "edge_detect.h"
#include "frame_buffer.h"
#include "display_interface.h"
int sc_main(int, char **)
{
    /*-	Signal Declaration	-*/
    sc_clock C1;

    /*-	Instantiation	-*/
    simple_bus          iBus("iBus");
    simple_bus_arbiter	iArbiter("iArbiter");
    edge_detect	        iEdge_detect("iEdge_detect",true,512,512);
    frame_buffer        iFrame_buffer("iFrame_buffer",0x00000,0xfffff);
    display_interface   iDisplay_interface("iDisplay_interface",0x100000,0x100003);


    /*-	Net Connection	-*/
    iBus.clock(C1);
    iBus.arbiter_port(iArbiter);
    iBus.slave_port(iFrame_buffer);
    iBus.slave_port(iDisplay_interface);
    iEdge_detect.clock(C1);
    iEdge_detect.bus_port(iBus);


    sc_start(10000, SC_NS);

    return 0;
}
