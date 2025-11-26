/**
 *	@file		appThermostat.hpp
 * 	@brief 		header file for the Application Interface and ThermostatApp class
 * 	@author
 * 	@date		11/2025
 *
 */
#ifndef __APP_THERMOSTAT_H__
#define __APP_THERMOSTAT_H__

#include <array>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

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
 * @brief Thermostat Application class
 *
 */
class ThermostatApp : public Application {

  private:
  public:
    ThermostatApp() = delete; /**< Deleted default Ctor		*/

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
