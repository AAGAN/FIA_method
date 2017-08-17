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
     * @param temperature for Liquifiable is not required and is set to 0 as first argument.
     * @param spec_vol_ext
     * @param room_strength
     * @param mass_flow_rate / peak discharge
     * @param pressure_excur
     * @param neg_press_excur
     * @param total_vent_area
     */

//    double vent_area = vent_area_agent_non_liquifiable.get_FIA_vent_area(20 , 0.7081 , 500 , 6.74 , 0 , 1 , 0.0);
//    cout << endl;
//    cout << "FIA Vent Area input values " <<endl;
//    cout << "*********************************************************************************************************"<<endl;
//    cout << "Agent index = 1 (Non Liquefiable Agent), Enclosure Volume = 260 , Design Concentration = 45.2 " <<endl ;
//    cout << "Discharge Time = 6.74 , Relative Humidity = 0 (Not Required) ,temperature = 20, spec_vol_ext = 0.7081 , room_strength = 500" << endl;
//    cout << "mass_flow_rate = 6.74 , pressure_excur = 0 , neg_press_excur = 1 , total_vent_area = 0" <<endl;
//    cout << "*********************************************************************************************************"<<endl;
//    cout << endl;
//    cout << "Required output = 0.242422 " << endl;
//    cout << "FIA Vent Area output after calculation = " << vent_area << endl;


    auto vent_area_agent_liquifiable = vent_calculation(
            0.0,     // Extinguishing agent
            125.0,   // Protected Enclosure Volume(S)
            8.5,     // Design Concentration
            9.2,     // Discharge Time / Peak discharge
            50.0     // Relative Humidity
    );

    double vent_area = vent_area_agent_liquifiable.get_FIA_vent_area(0 , 125 , 500 , 6.74 , 0 , 0 , 0.042 );    // for HFC-23
    cout << endl;
    cout << "FIA Vent Area input values for HFC-23" <<endl;
    cout << "*********************************************************************************************************"<<endl;
    cout << "Agent index = 0 ( Liquefiable Agent ), Enclosure Volume = 125 , Design Concentration = 9.2 " <<endl ;
    cout << "Discharge Time = 9.2 , Relative Humidity = 50 ,temperature = 0 (Not Required for Liquifiable )" <<endl;
    cout << "spec_vol_ext = 125 , room_strength = 500" << endl;
    cout << "mass_flow_rate = 6.74 , pressure_excur = 0 , neg_press_excur = 0 , total_vent_area = 0.042" <<endl;

    cout << endl;
    cout << "FIA Vent Area output for agent HFC-23 = " << vent_area << endl;



    // for FK-5-1-12
    cout << endl;
    cout << "*********************************************************************************************************"<<endl;
    cout << "FIA Vent Area input values for FK-5-1-12" <<endl;
    cout << "temperature = 0 (Not Required for Liquifiable )" <<endl;
    cout << "spec_vol_ext = 125 , room_strength = 500" << endl;
    cout << "mass_flow_rate = 6.74 , pressure_excur = 1 , neg_press_excur = 0 , total_vent_area = 0.042" <<endl;

    vent_area = vent_area_agent_liquifiable.get_FIA_vent_area(0 , 125 , 500 , 6.74 , 1 , 0 , 0.042 ) ;
    cout << "FIA Vent Area output for agent FK-5-1-12 = " << vent_area << endl;


    // for HFC-227-ea
    cout << endl;
    cout << "*********************************************************************************************************"<<endl;
    cout << "FIA Vent Area input values for HFC-227-ea" <<endl;
    cout << "temperature = 0 (Not Required for Liquifiable )" <<endl;
    cout << "spec_vol_ext = 125 , room_strength = 500" << endl;
    cout << "mass_flow_rate = 6.74 , pressure_excur = 1 , neg_press_excur = 1 , total_vent_area = 0.042" <<endl;

    vent_area = vent_area_agent_liquifiable.get_FIA_vent_area(0 , 125 , 500 , 6.74 , 1 , 1 , 0.042 );
    cout << "FIA Vent Area output for agent HFC-227-ea = " << vent_area << endl;

    // for HFC-125
    cout << endl;
    cout << "*********************************************************************************************************"<<endl;
    cout << "FIA Vent Area input values for HFC-125" <<endl;
    cout << "temperature = 0 (Not Required for Liquifiable )" <<endl;
    cout << "spec_vol_ext = 260 , room_strength = 500" << endl;
    cout << "mass_flow_rate = 6.74 , pressure_excur = 1 , neg_press_excur = 2 , total_vent_area = 0.042" <<endl;

    vent_area = vent_area_agent_liquifiable.get_FIA_vent_area(0 , 260 , 500  , 6.74 , 1 , 2 , 0.042 );
    cout << "FIA Vent Area output for agent HFC-125 = " << vent_area << endl;


    auto vent_area_agent_1 = vent_calculation(
            1.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            5.2,     // Design Concentration
            9.0,     // Discharge Time
            30.0     // Relative Humidity
    );

    /*
     * Method for FSSA Vent Area
     * @param pressure_limit takes a double value for Enclosure pressure Limit in Pascal
     * @param hd_index takes a int value for Hardware index 0 (not used) for Extinguishing agent 2
     * @param ext_vent_area takes a double value for Existing vent area in meter^2 and default is 0.0
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */

