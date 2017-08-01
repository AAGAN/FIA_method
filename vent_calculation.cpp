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
 * @param temperature
 * @param spec_vol_ext takes a double for Specific vapour volume of air given
 * @param room_str takes a double for Room Strength
 * @param flood_fact takes a double for flooding factor
 * @param flow_rate takes a double for Mass flow rate of extinguishant
 */

double vent_calculation::get_FIA_vent_area(double temperature,double spec_vol_ext ,double room_strength ,double flooding_factor,double mass_flow_rate)
{
	if( agent_index == 1 ) {						// Non Liquefiable Agent

		double spec_vapvol_mix;					    // Specific Vapour Volume of Homogeneous
        double K1 = 0.773824;
        double K2 = 0.002832967;
		double spec_vapvol_air =  K1 + (K2 * temperature);

        spec_vapvol_mix = ( ( design_concentration * spec_vol_ext ) / 100) + ((( 100 - design_concentration) / 100) * spec_vapvol_air );

		FIA_Area = ( mass_flow_rate * spec_vol_ext ) / sqrt( room_strength * spec_vapvol_mix );

		return FIA_Area;
	} else if( agent_index == 0 ){ 				    // Liquefiable Agent

        // code to be added for Liquefiable Agent
	}
	return FIA_Area;
}

/*
 *  Calculate FSSA Vent Area
 *  @param ext_vent_area takes a double value for Existing vent area
 *  @param pressure_limit takes a double value for Enclosure pressure Limit
 *  @param safety_factor_area takes a double value for Safety factor vent area
 *  @param rel_humidity takes a double value for Relative Humidity of agent
 *  @param hd_index takes a int value for Hardware index
 */
