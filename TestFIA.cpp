/*
 * TestFIA.cpp
 *
 *  Created on: Jul 19, 2017
 *      Author: skbiswas
 */
#include <iostream>
#include "TestFIA.h"
#include "vent_calculation.h"

using namespace std;

int main(){

    auto vent_area_agent_non_liquifiable = vent_calculation(
            1.0,     // Extinguishing agent
            260.0,   // Protected Enclosure Volume(S)
            45.2,    // Design Concentration
            6.74,    // Discharge Time
            0.0      // Relative Humidity
    );

    /*
     * @param temperature
     * @param spec_vol_ext
     * @param room_strength
     * @param mass_flow_rate / peak discharge
     * @param pressure_excur
     * @param neg_press_excur
     * @param total_vent_area
     */
    //cout << vent_area_agent_non_liquifiable.get_FIA_vent_area(20 , 0.7081 , 500 , 6.74 , 0 , 1 , 0.0) << endl;

    auto vent_area_agent_liquifiable = vent_calculation(
            0.0,     // Extinguishing agent
            125.0,   // Protected Enclosure Volume(S)
            8.5,     // Design Concentration
            9.2,     // Discharge Time / Peak discharge
            50.0     // Relative Humidity
    );
    // for HFC-23
    //cout << vent_area_agent_liquifiable.get_FIA_vent_area(0 , 125 , 500 , 6.74 , 0 , 0 , 0.042 ) << endl;

    // for FK-5-1-12
    // cout << vent_area_agent_liquifiable.get_FIA_vent_area(0 , 125 , 500 , 6.74 , 1 , 0 , 0.042 ) << endl;

    // for HFC-227-ea
        cout << vent_area_agent_liquifiable.get_FIA_vent_area(0 , 125 , 500 , 6.74 , 1 , 1 , 0.042 ) << endl;

    // for HFC-125
    // cout << vent_area_agent_liquifiable.get_FIA_vent_area(0 , 260 , 500  , 6.74 , 1 , 2 , 0.042 ) << endl;


    auto vent_area_agent_1 = vent_calculation(
            1.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            5.2,     // Design Concentration
            9.0,     // Discharge Time
            30.0     // Relative Humidity
    );

    //cout << vent_area_agent_1.get_FSSA_vent_area( 225.0 , 0 , 0.015 , 1.1 ) << endl;
    auto vent_area_agent_2 = vent_calculation(
            2.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            6.25,    // Design Concentration
            9.0,     // Discharge Time
            30.0     // Relative Humidity
    );

    //cout << vent_area_agent_2.get_FSSA_vent_area(239.5 , 0 , 0.015 , 1.1 ) << endl;

    auto vent_area_agent_3 = vent_calculation(
            3.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            8.0,     // Design Concentration
            9.0,     // Discharge Time
            30.0     // Relative Humidity
    );

   //cout << vent_area_agent_3.get_FSSA_vent_area( 239.5, 4 , 0.015,  1.1 ) << endl;

    auto vent_area_agent_4 = vent_calculation(
            4.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            18.0,    // Design Concentration
            9.0,     // Discharge Time
            30.0     // Relative Humidity
    );

    /*
     * Method for FSSA Vent Area
     * @param ext_vent_area takes a double value for Existing vent area
     * @param pressure_limit takes a double value for Enclosure pressure Limit
     * @param safety_factor_area takes a double value for Safety factor vent area
     * @param hd_index takes a int value for Hardware index
     */

    //cout << vent_area_agent_4.get_FSSA_vent_area( 239.5 , 2 , 0.015 , 1.1 ) << endl;


    auto vent_area_agent_5 = vent_calculation(
            5.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            37.0,    // Design Concentration
            55.0,    // Discharge Time
            0.0      // Relative Humidity
    );
    /*
    * Method for FSSA Vent Area
    * @param ext_vent_area takes a double value for Existing vent area
    * @param pressure_limit takes a double value for Enclosure pressure Limit
    * @param safety_factor_area takes a double value for Safety factor vent area
    * @param hd_index takes a int value for Hardware index
    */
    //cout << vent_area_agent_5.get_FSSA_vent_area( 239.5 , 5 , 0.015 , 1.1 ) << endl;


    auto vent_area_agent_6 = vent_calculation(
            6.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            37.0,    // Design Concentration
            55.0,    // Discharge Time
            0.0     // Relative Humidity
    );

    /*
    * Method for FSSA Vent Area
    * @param ext_vent_area takes a double value for Existing vent area
    * @param pressure_limit takes a double value for Enclosure pressure Limit
    * @param safety_factor_area takes a double value for Safety factor vent area
    * @param hd_index takes a int value for Hardware index
    */
    //cout << vent_area_agent_6.get_FSSA_vent_area( 239.5 , 4 , 0.015 , 1.1 );


    auto vent_area_agent_8 = vent_calculation(
            8.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            37.0,    // Design Concentration
            55.0,    // Discharge Time
            0.0     // Relative Humidity
    );

    /*
    * Method for FSSA Vent Area
    * @param ext_vent_area takes a double value for Existing vent area
    * @param pressure_limit takes a double value for Enclosure pressure Limit
    * @param safety_factor_area takes a double value for Safety factor vent area
    * @param hd_index takes a int value for Hardware index
    */
    //cout << vent_area_agent_8.get_FSSA_vent_area( 239.5 , 1 , 0.015 , 1.1 );

};




