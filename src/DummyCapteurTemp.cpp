/**
 *	@file	DummyCapteurTemp.cpp
 * 	@brief 	Definition file for the DummyCapteurTemp concrete class
 *          (based on CapteurTemp interface)
 * 	@author	Alexis ROLLAND
 * 	@date	09/2024
 *
 */
#include "DummyCapteurTemp.hpp"

float DummyCapteurTemp::getTemp() const noexcept {

    float temp{0};

    std::random_device rdev{};
    this->generator.seed(rdev());

    std::uniform_int_distribution<int16_t> distrib{
        this->getTmin(), this->getTmax()}; /** Construction du "vrai générateur" de nombres aléatoires pour des entiers
                                              entre Tmin et Tmax */

    int16_t rndValue{0};
    uint16_t Ecart{0};

    do {
        rndValue = distrib(this->generator);
        Ecart = std::abs(rndValue - this->getprevTemp());
    } while (Ecart > this->getDeltaMax());

    this->setprevTemp(rndValue);
    temp = static_cast<float>(rndValue) / 10.0;

    return temp;
}

//----------------------------------------------------------------------------