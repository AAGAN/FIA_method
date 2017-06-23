#include <assert.h>
#include <iostream>
#include "FIA.h"

int main()
{
    
double A = 1.0;

int error_code =  fia_method
(
  A, //total vent area in (m^2)
  1.0, //mass flow of the extinguishing agent (kg/s)
  1.0, //specific vapor volume of extinguishant (cubic meters/kg)
  1000.0, //maximum room strength (Pa)
  46.0, //design concentration (%)
  370.0 //temperature (K)
);

std::cout << error_code<< std::endl;

return 0;
}
