/**
 *	@file	Chaudiere.hpp
 * 	@brief 	Header file for the Chaudiere interface and the
 * 			DummyChaudiere concrete class
 * 	@author
 * 	@date	11/2025
 *
 */

#ifndef __CHAUDIERE_H__
#define __CHAUDIERE_H__

#include <iostream>
#include <print>

//----------------------------------------------------------------------
class BoilerAlreadyONexception : public std::exception {
}; /**< Exception thrown if trying to set ON an already on boiler	*/
class BoilerAlreadyOFFexception : public std::exception {
}; /**< Exception thrown if trying to set OFF an already off boiler	*/
//----------------------------------------------------------------------
/**
 * 	Class Chaudiere
 *
 * 	Interface to a "boiler"
 */
class Chaudiere {
  public:
    enum class Status {
        ON, /**<	Boiler ON status value	*/
        OFF /**<	Boiler OFF status value	*/
    };

  private:
    Status _status{Status::OFF}; /**<	Boiler status	*/
  protected:
    /**
     *	Setter for the status field
     * 	@param[in] : new status
     *
     * 	noexcept : this function throws no exception
     *
     */
    void setStatus(Status status) noexcept { this->_status = status; };

  public:
    Chaudiere() = default;                             /**<	Defaulted default Ctor	*/
    Chaudiere(const Chaudiere &) = default;            /**<	Defaulted copy Ctor		*/
    Chaudiere(Chaudiere &&) = default;                 /**<	Defaulted move Ctor		*/
    Chaudiere &operator=(const Chaudiere &) = default; /**<	Defaulted copy assignment	*/
    Chaudiere &operator=(Chaudiere &&) = default;      /**<	Defaulted move assignment	*/
    virtual ~Chaudiere() = default;                    /**<	Defaulted Dtor			*/

    /**
     *	@brief getter for the status field
     *
     *	const : this function is usable with a const object
     * 	noexcept : this function throws no exception
     *
     * 	@return : heater status
     */
    Status getStatus() const noexcept { return this->_status; };

    /**
     *	@brief setON() function - pure virtual function
     * 		Sets the boiler on (if not)
     *
     * 	@throw	HeaterAlreadyONexception	if the boiler is already on
     *
     */
    virtual void setON() = 0;

    /**
     *	@brief setOFF() function - pure virtual function
     * 		Sets the boiler off (if not)
     *
     * 	@throw	HeaterAlreadyOFFexception	if the boiler is already off
     *
     */
    virtual void setOFF() = 0;
};

//----------------------------------------------------------------------
class DummyChaudiere : public Chaudiere {
  private:
  public:
    DummyChaudiere() = default;                                  /**<	Defaulted default Ctor	*/
    DummyChaudiere(const DummyChaudiere &) = default;            /**<	Defaulted copy Ctor		*/
    DummyChaudiere(DummyChaudiere &&) = default;                 /**<	Defaulted move Ctor		*/
    DummyChaudiere &operator=(const DummyChaudiere &) = default; /**<	Defaulted copy assignment	*/
    DummyChaudiere &operator=(DummyChaudiere &&) = default;      /**<	Defaulted move assignment	*/
    virtual ~DummyChaudiere() = default;                         /**<	Defaulted Dtor			*/

    /**
     *	@brief setON() function
     * 		Sets the boiler on (if not)
     *
     * 	@throw	HeaterAlreadyONexception	if the boiler is already on
     *
     */
    virtual void setON() override;

    /**
     *	@brief setOFF() function
     * 		Sets the boiler off (if not)
     *
     * 	@throw	HeaterAlreadyOFFexception	if the boiler is already off
     *
     */
    virtual void setOFF() override;
};
//----------------------------------------------------------------------

#endif /* __CHAUDIERE_H__ */
