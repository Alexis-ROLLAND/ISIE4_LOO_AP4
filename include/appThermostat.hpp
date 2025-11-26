/**
 *	@file		appThermostat.hpp
 * 	@brief 		header file for the Application Interface and ThermostatApp class
 * 	@author		Alexis ROLLAND
 * 	@date		09/2024
 *
 */
#ifndef __APP_THERMOSTAT_H__
#define __APP_THERMOSTAT_H__

#define DUMMY_SENSOR 1
#define NETWORK_SENSOR 2
#define SENSOR_TYPE DUMMY_SENSOR

#include <array>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "Chaudiere.hpp"
#include "DummyCapteurTemp.hpp"
#include "NetworkCapteurTemp.hpp"

using namespace std::literals::chrono_literals;

//----------------------------------------------------------------------
/**
 * 	Class Application
 *
 * 	Interface to a "classic" embedded (or not) app
 */
class Application {
  public:
    Application() = default;                              /**<	Defaulted default Ctor	*/
    Application(const Application &) = delete;            /**<	Application class is non copyable		*/
    Application &operator=(const Application &) = delete; /**<	Application class is non copyable	*/
    Application(Application &&) = delete;                 /**<	Application class is non movable		*/
    Application &operator=(Application &&) = delete;      /**<	Application class is non movable		*/
    virtual ~Application() = default;                     /**<	Defaulted Dtor	*/

    /**
     * 	@brief Init function - pure virtual
     * 			Must include all init stuff
     */
    virtual void Init() = 0;

    /**
     * @brief Run function - pure virtual
     * 			Could include main task code
     */
    virtual void Run() = 0;
};
//----------------------------------------------------------------------
/**
 * 	Class ThermostatApp
 *
 * 	Concrete Thermostat app
 */

/**
 * @brief  Exception class - NoBoilerException
 */
class NoBoilerException : public std::exception {}; /**< Exception thrown if no boiler exists	*/

constexpr int filterSize{5};            /**< Size of the moving average filter	*/
constexpr float defaultConsigne{19.0};  /**< Default temperature setpoint in °C	*/
constexpr float defaultHysteresis{1.0}; /**< Default hysteresis value in °C	*/

constexpr auto measure_delay = 1s; /**< Delay between two measurements	*/
constexpr auto process_delay = 5s; /**< Delay between two processing steps	*/

/**
 * @brief Thermostat Application class
 *
 */
class ThermostatApp : public Application {

  private:
#if (SENSOR_TYPE == DUMMY_SENSOR)
    DummyCapteurTemp Capteur{};
#elif (SENSOR_TYPE == NETWORK_SENSOR)
    NetworkCapteurTemp Capteur{};
#else
#endif

    Chaudiere *_pChaudiere{nullptr}; /**< Pointer to the boiler object	*/

    std::array<float, filterSize> tabTemp{}; /**< Array for the moving average filter	*/
    uint8_t ptr{0};                          /**< Pointer/index for the moving average filter array	*/
    std::mutex arrayMutex{};                 /**< Mutex to protect access to the temperature array	*/
    float Consigne{defaultConsigne};         /**< Temperature setpoint in °C	*/
    float Hysteresis{defaultHysteresis};     /**< Hysteresis value in °C	*/

    /**
     * @brief Get the ptr object
     *
     * @return uint8_t
     */
    uint8_t getptr() { return this->ptr; };

    /** * @brief Set the ptr object
     * @param newPtr
     */
    void setptr(uint8_t newPtr) { this->ptr = newPtr; };

    /**
     * @brief Add a temperature to the filter array
     *
     * @param temp
     */
    void addTemp(float temp);

    /**
     * @brief Get the Temp value - gets the filtered temperature
     *
     * @return float
     */
    float getTemp();

    /**
     * @brief Get the Consigne value
     *
     * @return float
     */
    float getConsigne() { return this->Consigne; };

    /**
     * @brief Get the Hysteresis value
     *
     * @return float
     */
    float getHysteresis() { return this->Hysteresis; };

    std::jthread measureThread; /**< Thread for measuring temperature */
    void _measureThread();      /**< Function executed by the measure thread */

    std::jthread processingThread; /**< Thread for processing temperature data */
    void _processingThread();      /**< Function executed by the processing thread */

  public:
    ThermostatApp() = delete; /**< Deleted default Ctor		*/
    ThermostatApp(Chaudiere *pChaudiere) : _pChaudiere{pChaudiere} {};
    ThermostatApp(const ThermostatApp &) = delete;            /**<	ThermostatApp class is non copyable		*/
    ThermostatApp &operator=(const ThermostatApp &) = delete; /**<	ThermostatApp class is non copyable	*/
    ThermostatApp(ThermostatApp &&) = delete;                 /**<	ThermostatApp class is non movable		*/
    ThermostatApp &operator=(ThermostatApp &&) = delete;      /**<	ThermostatApp class is non movable		*/
    virtual ~ThermostatApp() = default;

    /**
     * 	Init function
     * 		This function :
     * 			MUST be called once.
     * 			Checks the pChaudiere pointer
     * 			Creates and starts the threads
     * 	@throw	NoBoilerException if pChaudiere is a nullptr
     *
     */
    virtual void Init() override;

    /**
     * 	Run function
     * 		main task
     * 		May be empty (multithreaded app)
     */
    virtual void Run() override;
};

#endif /* __APP_THERMOSTAT_H__ */
