#ifndef AVG_PERIODTEMP_H
#define AVG_PERIODTEMP_H

#include "WeatherDataLine.h"
#include "WeatherDataVec.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>

// ROOT library objects
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TLegend.h>

void temperature_over_two_periods(Int_t year1a, Int_t year1b, Int_t year2a, Int_t year2b,
                                  WeatherDataVec data);



#endif /* AVG_PERIODTEMP_H */

