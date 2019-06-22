//  Created by Patrick Wilke on 27.05.19.
//  Copyright © 2019 Patrick Wilke. All rights reserved.
//

#ifndef D_Ising_System_hpp
#define D_Ising_System_hpp

#include <array>
#include <random>
#include <cmath>
#include "Vector2D.h"

class Ising_System{

public:
    //Constructor
    Ising_System(const double temperature, const int system_width);
    
    //simulation functions
    void Simulate(const long iteration_steps);

    void IterationStep();

    long GetMagnetization()const;

    long GetEnergy()const;

private:
    //helper functions
    void FlipSpin(const int row,const int column);

    const bool GetSpinAbove(const int row,const int column)const;
   
    const bool GetSpinBelow(const int row,const int column)const;
    
    const bool GetSpinLeft(const int row,const int column)const;
    
    const bool GetSpinRight(const int row,const int column)const;
    
    const int GetEnergyContribution(const int row,const int column)const;

    //system length scale
    const int system_width_;
    
    //spin-spin coupling
    const double beta_J_;
    const std::array<const double, 5> lookup_table_;

    //observables
    long magnetization_;
    long energy_;

    //spin representation
    Vector2D<bool> ising_spins_;

    //rng engine
    std::mt19937 random_number_generator_;
};

#endif /* D_Ising_System_hpp */
