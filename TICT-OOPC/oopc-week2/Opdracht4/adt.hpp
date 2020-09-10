#ifndef ADT_HPP
#define ADT_HPP

#include <iomanip>
#include <iostream>
/// @file

/// \brief
/// Vector ADT
/// \details
/// This is an ADT that implements a math vector 
/// with an x coordinate and a y coordinate
class vector{
private:
    int x, y;

public:

    /// \brief
    /// Constructor with default inputs
    /// \details
    /// This constructor loads default values if
    /// none are submitted.
    vector(int x = 0, int y = 0);

    /// \brief
    /// Compare two vectors
    /// \details
    /// This operator returns true or false depending
    /// on if the entered vectors are the same or not
    bool operator==(const vector & rhs) const;

    /// \brief
    /// Add vectors
    /// \details
    /// This operator adds the x values of both vectors
    /// and adds the y value of both vectors and saves it
    /// in another vector
    vector operator+(const vector & rhs) const;

    /// \brief
    /// Add vectors
    /// \details
    /// This operator adds the x values of both vectors
    /// and adds the y value of both vectors and saves it
    /// in another vector
    vector operator+(const vector & lhs, const vector & rhs);

    /// \brief
    /// Add vector
    /// \details
    /// This operator adds the x value of both vectos
    /// and add the y value of both vectors ans saves it
    /// in the lhs
    vector & operator+=(const vector & rhs);

    /// \brief
    /// Multipy vector
    /// \details
    /// This operator multiplies a vector with another vector
    vector operator*(const vector & rhs) const;

    /// \brief
    /// Multipy vector
    /// \details
    /// This operator multiplies an integer with another vector
    vector operator*(const int x, const vector & lhs);

    /// \brief
    /// Multipy vector
    /// \details
    /// This operator multiplies an integer with another vector
    vector operator*(const vector & rhs, const int x);
    
    /// \brief
    /// Multiply vector
    /// \details
    /// This operator multiplies a vector with another vector
    vector & operator*=(const vector & rhs);

    /// \brief
    /// Outputs vector in hex 
    /// \details
    /// This operator outputs the contents of a vector to
    /// the terminal.
    friend std::ostream & operator<<(std::ostream & lhs, const vector & rhs);

};

#endif