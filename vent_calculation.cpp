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

#define VENT_AREA_OK                  -1;
#define POS_PRESSURE_239              -2;
#define NEG_PRESSURE_1197             -3;
#define POS_PRESSURE_958              -4;
#define POS_PRESSURE_383              -5;
#define NEG_PRESSURE_958              -6;
#define POS_PRESSURE_1479             -7;
#define NEG_PRESSURE_479              -8;
#define DIS_TIME_30_60                -9;
#define DIS_TIME_6_10                -10;
#define AGENT_CONCEN_34_52           -11;
#define AGENT_CONCEN_34_50           -12;
#define AGENT_CONCEN_37_50           -13;
#define AGENT_CONCEN_18_30           -14;
#define AGENT_CONCEN_8_10            -15;
#define AGENT_CONCEN_6_10            -16;
#define AGENT_CONCEN_625_105         -17;
#define AGENT_ANSUL_JCI_541          -18;
#define AGENT_FIKE_55PI              -19;
#define AGENT_KID_FEN_HFC23          -20;
#define AGENT_KID_FEN_CHEM_55PI100   -21;
#define AGENT_FIKE_HFC125            -22;
#define REL_HUMIDITY_20_80           -23;
#define AGENT_CONCEN_8_105           -24;




double vent_calculation::FIA(){

	return FIA_Area;		// Total Vent Area (Sq mtr)
}

double vent_calculation::FSSA()
{
	return FSSA_Area;			// Pressure Relief Vent Area
}

/*
     * @method for FIA Vent Area
     * @param temperature takes a double for Temperature in Fahrenheit
     * @param spec_vol_extinguishant takes a double for Specific vapour volume of air given in (Cubic meters/Kg)
     * @param room_strength takes a double for Room Strength in Pascals
     * @param flooding_factor takes a double for flooding factor in percentage
     * @param mass_flow_rate takes a double for Mass flow rate of extinguishant in (Kg/seconds)
     * @param pressure_excur takes a double for Pressure Exceurion in range of (0,1)
     * @param neg_press_excur takes a double for Negative Pressure Exceurion in range of (0,1,2)
     * @param total_vent_area takes a double for Total Vent Area in meter^2
     */

