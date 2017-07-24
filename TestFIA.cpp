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
            4.0    // Discharge Time

    );
	cout << vent.get_FIA_vent_area( 5.0, 6.0, 7.0, 8.0, 9.0 ) << endl;
    //cout << vent.get_FSSA_vent_area();



};




