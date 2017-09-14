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

int main() {



    auto vent_area_fia_agent_1 = vent_calculation(
            1,       // guidance document index
            1.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            5.2,     // Design Concentration
            9,       // Peak discharge time in seconds
            30,      // Relative Humidity ( Not Required for Non Lequifiable)
            0.015,   // eva
            1.1,     // Safty factor for vent area
            225      // Pressure Limit (Pascles)

    );

    cout << endl;
    cout << "FIA Vent Area input values Agent index = 1" <<endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << "Enclosure Volume = 283.3 , Design Concentration = 5.2 "<< endl;
    cout << "Discharge Time = 9 , Relative Humidity = 30 , Pressure Limit = 225  "<< endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << endl;
    cout << "Standard output= 0.3439" << endl;

    double vent_area = vent_area_fia_agent_1.get_FIA_vent_area( );
    if(vent_area>0)
        cout << "FIA Vent Area output after calculation = " << vent_area << " m^2" << endl;
    cout << endl;


    auto vent_area_fia_agent_2 = vent_calculation(
            1,       // guidance document index
            2.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            6.25,    // Design Concentration
            9,       // Peak discharge time in seconds
            30,      // Relative Humidity ( Not Required for Non Lequifiable)
            0.015,   // eva
            1.1,     // Safty factor for vent area
            239.5      // Pressure Limit (Pascles)

    );

    cout << endl;
    cout << "FIA Vent Area input values Agent index = 2" <<endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << "Enclosure Volume = 283.3 , Design Concentration = 6.25 "<< endl;
    cout << "Discharge Time = 9 , Relative Humidity = 30 , Pressure Limit = 239.5  "<< endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << endl;
    cout << "Standard output= 0.1327" << endl;

    vent_area = vent_area_fia_agent_2.get_FIA_vent_area();
    if(vent_area>0)
        cout << "FIA Vent Area output after calculation = " << vent_area << " m^2" << endl;
    cout << endl;


    auto vent_area_fia_agent_3 = vent_calculation(
            1,       // guidance document index
            3.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            8,       // Design Concentration
            9,       // Peak discharge time in seconds
            30,      // Relative Humidity ( Not Required for Non Lequifiable)
            0.015,   // eva
            1.1,     // Safty factor for vent area
            239.5      // Pressure Limit (Pascles)

    );

    cout << endl;
    cout << "FIA Vent Area input values Agent index = 3" <<endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << "Enclosure Volume = 283.3 , Design Concentration = 8 "<< endl;
    cout << "Discharge Time = 9 , Relative Humidity = 30 , Pressure Limit = 239.5  "<< endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << endl;
    cout << "Standard output= 0.0363" << endl;

    vent_area = vent_area_fia_agent_3.get_FIA_vent_area();

    if(vent_area>0)
        cout << "FIA Vent Area output after calculation = " << vent_area << " m^2" << endl;
    cout << endl;




    auto vent_area_fia_agent_4 = vent_calculation(
            1,       // guidance document index
            4.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            18,       // Design Concentration
            9,       // Peak discharge time in seconds
            30,      // Relative Humidity ( Not Required for Non Lequifiable)
            0.015,   // eva
            1.1,     // Safty factor for vent area
            239.5      // Pressure Limit (Pascles)

    );
    cout << endl;
    cout << "FIA Vent Area input values Agent index = 4" <<endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << "Enclosure Volume = 283.3 , Design Concentration = 18 "<< endl;
    cout << "Discharge Time = 9 , Relative Humidity = 30 , Pressure Limit = 239.5  "<< endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << endl;
    cout << "Standard output= 0.1912" << endl;

    vent_area = vent_area_fia_agent_4.get_FIA_vent_area();
    if(vent_area>0)
        cout << "FIA Vent Area output after calculation = " << vent_area << " m^2" << endl;
    cout << endl;


    auto vent_area_fia_agent_5 = vent_calculation(
            1,       // guidance document index
            5.0,     // Extinguishing agent
            260,     // Protected Enclosure Volume(S)
            45.2,    // Design Concentration
            9,       // Peak discharge time in seconds
            30,      // Relative Humidity ( Not Required for Non Lequifiable)
            0.015,   // eva
            1.1,     // Safty factor for vent area
            500      // Pressure Limit (Pascles)

    );

    cout << endl;
    cout << "FIA Vent Area input values Agent index = 5" <<endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << "Enclosure Volume = 283.3 , Design Concentration = 5.2 "<< endl;
    cout << "Discharge Time = 9 , Relative Humidity = 30 , Pressure Limit = 225  "<< endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << endl;
    cout << "Standard output= 0.248" << endl;
    /*
     * @method for FIA Vent Area
     * @param peek_mass_flow_rate takes a double for Peek Mass flow rate of extinguishant in (Kg/seconds)
     * @param system_technology_index takes int for identifying Orifice or IFloy System(1=iFlow , else Orifice)
     * @param total_agent_mass_cylinder_bank takes a double takes double (Kg)
     * @param temperature takes a double for Temperature in Fahrenheit , if not required should be set to 0
     */
    vent_area = vent_area_fia_agent_5.get_FIA_vent_area(6.65, 1 ,221.6 ,20);

    if(vent_area>0)
        cout << "FIA Vent Area output after calculation = " << vent_area << " m^2" << endl;
    cout << endl;



    auto vent_area_fia_agent_7 = vent_calculation(
            1,       // guidance document index
            7.0,     // Extinguishing agent
            530,     // Protected Enclosure Volume(S)
            40.3,    // Design Concentration
            60,       // Peak discharge time in seconds
            30,      // Relative Humidity ( Not Required for Non Lequifiable)
            0.015,   // eva
            1.1,     // Safty factor for vent area
            250      // Pressure Limit (Pascles)

    );

    cout << endl;
    cout << "FIA Vent Area input values Agent index = 7" <<endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << "Enclosure Volume = 283.3 , Design Concentration = 5.2 "<< endl;
    cout << "Discharge Time = 9 , Relative Humidity = 30 , Pressure Limit = 225  "<< endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << endl;
    cout << "Standard output= 0.8683" << endl;

    /*
    * @method for FIA Vent Area
    * @param peek_mass_flow_rate takes a double for Peek Mass flow rate of extinguishant in (Kg/seconds)
    * @param system_technology_index takes int for identifying Orifice or IFloy System(1=iFlow , else Orifice)
    * @param total_agent_mass_cylinder_bank takes a double takes double (Kg)
    * @param temperature takes a double for Temperature in Fahrenheit , if not required should be set to 0
    */
    vent_area = vent_area_fia_agent_7.get_FIA_vent_area (13.93 , 1 , 348.32, 5 );
    if(vent_area>0)
        cout << "FIA Vent Area output after calculation = " << vent_area << " m^2" << endl;
    cout << endl;


    auto vent_area_fia_agent_8 = vent_calculation(
            1,       // guidance document index
            8.0,     // Extinguishing agent
            435,     // Protected Enclosure Volume(S)
            39.9,    // Design Concentration
            60,      // Peak discharge time in seconds
            30,      // Relative Humidity ( Not Required for Non Lequifiable)
            0.015,   // eva
            1.1,     // Safty factor for vent area
            350      // Pressure Limit (Pascles)

    );


    cout << endl;
    cout << "FIA Vent Area input values Agent index = 8" <<endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << "Enclosure Volume = 435 , Design Concentration = 39.9 "<< endl;
    cout << "Discharge Time = 60 , Relative Humidity = 30 , Pressure Limit = 350  "<< endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << endl;
    cout << "Standard output= 0.3282" << endl;

   /*
   * @method for FIA Vent Area
   * @param peek_mass_flow_rate takes a double for Peek Mass flow rate of extinguishant in (Kg/seconds)
   * @param system_technology_index takes int for identifying Orifice or IFloy System(1=iFlow , else Orifice)
   * @param total_agent_mass_cylinder_bank takes a double takes double (Kg)
   * @param temperature takes a double for Temperature in Fahrenheit , if not required should be set to 0
   */
    vent_area = vent_area_fia_agent_8.get_FIA_vent_area( 7.13, 1 , 285.2 , 35 );
    if(vent_area>0)
        cout << "FIA Vent Area output after calculation = " << vent_area << " m^2" << endl;
    cout << endl;


    auto vent_area_fssa_agent_1 = vent_calculation(
            2,       // guiding doc index
            1.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            5.2,     // Design Concentration
            9.0,     // Discharge Time
            30.0,    // Relative Humidity
            0.015,   // eva
            1.1,     // Safty factor for vent area
            225.0    // Pressure Limit (Pascles)
    );

    /*
     * Method for FSSA Vent Area
     * @param hd_index takes a int value for Hardware index 0 (not used) for Extinguishing agent 2
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */

    vent_area = vent_area_fssa_agent_1.get_FSSA_vent_area( 0 , 1.1 );
    cout << endl;
    cout << endl;
    cout << "FSSA Vent Area input values for Agent index = 1, " <<endl;
    cout << "*********************************************************************************************************"<<endl;
    cout << "Enclosure Volume = 283.3 , Design Concentration = 5.2 " <<endl ;
    cout << "Discharge Time = 9 , Relative Humidity = 30 , Pressure Limit = 225.0 , Hardware index = 0 (Not required)" << endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" <<endl;
    cout << "*********************************************************************************************************"<<endl;
    cout << endl;
    cout << "Required output= 0.3439 " << endl;
    cout << "FSSA Vent Area output after calculation = " << vent_area << endl;

    auto vent_area_fssa_agent_2 = vent_calculation(
            2,
            2.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            6.25,    // Design Concentration
            9.0,     // Discharge Time
            30.0,     // Relative Humidity
            0.015,   // eva
            1.1,     // Safty factor for vent area
            239.5    // Pressure Limit (Pascles)
    );

    /*
     * Method for FSSA Vent Area
     * @param hd_index takes a int value for Hardware index 0 (not used) for Extinguishing agent 2
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */
    vent_area = vent_area_fssa_agent_2.get_FSSA_vent_area( 0 , 1.1 );
    cout << endl;
    cout << endl;
    cout << "FSSA Vent Area input values for Agent index = 2 " <<endl;
    cout << "*********************************************************************************************************"<<endl;
    cout << "Enclosure Volume = 283.3 , Design Concentration = 6.25 , " << endl;
    cout << "Discharge Time = 9 , Relative Humidity = 30 , Pressure Limit = 239.5 , Hardware index = 0 (Not required)" << endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
    cout << "*********************************************************************************************************"<<endl;
    cout << endl;
    cout << "Required output = 0.1575 " << endl;
    cout << "FSSA Vent Area output after calculation = " << vent_area << endl;

    auto vent_area_fssa_agent_3 = vent_calculation(
            2,
            3.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            8.0,     // Design Concentration
            9.0,     // Discharge Time
            30.0,    // Relative Humidity
            0.015,   // eva
            1.1,     // Safty factor for vent area
            239.5    // Pressure Limit (Pascles)
    );

    /*
     * Method for FSSA Vent Area
     * @param hd_index takes a int value for Hardware index 4 for Extinguishing agent 3
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */
    vent_area = vent_area_fssa_agent_3.get_FSSA_vent_area( 4 ,  1.1 );
    cout << endl;
    cout << endl;
    cout << "FSSA Vent Area input values for Agent index = 3" <<endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << "Enclosure Volume = 283.3 , Design Concentration = 8 " << endl;
    cout << "Discharge Time = 9 , Relative Humidity = 30 , Pressure Limit = 239.5 , Hardware index = 4 " << endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << endl;
    cout << "Required output= 0.0592 " << endl;
    cout << "FSSA Vent Area output after calculation = " << vent_area << endl;

    auto vent_area_fssa_agent_4 = vent_calculation(
            2,
            4.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            18.0,    // Design Concentration
            9.0,     // Discharge Time
            30.0,    // Relative Humidity
            0.015,   // eva
            1.1,     // Safty factor for vent area
            239.5    // Pressure Limit (Pascles)
    );

    /*
     * Method for FSSA Vent Area
     * @param hd_index takes a int value for Hardware index 2/3 for Extinguishing agent 4
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */
    vent_area = vent_area_fssa_agent_4.get_FSSA_vent_area( 2 , 1.1 );
    cout << endl;
    cout << endl;
    cout << "FSSA Vent Area input values for Agent index = 4" <<endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << "Enclosure Volume = 283.3 , Design Concentration = 18  " <<endl;
    cout << "Discharge Time = 9 , Relative Humidity = 30, Pressure Limit = 239.5 , Hardware index = 2  " <<endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << endl;
    cout << "Required output= 0.6596 " << endl;
    cout << "FSSA Vent Area output after calculation = "<< vent_area << endl;


    auto vent_area_fssa_agent_5 = vent_calculation(
            2,
            5.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            37.0,    // Design Concentration
            55.0,    // Discharge Time
            0.0,      // Relative Humidity
            0.015,   // eva
            1.1,     // Safty factor for vent area
            239.5    // Pressure Limit (Pascles)
    );

    /*
     * Method for FSSA Vent Area
     * @param hd_index takes a int value for Hardware index 2/3/5 for Extinguishing agent 5
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */
    vent_area = vent_area_fssa_agent_5.get_FSSA_vent_area( 5 , 1.1 );
    cout << endl;
    cout << endl;
    cout << "FSSA Vent Area input values for Agent index = 5" <<endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << "Enclosure Volume = 283.3 , Design Concentration = 37  " << endl;
    cout << "Discharge Time = 55 , Relative Humidity = 0 , Pressure Limit = 239.5 , Hardware index = 5 " << endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << endl;
    cout << "Required output= 0.7991" << endl;
    cout << "FSSA Vent Area output after calculation = " << vent_area << endl;


    auto vent_area_fssa_agent_6 = vent_calculation(
            2,
            6.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            37.0,    // Design Concentration
            55.0,    // Discharge Time
            0.0,    // Relative Humidity
            0.015,   // eva
            1.1,     // Safty factor for vent area
            239.5    // Pressure Limit (Pascles)
    );

    /*
     * Method for FSSA Vent Area
     * @param hd_index takes a int value for Hardware index 4 for Extinguishing agent 6
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */
    vent_area = vent_area_fssa_agent_6.get_FSSA_vent_area( 4 , 1.1 );
    cout << endl;
    cout << endl;
    cout << "FSSA Vent Area input values for Agent index = 6" <<endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << "Enclosure Volume = 283.3 , Design Concentration = 37 "<< endl;
    cout << "Discharge Time = 55 , Relative Humidity = 0 , Pressure Limit = 239.5 , Hardware index = 4 "<< endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << endl;
    cout << "Standard output= 0.3766" << endl;
    cout << "FSSA Vent Area output after calculation = " << vent_area;


    auto vent_area_fssa_agent_8 = vent_calculation(
            2,
            8.0,     // Extinguishing agent
            283.3,   // Protected Enclosure Volume(S)
            37.0,    // Design Concentration
            55.0,    // Discharge Time
            0.0,     // Relative Humidity
            0.015,   // eva
            1.1,     // Safty factor for vent area
            239.5    // Pressure Limit (Pascles)
    );

    /*
     * Method for FSSA Vent Area
     * @param hd_index takes a int value for Hardware index 1 for Extinguishing agent 8
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */
    vent_area = vent_area_fssa_agent_8.get_FSSA_vent_area(  1 , 1.1 );
    cout << endl;
    cout << endl;
    cout << "FSSA Vent Area input values for Agent index = 8" <<endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << "Enclosure Volume = 283.3 , Design Concentration = 37 "<< endl;
    cout << "Discharge Time = 55 , Relative Humidity = 0 , Pressure Limit = 239.5 , Hardware index = 1 "<< endl;
    cout << "Existing vent area = 0.015 , Safety factor = 1.1" << endl;
    cout << "*********************************************************************************************************"<< endl;
    cout << endl;
    cout << "Standard output= 0.4884" << endl;
    cout << "FSSA Vent Area output after calculation = " << vent_area;

};
