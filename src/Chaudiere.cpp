/**
 *	@file		Chaudiere.cpp
 * 	@brief 		Definition file for (concrete) Boiler
 * 	@author		Alexis ROLLAND
 * 	@date		11/2025
 *
 */
#include "Chaudiere.hpp"

//----------------------------------------------------------------------
void DummyChaudiere::setON() {
    if (this->getStatus() == Status::OFF) {
        this->setStatus(Status::ON);
        std::println(std::clog, "Chaudière ON");
    } else {
        throw BoilerAlreadyONexception{};
    }
}
//----------------------------------------------------------------------
void DummyChaudiere::setOFF() {
    if (this->getStatus() == Status::ON) {
        this->setStatus(Status::OFF);
        std::println(std::clog, "Chaudière OFF");
    } else {
        throw BoilerAlreadyOFFexception{};
    }
}
//----------------------------------------------------------------------
