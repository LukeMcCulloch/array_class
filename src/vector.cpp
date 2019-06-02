

#include <iostream>

#include "../include/vector.h"

// CONSTRUCTORS ----------------------------------------------------------------

// template <class T>
// Vector<T> :: Vector( ){
//     x=0.;
//     y=0.;
//     z=0.;
//     printf("0");
// }

//template <class T>
Vector::Vector( void )
// initializes all components to zero
: x( 0. ),
  y( 0. ),
  z( 0. )
{
    printf("\n1");
};


//template <class T>
Vector::Vector( double x0,
                   double y0,
                   double z0 )
// initializes with specified components
: x( x0 ),
  y( y0 ),
  z( z0 )
{
    printf("\n2");
};


//template <class T>
Vector::Vector(const  Vector& v )
// initializes from existing vector
: x( v.x ),
  y( v.y ),
  z( v.z )
{
    printf("\n3");
};


//template<class T>
Vector::~Vector(){
}