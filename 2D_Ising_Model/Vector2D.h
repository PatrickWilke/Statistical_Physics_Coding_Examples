//  Created by Patrick Wilke on 27.05.19.
//  Copyright © 2019 Patrick Wilke. All rights reserved.
//

#ifndef VEC_2D_hpp
#define VEC_2D_hpp

#include <memory>
#include <new>
#include <type_traits>
#include <limits>

//Just ignore this code. I added it for convenience and to speed the code up a little.
template<class DataType>
class Vector2D{
    
 public:
    
    Vector2D(const long width,const long length,DataType data_init):width_{width},data_(new DataType[width*length]){
        for (long long i=0; i<width*length; ++i) {
            data_[i]=data_init;
        }
    }
    
    template<class IndexType>
    DataType* operator[](const IndexType row)const{
        static_assert(std::numeric_limits<IndexType>::is_integer,
                      "[] can only be used with integer datatypes");
        return data_.get()+width_*row;
    }
    
 private:
    
    const long width_;
    const std::unique_ptr<DataType[]> data_;
};


#endif /* VEC_2D_hpp */
