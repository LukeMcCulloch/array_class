/*
Specialization of Array2D to vector
*/

//=================================
#ifndef Special_VECTOR_H
#define Special_VECTOR_H

//=================================
#include <cassert>
#include <iostream>
#include <limits>


//=================================
#include "../include/tests_array.hpp"
#include "../include/array_template.hpp"
#include "../include/arrayops.hpp"

//template <class T>
class Vector{

public:
    // CONSTRUCTORS ----------------------------------------------------------
    //Vector();                        // default init to zero
    Vector( void );                        // initializes all components to zero
    Vector( double x, double y, double z); // initializes with specified components
    Vector(const Vector& v );             // initializes from existing vector
   

    // destructor
    ~Vector ();

    // STORAGE ---------------------------------------------------------------
    double x, y, z; // components

};
#endif