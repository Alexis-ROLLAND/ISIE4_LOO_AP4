/**
 *	@file	DummyCapteurTemp.hpp
 * 	@brief 	Header file for the DummyCapteurTemp concrete class
 *          (based on CapteurTemp interface)
 * 	@author	Alexis ROLLAND
 * 	@date	11/2025
 *
 */

#ifndef __DUMMY_CAPTEUR_TEMP_H__
#define __DUMMY_CAPTEUR_TEMP_H__

#include <random>

#include "CapteurTemp.hpp"

constexpr int16_t defaultTmin{-200};      /**<	Default min temperature - in 1/10°C			*/
constexpr int16_t defaultTmax{+700};      /**<	Default max temperature - in 1/10°C			*/
constexpr uint16_t defaultDeltaMax{40};   /**<	Default max Delta temparature - in 1/10°C	*/
constexpr int16_t defaultStartTemp{+200}; /**<	Default start temperature - in 1/10°C			*/

class DummyCapteurTemp : public CapteurTemp {
  private:
    mutable std::default_random_engine generator{};
    int16_t _Tmin{defaultTmin};
    int16_t _Tmax{defaultTmax};
    uint16_t _DeltaMax{defaultDeltaMax};
    mutable int16_t _prevTemp{defaultStartTemp};

    int16_t getTmin() const noexcept { return this->_Tmin; };
    int16_t getTmax() const noexcept { return this->_Tmax; };

    uint16_t getDeltaMax() const noexcept { return this->_DeltaMax; };

    int16_t getprevTemp() const noexcept { return this->_prevTemp; };
    void setprevTemp(int16_t prevtemp) const noexcept { this->_prevTemp = prevtemp; };

  public:
    DummyCapteurTemp() = default;                                    /**< Default constructor */
    DummyCapteurTemp(const DummyCapteurTemp &) = default;            /**< Defaulted copy Ctor		*/
    DummyCapteurTemp &operator=(const DummyCapteurTemp &) = default; /**< Defaulted copy assignment operator */
    DummyCapteurTemp(DummyCapteurTemp &&) = default;                 /**< Defaulted move constructor */
    DummyCapteurTemp &operator=(DummyCapteurTemp &&) = default;      /**< Defaulted move assignment operator */
    virtual ~DummyCapteurTemp() = default;

    /**
     * @brief Construct a new Dummy Capteur Temp object - with parameters
     *
     * @param Tmin  Minimum temperature in 1/10°C
     * @param Tmax  Maximum temperature in 1/10°C
     * @param Delta Maximum delta temperature in 1/10°C
     * @param StartTemp Starting temperature in 1/10°C
     */
    DummyCapteurTemp(int16_t Tmin, int16_t Tmax, uint16_t Delta, int16_t StartTemp)
        : _Tmin{Tmin}, _Tmax{Tmax}, _DeltaMax{Delta}, _prevTemp{StartTemp} {};

    /**
     * @brief getTemp() function - gets the temperature
     * @return Temperature in °C (float)
     *
     */
    virtual float getTemp() const noexcept override;
};

#endif /*  __DUMMY_CAPTEUR_TEMP_H__ */
