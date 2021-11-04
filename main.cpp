#include "csvregex.h"
#include "WeatherDataLine.h"
#include "WeatherDataVec.h"
#include <iostream>

#include "avg_periodtemp.h"
#include "command_line.h"
#include "project.h"


int main(){
    std::string filename {"datasets/smhi-opendata_1_53430_20210926_101122_Lund.csv"};
    WeatherDataVec Wdata {datavec(filename)};

    //std::cout << Wdata.data[0].get_temp() << std::endl;

	projectQL(10, (std::string)"Lund", filename);

	//command_line_loop();

	

    return 0;
}

