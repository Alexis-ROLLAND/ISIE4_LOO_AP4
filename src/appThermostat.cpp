/**
 *	@file		appThermostat.cpp
 * 	@brief 		appThermostat definition file
 * 	@author		Alexis ROLLAND
 * 	@date		11/2025
 *
 */

#include "appThermostat.hpp"
//----------------------------------------------------------------------
void ThermostatApp::addTemp(float temp) {

    std::scoped_lock<std::mutex> lock{
        this->arrayMutex}; /**< Lock the mutex to protect access to the temperature array */

    uint8_t newPtr = this->getptr();

    if (newPtr >= (filterSize - 1))
        newPtr = 0;
    else
        newPtr++;
    this->setptr(newPtr);

    this->tabTemp.at(newPtr) = temp;
    /** Note : no need to unlock the mutex explicitly, scoped_lock will handle it (RAII object) */
}
//----------------------------------------------------------------------
float ThermostatApp::getTemp() {
    std::scoped_lock<std::mutex> lock{
        this->arrayMutex}; /**< Lock the mutex to protect access to the temperature array */
    return (std::accumulate(this->tabTemp.begin(), this->tabTemp.end(), 0) / filterSize);
    /** Note : no need to unlock the mutex explicitly, scoped_lock will handle it (RAII object) */
}
//----------------------------------------------------------------------
void ThermostatApp::_measureThread() {
    while (true) {
        this->addTemp(this->Capteur.getTemp());
        std::this_thread::sleep_for(measure_delay);
    }
}
//----------------------------------------------------------------------
void ThermostatApp::_processingThread() {
    float actualTemp;
    while (true) {
        std::this_thread::sleep_for(process_delay);
        actualTemp = this->getTemp();

        std::println(
            std::clog, "Actual temperature = {0:0.1f}°C. Setpoint is {1:0.1f}.", actualTemp, this->getConsigne());

        if (actualTemp > (this->getConsigne() + this->getHysteresis())) {
            try {
                this->_pChaudiere->setOFF();
            } catch (const std::exception &e) {
                std::println(std::clog, "Chaudiere already OFF.");
            }

        } else if (actualTemp < (this->getConsigne() - this->getHysteresis())) {
            try {
                this->_pChaudiere->setON();
            } catch (const std::exception &e) {
                std::println(std::clog, "Chaudiere already ON.");
            }
        } else {
            std::println(std::clog, "No action required...");
        }
    }
}
//----------------------------------------------------------------------
void ThermostatApp::Init() {
    if (this->_pChaudiere == nullptr) throw NoBoilerException{}; /** Check if the boiler pointer is valid */
    this->measureThread = std::jthread(&ThermostatApp::_measureThread, this); /** Create and start the measure thread */
    this->processingThread =
        std::jthread(&ThermostatApp::_processingThread, this); /** Create and start the processing thread */
}
//----------------------------------------------------------------------
void ThermostatApp::Run() { /**<	 Nothing to do in the main task	*/ }
//----------------------------------------------------------------------
//----------------------------------------------------------------------
