/**
 *	@file	CapteurTemp.hpp
 * 	@brief 	Header file for the CapteurTemp interface
 * 	@author
 * 	@date	11/2025
 *
 */

#ifndef __CAPTEUR_TEMP_H__
#define __CAPTEUR_TEMP_H__

class CapteurTemp {

  public:
    CapteurTemp() = default;                               /**<	Defaulted default Ctor	*/
    CapteurTemp(const CapteurTemp &) = default;            /**<	Defaulted copy Ctor		*/
    CapteurTemp &operator=(const CapteurTemp &) = default; /**<	Defaulted copy assignment	*/
    CapteurTemp(CapteurTemp &&) = default;                 /**<	Defaulted move Ctor		*/
    CapteurTemp &operator=(CapteurTemp &&) = default;      /**<	Defaulted move assignment	*/
    virtual ~CapteurTemp() = default;                      /**<	Defaulted Dtor			*/

    /**
     *	@brief getTemp() function - pure virtual function
     * 		gets the temperature
     *
     *	@return  Temperature in °C (float)
     */
    virtual float getTemp() const = 0;
};

#endif /* __CAPTEUR_TEMP_H__ */
