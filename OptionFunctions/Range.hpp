//  Header file for template class Range
//
//  Convience class with interval functionalities
//
//

#ifndef RANGE_HPP
#define RANGE_HPP

template <typename T>
class Range
{
    private:
        T lower;
        T upper;
    public:
        Range<T>::Range() : lower(0), upper(0) {};
        Range<T>::Range(const T& val1, const T& val2) : lower(val1), upper(val2) {};

};

#endif  // RANGE_HPP