double vent_calculation::get_FIA_vent_area( double temperature , double spec_vol_ext , double room_strength, double mass_flow_rate , double pressure_excur ,
                                            double neg_press_excur, double total_vent_area ) {
    cout << "get_FIA_vent_area agent index =" << agent_index << endl;
    if (agent_index == 1) {                            // Non Liquefiable Agent

        double spec_vapvol_mix;                        // Specific Vapour Volume of Homogeneous
        double K1 = 0.773824;
        double K2 = 0.002832967;
        double spec_vapvol_air = K1 + (K2 * temperature);

        spec_vapvol_mix = ((design_concentration * spec_vol_ext) / 100) +
                          (((100 - design_concentration) / 100) * spec_vapvol_air);

        FIA_Area = (mass_flow_rate * spec_vol_ext) / sqrt(room_strength * spec_vapvol_mix);
        return FIA_Area;

    } else if (agent_index == 0) {                    // Liquefiable Agent

        if (pressure_excur == 0) {
            /*
             * calculating for agent type HFC-23
             */
            if (discharge_time >= 6 && discharge_time <= 10) {
                if (design_concentration >= 18 && design_concentration <= 30) {
                    if (rel_humidity >= 20 && rel_humidity <= 80) {

                        double pos_pressure_excur =
                                pow((0.08827 *
                                     ((total_vent_area / spec_vol_ext) * (discharge_time / design_concentration))),
                                    -1.165) * (0.81 + 0.51 * (rel_humidity / 100));

                        if (pos_pressure_excur <= -1400) {

                        } else {
                            return VENT_AREA_OK;
                        }

                        double pos_total_vent_area = 0.12384 * (design_concentration / discharge_time) * spec_vol_ext *
                                                     pow((pos_pressure_excur / 0.81 + 0.51 * (rel_humidity / 100)),
                                                         -0.8587);

                        return pos_total_vent_area;
                    } else {
                        /*
                        * Relative Humidity is outside of valid interval [20.. 80]
                        */
                        return REL_HUMIDITY_20_80;
                    }
                } else {
                    /*
                    * Agent concentration is outside of valid interval [18.. 30s]
                   */
                    return AGENT_CONCEN_18_30;
                }
            } else {
                /*
                * Discharge time is outside of valid interval [6.. 10s]
                */
                return DIS_TIME_6_10;
            }
        } else if (pressure_excur == 1) {

            if (neg_press_excur == 0) {
                /*
                 * calculating for agent type FK-5-1-12
                 */
                if (discharge_time >= 6 && discharge_time <= 10) {
                    if (design_concentration >= 4.2 && design_concentration <= 6.0) {
                        if (rel_humidity >= 20 && rel_humidity <= 80) {
                            double pos_pressure_excur = pow((0.042649 * ((total_vent_area / encl_volume) *
                                                                         (discharge_time / design_concentration))),
                                                            -1.0334) * (0.81 + 0.51 * (rel_humidity / 100));
                            double neg_pressure_excur = pow((0.32170 * ((total_vent_area / encl_volume) *
                                                                        (discharge_time / design_concentration))),
                                                            -1.0318) * (1.68 - 1.79 * (rel_humidity / 100));

                            if (pos_pressure_excur <= 240) {

                            } else if (neg_pressure_excur <= -1200) {

                            } else {
                                return VENT_AREA_OK;
                            }
                            double pos_vent_area = 0.04678 * (design_concentration / discharge_time) * spec_vol_ext *
                                                   pow((pos_pressure_excur / 0.81 + 0.51 * (rel_humidity / 100)),
                                                       -0.9677);
                            double neg_vent_area = 0.04589 * (design_concentration / discharge_time) * spec_vol_ext *
                                                   pow((neg_pressure_excur / 1.68 - 1.79 * (rel_humidity / 100)),
                                                       -0.9692);

                            double req_vent_area = fmax( pos_vent_area , neg_vent_area );
                            return req_vent_area;
                        } else {
                            /*
                            * Relative Humidity is outside of valid interval [20.. 80]
                            */
                            return REL_HUMIDITY_20_80;
                        }
                    } else {
                        /*
                        * Agent concentration is outside of valid interval [4.2.. 6.0s]
                       */
                        return AGENT_CONCEN_18_30;
                    }
                } else {
                    /*
                    * Discharge time is outside of valid interval [6.. 10s]
                    */
                    return DIS_TIME_6_10;
                }

            } else if (neg_press_excur == 1) {

                /*
                 * calculating for agent type HFC-227-ea
                 */
                if (discharge_time >= 6 && discharge_time <= 10) {
                    if (design_concentration >= 6.25 && design_concentration <= 10.25) {
                        if (rel_humidity >= 20 && rel_humidity <= 80) {
                            double pos_pressure_excur = (48.359 * (4.2 * log((spec_vol_ext * design_concentration) /
                                                                             (total_vent_area * discharge_time)) -
                                                                   27.922) * (0.81 + 0.51 * (rel_humidity / 100)));
                            double neg_pressure_excur = (46.444 * (9.41 * log((spec_vol_ext * design_concentration) /
                                                                              (total_vent_area * discharge_time)) -
                                                                   62.76) * (1.68 - 1.79 * (rel_humidity / 100)));

                            cout << "pos_pressure_excur  " << pos_pressure_excur << endl;
                            cout << "neg_pressure_excur " << neg_pressure_excur << endl;

                            if (pos_pressure_excur <= 380 || neg_pressure_excur <= -1000) {

                                double pos_vent_area = 0.00130 * (design_concentration / discharge_time) * spec_vol_ext *
                                                       exp(-0.00497 * pos_pressure_excur / 0.81 +
                                                           0.51 * (rel_humidity / 100));
                                double neg_vent_area = 0.00127 * (design_concentration / discharge_time) * spec_vol_ext *
                                                       exp(-0.00222 * neg_pressure_excur / 1.68 -
                                                           1.79 * (rel_humidity / 100));

                                cout << endl;
                                cout << "pos_vent_area  " << pos_vent_area << endl;
                                cout << "neg_vent_area " << neg_vent_area << endl;
                                double req_vent_area = fmax( pos_vent_area , neg_vent_area );
                                return req_vent_area;

                            } else {
                                return VENT_AREA_OK;
                            }

                        } else {
                            /*
                            * Relative Humidity is outside of valid interval [20.. 80]
                            */
                            return REL_HUMIDITY_20_80;
                        }
                    } else {
                        /*
                        * Agent concentration is outside of valid interval [4.2.. 6.0s]
                       */
                        return AGENT_CONCEN_625_105;
                    }
                } else {
                    /*
                    * Discharge time is outside of valid interval [6.. 10s]
                    */
                    return DIS_TIME_6_10;
                }

            } else if (neg_press_excur == 2) {
                /*
                 * calculating for agent type HFC-125
                 */
                if (discharge_time >= 6 && discharge_time <= 10) {
                    if (design_concentration >= 8.0 && design_concentration <= 10.5) {
                        if (rel_humidity >= 20 && rel_humidity <= 80) {
                            double pos_pressure_excur =
                                    pow((0.045349 *
                                         ((total_vent_area / encl_volume) * (discharge_time / design_concentration))),
                                        -1.037) * (0.81 + 0.51 * (rel_humidity / 100));
                            double neg_pressure_excur =
                                    pow((0.03949 *
                                         ((total_vent_area / encl_volume) * (discharge_time / design_concentration))),
                                        -1.039) * (1.68 - 1.79 * (rel_humidity / 100));
                            if( pos_pressure_excur <= 480){

                            } else if( neg_pressure_excur <= -480 ){

                            } else {
                                return VENT_AREA_OK;
                            }

                            double pos_vent_area = 0.050 * (design_concentration / discharge_time) * spec_vol_ext *
                                                   pow(pos_pressure_excur / 0.81 + 0.51 * (rel_humidity / 100), -0.964);
                            double neg_vent_area = 0.04589 * (design_concentration / discharge_time) * spec_vol_ext *
                                                   pow(neg_pressure_excur / 1.68 - 1.79 * (rel_humidity / 100),
                                                       -0.9622);
                            cout << endl;
                            cout << "pos_vent_area pressure_excur 2" << pos_vent_area << endl;
                            cout << "neg_vent_area " << neg_vent_area << endl;
                            double req_vent_area = fmax( pos_vent_area , neg_vent_area );
                            return req_vent_area;
                        } else {
                            /*
                            * Relative Humidity is outside of valid interval [20.. 80]
                            */
                            return REL_HUMIDITY_20_80;
                        }
                    } else {
                        /*
                        * Agent concentration is outside of valid interval [8.0.. 10.5s]
                       */
                        return AGENT_CONCEN_8_105;
                    }
                } else {
                    /*
                    * Discharge time is outside of valid interval [6.. 10s]
                    */
                    return DIS_TIME_6_10;
                }
            }
        }
    }
}

