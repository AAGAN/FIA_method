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
    int guidance_document_index;        // for identifying FIA = 1 or FSSA = 2
    int extinguishant_agent_index;      // Extinguishant Agent Index in numeric range( 1,2,3,4,5,6,7,8 )
    int system_technology_index;        // Extinguishant Agent Index in numeric range( 1 )
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
     * @param discharge_time takes a double for Discharge time in seconds
     * @param Relative Humidity in Hg
     * @param existing vent area
     * @param safety factor vent area
     * @param pressure limit in Pascal
     */
    vent_calculation(int gudance_doc_index,
                     int agent_id,
                     double volume,
                     double design_concen,
                     double discharge_time,
                     double rel_humidity,
                     double eva,
                     double sf_area,
                     double plimit
    ) :
            guidance_document_index(gudance_doc_index),
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
     * @param temperature takes a double for Temperature in Fahrenheit , if not required should be set to 0
     * @param spec_vol_extinguishant takes a double for Specific vapour volume of air given in (Cubic meters/Kg)
     * @param mass_flow_rate takes a double for Mass flow rate of extinguishant in (Kg/seconds)
     * @param total_agent_mass_cylinder_bank takes a double takes double (Kg)
     * @param Sair takes double (m^3/Kg)
     * @param system_technology_index takes int for identifying Orifice or IFloy System(1=iFlow , else Orifice)
     */

    double get_FIA_vent_area(double temperature, double spec_vol_ext, double mass_flow_rate, double total_agent_mass_cylinder_bank,
                             double Sair, int system_technology_index);

    /*
     * Method for FSSA Vent Area
     * @param pressure_limit takes a double value for Enclosure pressure Limit in Pascal
     * @param hd_index takes a int value for Hardware index 1,2,3,4,5
     * @param ext_vent_area takes a double value for Existing vent area in meter^2 and default is 0.0
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */

    double get_FSSA_vent_area(double pressure_limit, int hw_index, double safety_factor_area = 1.0);

    double FIA();

    double FSSA();


    /*
    * Helper Method for FIA Vent Area Calculation
    */

    double getVentAreaFIAforAgentIndex_1();

    double getVentAreaFIAforAgentIndex_2();

    double getVentAreaFIAforAgentIndex_3();

    double getVentAreaFIAforAgentIndex_4();

    double getVentAreaFIAforAgentIndex_5(double temperature, double Sair, int system_technology_index,
                                         double peak_mass_flow_rate, double total_agent_mass_cylinder_bank,
                                         double spec_vol_ext);

    double getVentAreaFIAforAgentIndex_7(double temperature, double Sair, int system_technology_index,
                                         double peak_mass_flow_rate, double total_agent_mass_cylinder_bank,
                                         double spec_vol_ext);

    double getVentAreaFIAforAgentIndex_8(double temperature, double Sair, int system_technology_index,
                                         double peak_mass_flow_rate, double total_agent_mass_cylinder_bank,
                                         double spec_vol_ext);

    /*
     * Helper Method for FSSA Vent Area Calculation
     */
    double getVentAreaFSSAforHWAgentIndex_1();

    double getVentAreaFSSAforHWAgentIndex_2();

    double getVentAreaFSSAforHWAgentIndex_3();

    double getVentAreaFSSAforHWAgentIndex_4();

    double getVentAreaFSSAforHWAgentIndex_5_7();

    double getVentAreaFSSAforHWAgentIndex_6();

    double getVentAreaFSSAforHWAgentIndex_8();


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