double vent_calculation::get_FSSA_vent_area(double ext_vent_area, double pressure_limit , double safety_factor_area ,double rel_humidity , int hw_index)
{
    if(agent_index == 1){

        if(design_concentration > 4.2 && design_concentration < 6){

            if(discharge_time > 6 && discharge_time <10){
                bool evaflag = false;
                if(ext_vent_area > 0){
                    double pos_pressure = (467.6 + (2.969 * rel_humidity)) * (pow(((ext_vent_area)/(encl_volume * discharge_time)/design_concentration), (-1.0334)));
                    double neg_pressure = (7251 - (77.29 * rel_humidity)) * (pow(((ext_vent_area)/(encl_volume * discharge_time)/design_concentration) , (-1.0318)));

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

                double pos_vent_area = pow(((468.1 * encl_volume * safety_factor_area * design_concentration / discharge_time) * (pressure_limit / (0.8136+0.005166 * rel_humidity))),(-0.9677));
                double neg_vent_area = pow(((3433 * encl_volume * safety_factor_area * design_concentration / discharge_time) * (pressure_limit / (1.6305-0.01738 * rel_humidity))),(-0.9692));

                double pos_pressure = (467.6 + (2.969 * rel_humidity)) * (pow(((pos_vent_area)/(encl_volume * discharge_time) / design_concentration), (-1.0334)));
                double neg_pressure = (7251 - (77.29 * rel_humidity)) * (pow(((neg_vent_area)/(encl_volume * discharge_time) / design_concentration) , (-1.0318)));

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


    } else if ( agent_index == 2){

        if( design_concentration > 6.25 && design_concentration < 10.5 ){

            if( discharge_time > 6 && discharge_time < 10 ){
                bool evaflag = false;
                if( ext_vent_area > 0 ){
                    double pos_pressure = (415.9 + (2.64 * rel_humidity)) * ((1 - 0.3896) * log(((ext_vent_area)/(encl_volume * discharge_time) / design_concentration)));
                    double neg_pressure = (1925 - (20.52 * rel_humidity)) * ((1 - 0.3935) * log(((ext_vent_area)/(encl_volume * discharge_time) / design_concentration)));

                    if( pos_pressure > pressure_limit || neg_pressure > pressure_limit ){
                        evaflag = true;
                    } else {
                        if( pos_pressure > 383 ){
                            evaflag = true;
                        } else {
                            if ( neg_pressure > 958 ){
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


                double pos_vent_area = (13.02 * encl_volume * safety_factor_area * design_concentration / discharge_time ) * exp( - pressure_limit / (162.1+1.029 * (rel_humidity)));
                double neg_vent_area = (12.69 * encl_volume * safety_factor_area * design_concentration / discharge_time ) * exp( - pressure_limit / (757.1-8.072 * (rel_humidity)));

                 pos_pressure = (415.9 + (2.64 * rel_humidity)) * ((1-0.3896) * log(((pos_vent_area)/(encl_volume * discharge_time) / design_concentration)));
                 neg_pressure = (1925 - (20.52 * rel_humidity)) * ((1-0.3935) * log(((neg_vent_area)/(encl_volume * discharge_time) / design_concentration)));

                if(pos_pressure > 383){
                    cout <<  "Positive pressure is higher than limit 383 " << endl;
                    /*
                     * Fatal Return code type 1
                     */
                    return -1;
                } else {
                    if (neg_pressure > 958){
                        cout << "Negative pressure is higher than limit 958 " << endl;
                        /*
                         * Fatal Return code type 2
                         */
                        return -2;
                    } else {
                        pos_vent_area = pos_vent_area - ext_vent_area;
                        neg_vent_area = neg_vent_area - ext_vent_area;

                        return fmax( pos_vent_area , neg_vent_area );
                    }
                }
             }
            } else {
                cout << "Discharge time is outside of valid interval [6.. 10s]" << endl;
            }

        } else {
            cout << "Agent concentration is outside of valid interval [6.25.. 10.5s]" << endl;
        }

    } else if ( agent_index == 3 ){

        if( hw_index == 4 ) {
            if ( design_concentration > 8 && design_concentration < 10.5 ) {
                if ( discharge_time > 6 && discharge_time < 10 ) {
                    if ( ext_vent_area > 0 ) {

                        double pos_pressure = pow((( 508.7 + 3.23 * ( rel_humidity )) * (( ext_vent_area ) / ( encl_volume * discharge_time ) / design_concentration )), -1.037 );
                        double neg_pressure = pow((( 980.3 - 10.45 * (rel_humidity)) * (( ext_vent_area ) / ( encl_volume * discharge_time ) / design_concentration )) , -1.039 );

                        bool positive_flag = false;
                        if ( pos_pressure > pressure_limit || neg_pressure > pressure_limit) {


                        } else {
                            if ( pos_pressure > 1479 ) {

                            } else if ( neg_pressure > 479 ) {

                            } else {
                                cout << "Existing vent (Equivalent leakage) area is sufficient" << endl;
                                return 0;
                            }


                        }
                    }
                    double pos_vent_area = pow(((1328 * encl_volume * safety_factor_area * design_concentration)/ (discharge_time * pressure_limit)),(-0.7783));
                    double pos_pressure = pow((10.298 * ( pos_vent_area / encl_volume  * discharge_time / design_concentration )), -1.285);

                    if (pos_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return -2;
                    }

                    double req_vent_area = pos_vent_area - ext_vent_area;
                    return req_vent_area;

                } else {
                    cout << "Discharge Time is outside of valid interval [30 .. 60]" << endl;
                    return -2;
                }
            } else {
                cout << "Agent concentration is outside of valid interval [34.2 .. 50%]" << endl;
                return -2;
            }
        } else {
            cout << "Agent HFC-125 can be calculated for Fike hardware only" << endl;
            return -2;
        }

    } else if ( agent_index == 4 ) {

        if( hw_index == 2 || hw_index == 3 ) {
            if ( design_concentration > 18 && design_concentration < 30 ) {
                if ( discharge_time > 6 && discharge_time < 10 ) {
                    if ( ext_vent_area > 0 ) {

                        double pos_pressure = pow((3218 + ((ext_vent_area)/(encl_volume*discharge_time)/design_concentration)),-1.285);
                        bool positive_flag = false;

                        if ( pos_pressure > pressure_limit ) {
                            positive_flag = true;

                        } else if ( pos_pressure > 958 ) {

                            positive_flag = true;

                        } else {

                            cout << "Existing vent area is sufficient" << endl;
                            /*
                             * code 0 for existing area is sufficient
                             */
                            return -0;
                        }
                    }
                    double pos_vent_area = pow(((1328 * encl_volume * safety_factor_area * design_concentration)/ (discharge_time * pressure_limit)),(-0.7783));
                    double pos_pressure = pow((10.298 * ( pos_vent_area / encl_volume  * discharge_time / design_concentration )), -1.285);

                    if (pos_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return -2;
                    }

                    double req_vent_area = pos_vent_area - ext_vent_area;
                    return req_vent_area;

                } else {
                    cout << "Discharge Time is outside of valid interval [30 .. 60]" << endl;
                    return -2;
                }
            } else {
                cout << "Agent concentration is outside of valid interval [34.2 .. 50%]" << endl;
                return -2;
            }
        } else {
            cout << "Agent HFC-125 can be calculated for Fike hardware only" << endl;
            return -2;
        }

    } else if ( agent_index == 5 || agent_index == 7 ) {



    } else if ( agent_index == 6 ) {

        if( hw_index == 4 ) {
            if ( design_concentration > 34.2 && design_concentration < 50 ) {
                if ( discharge_time > 30 && discharge_time < 60 ) {
                    if ( ext_vent_area > 0 ) {

                        double pos_pressure = pow((10.298 *((ext_vent_area)/(encl_volume*discharge_time)/design_concentration)),-1.285);
                        bool positive_flag = false;

                        if ( pos_pressure > pressure_limit ) {
                            positive_flag = true;

                        } else if ( pos_pressure > 958 ) {

                            positive_flag = true;

                        } else {

                            cout << "Existing vent area is sufficient" << endl;
                            /*
                             * code 0 for existing area is sufficient
                             */
                            return -0;
                        }
                    }
                    double pos_vent_area = pow(((1328 * encl_volume * safety_factor_area * design_concentration)/ (discharge_time * pressure_limit)),(-0.7783));
                    double pos_pressure = pow((10.298 * ( pos_vent_area / encl_volume  * discharge_time / design_concentration )), -1.285);

                    if (pos_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return -2;
                    }

                    double req_vent_area = pos_vent_area - ext_vent_area;
                    return req_vent_area;

                } else {
                    cout << "Discharge Time is outside of valid interval [30 .. 60]" << endl;
                    return -2;
                }
            } else {
                cout << "Agent concentration is outside of valid interval [34.2 .. 50%]" << endl;
                return -2;
            }
        } else {
            cout << "Agent IG-55PI can be calculated for Fike hardware only" << endl;
            return -2;
        }
    } else if ( agent_index == 8 ){

        if( hw_index == 1 ) {
            if ( design_concentration > 34.2 && design_concentration < 52 ) {
                if ( discharge_time > 30 && discharge_time < 60 ) {
                    if ( ext_vent_area > 0 ) {

                        double pos_pressure = pow((10.462 *((ext_vent_area)/(encl_volume*discharge_time)/design_concentration)),-1.188);
                        bool positive_flag = false;

                        if ( pos_pressure > pressure_limit ) {
                            positive_flag = true;
                        } else if ( pos_pressure > 958 ) {
                            positive_flag = true;
                        } else {
                            cout << "Existing vent area is sufficient" << endl;
                            /*
                             * code 0 for existing area is sufficient
                             */
                            return -0;
                        }
                    }
                    double pos_vent_area = pow(((2416 * encl_volume * safety_factor_area * design_concentration)/ (discharge_time * pressure_limit)),(-0.8417));
                    double pos_pressure = pow((10.462 * ( pos_vent_area / encl_volume  * discharge_time / design_concentration )), -1.188);

                    if (pos_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return -2;
                    }

                    double req_vent_area = pos_vent_area - ext_vent_area;
                    return req_vent_area;

                } else {
                    cout << "Discharge Time is outside of valid interval [30 .. 60]" << endl;
                    return -2;
                }
            } else {
                cout << "Agent concentration is outside of valid interval [34.2 .. 52%]" << endl;
                return -2;
            }
        } else {
            cout << "Agent IG-541PI can be calculated for Ansul / JCI hardware only" << endl;
            return -2;
        }

    }

	return FSSA_Area;
}




