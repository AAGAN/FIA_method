#pragma once

int fia_method
(
  double& A, //total vent area in (m^2)
  double M, //mass flow of the extinguishing agent (kg/s)
  double S, //specific vapor volume of extinguishant (cubic meters/kg)
  double P, //maximum room strength (Pa)
  double C, //design concentration (%)
  double T //temperature (K)
);
