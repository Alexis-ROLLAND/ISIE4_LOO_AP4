/**
 *	@file		appThermostat_main.cpp
 * 	@brief 		main for the Thermostat App
 * 	@author
 * 	@date		11/2025
 *
 */
#include <memory>
#include <print>

#include "Chaudiere.hpp"

#include "appThermostat.hpp"

#include <cassert>

#define TEST_CHAUDIERE
//  #define TEST_DUMMY_CAPTEUR_TEMP
//  #define TEST_NETWORK_CAPTEUR_TEMP
// #define APPLICATION

//----------------------------------------------------------------------------
//--------------------- Unit test : Chaudiere	------------------------------
#ifdef TEST_CHAUDIERE
int main() { return 0; }
#endif
//----------------------------------------------------------------------------
//--------------------- Unit test : DummyCapteurTemp	----------------------
#ifdef TEST_DUMMY_CAPTEUR_TEMP
int main() { return 0; }
#endif /* 	TEST_DUMMY_CAPTEUR_TEMP 	*/

//----------------------------------------------------------------------------
//--------------------- Unit test : NetworkCapteurTemp	----------------------
#ifdef TEST_NETWORK_CAPTEUR_TEMP

/**
 * To test this unit test, you can use the following command to send UDP packets to the server:
 * echo -n "215" | nc -4u -w1 localhost 6666
 * or nc -u localhost 6666 and then type the value followed by Enter - CTRL+C to stop
 */

int main() { return 0; }
#endif /* 	TEST_NETWORK_CAPTEUR_TEMP 	*/

//----------------------------------------------------------------------------
//--------------------------- Application ------------------------------------
#ifdef APPLICATION
int main() { return 0; }
#endif /* APPLICATION 	*/
//----------------------------------------------------------------------------
