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
	double volume;              // Volume
	double desg_const;          // Design concentration (C) in Percentage
	double flooding_factor;     // flooding factor
	double mass_fl_rate_agent;  // Mass Flow of Extinguishant (kgs/second)
	int ext_agent;              // Extinguishant Agent Index
	double discharge_time;      // Discharge Time
	//double ac;

	double FIA_Area;            // Total Vent Area (Sq mtr)
	double FSSA_Area;           // Pressure Relief Vent Area
    double temperature;         // Temperature



public:

    /*
     *  Default Constructor
     */
	vent_calculation();

    /*
     * Constructor for FIA
     */
	vent_calculation( double temperature,
                      double sp_volume,
                      double room_str,
                      double vol,
                      double desg_const,
                      double flood_fact,
                      double fl_rate,
                      int ext_agent,
                      double discharge_time):
            temperature(temperature),
            sp_volume(sp_volume),
            room_str(room_str),
            volume(vol),
            desg_const(desg_const),
            flooding_factor(flood_fact),
            mass_fl_rate_agent(fl_rate),
            ext_agent(ext_agent),
            discharge_time(discharge_time)
    {};

    double get_FIA_vent_area();
	double get_FSSA_vent_area();

	double FIA();
	double FSSA();


};

