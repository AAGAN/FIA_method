/*
 * Ventcalculation.h
 *
 *  Created on: Jul 19, 2017
 *  Author: skbiswas
 */


class vent_calculation {


private:

    double encl_volume;             // Enclosure Volume (V) in m^3
    double design_concentration;    // Design concentration (C) in Percentage
    int agent_index;                // Extinguishant Agent Index in numeric range( 1,2,3,4,5,6,7,8)
    double discharge_time;          // Discharge Time (t) in seconds
    double rel_humidity;            // Relative Humidity in Hg


    double FIA_Area;                // Total Vent Area (Sq mtr) for FIA
    double FSSA_Area;               // Pressure Relief Vent Area




public:

    /*
     *  Default Constructor
     */
    vent_calculation();

    /*
     * Constructor for vent_calculation
     * @param agent_id takes an int argument for Extinguishant agent index
     * @param volume takes a double value for Enclosure volume
     * @param design_concen takes a double value for Design concentration
     * @param discharge_time takes a double for Discharge time
     */
    vent_calculation( int agent_id,
                      double volume,
                      double design_concen,
                      double discharge_time,
                      double rel_humidity
    ):
            agent_index(agent_id),
            encl_volume(volume),
            design_concentration(design_concen),
            discharge_time(discharge_time),
            rel_humidity(rel_humidity)
    {};


    /*
     * @method for FIA Vent Area
     * @param temperature takes a double for Temperature in Fahrenheit , if not required should be set to 0
     * @param spec_vol_extinguishant takes a double for Specific vapour volume of air given in (Cubic meters/Kg)
     * @param room_strength takes a double for Room Strength in Pascals
     * @param flooding_factor takes a double for flooding factor in percentage
     * @param mass_flow_rate takes a double for Mass flow rate of extinguishant in (Kg/seconds)
     * @param pressure_excur takes a double for Pressure Exceurion in range of (0,1)
     * @param neg_press_excur takes a double for Negative Pressure Exceurion in range of (0,1,2)
     * @param total_vent_area takes a double for Total Vent Area in meter^2
     */

    double get_FIA_vent_area( double temperature , double spec_vol_ext , double room_strength , double mass_flow_rate , double pressure_excur ,
                              double neg_press_excur, double total_vent_area );

    /*
     * Method for FSSA Vent Area
     * @param pressure_limit takes a double value for Enclosure pressure Limit in Pascal
     * @param hd_index takes a int value for Hardware index
     * @param ext_vent_area takes a double value for Existing vent area in meter^2 and default is 0.0
     * @param safety_factor_area takes a double value for Safety factor vent area and default is 1.0
     */

    double get_FSSA_vent_area( double pressure_limit , int hw_index , double ext_vent_area = 0.0 , double safety_factor_area = 1.0 );

    double FIA();
    double FSSA();


};

