#ifndef GLOBAL_TEMPERATURE_REGRESSION_H
#define GLOBAL_TEMPERATURE_REGRESSION_H

#include "WeatherDataLine.h"
#include "WeatherDataVec.h"
#include "Gregorian.h"
#include <iostream>

// ROOT library objects
#include <TF1.h> // 1d function class
#include <TGraph.h> // graph class
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TFitResult.h>
#include <TFitResultPtr.h>


void global_temperature_regression(int year1, int year2, WeatherDataVec rawdata);


#endif /* GLOBAL_TEMPERATURE_REGRESSION_H */
