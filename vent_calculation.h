/*
 * Ventcalculation.h
 *
 *  Created on: Jul 19, 2017
 *      Author: skbiswas
 */


class vent_calculation {


private:

	double sp_volume;           // specific vapour volume of air given (T)
	double room_str;            // Room Strength (P)
	double encl_volume;         // Volume (V)
	double desg_concnt;         // Design concentration (C) in Percentage
	double flooding_factor;     // flooding factor
	double mass_fl_rate_agent;  // Mass Flow of Extinguishant (kgs/second)
	int agent_index;            // Extinguishant Agent Index
	double discharge_time;      // Discharge Time (t)
    double temperature;         // Temperature

    double eva = 1.0;           // Existing Vent Area
    double pa_limit;            // Enclosure pressure Limit
    double sf_area = 1.0;       // Saftey factor for vent area
    double rel_humidity;        // Relative Humidity applicable for Agent 1,2,3,4 (RH)
    int hd_index;               // Hardware Index

	double FIA_Area;            // Total Vent Area (Sq mtr)
	double FSSA_Area;           // Pressure Relief Vent Area




public:

    /*
     *  Default Constructor
     */
	vent_calculation();

    /*
     * Constructor for FIA
     * @param agent_id takes an int argument for Extinguishant agent index
     * @param temperature
     * @param volume takes a double value for Encosure volume
     * @param desg_concnt takes a double value for Design concentration
     * @param discharge_time takes a double for Discharge time
     * @param sp_volume takes a double for Specific vapour volume of air given
     * @param room_str takes a double for Room Strength
     * @param flood_fact takes a double for flooding factor
     * @param fl_rate takes a double for Mass flow of extinguishant
     */
    vent_calculation( int agent_id,
                      double temperature,
                      double volume,
                      double desg_concnt,
                      double discharge_time,
                      double sp_volume,
                      double room_str,
                      double flood_fact,
                      double fl_rate
                      ):
            agent_index(agent_id),
            temperature(temperature),
            encl_volume(volume),
            desg_concnt(desg_concnt),
            discharge_time(discharge_time),
            sp_volume(sp_volume),
            room_str(room_str),
            flooding_factor(flood_fact),
            mass_fl_rate_agent(fl_rate)
    {};

    /*
     * Constructor for FSSA
     * @param agent_id takes an int argument for Extinguishant agent index
     * @param volume takes a double value for Encosure volume
     * @param concentration takes a double value for Design concentration
     * @param discharge_time takes a double for Discharge time
     * @param eva takes a double value for Existing vent area
     * @param pa takes a double value for Enclosure pressure Limit
     * @param sf takes a double value for Safety factor vent area
     * @param rel_humidity takes a double value for Relative Humidity of agent
     * @param hd_index takes a int value for Hardware index
     */
    vent_calculation( int agent_id,
                      double volume,
                      double concentration,
                      double discharge_time,
                      double eva,
                      double pa,
                      double sf,
                      double rel_humidity,
                      int hd_index):
            agent_index(agent_id),
            encl_volume(volume),
            desg_concnt(concentration),
            discharge_time(discharge_time),
            eva(eva),
            pa_limit(pa),
            sf_area(sf),
            rel_humidity(rel_humidity),
            hd_index(hd_index)
    {};





    double get_FIA_vent_area();
	double get_FSSA_vent_area();

	double FIA();
	double FSSA();


};