/*
 * Method for FSSA Vent Area
 * @param pressure_limit takes a double value for Enclosure pressure Limit in Pascal
 * @param hd_index takes a int value for Hardware index
 * @param ext_vent_area takes a double value for Existing vent area in meter^2
 * @param safety_factor_area takes a double value for Safety factor vent area
 */

double vent_calculation::get_FSSA_vent_area(double pressure_limit , int hw_index , double ext_vent_area , double safety_factor_area )
{
    if(agent_index == 1){

        if(design_concentration > 4.2 && design_concentration < 6){

            if(discharge_time > 6 && discharge_time <10){
                bool evaflag = false;
                if(ext_vent_area > 0){

                    double pos_pressure = (467.6 + 2.969 * (rel_humidity)) * pow(( ext_vent_area  *   pow(10,4)/  encl_volume * discharge_time  / design_concentration ), -1.0334 );
                    double neg_pressure = (7251 - 77.29 * (rel_humidity)) * pow(( ext_vent_area  *   pow(10,4) /  encl_volume * discharge_time  / design_concentration  ), -1.0318 );

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
                                return VENT_AREA_OK;
                            }
                        }
                    }
                }

                double pos_vent_area = ( 468.1 * encl_volume * safety_factor_area * design_concentration ) / discharge_time * pow((pressure_limit / ( 0.8136 + 0.005166 * (rel_humidity))), -0.9677 );
                double neg_vent_area = ( 3433 * encl_volume * safety_factor_area * design_concentration) / discharge_time * pow((pressure_limit / ( 1.6305 - 0.01738 * (rel_humidity))), -0.9692 );

                double pos_pressure = (467.6 + 2.969 * (rel_humidity) ) * pow((pos_vent_area/encl_volume * discharge_time / design_concentration), -1.0334);
                double neg_pressure = (7251 - 77.29 * (rel_humidity) ) * pow((neg_vent_area/encl_volume * discharge_time / design_concentration) , -1.0318);

                if(pos_pressure > 239){
                    return POS_PRESSURE_239;
                } else  if (neg_pressure > 1197){
                    return NEG_PRESSURE_1197;
                } else {

                    pos_vent_area = pos_vent_area * pow( 10, -4 ) - (ext_vent_area );
                    neg_vent_area = neg_vent_area * pow( 10, -4 ) - (ext_vent_area) ;

                    double req_vent_area = fmax(pos_vent_area,neg_vent_area);

                    return req_vent_area;
                }

            } else {
               /*
                * Discharge time is outside of valid interval [6.. 10s]
                */
                return DIS_TIME_6_10;
            }

        } else {
            /*
             * Agent concentration is outside of valid interval [6.. 10s]
             */
            return AGENT_CONCEN_6_10;
        }

    } else if ( agent_index == 2 ) {

        if( design_concentration >= 6.25 && design_concentration < 10.5 ){

            if( discharge_time > 6 && discharge_time < 10 ){
                bool evaflag = false;
                if( ext_vent_area > 0 ){
                    double pos_pressure = ( 415.9 + 2.64 * ( rel_humidity ) ) *  ( 1 - 0.3896  * log((ext_vent_area)* pow(10,4)/  encl_volume * discharge_time  / design_concentration ) );
                    double neg_pressure = ( 1925 - 20.52 * ( rel_humidity ) ) * ( 1 - 0.3935  * log((ext_vent_area )* pow(10,4)/  encl_volume * discharge_time  / design_concentration ) );

                    if( pos_pressure > pressure_limit || neg_pressure > pressure_limit ){
                        evaflag = true;
                    } else {
                        if( pos_pressure > 383 ){
                            evaflag = true;
                        } else if ( neg_pressure > 958 ){
                                evaflag = true;
                            } else {
                                cout << "Existing vent Equivalent leakage area is sufficient " << endl;
                                /*
                                 * Return code 0 for existing leakage area is sufficient
                                 */
                                return VENT_AREA_OK;
                            }

                    }

                    double pos_vent_area = (13.02 * encl_volume * safety_factor_area * design_concentration / discharge_time ) * exp( - pressure_limit / (162.1+1.029 * (rel_humidity)));

                    double neg_vent_area = (12.69 * encl_volume * safety_factor_area * design_concentration / discharge_time ) * exp( - pressure_limit / (757.1-8.072 * (rel_humidity)));

                    pos_pressure = (415.9 + 2.64 * ( rel_humidity )) * (1-0.3896 * log(pos_vent_area/ encl_volume * discharge_time / design_concentration));

                    neg_pressure = (1925 - 20.52 * ( rel_humidity )) * (1-0.3935 * log(neg_vent_area/encl_volume * discharge_time / design_concentration));

                if(pos_pressure > 383){
                    cout <<  "Positive pressure is higher than limit 383 " << endl;
                    /*
                     * Fatal Return code type 1
                     */
                    return POS_PRESSURE_383;
                } else if (neg_pressure > 958){
                        cout << "Negative pressure is higher than limit 958 " << endl;
                        /*
                         * Fatal Return code type 2
                         */
                        return NEG_PRESSURE_958;
                    }

                    pos_vent_area = pos_vent_area * pow( 10, -4 ) - ext_vent_area ;
                    neg_vent_area = neg_vent_area * pow( 10, -4 ) - ext_vent_area ;
                    double req_vent_area = fmax( pos_vent_area , neg_vent_area );

                    return req_vent_area;
             }
            } else {
                /*
                 * Discharge time is outside of valid interval [6.. 10s]
                 */
                return DIS_TIME_6_10;
            }

        } else {
            /*
             * Agent concentration is outside of valid interval [6.25.. 10.5s]
             */
            return AGENT_CONCEN_625_105;
        }

    } else if ( agent_index == 3 ){

        if( hw_index == 4 ) {

            if ( design_concentration >= 8 && design_concentration < 10.5 ) {

                if ( discharge_time > 6 && discharge_time < 10 ) {

                    if ( ext_vent_area > 0 ) {

                        double pos_pressure = ( 508.7 + 3.23 * ( rel_humidity )) *  pow(( ext_vent_area  *   pow(10,4) /  encl_volume * discharge_time  / design_concentration  ) , -1.037 );
                        double neg_pressure = ( 980.3 - 10.45 * ( rel_humidity )) * pow(( ext_vent_area  *  pow(10,4)  /  encl_volume * discharge_time  / design_concentration  ) , -1.039 );
                        bool positive_flag = false;

                        if ( pos_pressure > pressure_limit || neg_pressure > pressure_limit ) {

                        } else {
                            if ( pos_pressure > 1479 ) {

                            } else if ( neg_pressure > 479 ) {

                            } else {
                                cout << "Existing vent (Equivalent leakage) area is sufficient" << endl;
                                return VENT_AREA_OK;
                            }
                        }
                    }

                    double pos_vent_area = ( 500.3 * encl_volume * safety_factor_area * design_concentration ) / discharge_time * pow((pressure_limit / ( 0.8056 + 0.005115 * (rel_humidity))), -0.964 );
                    double neg_vent_area = ( 458.3 * encl_volume * safety_factor_area * design_concentration) / discharge_time * pow((pressure_limit / (1.6809 - 0.0179 * (rel_humidity))), -0.9622 );

                    double pos_pressure = ( 508.7 + 3.23 * ( rel_humidity) ) * pow(( pos_vent_area / encl_volume* discharge_time / design_concentration ), -1.037);
                    double neg_pressure = ( 980.3 - 10.45 * ( rel_humidity) ) * pow(( neg_vent_area / encl_volume* discharge_time / design_concentration ), -1.039);

                    if (pos_pressure > 1479) {
                        cout << "Positive pressure is higher than limit 1479" << endl;
                        return POS_PRESSURE_1479;
                    } else if (neg_pressure > 479) {
                        cout << "Negative pressure is higher than limit 479" << endl;
                        return NEG_PRESSURE_479;
                    }

                    pos_vent_area = (pos_vent_area * pow( 10, -4 )) - ext_vent_area ;
                    neg_vent_area = neg_vent_area * pow( 10, -4 ) - ext_vent_area ;

                    double req_vent_area = fmax( pos_vent_area , neg_vent_area );
                    return req_vent_area;

                } else {
                    /*
                     * Discharge Time is outside of valid interval [6 .. 10s]
                     */
                    return DIS_TIME_6_10;
                }
            } else {
                /*
                 * Agent concentration is outside of valid interval [8 .. 10%]
                 */
                return AGENT_CONCEN_8_10;
            }
        } else {
            /*
             * Agent HFC-125 can be calculated for Fike hardware only
             */
            return AGENT_FIKE_HFC125;
        }

    } else if ( agent_index == 4 ) {

        if( hw_index == 2 || hw_index == 3 ) {
            if ( design_concentration >= 18 && design_concentration < 30 ) {
                if ( discharge_time > 6 && discharge_time < 10 ) {
                    if ( ext_vent_area > 0 ) {

                        double pos_pressure = ( 3218 + 20.43 * ( rel_humidity )) * pow(( ext_vent_area  *   pow(10,4) /  encl_volume * discharge_time  / design_concentration  ), -1.165 );
                        bool positive_flag = false;
                        if ( pos_pressure > pressure_limit ) {
                            positive_flag = true;

                        } else if ( pos_pressure > 1437 ) {
                            positive_flag = true;
                        } else {
                           return VENT_AREA_OK;
                        }
                    }
                    double pos_vent_area = ((1239 * encl_volume * safety_factor_area * design_concentration)/ discharge_time) * pow(pressure_limit /(0.8056+0.005115*(rel_humidity)),(-0.8587));
                    double pos_pressure =  ( 3218 + 20.43 * ( rel_humidity )) * pow(( pos_vent_area  /  encl_volume * discharge_time / design_concentration ), -1.165 );

                    if (pos_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return POS_PRESSURE_958;
                    }
                    double req_vent_area = (pos_vent_area * pow( 10, -4 )) - ext_vent_area ;
                    return req_vent_area;

                } else {
                    /*
                     * Discharge Time is outside of valid interval [6 .. 10]
                     */
                    return DIS_TIME_6_10;
                }
            } else {
                /*
                 * Agent concentration is outside of valid interval [18 .. 30 %]
                 */
                return AGENT_CONCEN_18_30;
            }
        } else {
            /*
             * Agent HFC-23 can be calculated for Kiddie or Fenwal hardware only
             */
            return AGENT_KID_FEN_HFC23;
        }

    } else if ( agent_index == 5 || agent_index == 7 ) {

        if( hw_index == 2 || hw_index == 3 || hw_index == 5  ) {
            if ( design_concentration >= 37 && design_concentration < 50 ) {
                if ( discharge_time > 30 && discharge_time < 60 ) {
                    if ( ext_vent_area > 0 ) {

                        double pos_pressure =  12875 * pow(( ext_vent_area  *   pow(10,4)/  encl_volume * discharge_time  / design_concentration ) , -1.089 );
                        bool positive_flag = false;

                        if ( pos_pressure > pressure_limit ) {
                            positive_flag = true;

                        } else if ( pos_pressure > 958 ) {
                            positive_flag = true;
                        } else {
                            /*
                             * existing area is sufficient
                             */
                            return VENT_AREA_OK;
                        }
                    }
                    double pos_vent_area =  5948 * encl_volume * safety_factor_area * design_concentration /  discharge_time * pow(pressure_limit , -0.9184 );
                    double pos_pressure = 12875 * pow( (pos_vent_area / encl_volume  * discharge_time / design_concentration ), -1.089);

                    if (pos_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return POS_PRESSURE_958;
                    }
                    double req_vent_area = (pos_vent_area * pow( 10, -4 )) - ext_vent_area;
                    return req_vent_area;

                } else {
                    /*
                     * Discharge Time is outside of valid interval [30 .. 60s]
                     */
                    return DIS_TIME_30_60;
                }
            } else {
                /*
                 * Agent concentration is outside of valid interval [37 .. 50 %]
                 */
                return AGENT_CONCEN_37_50;
            }
        } else {
            /*
             * Agent IG-55PI or IG-100 can be calculated for kiddie, Fenwal or Chemetron hardware only
             */
            return AGENT_KID_FEN_CHEM_55PI100;
        }

    } else if ( agent_index == 6 ) {

        if( hw_index == 4 ) {
            if ( design_concentration > 34.2 && design_concentration < 50 ) {
                if ( discharge_time > 30 && discharge_time < 60 ) {
                    if ( ext_vent_area > 0 ) {

                        double pos_pressure = 10298 * pow(( ext_vent_area  *   pow(10,4)/  encl_volume * discharge_time  / design_concentration ), -1.285 );
                        bool positive_flag = false;

                        if ( pos_pressure > pressure_limit ) {
                            positive_flag = true;
                        } else if ( pos_pressure > 958 ) {
                            positive_flag = true;
                        } else {
                             /*
                             *  existing area is sufficient
                             */
                            return VENT_AREA_OK;
                        }
                    }
                    double pos_vent_area = 1328 * encl_volume * safety_factor_area * design_concentration /  discharge_time * pow(pressure_limit , -0.7783 );

                    double pos_pressure = 10298  * pow( (pos_vent_area / encl_volume  * discharge_time / design_concentration ), -1.285);

                    if (pos_pressure > 958) {
                        /*
                         * Positive pressure is higher than limit 958
                         */
                        return POS_PRESSURE_958;
                    }

                    double req_vent_area = (pos_vent_area * pow( 10, -4 )) - ext_vent_area;
                    return req_vent_area;

                } else {
                    /*
                     * Discharge Time is outside of valid interval [30 .. 60]
                     */
                    return DIS_TIME_30_60;
                }
            } else {
                /*
                 * Agent concentration is outside of valid interval [34.2 .. 50%]
                 */
                return AGENT_CONCEN_34_50;
            }
        } else {
            /*
             * Agent IG-55PI can be calculated for Fike hardware only
             */
            return AGENT_FIKE_55PI;
        }

    } else if ( agent_index == 8 ){

        if( hw_index == 1 ) {
            if ( design_concentration > 34.2 && design_concentration < 52 ) {
                if ( discharge_time > 30 && discharge_time < 60 ) {
                    if ( ext_vent_area > 0 ) {

                        double pos_pressure = 10462 * pow(( ext_vent_area  *   pow(10,4)/  encl_volume * discharge_time  / design_concentration ),-1.188);
                        bool positive_flag = false;

                        if ( pos_pressure > pressure_limit ) {
                            positive_flag = true;
                        } else if ( pos_pressure > 958 ) {
                            positive_flag = true;
                        } else {
                             /*
                             * code 0 for existing area is sufficient
                             */
                            return VENT_AREA_OK;
                        }
                    }

                    double pos_vent_area = 2416 * encl_volume * safety_factor_area * design_concentration /  discharge_time * pow(pressure_limit , (-0.8417) );
                    double pos_pressure = 10462  * pow( (pos_vent_area / encl_volume  * discharge_time / design_concentration ), -1.188);

                    if (pos_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return POS_PRESSURE_958;
                    }

                    double req_vent_area = (pos_vent_area * pow( 10, -4 )) - ext_vent_area;
                    return req_vent_area;

                } else {
                    /*
                     * "Discharge Time is outside of valid interval [30 .. 60]"
                     */
                    return DIS_TIME_30_60;
                }
            } else {
                /*
                 * Agent concentration is outside of valid interval [34.2 .. 52%]
                 */
                return AGENT_CONCEN_34_52;
            }
        } else {
            /*
             * Agent IG-541PI can be calculated for Ansul / JCI hardware only
             */
            return AGENT_ANSUL_JCI_541;
        }

    }

}




