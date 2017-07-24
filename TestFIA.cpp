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

    auto vent = vent_calculation(
            1.0,     // Extinguishing agent
            2.0,    // Specific Vapour Volume(S)
            3.0,    // Room strength
            4.0,    // Volume
            5.0,    // Design conc
            6.0,    // Flooding factor
            7.0,    // Mass flow rate of agent
            8.0,    // Temp in Deg. C
            9.0     // Discharge Time

    );
	cout << vent.get_FIA_vent_area() << endl;
    //cout << vent.get_FSSA_vent_area();



};

