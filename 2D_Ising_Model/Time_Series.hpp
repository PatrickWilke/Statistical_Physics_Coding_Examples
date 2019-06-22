//  Created by Patrick Wilke on 27.05.19.
//

#ifndef Time_Series_h
#define Time_Series_h

#include "2D_Ising_System.hpp"
#include <vector>
#include <fstream>
#include <string>

class Time_Series {
    
public:
    //Constructor
    Time_Series(const double temperature,const int system_width);

    //simulation function
    void PerformSeries(const long number_of_iterations,const long burnin_iterations,const int number_of_datapoints);

    //result functions
    std::vector<double> GetMagnetizationSeries()const;
    
    std::vector<double> GetEnergySeries()const;
    
    double GetAverageEnergy()const;
    
    double GetAverageMagnetization()const;
    
    double GetAverageMagnetizationABS()const;
    
    double GetVarianceEnergy()const;
    
    double GetVarianceMagnetization()const;
    
    double GetSpecificHeat()const;
    
    double GetSpecificSusceptibility()const;
    
    //save results to txt file
    void WriteToFile()const;

private:
    static std::string NiceDoubleToString(const double number);
    
    //measurements
    std::vector<double> magnetization_series_;
    std::vector<double> energy_series_;
    std::vector<double> iteration_series_;
    
    //system parameters
    const double temperature_;
    const int system_width_;
    
};


#endif /* Time_Series_h */
