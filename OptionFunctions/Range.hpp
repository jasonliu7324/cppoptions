//  Header file for template class Range
//
//  Convience class with interval functionalities
//
//

#ifndef RANGE_HPP
#define RANGE_HPP

#include <vector>
#include <cmath>

template <typename T>
class Range
{
    private:
        T lower_;        // Lower bound
        T upper_;        // Upper bound
    public:
        Range();                                // Default constructor
        Range(const T& low, const T& high);     // Specific constructor
        Range(const Range<T>& source);          // Copy constructor

        Range<T>& operator = (const Range<T>& comp);        // Assignment operator

        ~Range();       // Destructor

        // Setter
        void lower(const T& val) {lower_ = val;};       
        void upper(const T& val) {upper_ = val;};

        // Getter
        T lower() const {return lower_;};
        T upper() const {return upper_;};

        std::vector<T> mesh(long steps) const;      // Mesh generator
};

// Class implementation

// Default constructor
template <typename T> 
Range<T>::Range() : lower(0), upper(0) {};

// Specific constructor
template <typename T> 
Range<T>::Range(const T& low, const T& high) : lower(low), upper(high) {};

// Copy Constructor
template <typename T>
Range<T>::Range(const Range<T>& source) : lower(source.lower), upper(source.upper) {};

// Assignment operator
template <typename T>
Range<T>& Range<T>::operator = (const Range<T>& source)
{
    if (this == &source)
    {
        return *this;
    }

    upper_ = comp.upper_;
    lower_ = comp.lower_;

    return *this;
}

// Default destructor
template <typename T>
Range<T>::~Range() {};

// Mesh generator
template <typename T> 
std::vector<T> Range<T>::mesh(long steps) const
{
    T h = (std::round(upper_ - lower_) / T(steps));       // Step size
    std::vector<T> result.reserve(steps + 1);             // return vector

    for (long i = 0; i <= steps; ++i)
    {
        result.push_back(lower_ + i * h);
    }

    return result;
}


#endif  // RANGE_HPP