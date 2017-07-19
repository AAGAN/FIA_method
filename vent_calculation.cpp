/*
 * Ventcalculation.cpp
 *
 *  Created on: Jul 19, 2017
 *      Author: skbiswas
 */

#include "vent_calculation.h"
#include "cmath"


double vent_calculation::FIA(){

	return FIA_Area;		// Total Vent Area (Sq mtr)
}

double vent_calculation::FSSA()
{
	return FSSA_Area;			// Pressure Relief Vent Area
}

/* Vent Caluculation for FIA
 * returns Vent Area based on fire Extinguishing Agent Type
 */
double vent_calculation::get_FIA_vent_area()
{
	if(ext_agent == 1 ) {						// Non Liquefiable Agent

		double sh;								// Specific Vapour Volume of Homogeneous
		double s_air = ( desg_const + temperature ) * temperature;

		sh = ((desg_const * sp_volume) / 100) + (((100 - desg_const) / 100) * s_air);

		FIA_Area = (mass_fl_rate_agent*sp_volume)/sqrt(room_str*sh);

		return FIA_Area;
	} else if( ext_agent == 0 ){ 				// Liquefiable Agent


	}
	return FIA_Area;
}


double vent_calculation::get_FSSA_vent_area()
{
	FSSA_Area = 1.0;
	return FSSA_Area;
}




