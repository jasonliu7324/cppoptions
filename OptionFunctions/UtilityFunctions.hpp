//  General Utility functions that are not finance related
//
//
//
//

#include <vector>;

// Generic vector print function
template <typename T>
void print(const std::vector<T>& list)
{
    std::cout << std::endl << "Size of vector is: " << list.size() << "\n[";

    typename std::vector<T>::const_iterator i;
    for (i = list.begin; i != list.end(); ++i)
    {
        std::cout << *i << ", ";
    }

    std::cout << "]\n";
}