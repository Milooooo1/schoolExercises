#include <iostream>
#include <vector>


bool is_sorted(const std::vector<float>& vect, unsigned int i = 0);


bool is_sorted(const std::vector<float>& vect, unsigned int i)
{
    if(i == vect.size()-1)
        return true;

    return ((vect[i+1] > vect[i]) ? (is_sorted(vect, i+1)) : (false));
}


int main(void)
{
    std::cout << is_sorted({1.9,2.4,4.5,5.6}) << std::endl;
    std::cout << is_sorted({5.0,4.0,3.0}) << std::endl;

    return 0;