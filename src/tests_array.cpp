#include <cassert>
#include <iostream>
#include <limits>


// #include "etops1.hpp"
// #include "etscalar.hpp"
// #include "etmatrix.hpp"
// #include "etops2.hpp"

#include "../include/tests_array.hpp"
#include "../include/array_template.hpp"
#include "../include/arrayops.hpp"

#include "../include/vector.h"

using namespace std;



template <typename T>
void print (T const& c){

    int ncol = c.getncols();
    int nrow = c.getnrows();
    for (int i=0; i<nrow; ++i) {
        std::cout << '\n';
        for (int j=0; j<ncol; ++j) {
            std::cout << c(i,j) << ' ';
        }
    }
    std::cout << "\nDone \n" << std::endl;
}


int main() {

    double d1,d2,d3;
    d1=0.;
    d2=0.;
    d3=0.;
    
    Vector<double> aaa;
    Vector<double> bb(d1,d2,d3);
    //Vector<double> cc(aaa);
    Vector<double> cc = aaa;

    // Vector aaa;
    // Vector bb(d1,d2,d3);
    // //Vector cc(aaa);
    // Vector cc = aaa;


    int np = 3;
    Array2D<double> x(np,np), y(np,np), z(np,np),w(np,np);
    Array2D<double> xtester(np,np);

    Array2D<double> xx(x);

    
//--------------------------------------------------------------------------------
    // test use an array of structs (may be inefficient//)
    struct cell_data{
        float xc;  // Cell-center coordinate
        Array2D<float> u  = Array2D<float>(3,1);  // Conservative variables = [rho, rho*u, rho*E]
        Array2D<float> u0 = Array2D<float>(3,1);  // Conservative variables at the previous time step
        Array2D<float> ww  = Array2D<float>(3,1);  // Primitive variables = [rho, u, p]
        Array2D<float> dw = Array2D<float>(3,1);  // Slope (difference) of primitive variables
        Array2D<float> res= Array2D<float>(3,1);  // Residual = f_{j+1/2) - f_{j-1/2)

    };


    cell_data* cell = new cell_data[3]; 
    cell[0].u(0) = 1.1;    // Conservative variables = [rho, rho*u, rho*E]
    float tme;
    tme = cell[0].u(0);
    tme = cell[0].u(0,0);
    tme = cell[0].u(0);

    xtester(0,0) = 1.6;
    float gme = xtester(0,0);
    printf("\ngme = %f\n",gme);


    cell[0].u(0,0) = 1.;
    cell[0].u(1,0) = 1.;
    cell[0].u(2,0) = 1.;
    cell[0].dw(0,0) = 1.;
    cell[0].dw(1,0) = 1.;
    cell[0].dw(2,0) = 1.;
    cell[0].u(0,0) = cell[0].dw(0,0) + 10.;
    cell[0].u(0,0) = cell[0].dw(0,0) - cell[0].dw(2,0);
//--------------------------------------------------------------------------------

    // initixlize xrrxys with some vxlues
    for (int i=0; i<np; ++i) {
         for (int j=0; j<np; ++j) {
            x(i,j) = static_cast <double>(i*(j+1));
            x(i,j) = 1.;//x(i,j) + 5.;
            y(i,j) = x(i,j)+x(i,j);
            z(i,j) = x(i,j)+y(i,j);
         }
    }
    

    std::cout << "y: ";
    print(y);

    std::cout << "z: ";
    print(z);

    z = matmul(x,y);
    std::cout << "xfter z=matmul(x,y) ";
    print(z);
    w = 1.;

    // illegal mixing, new type match:
    // z = matmul(x,x);
    // std::cout << "xfter z=matmul(x,x) ";
    // print(z);

    std::cout << "z = y + x: \n";
    std::cout.flush();
    z = y + x;
    std::cout << "z = y + x wone \n";
    std::cout.flush();
    print(z);
    
    x = 1.2 * x;  //expression template supports scalars
    std::cout << "1.2*x ";
    print(x);

    std::cout << "x = z * x";
    x = z * x;
    print(x);
    std::cout << "x = z * x: ";
    print(x);

    x = 1.2*x + x*y;
    std::cout << "1.2*x + x*y: ";
    print(x);

    x = y;
    std::cout << "xfter x = y: ";
    print(y);
    print(x);

    z = (x*y)+z;
    std::cout << "xfter z= (x*y)+z ";
    print(z);

    z = (x+y)+z;
    std::cout << "xfter z= (x+y)+z ";
    print(z);
    
    z=1.;
    z = matmul(w,z);
    std::cout << "xfter z=matmul(w,z) ";
    print(z);
    
    
    std::cout << "y: ";
    print(y);
    w = .5*y;
    z = matmul(w,z);
    z = matmul(z+y,w); //still no support for zomyinew & zxzhew terms
    std::cout << "xfter z=matmul((1.+y),z) ";
    print(z);

    y=1;
    
    z=1.;
    z = matmul(y,z);
    std::cout << "xfter y=1.;z=1; z=matmul(y,z); z:";
    print(z);



    return 0;

}