//    double vent_area = vent_area_agent_1.get_FSSA_vent_area( 225.0 , 0 , 0.015 , 1.1 );
//    cout << endl;
//    cout << "FSSA Vent Area input values " <<endl;
//    cout << "*********************************************************************************************************"<<endl;
//    cout << "Agent index = 1, Enclosure Volume = 283.3 , Design Concentration = 5.2 " <<endl ;
//    cout << "Discharge Time = 9 , Relative Humidity = 30 , Pressure Limit = 225.0 , Hardware index = 0 (Not required)" << endl;
//    cout << "Existing vent area = 0.015 , Safety factor = 1.1" <<endl;
//    cout << "*********************************************************************************************************"<<endl;
//    cout << endl;
//    cout << "Required output= 0.3439 " << endl;
//    cout << "FSSA Vent Area output after calculation = " << vent_area << endl;

    auto vent_area_agent_2 = vent_calculation(
            2.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            6.25,    // Design Concentration
            9.0,     // Discharge Time
            30.0     // Relative Humidity
    );

    /*
     * Method for FSSA Vent Area
     * @param pressure_limit takes a double value for Enclosure pressure Limit in Pascal
     * @param hd_index takes a int value for Hardware index 0 (not used) for Extinguishing agent 2
     * @param ext_vent_area takes a double value for Existing vent area in meter^2 and default is 0.0
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */
//    double vent_area = vent_area_agent_2.get_FSSA_vent_area(239.5 , 0 , 0.015 , 1.1 );
//    cout << endl;
//    cout << "FSSA Vent Area input values " <<endl;
//    cout << "*********************************************************************************************************"<<endl;
//    cout << "FSSA Vent Area for Agent index =2, Enclosure Volume = 283.3 , Design Concentration = 6.25 , " << endl;
//    cout << "Discharge Time = 9 , Relative Humidity = 30 , Pressure Limit = 239.5 , Hardware index = 0 (Not required)" << endl;
//    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
//    cout << "*********************************************************************************************************"<<endl;
//    cout << endl;
//    cout << "Required output = 0.1575 " << endl;
//    cout << "FSSA Vent Area output after calculation = " << vent_area << endl;

    auto vent_area_agent_3 = vent_calculation(
            3.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            8.0,     // Design Concentration
            9.0,     // Discharge Time
            30.0     // Relative Humidity
    );

    /*
     * Method for FSSA Vent Area
     * @param pressure_limit takes a double value for Enclosure pressure Limit in Pascal
     * @param hd_index takes a int value for Hardware index 4 for Extinguishing agent 3
     * @param ext_vent_area takes a double value for Existing vent area in meter^2 and default is 0.0
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */
//    double vent_area = vent_area_agent_3.get_FSSA_vent_area( 239.5, 4 , 0.015,  1.1 );
//    cout << endl;
//    cout << "FSSA Vent Area input values " <<endl;
//    cout << "*********************************************************************************************************"<< endl;
//    cout << "FSSA Vent Area for Agent index = 3, Enclosure Volume = 283.3 , Design Concentration = 8 " << endl;
//    cout << "Discharge Time = 9 , Relative Humidity = 30 , Pressure Limit = 239.5 , Hardware index = 4 " << endl;
//    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
//    cout << "*********************************************************************************************************"<< endl;
//    cout << endl;
//    cout << "Required output= 0.0592 " << endl;
//    cout << "FSSA Vent Area output after calculation = " << vent_area << endl;

    auto vent_area_agent_4 = vent_calculation(
            4.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            18.0,    // Design Concentration
            9.0,     // Discharge Time
            30.0     // Relative Humidity
    );

    /*
     * Method for FSSA Vent Area
     * @param pressure_limit takes a double value for Enclosure pressure Limit in Pascal
     * @param hd_index takes a int value for Hardware index 2/3 for Extinguishing agent 4
     * @param ext_vent_area takes a double value for Existing vent area in meter^2 and default is 0.0
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */
//    double vent_area = vent_area_agent_4.get_FSSA_vent_area( 239.5 , 2 , 0.015 , 1.1 );
//    cout << endl;
//    cout << "FSSA Vent Area input values " <<endl;
//    cout << "*********************************************************************************************************"<< endl;
//    cout << "FSSA Vent Area for Agent index = 4, Enclosure Volume = 283.3 , Design Concentration = 18  " <<endl;
//    cout << "Discharge Time = 9 , Relative Humidity = 30, Pressure Limit = 239.5 , Hardware index = 2  " <<endl;
//    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
//    cout << "*********************************************************************************************************"<< endl;
//    cout << endl;
//    cout << "Required output= 0.6596 " << endl;
//    cout << "FSSA Vent Area output after calculation = "<< vent_area << endl;


    auto vent_area_agent_5 = vent_calculation(
            5.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            37.0,    // Design Concentration
            55.0,    // Discharge Time
            0.0      // Relative Humidity
    );

    /*
     * Method for FSSA Vent Area
     * @param pressure_limit takes a double value for Enclosure pressure Limit in Pascal
     * @param hd_index takes a int value for Hardware index 2/3/5 for Extinguishing agent 5
     * @param ext_vent_area takes a double value for Existing vent area in meter^2 and default is 0.0
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */
//    double vent_area = vent_area_agent_5.get_FSSA_vent_area( 239.5 , 5 , 0.015 , 1.1 );
//    cout << endl;
//    cout << "FSSA Vent Area input values " <<endl;
//    cout << "*********************************************************************************************************"<< endl;
//    cout << "FSSA Vent Area for Agent index = 6, Enclosure Volume = 283.3 , Design Concentration = 37  " << endl;
//    cout << "Discharge Time = 55 , Relative Humidity = 0 , Pressure Limit = 239.5 , Hardware index = 5 " << endl;
//    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
//    cout << "*********************************************************************************************************"<< endl;
//    cout << endl;
//    cout << "Required output= 0.7991" << endl;
//    cout << "FSSA Vent Area output after calculation = " << vent_area << endl;


    auto vent_area_agent_6 = vent_calculation(
            6.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            37.0,    // Design Concentration
            55.0,    // Discharge Time
            0.0     // Relative Humidity
    );

    /*
     * Method for FSSA Vent Area
     * @param pressure_limit takes a double value for Enclosure pressure Limit in Pascal
     * @param hd_index takes a int value for Hardware index 4 for Extinguishing agent 6
     * @param ext_vent_area takes a double value for Existing vent area in meter^2 and default is 0.0
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */
//    double vent_area = vent_area_agent_6.get_FSSA_vent_area( 239.5 , 4 , 0.015 , 1.1 );
//    cout << endl;
//    cout << "FSSA Vent Area input values " <<endl;
//    cout << "*********************************************************************************************************"<< endl;
//    cout << "FSSA Vent Area for Agent index = 6, Enclosure Volume = 283.3 , Design Concentration = 37 "<< endl;
//    cout << "Discharge Time = 55 , Relative Humidity = 0 , Pressure Limit = 239.5 , Hardware index = 4 "<< endl;
//    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
//    cout << "*********************************************************************************************************"<< endl;
//    cout << endl;
//    cout << "Standard output= 0.3766" << endl;
//    cout << "FSSA Vent Area output after calculation = " << vent_area;


    auto vent_area_agent_8 = vent_calculation(
            8.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            37.0,    // Design Concentration
            55.0,    // Discharge Time
            0.0     // Relative Humidity
    );

    /*
     * Method for FSSA Vent Area
     * @param pressure_limit takes a double value for Enclosure pressure Limit in Pascal
     * @param hd_index takes a int value for Hardware index 1 for Extinguishing agent 8
     * @param ext_vent_area takes a double value for Existing vent area in meter^2 and default is 0.0
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */
//    double vent_area = vent_area_agent_8.get_FSSA_vent_area( 239.5 , 1 , 0.015 , 1.1 );
//    cout << endl;
//    cout << "FSSA Vent Area input values " <<endl;
//    cout << "*********************************************************************************************************"<< endl;
//    cout << "FSSA Vent Area for Agent index = 8, Enclosure Volume = 283.3 , Design Concentration = 37 "<< endl;
//    cout << "Discharge Time = 55 , Relative Humidity = 0 , Pressure Limit = 239.5 , Hardware index = 1 "<< endl;
//    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
//    cout << "*********************************************************************************************************"<< endl;
//    cout << endl;
//    cout << "Standard output= 0.4884" << endl;
//    cout << "FSSA Vent Area output after calculation = " << vent_area;

};




