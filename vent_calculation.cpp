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

int vent_calculation::get_FIA_vent_area( double temperature , double spec_vol_ext , double room_strength , double flooding_factor , double mass_flow_rate , double pressure_excur ,
                                            double neg_press_excur, double total_vent_area , double ext_vent_press , double neg_press_limit)
{
	if( agent_index == 1 ) {						// Non Liquefiable Agent

		double spec_vapvol_mix;					    // Specific Vapour Volume of Homogeneous
        double K1 = 0.773824;
        double K2 = 0.002832967;
		double spec_vapvol_air =  K1 + (K2 * temperature);

        spec_vapvol_mix = ( ( design_concentration * spec_vol_ext ) / 100) + ((( 100 - design_concentration) / 100) * spec_vapvol_air );

		FIA_Area = ( mass_flow_rate * spec_vol_ext ) / sqrt( room_strength * spec_vapvol_mix );

		return FIA_Area;

	} else if( agent_index == 0 ) { 				    // Liquefiable Agent

        if( pressure_excur == 0 ) {
            /*
             * calculating for agent type HFC-23
             */
            double pos_pressure_excur = pow((0.08827 * (( total_vent_area / spec_vol_ext ) * ( discharge_time / encl_volume ) )), -1.165) *(0.81 + 0.51 * (rel_humidity/100));
            double pos_total_vent_area =  0.12384*(encl_volume/discharge_time)* spec_vol_ext * pow(( pos_pressure_excur /0.81+0.51*(rel_humidity/100)),-0.8587);

        } else if( pressure_excur == 1 ) {

            if ( neg_press_excur == 1) {

                /*
                 * calculating for agent type HFC-227-ea
                 */
                double pos_pressure_excur = ( 48.359 * ( 4.2*log( (spec_vol_ext * encl_volume ) / (total_vent_area * discharge_time) ) - 27.922) * (0.81+0.51*(rel_humidity/100))) ;
                double neg_pressure_excur = pow( ( 46.444 * ( ( total_vent_area / encl_volume ) * ( discharge_time / encl_volume ) ) ), -1.037 ) *( 1.68 - 1.79 * (rel_humidity/100));

                double pos_vent_area = 0.050 * ( encl_volume / discharge_time) * spec_vol_ext * ( pos_pressure_excur / 0.81+0.51 * ( rel_humidity / 100 ) );
                double neg_vent_area = 0.04589 * ( encl_volume / discharge_time) * spec_vol_ext * ( neg_pressure_excur / 1.68-1.79 * ( rel_humidity / 100 ) );

            } else if ( neg_press_excur == 2) {
                /*
                 * calculating for agent type HFC-125
                 */
                double pos_pressure_excur = pow( ( 0.045349 * (( total_vent_area / encl_volume ) * ( discharge_time / encl_volume ) ) ), -1.037 ) *( 0.81 + 0.51 * (rel_humidity/100));
                double neg_pressure_excur = pow( ( 0.03949 * (( total_vent_area / encl_volume ) * ( discharge_time / encl_volume ) ) ), -1.037 ) *( 1.68 - 1.79 * (rel_humidity/100));

                double pos_vent_area = 0.050 * ( encl_volume / discharge_time) * spec_vol_ext * ( pos_pressure_excur / 0.81+0.51 * ( rel_humidity / 100 ) );
                double neg_vent_area = 0.04589 * ( encl_volume / discharge_time) * spec_vol_ext * ( neg_pressure_excur / 1.68-1.79 * ( rel_humidity / 100 ) );



            } else if ( neg_press_excur == 0 ) {

                double pos_pressure_excur = pow( ( 0.042649 * (( total_vent_area / encl_volume ) * ( discharge_time / encl_volume ) ) ), -1.0334 ) *( 0.81 + 0.51 * (rel_humidity/100));
                double neg_pressure_excur = pow( ( 0.32170 * (( total_vent_area / encl_volume ) * ( discharge_time / encl_volume ) ) ), -1.0318 ) *( 1.68 - 1.79 * (rel_humidity/100));

                double pos_vent_area = 0.04678 * ( encl_volume / discharge_time ) * spec_vol_ext * ( pos_pressure_excur / 0.81+0.51 * ( rel_humidity / 100 ) );
                double neg_vent_area = 0.04589 * ( encl_volume / discharge_time ) * spec_vol_ext * ( neg_pressure_excur / 1.68-1.79 * ( rel_humidity / 100 ) );

            }

        }

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
int vent_calculation::get_FSSA_vent_area(double ext_vent_area, double pressure_limit , double safety_factor_area , int hw_index)
{
    if(agent_index == 1){

        if(design_concentration > 4.2 && design_concentration < 6){

            if(discharge_time > 6 && discharge_time <10){
                bool evaflag = false;
                if(ext_vent_area > 0){

                    double pos_pressure = (467.6 + 2.969 * (rel_humidity)) * pow((( ext_vent_area ) *  ( pow(10,4) )/ ( encl_volume * discharge_time  / design_concentration ) ), -1.0334 );
                    double neg_pressure = (7251 + 77.229 * (rel_humidity)) * pow((( ext_vent_area ) *  ( pow(10,4) )/ ( encl_volume * discharge_time  / design_concentration ) ), -1.0318 );

                    cout << "pos_pressure = " << pos_pressure << endl;
                    cout << "neg_pressure = " << neg_pressure << endl;

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

                double pos_vent_area = ( 468.1 * encl_volume * safety_factor_area * design_concentration ) / discharge_time * pow((pressure_limit / ( 0.8136 + 0.005166 * (rel_humidity))), -0.9677 );
                double neg_vent_area = ( 3433 * encl_volume * safety_factor_area * design_concentration) / discharge_time * pow((pressure_limit / ( 1.6305 - 0.01738 * (rel_humidity))), -0.9692 );

                cout << "pos_vent_area = " << pos_vent_area << endl;
                cout << "neg_vent_area = " << neg_vent_area << endl;

                double pos_pressure = (467.6 + 2.969 * (rel_humidity) ) * pow((pos_vent_area/encl_volume * discharge_time / design_concentration), -1.0334);
                double neg_pressure = (7251 - 77.29 * (rel_humidity) ) * pow((neg_vent_area/encl_volume * discharge_time / design_concentration) , -1.0318);

                cout << "pos_pressure = " << pos_pressure << endl;
                cout << "neg_pressure = " << neg_pressure << endl;

                if(pos_pressure > 239){
                    cout << "Positive pressure is higher than limit 239 " << endl;
                    return -1;
                } else  if (neg_pressure > 1197){
                    cout << "Negative pressure is higher than limit 1197 " << endl;
                    return -2;
                } else {

                    pos_vent_area = pos_vent_area * pow( 10, -4 ) - (ext_vent_area );
                    neg_vent_area = neg_vent_area * pow( 10, -4 ) - (ext_vent_area) ;
                    cout << "pos_pressure = " << pos_pressure << endl;
                    cout << "neg_pressure = " << neg_pressure << endl;
                    double vent_area = max(pos_vent_area,neg_vent_area);
                    cout << "vent_area = " << vent_area << endl;

                    return vent_area;
                }

            } else {
                cout << "Discharge time is outside of valid interval [6.. 10s]" << endl;
            }

        } else {
            cout << "Agent concentration is outside of valid interval [6.. 10s]" << endl;
        }

    } else if ( agent_index == 2 ) {

        if( design_concentration >= 6.25 && design_concentration < 10.5 ){

            if( discharge_time > 6 && discharge_time < 10 ){
                bool evaflag = false;
                if( ext_vent_area > 0 ){
                    double pos_pressure = ( 415.9 + 2.64 * ( rel_humidity ) ) *  ( 1 - 0.3896  * log((ext_vent_area)* ( pow(10,4) ) / ( encl_volume * discharge_time  / design_concentration ) ) );
                    double neg_pressure = ( 1925 - 20.52 * ( rel_humidity ) ) * ( 1 - 0.3935  * log((ext_vent_area )* ( pow(10,4) ) / ( encl_volume * discharge_time / design_concentration ) ) );

                    cout << "pos_pressure = " << pos_pressure << endl;
                    cout << "neg_pressure = " << neg_pressure << endl;

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

                    cout << "pos_vent_area = " << pos_vent_area << endl;
                    cout << "neg_vent_area = " << neg_vent_area << endl;


                    pos_pressure = (415.9 + 2.64 * ( rel_humidity )) * ((1-0.3896) * log(pos_vent_area/ (encl_volume * discharge_time / design_concentration)));

                    neg_pressure = (1925 - 20.52 * ( rel_humidity )) * ((1-0.3935) * log(neg_vent_area/(encl_volume * discharge_time / design_concentration)));

                    cout << "pos_pressure = " << pos_pressure << endl;
                    cout << "neg_pressure = " << neg_pressure << endl;

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

            if ( design_concentration >= 8 && design_concentration < 10.5 ) {

                if ( discharge_time > 6 && discharge_time < 10 ) {

                    if ( ext_vent_area > 0 ) {

                        cout << "ext_vent_area = " << ( pow(10,4) )/ (( encl_volume * discharge_time ) / design_concentration ) << endl;
                        cout << "encl_volume = " << encl_volume << endl;
                        cout << "rel_humidity = " << rel_humidity << endl;
                        cout << "discharge_time = " << discharge_time << endl;
                        cout << "design_concentration = " << design_concentration << endl;

                        double pos_pressure = ( 508.7 + 3.23 * ( rel_humidity )) *  pow((( ext_vent_area ) *  ( pow(10,4) )/ ( encl_volume * discharge_time  / design_concentration ) ) , -1.037 );
                        double neg_pressure = ( 980.3 - 10.45 * ( rel_humidity )) * pow((( ext_vent_area ) * ( pow(10,4) )/ ( encl_volume * discharge_time  / design_concentration ) ) , -1.039 );

                        cout << "pos_pressure = " << pos_pressure << endl;
                        cout << "neg_pressure = " << neg_pressure << endl;

                        bool positive_flag = false;

                        if ( pos_pressure > pressure_limit || neg_pressure > pressure_limit ) {


                        } else {
                            if ( pos_pressure > 1479 ) {

                            } else if ( neg_pressure > 479 ) {

                            } else {
                                cout << "Existing vent (Equivalent leakage) area is sufficient" << endl;
                                return pos_pressure;
                            }


                        }
                    }

                    double pos_vent_area = ( 500.3 * encl_volume * safety_factor_area * design_concentration ) / discharge_time * pow((pressure_limit / ( 0.8056 + 0.005115 * (rel_humidity))), -0.964 );
                    double neg_vent_area = ( 458.3 * encl_volume * safety_factor_area * design_concentration) / discharge_time * pow((pressure_limit / (1.6809 - 0.0179 * (rel_humidity))), -0.9622 );

                    cout << "pos_vent_area =" << pos_vent_area << endl;
                    cout << "neg_vent_area =" << neg_vent_area << endl;

                    double pos_pressure = ( 508.7 + 3.23 * ( rel_humidity) ) * pow(( pos_vent_area / encl_volume* discharge_time / design_concentration ), -1.037);
                    double neg_pressure = ( 980.3 - 10.45 * ( rel_humidity) ) * pow(( neg_vent_area / encl_volume* discharge_time / design_concentration ), -1.039);

                    cout << "pos_pressure =" << pos_pressure << endl;
                    cout << "neg_pressure =" << neg_pressure << endl;

                    if (pos_pressure > 1479) {
                        cout << "Positive pressure is higher than limit 1479" << endl;
                        return -2;
                    } else if (neg_pressure > 479) {
                        cout << "Negative pressure is higher than limit 479" << endl;
                        return -2;
                    }

                    pos_vent_area = (pos_vent_area * pow( 10, -4 )) - ext_vent_area ;
                    neg_vent_area = neg_vent_area * pow( 10, -4 ) - ext_vent_area ;

                    //cout << "pos_vent_area =" << pos_vent_area << endl;
                    //cout << "neg_vent_area =" << neg_vent_area << endl;
                    cout << " vent_area =" << max( pos_vent_area , neg_vent_area ) << endl;

                    return max( pos_vent_area , neg_vent_area );

                } else {
                    cout << "Discharge Time is outside of valid interval [6 .. 10s]" << endl;
                    return -2;
                }
            } else {
                cout << "Agent concentration is outside of valid interval [8 .. 10%]" << endl;
                return -2;
            }
        } else {
            cout << "Agent HFC-125 can be calculated for Fike hardware only" << endl;
            return -2;
        }

    } else if ( agent_index == 4 ) {

        if( hw_index == 2 || hw_index == 3 ) {
            if ( design_concentration >= 18 && design_concentration < 30 ) {
                if ( discharge_time > 6 && discharge_time < 10 ) {
                    if ( ext_vent_area > 0 ) {

                        double pos_pressure = ( 3218 + 20.43 * ( rel_humidity )) * pow((( ext_vent_area ) *  ( pow(10,4) )/ ( encl_volume * discharge_time  / design_concentration ) ), -1.165 );
                        bool positive_flag = false;
                        cout << "pos_pressure =" << pos_pressure << endl;
                        if ( pos_pressure > pressure_limit ) {
                            positive_flag = true;

                        } else if ( pos_pressure > 1437 ) {

                            positive_flag = true;

                        } else {

                            cout << "Existing vent area is sufficient" << endl;
                            /*
                             * code 0 for existing area is sufficient
                             */
                            return pos_pressure;
                        }
                    }
                    double pos_vent_area = ((1239 * encl_volume * safety_factor_area * design_concentration)/ discharge_time) * pow(pressure_limit /(0.8056+0.005115*(rel_humidity)),(-0.8587));
                    double pos_pressure =  ( 3218 + 20.43 * ( rel_humidity )) * pow(( pos_vent_area  /  encl_volume * discharge_time / design_concentration ), -1.165 );

                    cout << "pos_vent_area =" << pos_vent_area << endl;
                    cout << "pos_pressure =" << pos_pressure << endl;

                    if (pos_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return -2;
                    }

                    pos_vent_area = (pos_vent_area * pow( 10, -4 )) - ext_vent_area ;
                    cout << "vent_area =" << pos_vent_area << endl;
                    return pos_vent_area;

                } else {
                    cout << "Discharge Time is outside of valid interval [6 .. 10]" << endl;
                    return -2;
                }
            } else {
                cout << "Agent concentration is outside of valid interval [18 .. 30 %]" << endl;
                return -2;
            }
        } else {
            cout << "Agent HFC-23 can be calculated for Kiddie or Fenwal hardware only" << endl;
            return -2;
        }

    } else if ( agent_index == 5 || agent_index == 7 ) {

        if( hw_index == 2 || hw_index == 3 || hw_index == 5  ) {
            if ( design_concentration >= 37 && design_concentration < 50 ) {
                if ( discharge_time > 30 && discharge_time < 60 ) {
                    if ( ext_vent_area > 0 ) {

                        double pos_pressure =  12875 * pow(((( ext_vent_area ) *  (( pow(10,4) )/ ( encl_volume * discharge_time  / design_concentration )) ) / design_concentration), -1.089 );

                        cout << "pos_pressure =" << pos_pressure << endl;

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
                    double pos_vent_area =  5948 * encl_volume * safety_factor_area * design_concentration /  discharge_time * pow(pressure_limit , -0.9184 );
                    double pos_pressure = 12875 * pow( (pos_vent_area / encl_volume  * discharge_time / design_concentration ), -1.089);

                    cout << "pos_vent_area =" << pos_vent_area << endl;
                    cout << "pos_pressure =" << pos_pressure << endl;

                    if (pos_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return -2;
                    }

                    double req_vent_area = (pos_vent_area * pow( 10, -4 )) - ext_vent_area;
                    cout << "req_vent_area =" << req_vent_area << endl;
                    return req_vent_area;

                } else {
                    cout << "Discharge Time is outside of valid interval [30 .. 60s]" << endl;
                    return -2;
                }
            } else {
                cout << "Agent concentration is outside of valid interval [37 .. 50 %]" << endl;
                return -2;
            }
        } else {
            cout << "Agent IG-55PI or IG-100 can be calculated for kiddie, Fenwal or Chemetron hardware only" << endl;
            return -2;
        }

    } else if ( agent_index == 6 ) {

        if( hw_index == 4 ) {
            if ( design_concentration > 34.2 && design_concentration < 50 ) {
                if ( discharge_time > 30 && discharge_time < 60 ) {
                    if ( ext_vent_area > 0 ) {

                        double pos_pressure = 10298 * pow(((( ext_vent_area ) *  (( pow(10,4) )/ ( encl_volume * discharge_time  / design_concentration )) ) / design_concentration), -1.285 );
                        cout << "pos_pressure =" << pos_pressure << endl;
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
                    double pos_vent_area = 1328 * encl_volume * safety_factor_area * design_concentration /  discharge_time * pow(pressure_limit , -0.7783 );
                    cout << "pos_vent_area =" << pos_vent_area << endl;
                    double pos_pressure = 10298  * pow( (pos_vent_area / encl_volume  * discharge_time / design_concentration ), -1.285);
                    cout << "pos_pressure =" << pos_pressure << endl;

                    if (pos_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return -2;
                    }

                    double req_vent_area = (pos_vent_area * pow( 10, -4 )) - ext_vent_area;
                    cout << "req_vent_area =" << req_vent_area << endl;
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

                        double pos_pressure = 10462 * pow(((( ext_vent_area ) *  (( pow(10,4) )/ ( encl_volume * discharge_time  / design_concentration )) ) / design_concentration),-1.188);
                        cout << "pos_pressure =" << pos_pressure << endl;
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

                    double pos_vent_area = 2416 * encl_volume * safety_factor_area * design_concentration /  discharge_time * pow(pressure_limit , (-0.8417) );
                    cout << "pos_vent_area =" << pos_vent_area << endl;
                    double pos_pressure = 10462  * pow( (pos_vent_area / encl_volume  * discharge_time / design_concentration ), -1.188);
                    cout << "pos_pressure =" << pos_pressure << endl;

                    if (pos_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return -2;
                    }

                    double req_vent_area = (pos_vent_area * pow( 10, -4 )) - ext_vent_area;
                    cout << "req_vent_area =" << req_vent_area << endl;
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

}




