//  Created by Patrick Wilke on 27.05.19.
//  Copyright © 2019 Patrick Wilke. All rights reserved.
//

#include "2D_Ising_System.hpp"

//Constructor
Ising_System::Ising_System(const double temperature, const int system_width):
random_number_generator_(time(nullptr)),
system_width_{system_width},
beta_J_{temperature==0?std::numeric_limits<double>::infinity():1/temperature},
ising_spins_(system_width,system_width,true),
magnetization_{system_width*system_width},
energy_{-2*system_width*system_width},
lookup_table_({1,0,exp(-4.0*beta_J_),0,exp(-8.0*beta_J_)}){}
///////////////////////////////////////////////////////////////////////////
//simulation functions
void Ising_System::Simulate(const long iteration_steps){
    for (long i=0; i<iteration_steps; ++i){
        IterationStep();
    }
}
///////////////////////////////////////////////////////////////////////////
void Ising_System::IterationStep(){
    
    const int row=std::uniform_int_distribution<int>(0,system_width_-1)(random_number_generator_);
    const int column=std::uniform_int_distribution<int>(0,system_width_-1)(random_number_generator_);
    
    const long energy_contribution_of_chosen_spin=GetEnergyContribution(row, column);
    
    if (0<energy_contribution_of_chosen_spin) {
        if (std::uniform_real_distribution<double>(0,1)(random_number_generator_)<lookup_table_[energy_contribution_of_chosen_spin]) {
            FlipSpin(row, column);
        }
    }
    else{
        FlipSpin(row, column);
    }
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//helper functions
void Ising_System::FlipSpin(const int row,const int column){
    
    energy_+=2*GetEnergyContribution(row, column);
    
    ising_spins_[row][column]=!ising_spins_[row][column];
    
    if (ising_spins_[row][column]) {
        magnetization_+=2;
    }
    else{
        magnetization_-=2;
    }
}
///////////////////////////////////////////////////////////////////////////
const bool Ising_System::GetSpinAbove(const int row,const int column)const{
    //account for periodic BC
    if (row==system_width_-1) {
        return ising_spins_[0][column];
    }
    else{
        return ising_spins_[row+1][column];
    }
}
///////////////////////////////////////////////////////////////////////////
const bool Ising_System::GetSpinBelow(const int row,const int column)const{
    //account for periodic BC
    if (row==0) {
        return ising_spins_[system_width_-1][column];
    }
    else{
        return ising_spins_[row-1][column];
    }
}
///////////////////////////////////////////////////////////////////////////
const bool Ising_System::GetSpinLeft(const int row,const int column)const{
    //account for periodic BC
    if (column==0) {
        return ising_spins_[row][system_width_-1];
    }
    else{
        return ising_spins_[row][column-1];
    }
}
///////////////////////////////////////////////////////////////////////////
const bool Ising_System::GetSpinRight(const int row,const int column)const{
    //account for periodic BC
    if (column==system_width_-1) {
        return ising_spins_[row][0];
    }
    else{
        return ising_spins_[row][column+1];
    }
}
///////////////////////////////////////////////////////////////////////////
const int Ising_System::GetEnergyContribution(const int row,const int column)const{
    
    int contributions=0;
    
    if (ising_spins_[row][column]==GetSpinAbove(row, column)) {
        ++contributions;
    }
    else --contributions;
    if (ising_spins_[row][column]==GetSpinBelow(row, column)) {
        ++contributions;
    }
    else --contributions;
    if (ising_spins_[row][column]==GetSpinLeft(row, column)) {
        ++contributions;
    }
    else --contributions;
    if (ising_spins_[row][column]==GetSpinRight(row, column)) {
        ++contributions;
    }
    else --contributions;
    
    return contributions;
}
///////////////////////////////////////////////////////////////////////////
long Ising_System::GetMagnetization()const{
    return magnetization_;
}
///////////////////////////////////////////////////////////////////////////
long Ising_System::GetEnergy()const{
    return energy_;
}
///////////////////////////////////////////////////////////////////////////
