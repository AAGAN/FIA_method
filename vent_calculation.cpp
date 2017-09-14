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

#define VENT_AREA_OK                                    -1;
#define ERRCODE_POSITIVE_PRESSURE_239                        -2;
#define ERRCODE_NEG_PRESSURE_EXCEEDS_1197               -3;
#define POSITIVE_PRESSURE_958                                -4;
#define POSITIVE_PRESSURE_383                                -5;
#define NEGATIVE_PRESSURE_958                                -6;
#define POSITIVE_PRESSURE_1479                               -7;
#define NEGATIVE_PRESSURE_479                                -8;
#define DIS_TIME_30_60                                  -9;
#define DIS_TIME_6_10                                   -10;
#define AGENT_CONCEN_34_52                              -11;
#define AGENT_CONCEN_34_50                              -12;
#define AGENT_CONCEN_37_50                              -13;
#define AGENT_CONCEN_18_30                              -14;
#define AGENT_CONCEN_8_10                               -15;
#define AGENT_CONCEN_6_10                               -16;
#define AGENT_CONCEN_625_105                            -17;
#define AGENT_ANSUL_JCI_541                             -18;
#define AGENT_FIKE_55PI                                 -19;
#define AGENT_KID_FEN_HFC23                             -20;
#define AGENT_KID_FEN_CHEM_55PI100                      -21;
#define AGENT_FIKE_HFC125                               -22;
#define REL_HUMIDITY_20_80                              -23;
#define AGENT_CONCEN_8_105                              -24;
#define POSITIVE_PRESSURE_240                                -25;
#define NEGATIVE_PRESSURE_1200                               -26;
#define NEGATIVE_PRESSURE_1000                               -27;
#define POSITIVE_PRESSURE_380                                -28;
#define POSITIVE_PRESSURE_239                                -29;
#define NEGATIVE_PRESSURE_1197                               -30;
#define ERRCODE_Agent_IG_55PA_Not_Covered_in_FIA             -31;


double vent_calculation::FIA() {

    return FIA_Area;        // Total Vent Area (Sq mtr)
}

