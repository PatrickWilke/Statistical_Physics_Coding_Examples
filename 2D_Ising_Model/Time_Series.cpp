//  Created by Patrick Wilke on 27.05.19.
//  Copyright © 2019 Patrick Wilke. All rights reserved.
//

#include "Time_Series.hpp"


//Constructor
Time_Series::Time_Series(const double temperature,const int system_width):
temperature_{temperature},
system_width_{system_width}
{};
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//simulation function
void Time_Series::PerformSeries(const long number_of_iterations,const long burnin_iterations,const int number_of_datapoints){
    
    Ising_System system(temperature_,system_width_);
    system.Simulate(burnin_iterations);
    
    magnetization_series_.push_back(system.GetMagnetization());
    energy_series_.push_back(system.GetEnergy());
    iteration_series_.push_back(burnin_iterations);
    
    long iteration_intervals=(number_of_iterations-burnin_iterations)/number_of_datapoints;
    
    for (int i=0; i<number_of_datapoints; ++i) {
        
        system.Simulate(iteration_intervals);
        
        magnetization_series_.push_back(system.GetMagnetization());
        energy_series_.push_back(system.GetEnergy());
        iteration_series_.push_back(iteration_series_.back()+iteration_intervals);
    }
    
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//result functions
std::vector<double> Time_Series::GetMagnetizationSeries()const{
    return magnetization_series_;
}
///////////////////////////////////////////////////////////////////////////
std::vector<double> Time_Series::GetEnergySeries()const{
    return energy_series_;
}
///////////////////////////////////////////////////////////////////////////
double Time_Series::GetAverageEnergy()const{
    long tmp_energy=0;
    for (auto& x : energy_series_) {
        tmp_energy+=x;
    }
    return static_cast<double>(tmp_energy)/static_cast<double>(energy_series_.size());
}
///////////////////////////////////////////////////////////////////////////
double Time_Series::GetAverageMagnetization()const{
    long tmp_magnetization=0;
    for (auto& x : magnetization_series_) {
        tmp_magnetization+=x;
    }
    return static_cast<double>(tmp_magnetization)/static_cast<double>(magnetization_series_.size());
}
///////////////////////////////////////////////////////////////////////////
double Time_Series::GetAverageMagnetizationABS()const{
    long tmp_magnetization=0;
    for (auto& x : magnetization_series_) {
        tmp_magnetization+=x<0?-x:x;
    }
    return static_cast<double>(tmp_magnetization)/static_cast<double>(magnetization_series_.size());
}
///////////////////////////////////////////////////////////////////////////
double Time_Series::GetVarianceEnergy()const{
    long tmp_energy=0;
    for (auto& x : energy_series_) {
        tmp_energy+=x*x;
    }
    double av_en=GetAverageEnergy();
    return static_cast<double>(tmp_energy)/static_cast<double>(energy_series_.size())-av_en*av_en;
}
///////////////////////////////////////////////////////////////////////////
double Time_Series::GetVarianceMagnetization()const{
    long tmp_magnetization=0;
    for (auto& x : magnetization_series_) {
        tmp_magnetization+=x*x;
    }
    double av_mag=GetAverageMagnetization();
    return static_cast<double>(tmp_magnetization)/static_cast<double>(magnetization_series_.size())-av_mag*av_mag;
}
///////////////////////////////////////////////////////////////////////////
double Time_Series::GetSpecificHeat()const{
    if (temperature_) {
        return GetVarianceEnergy()/static_cast<double>(system_width_*system_width_)/temperature_/temperature_;
    }
    else return 0.0;
}
///////////////////////////////////////////////////////////////////////////
double Time_Series::GetSpecificSusceptibility()const{
    if (temperature_) {
        return GetVarianceMagnetization()/static_cast<double>(system_width_*system_width_)/temperature_;
    }
    else return 0.0;
    }
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//save results to txt file
void Time_Series::WriteToFile()const{
    
    std::ofstream file;
    file.open ("Trajectories/T_"+NiceDoubleToString(temperature_)+"_L_"+std::to_string(system_width_)+".txt");
    
    for(int i=0; i<magnetization_series_.size();++i){
        file<<iteration_series_[i]<<" "<<magnetization_series_[i]<<" "<<energy_series_[i]<<"\n";
    }
    
    file.close();
}
///////////////////////////////////////////////////////////////////////////
std::string Time_Series::NiceDoubleToString(const double number){
    std::string temp_string(std::to_string(number));
    while (temp_string.back()=='0') {
        temp_string.pop_back();
    }
    if (temp_string.back()=='.') {
        temp_string.pop_back();
    }
    return temp_string;
}
