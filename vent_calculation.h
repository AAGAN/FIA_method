/*
 * Ventcalculation.h
 *
 *  Created on: Jul 19, 2017
 *      Author: skbiswas
 */


class vent_calculation {


private:

    double encl_volume;             // Volume (V)
    double design_concentration;    // Design concentration (C) in Percentage
    int agent_index;                // Extinguishant Agent Index
    double discharge_time;          // Discharge Time (t)


    //double ext_vent_area = 1.0;     // Existing Vent Area
    //double pressure_limit;          // Enclosure pressure Limit
   // double safty_area = 1.0;        // Saftey factor for vent area

    double FIA_Area;                // Total Vent Area (Sq mtr)
    double FSSA_Area;               // Pressure Relief Vent Area




public:

    /*
     *  Default Constructor
     */
    vent_calculation();

    /*
     * Constructor for vent_calculation
     * @param agent_id takes an int argument for Extinguishant agent index
     * @param volume takes a double value for Encosure volume
     * @param design_concen takes a double value for Design concentration
     * @param discharge_time takes a double for Discharge time
     */
    vent_calculation( int agent_id,
                      double volume,
                      double design_concen,
                      double discharge_time
    ):
            agent_index(agent_id),
            encl_volume(volume),
            design_concentration(design_concen),
            discharge_time(discharge_time)
    {};


    /*
     * @method for FIA Vent Area
     * @param temperature takes a double for Temperature
     * @param spec_vol_extinguishant takes a double for Specific vapour volume of air given
     * @param room_strength takes a double for Room Strength
     * @param flooding_factor takes a double for flooding factor
     * @param mass_flow_rate takes a double for Mass flow rate of extinguishant
     */

    double get_FIA_vent_area(double temperature, double spec_vol_extinguishant, double room_strength, double flooding_factor, double mass_flow_rate);

    /*
     * Method for FSSA Vent Area
     * @param ext_vent_area takes a double value for Existing vent area
     * @param pressure_limit takes a double value for Enclosure pressure Limit
     * @param safety_factor_area takes a double value for Safety factor vent area
     * @param rel_humidity takes a double value for Relative Humidity of agent
     * @param hd_index takes a int value for Hardware index
     */

    double get_FSSA_vent_area(double ext_vent_area, double pressure_limit , double safety_factor_area ,double rel_humidity , int hd_index );

    double FIA();
    double FSSA();


};

