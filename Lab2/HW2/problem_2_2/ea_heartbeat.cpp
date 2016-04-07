//BEGIN ea_heartbeat.cpp (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See ea_heartbeat.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SC_USE_SC_STRING_OLD
#include <systemc.h>
#include "ea_heartbeat.h"

void ea_heartbeat::heartbeat_method(void) {
    m_heartbeat.notify(m_period);
}//end ea_heartbeat::heartbeat_method()
void ea_heartbeat::heartbeat_neg_method(void) {
    m_heartbeat_neg.notify(m_period/2);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: ea_heartbeat.cpp,v 1.1 2004/03/03 03:18:36 dcblack Exp $