double vent_calculation::FSSA() {
    return FSSA_Area;            // Pressure Relief Vent Area
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

double vent_calculation::get_FIA_vent_area(double peek_mass_flow_rate,int system_technology_index ,double total_agent_mass_cylinder_bank, double temperature) {

    //cout << "extinguishant_agent_index =" <<extinguishant_agent_index << endl;
    switch (extinguishant_agent_index) {
        case 1:
            return getVentAreaFIAforAgentIndex_1();
        case 2:
            return getVentAreaFIAforAgentIndex_2();
        case 3 :
            return getVentAreaFIAforAgentIndex_3();
        case 4:
            return getVentAreaFIAforAgentIndex_4();
        case 5:
            return getVentAreaFIAforAgentIndex_5(system_technology_index , peek_mass_flow_rate , total_agent_mass_cylinder_bank , temperature );
        case 6:
            return ERRCODE_Agent_IG_55PA_Not_Covered_in_FIA;
        case 7:
            return getVentAreaFIAforAgentIndex_7(system_technology_index , peek_mass_flow_rate , total_agent_mass_cylinder_bank , temperature );
        case 8:
            return getVentAreaFIAforAgentIndex_8(system_technology_index , peek_mass_flow_rate , total_agent_mass_cylinder_bank , temperature );

    }
}

double vent_calculation::getVentAreaFIAforAgentIndex_1() {

    if (design_concentration > 4.2 && design_concentration < 6) {
        if (discharge_time > 6 && discharge_time < 10) {
            if (relative_humidity > 20 && relative_humidity < 80) {
                if (existing_vent_area > 0) {

                    double positive_pressure = 0.042649 * (0.81 + 0.51 * (relative_humidity) / 100) *
                                               pow((existing_vent_area / enclosure_volume * discharge_time /
                                                    design_concentration),
                                                   -1.0334);
                    double negative_pressure = 0.3217 * (1.68 - 1.79 * (relative_humidity) / 100) *
                                               pow((existing_vent_area / enclosure_volume * discharge_time /
                                                    design_concentration),
                                                   -1.0318);
                    //cout << "positive_pressure="<<positive_pressure <<endl;
                    //cout << "negative_pressure="<<negative_pressure <<endl;
                    if (positive_pressure > pressure_limit || negative_pressure > pressure_limit) {
                        return getVentAreaFIAIndex_1();
                    } else {
                        if (positive_pressure > 240) {
                            return getVentAreaFIAIndex_1();
                        } else {
                            if (negative_pressure > 1200) {
                                return getVentAreaFIAIndex_1();
                            } else {
                                cout << "Existing vent Equivalent leakage area is sufficient" << endl;
                                return VENT_AREA_OK;
                            }
                        }
                    }
                }
            } else {
                /*
                 * relative_humidity is outside of valid interval [20.. 80s]
                 */
                return relative_humidity;
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
}


double vent_calculation::getVentAreaFIAforAgentIndex_2() {

    if (design_concentration >= 6.25 && design_concentration < 10.5) {
        if (discharge_time > 6 && discharge_time < 10) {
            if (relative_humidity > 20 && relative_humidity < 80) {
                if (existing_vent_area > 0) {

                    double positive_pressure = 48.359 * (0.81 + 0.51 * (relative_humidity) / 100) *
                            (4.2 * log(enclosure_volume / (existing_vent_area) * design_concentration  / discharge_time
                                                    ) -27.922);
                    double negative_pressure = 46.444 * (1.68 - 1.79 * (relative_humidity) / 100) *
                                               (9.41 * log(enclosure_volume /(existing_vent_area)   * design_concentration  / discharge_time
                                                    ) -62.76);

                    //cout <<"positive_pressure =" << positive_pressure <<endl;
                    //cout <<"negative_pressure =" << negative_pressure <<endl;
                    if (positive_pressure > pressure_limit || negative_pressure > pressure_limit) {
                        return getVentAreaFIAIndex_2();
                    } else {
                        if (positive_pressure > 480) {
                            return getVentAreaFIAIndex_2();
                        } else {
                            if (negative_pressure > 480) {
                                return getVentAreaFIAIndex_2();
                            } else {
                                cout << "Existing vent Equivalent leakage area is sufficient" << endl;
                                return VENT_AREA_OK;
                            }
                        }
                    }
                }
            } else {
                /*
                 * relative_humidity is outside of valid interval [20.. 80s]
                 */
                return relative_humidity;
            }
        } else {
            /*
             * Discharge time is outside of valid interval [6.. 10s]
             */
            return DIS_TIME_6_10;
        }
    } else {
        /*
         * Agent concentration is outside of valid interval [8.. 10.5s]
         */
        return AGENT_CONCEN_6_10;
    }
}

double vent_calculation::getVentAreaFIAforAgentIndex_3() {

    if (design_concentration >= 8 && design_concentration < 10.5) {
        if (discharge_time > 6 && discharge_time < 10) {
            if (relative_humidity > 20 && relative_humidity < 80) {
                if (existing_vent_area > 0) {

                    double positive_pressure = 0.045349 * (0.81 + 0.51 * (relative_humidity) / 100) *
                                               pow(((existing_vent_area) / enclosure_volume * discharge_time /
                                                    design_concentration), -1.037);
                    double negative_pressure = 0.03949 * (1.68 - 1.79 * (relative_humidity) / 100) *
                                               pow((existing_vent_area / enclosure_volume * discharge_time /
                                                    design_concentration), -1.039);

                    //cout <<"positive_pressure =" << positive_pressure <<endl;
                    //cout <<"negative_pressure =" << negative_pressure <<endl;
                    if (positive_pressure > pressure_limit || negative_pressure > pressure_limit) {
                        return getVentAreaFIAIndex_3();
                    } else {
                        if (positive_pressure > 239) {
                            return getVentAreaFIAIndex_3();
                        } else {
                            if (negative_pressure > 1197) {
                                return getVentAreaFIAIndex_3();
                            } else {
                                cout << "Existing vent Equivalent leakage area is sufficient" << endl;
                                return VENT_AREA_OK;
                            }
                        }
                    }
                }
            } else {
                /*
                 * relative_humidity is outside of valid interval [20.. 80s]
                 */
                return relative_humidity;
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
}


double vent_calculation::getVentAreaFIAforAgentIndex_4() {

    if (design_concentration >= 18 && design_concentration < 30) {
        if (discharge_time > 6 && discharge_time < 10) {
            if (relative_humidity > 20 && relative_humidity < 80) {
                if (existing_vent_area > 0) {

                    double positive_pressure = 0.08827 * (0.81 + 0.51 * (relative_humidity) / 100) *
                                               pow((existing_vent_area / enclosure_volume * discharge_time /
                                                    design_concentration), -1.165);
                    //cout << "positive_pressure=" << positive_pressure << endl;
                    if (positive_pressure > pressure_limit) {
                        return getVentAreaFIAIndex_4();
                    } else if (positive_pressure > 140) {
                        return getVentAreaFIAIndex_4();
                    } else {
                        cout << "Existing vent Equivalent area is sufficient" << endl;
                        return VENT_AREA_OK;
                    }
                }
            } else {
                /*
                 * relative_humidity is outside of valid interval [20.. 80s]
                 */
                return relative_humidity;
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
}

double vent_calculation::getVentAreaFIAforAgentIndex_5( int system_technology_index, double peak_mass_flow_rate ,double total_agent_mass_cylinder_bank, double temperature ) {


    //cout <<"agent_volume_at_given_condtion =" << agent_volume_at_given_condtion <<endl;
    double K1 = 0.773824;
    double K2 = 0.002832967;
    double specific_vapour_vol_air = K1 + (K2 * temperature);

    double agent_volume_at_given_condtion = 0.6598 + 0.00242 * temperature;

    double  specific_volume_of_homogenious_mixture = design_concentration * agent_volume_at_given_condtion /100 + (100-design_concentration)/100  * specific_vapour_vol_air;
    double required_vent_area = 0.0;
    //cout <<"specific_volume_of_homogenious_mixture =" << specific_volume_of_homogenious_mixture <<endl;

    if(system_technology_index == 1){
        required_vent_area = safety_factor_vent_area * peak_mass_flow_rate * agent_volume_at_given_condtion / sqrt( pressure_limit * specific_volume_of_homogenious_mixture);
        //cout <<"required_vent_area =" << required_vent_area <<endl;
    } else {
        double constant_mass_flow = total_agent_mass_cylinder_bank / discharge_time;
        cout <<"constant_mass_flow =" << constant_mass_flow <<endl;
        required_vent_area = safety_factor_vent_area * constant_mass_flow * agent_volume_at_given_condtion / sqrt(pressure_limit * specific_volume_of_homogenious_mixture);
        //cout <<"required_vent_area =" << required_vent_area <<endl;
    }

    required_vent_area = required_vent_area - existing_vent_area;

    return required_vent_area;

}



double vent_calculation::getVentAreaFIAforAgentIndex_7( int system_technology_index, double peak_mass_flow_rate ,double total_agent_mass_cylinder_bank ,double temperature ) {

    double agent_volume_at_given_condtion = 0.7997 + 0.00293 * temperature;
    double K1 = 0.773824;
    double K2 = 0.002832967;
    double specific_vapour_vol_air = K1 + (K2 * temperature);

    //cout << "agent_volume_at_given_condtion ="<< agent_volume_at_given_condtion<<endl;
    double  specific_volume_of_homogenious_mixture = design_concentration * agent_volume_at_given_condtion /100 + (100-design_concentration)/100  * specific_vapour_vol_air;
    double req_vent_area = 0.0;
    //cout << "specific_volume_of_homogenious_mixture ="<< specific_volume_of_homogenious_mixture<<endl;
    if(system_technology_index == 1){
        req_vent_area = safety_factor_vent_area * peak_mass_flow_rate * agent_volume_at_given_condtion / sqrt( pressure_limit * specific_volume_of_homogenious_mixture);
        //cout << "req_vent_area ="<< req_vent_area<<endl;
    } else {
        double constant_mass_flow = total_agent_mass_cylinder_bank / discharge_time;
        req_vent_area = safety_factor_vent_area * constant_mass_flow * agent_volume_at_given_condtion / sqrt(pressure_limit * specific_volume_of_homogenious_mixture);
    }

    req_vent_area = req_vent_area - existing_vent_area;

    return req_vent_area;

}


double vent_calculation::getVentAreaFIAforAgentIndex_8( int system_technology_index, double peak_mass_flow_rate ,double total_agent_mass_cylinder_bank , double temperature) {

    double K1 = 0.773824;
    double K2 = 0.002832967;
    double specific_vapour_vol_air = K1 + (K2 * temperature);

    double agent_volume_at_given_condtion = 0.65799 + 0.00239 * temperature;

    double  specific_volume_of_homogenious_mixture = design_concentration * agent_volume_at_given_condtion /100 + (100-design_concentration)/100  * specific_vapour_vol_air;
    double required_vent_area = 0.0;

    if(system_technology_index == 1){
        required_vent_area = safety_factor_vent_area * peak_mass_flow_rate * agent_volume_at_given_condtion / sqrt( pressure_limit * specific_volume_of_homogenious_mixture);
    } else {
        double constant_mass_flow = total_agent_mass_cylinder_bank / discharge_time;
        required_vent_area = safety_factor_vent_area * constant_mass_flow * agent_volume_at_given_condtion / sqrt(pressure_limit * specific_volume_of_homogenious_mixture);
    }

    required_vent_area = required_vent_area - existing_vent_area;

    return required_vent_area;

}

/*
 * Method for FSSA Vent Area
 * @param pressure_limit takes a double value for Enclosure pressure Limit in Pascal
 * @param hd_index takes a int value for Hardware index
 * @param existing_vent_area takes a double value for Existing vent area in meter^2
 * @param safety_factor_area takes a double value for Safety factor vent area
 */

double vent_calculation::get_FSSA_vent_area(int hw_index, double safety_factor_area) {
    switch (extinguishant_agent_index) {
        case 1:
            return getVentAreaFSSAforHWAgentIndex_1();
        case 2:
            return getVentAreaFSSAforHWAgentIndex_2();
        case 3: {
            if (hw_index == 4) {
                return getVentAreaFSSAforHWAgentIndex_3();
            } else {
                /*
                 * Agent HFC-125 can be calculated for Fike hardware only
                 */
                return AGENT_FIKE_HFC125;
            }
        }
        case 4:
            if (hw_index == 2 || hw_index == 3) {
                return getVentAreaFSSAforHWAgentIndex_4();
            } else {
                /*
                 * Agent HFC-23 can be calculated for Kiddie or Fenwal hardware only
                 */
                return AGENT_KID_FEN_HFC23;
            }
        case 5 :
            if (hw_index == 2 || hw_index == 3 || hw_index == 5) {
                return getVentAreaFSSAforHWAgentIndex_5_7();
            } else {
                /*
                 * Agent IG-55PI or IG-100 can be calculated for kiddie, Fenwal or Chemetron hardware only
                 */
                return AGENT_KID_FEN_CHEM_55PI100;
            }
        case 6 :
            if (hw_index == 4) {
                return getVentAreaFSSAforHWAgentIndex_6();
            } else {
                /*
                 * Agent IG-55PI can be calculated for Fike hardware only
                 */
                return AGENT_FIKE_55PI;
            }
        case 7 :
            if (hw_index == 2 || hw_index == 3 || hw_index == 5) {
                return getVentAreaFSSAforHWAgentIndex_5_7();
            } else {
                /*
                 * Agent IG-55PI or IG-100 can be calculated for kiddie, Fenwal or Chemetron hardware only
                 */
                return AGENT_KID_FEN_CHEM_55PI100;
            }
        case 8:
            if (hw_index == 1) {
                return getVentAreaFSSAforHWAgentIndex_8();
            } else {
                /*
                 * Agent IG-541PI can be calculated for Ansul / JCI hardware only
                 */
                return AGENT_ANSUL_JCI_541;
            }
    }
}

double vent_calculation::getVentAreaFSSAforHWAgentIndex_1() {

    if (design_concentration > 4.2 && design_concentration < 6) {
        if (discharge_time > 6 && discharge_time < 10) {
            bool evaflag = false;
            if (existing_vent_area > 0) {

                double positive_pressure = (467.6 + 2.969 * (relative_humidity)) *
                                           pow((existing_vent_area * pow(10, 4) / enclosure_volume * discharge_time /
                                                design_concentration), -1.0334);
                double negative_pressure = (7251 - 77.29 * (relative_humidity)) *
                                           pow((existing_vent_area * pow(10, 4) / enclosure_volume * discharge_time /
                                                design_concentration), -1.0318);
                if (positive_pressure > pressure_limit || negative_pressure > pressure_limit) {
                    return getVentAreaFSSAIndex_1();
                } else {
                    if (positive_pressure > 239) {
                        return getVentAreaFSSAIndex_1();
                    } else {
                        if (negative_pressure > 1197) {
                            return getVentAreaFSSAIndex_1();
                        } else {
                            cout << "Existing vent Equivalent leakage area is sufficient" << endl;
                            return VENT_AREA_OK;
                        }
                    }
                }
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
}


double vent_calculation::getVentAreaFSSAforHWAgentIndex_2() {

    if (design_concentration >= 6.25 && design_concentration < 10.5) {
        if (discharge_time > 6 && discharge_time < 10) {
            if (existing_vent_area > 0) {
                double positive_pressure = (415.9 + 2.64 * (relative_humidity)) * (1 - 0.3896 *
                                                                                       log((existing_vent_area) *
                                                                                           pow(10, 4) /
                                                                                           enclosure_volume *
                                                                                           discharge_time /
                                                                                           design_concentration));
                double negative_pressure = (1925 - 20.52 * (relative_humidity)) * (1 - 0.3935 *
                                                                                       log((existing_vent_area) *
                                                                                           pow(10, 4) /
                                                                                           enclosure_volume *
                                                                                           discharge_time /
                                                                                           design_concentration));

                if (positive_pressure > pressure_limit || negative_pressure > pressure_limit) {
                    return getVentAreaFSSAIndex_2();
                } else {
                    if (positive_pressure > 383) {
                        return getVentAreaFSSAIndex_2();
                    } else if (negative_pressure > 958) {
                        return getVentAreaFSSAIndex_2();
                    } else {
                        cout << "Existing vent Equivalent leakage area is sufficient " << endl;
                        /*
                         * Return code 0 for existing leakage area is sufficient
                         */
                        return VENT_AREA_OK;
                    }
                }
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
}

double vent_calculation::getVentAreaFSSAforHWAgentIndex_3() {

    if (design_concentration >= 8 && design_concentration < 10.5) {
        if (discharge_time > 6 && discharge_time < 10) {
            if (existing_vent_area > 0) {
                double positive_pressure = (508.7 + 3.23 * (relative_humidity)) *
                                           pow((existing_vent_area * pow(10, 4) / enclosure_volume * discharge_time /
                                                design_concentration), -1.037);
                double negative_pressure = (980.3 - 10.45 * (relative_humidity)) *
                                           pow((existing_vent_area * pow(10, 4) / enclosure_volume * discharge_time /
                                                design_concentration), -1.039);
                bool positive_flag = false;

                if (positive_pressure > pressure_limit || negative_pressure > pressure_limit) {
                    return getVentAreaFSSAIndex_3();
                } else {
                    if (positive_pressure > 1479) {
                        return getVentAreaFSSAIndex_3();
                    } else if (negative_pressure > 479) {
                        return getVentAreaFSSAIndex_3();
                    } else {
                        cout << "Existing vent (Equivalent leakage) area is sufficient" << endl;
                        return VENT_AREA_OK;
                    }
                }
            } else {
                return getVentAreaFSSAIndex_3();
            }
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
}

double vent_calculation::getVentAreaFSSAforHWAgentIndex_4() {

    if (design_concentration >= 18 && design_concentration < 30) {
        if (discharge_time > 6 && discharge_time < 10) {
            if (existing_vent_area > 0) {
                double positive_pressure = (3218 + 20.43 * (relative_humidity)) *
                                           pow((existing_vent_area * pow(10, 4) / enclosure_volume * discharge_time /
                                                design_concentration), -1.165);
                bool positive_flag = false;

                if (positive_pressure > pressure_limit || positive_pressure > 1437) {
                    double pos_vent_area =
                            ((1239 * enclosure_volume * safety_factor_vent_area * design_concentration) /
                             discharge_time) *
                            pow(pressure_limit / (0.8056 + 0.005115 * (relative_humidity)), (-0.8587));
                    double positive_pressure = (3218 + 20.43 * (relative_humidity)) *
                                               pow((pos_vent_area / enclosure_volume * discharge_time /
                                                    design_concentration),
                                                   -1.165);
                    if (positive_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return POSITIVE_PRESSURE_958;
                    }
                    double req_vent_area = (pos_vent_area * pow(10, -4)) - existing_vent_area;
                    return req_vent_area;
                } else {
                    return VENT_AREA_OK;
                }
            }
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
}


double vent_calculation::getVentAreaFSSAforHWAgentIndex_5_7() {
    if (design_concentration >= 37 && design_concentration < 50) {
        if (discharge_time > 30 && discharge_time < 60) {
            if (existing_vent_area > 0) {

                double positive_pressure =
                        12875 * pow((existing_vent_area * pow(10, 4) / enclosure_volume * discharge_time /
                                     design_concentration), -1.089);
                bool positive_flag = false;

                if (positive_pressure > pressure_limit || positive_pressure > 958) {
                    double pos_vent_area =
                            5948 * enclosure_volume * safety_factor_vent_area * design_concentration / discharge_time *
                            pow(pressure_limit, -0.9184);
                    double positive_pressure =
                            12875 *
                            pow((pos_vent_area / enclosure_volume * discharge_time / design_concentration), -1.089);

                    if (positive_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return POSITIVE_PRESSURE_958;
                    }
                    double req_vent_area = (pos_vent_area * pow(10, -4)) - existing_vent_area;
                    return req_vent_area;
                } else {
                    /*
                     * existing area is sufficient
                     */
                    return VENT_AREA_OK;
                }
            }
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
}

double vent_calculation::getVentAreaFSSAforHWAgentIndex_6() {

    if (design_concentration > 34.2 && design_concentration < 50) {
        if (discharge_time > 30 && discharge_time < 60) {
            if (existing_vent_area > 0) {

                double positive_pressure =
                        10298 * pow((existing_vent_area * pow(10, 4) / enclosure_volume * discharge_time /
                                     design_concentration), -1.285);
                bool positive_flag = false;

                if (positive_pressure > pressure_limit || positive_pressure > 958) {
                    double pos_vent_area =
                            1328 * enclosure_volume * safety_factor_vent_area * design_concentration / discharge_time *
                            pow(pressure_limit, -0.7783);
                    double positive_pressure =
                            10298 *
                            pow((pos_vent_area / enclosure_volume * discharge_time / design_concentration), -1.285);
                    double req_vent_area = (pos_vent_area * pow(10, -4)) - existing_vent_area;
                    return req_vent_area;
                    if (positive_pressure > 958) {
                        /*
                         * Positive pressure is higher than limit 958
                         */
                        return POSITIVE_PRESSURE_958;
                    }
                } else {
                    /*
                    *  existing area is sufficient
                    */
                    return VENT_AREA_OK;
                }
            }
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

}

double vent_calculation::getVentAreaFSSAforHWAgentIndex_8() {

    if (design_concentration > 34.2 && design_concentration < 52) {
        if (discharge_time > 30 && discharge_time < 60) {
            if (existing_vent_area > 0) {

                double positive_pressure =
                        10462 * pow((existing_vent_area * pow(10, 4) / enclosure_volume * discharge_time /
                                     design_concentration), -1.188);
                bool positive_flag = false;

                if (positive_pressure > pressure_limit || positive_pressure > 958) {
                    double pos_vent_area =
                            2416 * enclosure_volume * safety_factor_vent_area * design_concentration /
                            discharge_time *
                            pow(pressure_limit, (-0.8417));
                    double positive_pressure =
                            10462 *
                            pow((pos_vent_area / enclosure_volume * discharge_time / design_concentration), -1.188);

                    if (positive_pressure > 958) {
                        cout << "Positive pressure is higher than limit 958" << endl;
                        return POSITIVE_PRESSURE_958;
                    }
                    double req_vent_area = (pos_vent_area * pow(10, -4)) - existing_vent_area;
                    return req_vent_area;
                } else {
                    /*
                    * code 0 for existing area is sufficient
                    */
                    return VENT_AREA_OK;
                }
            }
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
}

double vent_calculation::getVentAreaFSSAIndex_3() {


    double pos_vent_area =
            (500.3 * enclosure_volume * safety_factor_vent_area * design_concentration) / discharge_time *
            pow((pressure_limit / (0.8056 + 0.005115 * (relative_humidity))), -0.964);
    double neg_vent_area =
            (458.3 * enclosure_volume * safety_factor_vent_area * design_concentration) / discharge_time *
            pow((pressure_limit / (1.6809 - 0.0179 * (relative_humidity))), -0.9622);

    double positive_pressure = (508.7 + 3.23 * (relative_humidity)) *
                               pow((pos_vent_area / enclosure_volume * discharge_time / design_concentration),
                                   -1.037);
    double negative_pressure = (980.3 - 10.45 * (relative_humidity)) *
                               pow((neg_vent_area / enclosure_volume * discharge_time / design_concentration),
                                   -1.039);

    if (positive_pressure > 1479) {
        cout << "Positive pressure is higher than limit 1479" << endl;
        return POSITIVE_PRESSURE_1479;
    } else if (negative_pressure > 479) {
        cout << "Negative pressure is higher than limit 479" << endl;
        return NEGATIVE_PRESSURE_479;
    }

    pos_vent_area = (pos_vent_area * pow(10, -4)) - existing_vent_area;
    neg_vent_area = neg_vent_area * pow(10, -4) - existing_vent_area;

    double req_vent_area = fmax(pos_vent_area, neg_vent_area);
    return req_vent_area;
}


double vent_calculation::getVentAreaFSSAIndex_1() {

    double pos_vent_area =
            (468.1 * enclosure_volume * safety_factor_vent_area * design_concentration) / discharge_time *
            pow((pressure_limit / (0.8136 + 0.005166 * (relative_humidity))), -0.9677);
    double neg_vent_area =
            (3433 * enclosure_volume * safety_factor_vent_area * design_concentration) / discharge_time *
            pow((pressure_limit / (1.6305 - 0.01738 * (relative_humidity))), -0.9692);

    double positive_pressure = (467.6 + 2.969 * (relative_humidity)) *
                               pow((pos_vent_area / enclosure_volume * discharge_time / design_concentration),
                                   -1.0334);
    double negative_pressure = (7251 - 77.29 * (relative_humidity)) *
                               pow((neg_vent_area / enclosure_volume * discharge_time / design_concentration),
                                   -1.0318);

    if (positive_pressure > 239) {
        return POSITIVE_PRESSURE_239;
    } else if (negative_pressure > 1197) {
        return NEGATIVE_PRESSURE_1197;
    } else {

        pos_vent_area = pos_vent_area * pow(10, -4) - (existing_vent_area);
        neg_vent_area = neg_vent_area * pow(10, -4) - (existing_vent_area);

        double req_vent_area = fmax(pos_vent_area, neg_vent_area);

        return req_vent_area;
    }


//    double pos_vent_area =
//            (500.3 * enclosure_volume * safety_factor_vent_area * design_concentration) / discharge_time *
//            pow((pressure_limit / (0.8056 + 0.005115 * (relative_humidity))), -0.964);
//    double neg_vent_area =
//            (458.3 * enclosure_volume * safety_factor_vent_area * design_concentration) / discharge_time *
//            pow((pressure_limit / (1.6809 - 0.0179 * (relative_humidity))), -0.9622);
//
//    double pos_pressure = (508.7 + 3.23 * (relative_humidity)) *
//                          pow((pos_vent_area / enclosure_volume * discharge_time / design_concentration),
//                              -1.037);
//    double NEGATIVE_PRESSURE = (980.3 - 10.45 * (relative_humidity)) *
//                          pow((neg_vent_area / enclosure_volume * discharge_time / design_concentration),
//                              -1.039);
//
//    if (pos_pressure > 1479) {
//        cout << "Positive pressure is higher than limit 1479" << endl;
//        return POS_PRESSURE_1479;
//    } else if (NEGATIVE_PRESSURE > 479) {
//        cout << "Negative pressure is higher than limit 479" << endl;
//        return NEGATIVE_PRESSURE_479;
//    }
//
//    pos_vent_area = (pos_vent_area * pow(10, -4)) - existing_vent_area;
//    neg_vent_area = neg_vent_area * pow(10, -4) - existing_vent_area;
//
//    double req_vent_area = fmax(pos_vent_area, neg_vent_area);
//    return req_vent_area;
}


double vent_calculation::getVentAreaFSSAIndex_2() {

    double pos_vent_area =
            (13.02 * enclosure_volume * safety_factor_vent_area * design_concentration / discharge_time) *
            exp(-pressure_limit / (162.1 + 1.029 * (relative_humidity)));

    double neg_vent_area =
            (12.69 * enclosure_volume * safety_factor_vent_area * design_concentration / discharge_time) *
            exp(-pressure_limit / (757.1 - 8.072 * (relative_humidity)));

    double positive_pressure =
            (415.9 + 2.64 * (relative_humidity)) * (1 - 0.3896 * log(pos_vent_area / enclosure_volume *
                                                                     discharge_time /
                                                                     design_concentration));

    double negative_pressure =
            (1925 - 20.52 * (relative_humidity)) * (1 - 0.3935 * log(neg_vent_area / enclosure_volume *
                                                                     discharge_time /
                                                                     design_concentration));
    if (positive_pressure > 383) {
        cout << "Positive pressure is higher than limit 383 " << endl;
        /*
         * Fatal Return code type 1
         */
        return POSITIVE_PRESSURE_383;
    } else if (negative_pressure > 958) {
        cout << "Negative pressure is higher than limit 958 " << endl;
        /*
         * Fatal Return code type 2
         */
        return NEGATIVE_PRESSURE_958;
    }
    pos_vent_area = pos_vent_area * pow(10, -4) - existing_vent_area;
    neg_vent_area = neg_vent_area * pow(10, -4) - existing_vent_area;
    double req_vent_area = fmax(pos_vent_area, neg_vent_area);

    return req_vent_area;
}


double vent_calculation::getVentAreaFIAIndex_1() {


    double positive_vent_area =
            (0.04678 * enclosure_volume * safety_factor_vent_area * design_concentration) / discharge_time *
            pow((pressure_limit / (0.81 + 0.51 * (relative_humidity) / 100)), -0.9677);
    double negative_vent_area =
            (0.34309 * enclosure_volume * safety_factor_vent_area * design_concentration) / discharge_time *
            pow((pressure_limit / (1.68 - 1.79 * (relative_humidity) / 100)), -0.9692);

    //cout<<"positive_vent_area= " <<positive_vent_area << endl;
    //cout<< "negative_vent_area = " << negative_vent_area << endl;
    double positive_pressure = 0.042649 * (0.81 + 0.51 * (relative_humidity) / 100) *
                               pow((positive_vent_area / enclosure_volume * discharge_time / design_concentration),
                                   -1.0334);
    double negative_pressure = 0.3217 * (1.68 - 1.79 * (relative_humidity) / 100) *
                               pow((negative_vent_area / enclosure_volume * discharge_time / design_concentration),
                                   -1.0318);

    //cout<<"positive_pressure= " <<positive_pressure << endl;
    //cout<< "negative_pressure = " << negative_pressure << endl;
    if (positive_pressure > 240) {
        cout << "Positive pressure is higher than limit 240 Pa" << endl;
        return POSITIVE_PRESSURE_240;
    } else if (negative_pressure > 1200) {
        cout << "Negative pressure is higher than limit 1200 Pa" << endl;
        return NEGATIVE_PRESSURE_1200;
    }

    positive_vent_area = positive_vent_area - existing_vent_area;
    negative_vent_area = negative_vent_area - existing_vent_area;

    double req_vent_area = fmax(positive_vent_area, negative_vent_area);
    return req_vent_area;
}

double vent_calculation::getVentAreaFIAIndex_2() {


    double positive_vent_area =
            (0.0013 * enclosure_volume * safety_factor_vent_area * design_concentration) / discharge_time *
            exp(-0.00497 * pressure_limit / (0.81 + 0.51 * (relative_humidity) / 100));
    double negative_vent_area =
            (0.00127 * enclosure_volume * safety_factor_vent_area * design_concentration) / discharge_time *
            exp(-0.00222 * pressure_limit / (1.68 - 1.79 * (relative_humidity) / 100));

    //cout << "positive_vent_area = " <<positive_vent_area << endl;
    //cout << "negative_vent_area = " <<negative_vent_area << endl;
    double positive_pressure = 48.359 * (0.81 + 0.51 * (relative_humidity) / 100) * (4.2 *
                                                                                     log((enclosure_volume /
                                                                                          (existing_vent_area) *
                                                                                          design_concentration /
                                                                                          discharge_time)) -
                                                                                     27.922);
    double negative_pressure = 46.444 * (1.68 - 1.79 * (relative_humidity) / 100) * (9.41 *
                                                                                     log((enclosure_volume /
                                                                                          (existing_vent_area) *
                                                                                          design_concentration /
                                                                                          discharge_time)) -
                                                                                     62.76);

    if (positive_pressure > 380) {
        cout << "Positive pressure is higher than limit 380 =" << positive_pressure << endl;
        return POSITIVE_PRESSURE_380;
    } else if (negative_pressure > 1000) {
        cout << "Negative pressure is higher than limit 1000 = " << negative_pressure << endl;
        return NEGATIVE_PRESSURE_1000;
    }

    positive_vent_area = positive_vent_area - existing_vent_area;
    negative_vent_area = negative_vent_area - existing_vent_area;

    double req_vent_area = fmax(positive_vent_area, negative_vent_area);
    return req_vent_area;
}

double vent_calculation::getVentAreaFIAIndex_3() {


    double positive_vent_area =
            (0.05 * enclosure_volume * safety_factor_vent_area * design_concentration) / discharge_time *
            pow((pressure_limit / (0.81 + 0.51 * (relative_humidity) / 100)), -0.964);
    double negative_vent_area =
            (0.045349 * enclosure_volume * safety_factor_vent_area * design_concentration) / discharge_time *
            pow((pressure_limit / (1.6809 - 0.0179 * (relative_humidity) / 100)), -0.9622);

    //cout <<"positive_vent_area =" << positive_vent_area <<endl;
    //cout <<"negative_vent_area =" << negative_vent_area <<endl;

    double positive_pressure = 0.045349 * (0.81 + 0.51 * (relative_humidity) / 100) * pow(positive_vent_area /
                                                                                          (existing_vent_area) *
                                                                                          design_concentration /
                                                                                          discharge_time,
                                                                                          -1.037);
    double negative_pressure = 0.03949 * (1.68 - 1.79 * (relative_humidity) / 100) * pow(negative_vent_area /
                                                                                         (existing_vent_area) *
                                                                                         design_concentration /
                                                                                         discharge_time,
                                                                                         -1.039);

    if (positive_pressure > 480) {
        cout << "Positive pressure is higher than limit 480" << endl;
        return POSITIVE_PRESSURE_1479;
    } else if (negative_pressure > 480) {
        cout << "Negative pressure is higher than limit 480" << endl;
        return NEGATIVE_PRESSURE_479;
    }

    positive_vent_area = positive_vent_area - existing_vent_area;
    negative_vent_area = negative_vent_area - existing_vent_area;

    double req_vent_area = fmax(positive_vent_area, negative_vent_area);
    return req_vent_area;
}

double vent_calculation::getVentAreaFIAIndex_4() {


    double positive_vent_area =
            (0.12384 * enclosure_volume * safety_factor_vent_area * design_concentration) / discharge_time *
            pow((pressure_limit / (0.81 + 0.51 * (relative_humidity)/100)), -0.8587);

    double positive_pressure = 0.08827 * (0.81 + 0.51 * (relative_humidity)/100) *
                               pow((positive_vent_area / enclosure_volume * discharge_time / design_concentration),
                                   -1.165);


    if (positive_pressure > 1400) {
        cout << "Positive pressure is higher than limit 1479" << endl;
        return POSITIVE_PRESSURE_1479;
    }

    positive_vent_area = positive_vent_area - existing_vent_area;

    return positive_vent_area;
}




