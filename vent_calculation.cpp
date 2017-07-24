/*
 * Ventcalculation.cpp
 *
 *  Created on: Jul 19, 2017
 *      Author: skbiswas
 */

#include "vent_calculation.h"
#include "cmath"
#include <iostream>

using namespace std;

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

		double spec_vapvol_mix;					// Specific Vapour Volume of Homogeneous
        double K1 = 0.773824;
        double K2 = 0.002832967;
		double spec_vapvol_air =  K1 + (K2 * temperature);

        spec_vapvol_mix = ((design_cntration * spec_vol_extinguishant) / 100) + (((100 - design_cntration) / 100) * spec_vapvol_air);

		FIA_Area = (mass_flow_rate*spec_vol_extinguishant)/sqrt(room_str*spec_vapvol_mix);

		return FIA_Area;
	} else if( agent_index == 0 ){ 				// Liquefiable Agent


	}
	return FIA_Area;
}

/*
 *  Calculate FSSA Vent Area
 */
double vent_calculation::get_FSSA_vent_area()
{
    if(agent_index == 1){

        if(design_cntration > 4.2 && design_cntration < 6){

            if(discharge_time > 6 && discharge_time <10){
                bool evaflag = false;
                if(ext_vent_area > 0){
                    double pos_pressure = (467.6 + (2.696*rel_humidity)) * (pow(((ext_vent_area)/(encl_volume*temperature)/design_cntration), (-1.0334)));
                    double neg_pressure = (7251 - (77.29*rel_humidity))*(pow(((ext_vent_area)/(encl_volume*temperature)/design_cntration) , (-1.0318)));

                    if( pos_pressure > pressure_limit || neg_pressure > pressure_limit ){
                        evaflag = true;
                    } else {
                        if(pos_pressure > 239){
                            evaflag = true;
                        } else {
                            if (neg_pressure > 1197){
                                evaflag = true;
                            } else {
                                cout << "Existing vent Equivalent leakage area is sufficient" << endl;
                                return 0;
                            }
                        }
                    }
                }

                double pos_vent_area = pow(((468.1*encl_volume*safty_area * design_cntration * temperature)*(pressure_limit / (0.8136+0.005166*rel_humidity))),(-0.9677));
                double neg_vent_area = pow(((3433*encl_volume*safty_area * design_cntration * temperature)*(pressure_limit / (1.6305-0.01738*rel_humidity))),(-0.9692));

                double pos_pressure = (467.6 + (2.696*rel_humidity)) * (pow(((pos_vent_area)/(encl_volume*temperature) / design_cntration), (-1.0334)));
                double neg_pressure = (7251 - (77.29*rel_humidity))*(pow(((neg_vent_area)/(encl_volume*temperature) / design_cntration) , (-1.0318)));

                if(pos_pressure > 239){
                    cout << "Positive pressure is higher than limit 239 " << endl;
                    return -1;
                } else  if (neg_pressure > 1197){
                    cout << "Negative pressure is higher than limit 1197 " << endl;
                    return -2;
                } else {

                    pos_vent_area = pos_vent_area - ext_vent_area;
                    neg_vent_area = neg_vent_area - ext_vent_area;

                    return fmax(pos_vent_area,neg_vent_area);
                }

            } else {
                cout << "Discharge time is outside of valid interval [6.. 10s]" << endl;
            }

        } else {
            cout << "Agent concentration is outside of valid interval [6.. 10s]" << endl;
        }


    } else if ( agent_index = 2){

        if(design_cntration > 6.25 && design_cntration < 10.5){

            if(discharge_time > 6 && discharge_time < 10){
                bool evaflag = false;
                if(ext_vent_area > 0){
                    double pos_pressure = (415.9 + (2.64 * rel_humidity)) * ((1 - 0.3896) * log(((ext_vent_area)/(encl_volume*temperature) / design_cntration)));
                    double neg_pressure = (1925 - (20.52 * rel_humidity))*((1 - 0.3935) * log(((ext_vent_area)/(encl_volume*temperature) / design_cntration)));

                    if( pos_pressure > pressure_limit || neg_pressure > pressure_limit ){
                        evaflag = true;
                    } else {
                        if(pos_pressure > 383){
                            evaflag = true;
                        } else {
                            if (neg_pressure > 958){
                                evaflag = true;
                            } else {
                                cout << "Existing vent Equivalent leakage area is sufficient " << endl;
                                /*
                                 * Return code 0 for existing leakage area is sufficient
                                 */
                                return 0;
                            }
                        }
                    }
                }

                double pos_vent_area = (13.02 * encl_volume * safty_area * design_cntration * temperature ) * exp( - pressure_limit / (162.1+1.029 * (rel_humidity)));
                double neg_vent_area = (12.69 * encl_volume * safty_area * design_cntration * temperature ) * exp( - pressure_limit / (757.1-8.072 * (rel_humidity)));

                double pos_pressure = (415.9 + (2.64*rel_humidity)) * ((1-0.3896) * log(((pos_vent_area)/(encl_volume*temperature) / design_cntration)));
                double neg_pressure = (7251-77.29*(rel_humidity))*((1-0.3935) * log(((neg_vent_area)/(encl_volume*temperature) / design_cntration)));

                if(pos_pressure > 383){
                    cout <<  "Positive pressure is higher than limit 383 " << endl;
                    /*
                     * Fatal Return code type 1
                     */
                    return -1;
                } else  if (neg_pressure > 958){
                    cout << "Negative pressure is higher than limit 958 " << endl;
                    /*
                     * Fatal Return code type 2
                     */
                    return -2;
                } else {

                    pos_vent_area = pos_vent_area - ext_vent_area;
                    neg_vent_area = neg_vent_area - ext_vent_area;

                    return fmax(pos_vent_area,neg_vent_area);
                }

            } else {
                cout << "Discharge time is outside of valid interval [6.. 10s]" << endl;
            }

        } else {
            cout << "Agent concentration is outside of valid interval [6.25.. 10.5s]" << endl;
        }

    }

	return FSSA_Area;
}




