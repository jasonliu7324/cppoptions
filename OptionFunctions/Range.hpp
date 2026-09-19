//  Header file for template class Range
//
//  Convience class with interval functionalities
//
//

#ifndef RANGE_HPP
#define RANGE_HPP

#include <vector>

template <typename T>
class Range
{
    private:
        T lower;        // Lower bound
        T upper;        // Upper bound
    public:
        Range();                                // Default constructor
        Range(const T& low, const T& high);     // Specific constructor
        Range(const Range<T>& source);          // Copy constructor

        Range<T>& operator = (const Range<T>& comp);        // Assignment operator

        ~Range();       // Destructor

        // Setter
        void lower(const T& val) {lower = val;};       
        void upper(const T& val) {upper = val;};

        // Getter
        T lower() const {return lower;};
        T upper() const {return upper;};

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
Range<T>& Range<T>::operator = (const Range<T>& comp)
{
    if (this == &source)
    {
        return *this;
    }

    upper = comp.upper;
    lower = comp.lower;

    return *this;
}

// Default destructor
template <typename T>
Range<T>::~Range() {};

// Mesh generator
template <typename T> 
std::vector<T> Range<T>::mesh(long steps) const
{
    T h = static_cast<int>(std::round(upper - lower) / T(steps));       // Step size
    std::vector<T> result(steps + 1);                                   // return vector

    for (long i = 0; i < steps; ++i)
    {
        result.push_back(lower + i * h);
    }

    return result;
}


#endif  // RANGE_HPP