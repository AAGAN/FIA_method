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
	if(agent_index == 1 ) {						// Non Liquefiable Agent

		double sh;								// Specific Vapour Volume of Homogeneous
        double K1 = 0.773824;
        double K2 = 0.002832967;
		double s_air =  K1 + (K2 * temperature);

		sh = ((desg_concnt * sp_volume) / 100) + (((100 - desg_concnt) / 100) * s_air);

		FIA_Area = (mass_fl_rate_agent*sp_volume)/sqrt(room_str*sh);

		return FIA_Area;
	} else if( agent_index == 0 ){ 				// Liquefiable Agent


	}
	return FIA_Area;
}


double vent_calculation::get_FSSA_vent_area()
{
    if(agent_index == 1){

        if(desg_concnt > 4.2 && desg_concnt < 6){

            if(discharge_time > 6 && discharge_time <10){
                bool evaflag = false;
                if(eva > 0){
                    double Pp = (467.6 + (2.696*rel_humidity)) * (pow(((eva)/(encl_volume*temperature)/desg_concnt), (-1.0334)));
                    double Pn = (7251 - (77.29*rel_humidity))*(pow(((eva)/(encl_volume*temperature)/desg_concnt) , (-1.0318)));

                    if( Pp > pa_limit || Pn > pa_limit ){
                        evaflag = true;
                    } else {
                        if(Pp > 239){
                            evaflag = true;
                        } else {
                            if (Pn > 1197){
                                evaflag = true;
                            } else {
                                // Exit Message: Existing vent Equivalent leakage area is sufficient
                                return 0;
                            }
                        }
                    }
                }

                double Ap = pow(((468.1*encl_volume*sf_area*desg_concnt*temperature)*(pa_limit/(0.8136+0.005166*rel_humidity))),(-0.9677));
                double An = pow(((3433*encl_volume*sf_area*desg_concnt*temperature)*(pa_limit/(1.6305-0.01738*rel_humidity))),(-0.9692));

                double Pp = (467.6 + (2.696*rel_humidity)) * (pow(((Ap)/(encl_volume*temperature)/desg_concnt), (-1.0334)));
                double Pn = (7251 - (77.29*rel_humidity))*(pow(((An)/(encl_volume*temperature)/desg_concnt) , (-1.0318)));

                if(Pp > 239){
                    // Error Message "Positive pressure is higher than limit 239 Pa"
                    return -1;
                } else  if (Pn > 1197){
                    // Error Message "Negative pressure is higher than limit 1197 Pa"
                    return -2;
                } else {

                    Ap = Ap - eva;
                    An = An - eva;

                    return fmax(Ap,An);
                }


            } else {
                // Error Message Discharge time is outside of valid interval [6.. 10s]
            }

        } else {
            // Error Message "Agent concentration is outside of valid interval [6.. 10s]
        }


    } else if ( agent_index = 2){

        if(desg_concnt > 6.25 && desg_concnt < 10.5){

            if(discharge_time > 6 && discharge_time < 10){
                bool evaflag = false;
                if(eva > 0){
                    double Pp = (415.9 + (2.64 * rel_humidity)) * ((1 - 0.3896) * log(((eva)/(encl_volume*temperature)/desg_concnt)));
                    double Pn = (1925 - (20.52 * rel_humidity))*((1 - 0.3935) * log(((eva)/(encl_volume*temperature)/desg_concnt)));

                    if( Pp > pa_limit || Pn > pa_limit ){
                        evaflag = true;
                    } else {
                        if(Pp > 383){
                            evaflag = true;
                        } else {
                            if (Pn > 958){
                                evaflag = true;
                            } else {
                                // Exit Message: Existing vent Equivalent leakage area is sufficient
                                return 0;
                            }
                        }
                    }
                }

                double Ap = (13.02 * encl_volume * sf_area * desg_concnt * temperature ) * exp( - pa_limit / (162.1+1.029 * (rel_humidity)));
                double An = (12.69 * encl_volume * sf_area * desg_concnt * temperature ) * exp( - pa_limit / (757.1-8.072 * (rel_humidity)));

                double Pp = (415.9 + (2.64*rel_humidity)) * ((1-0.3896) * log(((Ap)/(encl_volume*temperature)/desg_concnt)));
                double Pn = (7251-77.29*(rel_humidity))*((1-0.3935) * log(((An)/(encl_volume*temperature)/desg_concnt)));

                if(Pp > 383){
                    // Error Message "Positive pressure is higher than limit 383 Pa"
                    return -1;
                } else  if (Pn > 958){
                    // Error Message "Negative pressure is higher than limit 958 Pa"
                    return -2;
                } else {

                    Ap = Ap - eva;
                    An = An - eva;

                    return fmax(Ap,An);
                }

            } else {
                // Error Message Discharge time is outside of valid interval [6.. 10s]
            }

        } else {
            // Error Message "Agent concentration is outside of valid interval [6.25.. 10.5s]
        }


    }

	return FSSA_Area;
}




