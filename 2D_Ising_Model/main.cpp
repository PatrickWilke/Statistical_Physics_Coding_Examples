//  Created by Patrick Wilke on 27.05.19.
//  Copyright © 2019 Patrick Wilke. All rights reserved.
//

#include "Time_Series.hpp"
#include <vector>
#include <string>
#include <iostream>


int main(int argc, char const* argv[]){
    
    //check for proper input
    if (argc<4) {
        std::cout<<"Three arguments required: \n";
        std::cout<<"T min, T max, T steps.\n";
        std::cout<<"Additional arguments are interpreted as list of system sizes for which the simulations will be performed (default: 32)\n";
        exit(EXIT_FAILURE);
    }
    
    //set up system sizes
    std::vector<int> system_sizes;
    if (argc==4) {//case we look at on the first problem set
        system_sizes.push_back(32);
    }
    else{//for the finite size scaling problem we do later
        for(int i=4; i<argc;++i){
            system_sizes.push_back(std::stoi(argv[i]));
        }
    }
    
    //sweep the stationary observalbes for different system sizes and  temperatures in given range
    for(const auto size: system_sizes){
            
        std::ofstream file;
        //this will destroy old results -> stored them in a different directory if you wantto keep them!!!!
        file.open ("L_"+std::to_string(size)+"_sweep.txt");
            
        double T_min=std::stod(argv[1]);
        const double T_max=std::stod(argv[2]);
        const double T_step=std::stod(argv[3]);
        
        //just for conviniance
        const double inv_size_square=1.0/(static_cast<double>(size)*static_cast<double>(size));
        
        //run sweep
        while (T_min<=T_max+0.00001) {
                
            Time_Series sys(T_min,size);
            
            //run simulation
            sys.PerformSeries(20000*size*size,100*size*size,1000*size*size);
            
            //create output line
            file<<T_min<<" "<<sys.GetAverageMagnetizationABS()*inv_size_square<<" "<<sys.GetAverageEnergy()*inv_size_square<<" "<<sys.GetSpecificSusceptibility()<<" "<<sys.GetSpecificHeat()<<"\n";
                
                T_min+=T_step;
            }
            
            file.close();
    }

    return EXIT_SUCCESS;
}
