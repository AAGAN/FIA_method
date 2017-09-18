/*
 * Ventcalculation.h
 *
 *  Created on: Jul 19, 2017
 *  Author: skbiswas
 */


class vent_calculation {


private:

    double enclosure_volume;            // Enclosure Volume (V) in m^3
    double design_concentration;        // Design concentration (C) in Percentage
    int extinguishant_agent_index;      // Extinguishant Agent Index in numeric range( 1,2,3,4,5,6,7,8 )
    double discharge_time;              // Discharge Time (t) in seconds
    double relative_humidity;           // Relative Humidity in Hg ( Not Required for Non Lequifiable )
    double existing_vent_area = 0.0;    // existing_vent_area takes a double for Existing Vent Area in meter^2
    double safety_factor_vent_area;     //
    double pressure_limit;              // Pressure limit in Pascal

    double FIA_Area;                // Total Vent Area (Sq mtr) for FIA
    double FSSA_Area;               // Pressure Relief Vent Area for FSSA




public:

    /*
     *  Default Constructor
     */
    vent_calculation();

    /*
     * Constructor for vent_calculation
     * @param agent_id takes an int argument for Extinguishant agent index
     * @param volume takes a double value for Enclosure volume in m^3
     * @param design_concen takes a double value for Design concentration in Percentage
     * @param discharge_time takes a double for System Discharge time in seconds
     * @param Relative Humidity in Percentage
     * @param existing vent area in m^2
     * @param safety factor vent area
     * @param pressure limit in Pascal
     */
    vent_calculation(int agent_id,
                     double volume,
                     double design_concen,
                     double discharge_time,
                     double rel_humidity,
                     double eva,
                     double sf_area,
                     double plimit
    ) :
            extinguishant_agent_index(agent_id),
            enclosure_volume(volume),
            design_concentration(design_concen),
            discharge_time(discharge_time),
            relative_humidity(rel_humidity),
            existing_vent_area(eva),
            safety_factor_vent_area(sf_area),
            pressure_limit(plimit) {};


    /*
     * @method for FIA Vent Area
     * @param system_technology_index takes int for identifying Orifice or IFloy System(1=iFlow , else Orifice)
     * @param peek_mass_flow_rate takes a double for Peek Mass flow rate of extinguishant in (Kg/seconds)
     * @param total_agent_mass_cylinder_bank takes a double takes double (Kg)
     * @param temperature takes a double for Temperature in Fahrenheit , if not required should be set to 0
     */

    double get_FIA_vent_area(int system_technology_index = 0, double peek_mass_flow_rate = 0, double total_agent_mass_cylinder_bank = 0, double temperature = 0);


    double get_FSSA_vent_area();

    double FIA();

    double FSSA();


    /*
    * Helper Method for FIA Vent Area Calculation
    */

    double getVentAreaFIAforAgentIndex_1();

    double getVentAreaFIAforAgentIndex_2();

    double getVentAreaFIAforAgentIndex_3();

    double getVentAreaFIAforAgentIndex_4();

  /*
  * @method for FIA Vent Area
  * @param system_technology_index takes int for identifying Orifice or IFloy System(1=iFlow , else Orifice) if not required should be set to 0
  * @param peek_mass_flow_rate takes a double for Peek Mass flow rate of extinguishant in (Kg/seconds) if not required should be set to 0
  * @param total_agent_mass_cylinder_bank takes a double takes double (Kg) if not required should be set to 0.0
  * @param temperature takes a double for Temperature in Fahrenheit , if not required should be set to 0
  */
    double getVentAreaFIAforAgentIndex_5( int system_technology_index, double peak_mass_flow_rate, double total_agent_mass_cylinder_bank=0 ,double temperature =0 );

    double getVentAreaFIAforAgentIndex_7( int system_technology_index, double peak_mass_flow_rate, double total_agent_mass_cylinder_bank=0 ,double temperature =0 );

    double getVentAreaFIAforAgentIndex_8( int system_technology_index, double peak_mass_flow_rate, double total_agent_mass_cylinder_bank=0 ,double temperature=0 );

    /*
     * Helper Method for FSSA Vent Area Calculation
     */
    double getVentAreaFSSAforAgentIndex_1();

    double getVentAreaFSSAforAgentIndex_2();

    double getVentAreaFSSAforAgentIndex_3();

    double getVentAreaFSSAforAgentIndex_4();

    double getVentAreaFSSAforAgentIndex_5();

    double getVentAreaFSSAforAgentIndex_6();

    double getVentAreaFSSAforAgentIndex_8();


    /*
    * Sub Helper Method for FIA/FSSA Vent Area Calculation
    */

    double getVentAreaFIAIndex_1();

    double getVentAreaFIAIndex_2();

    double getVentAreaFIAIndex_3();

    double getVentAreaFIAIndex_4();

    double getVentAreaFSSAIndex_1();

    double getVentAreaFSSAIndex_2();

    double getVentAreaFSSAIndex_3();


};

