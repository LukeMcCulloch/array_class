
//=================================
// include guard
#ifndef __ARRAY_TEMPLATE_INCLUDED__
#define __ARRAY_TEMPLATE_INCLUDED__

//=================================
// array class
#include <cassert>
#include <iostream>
#include <limits>


//=================================
using namespace std;



template <class T>
class Array2D; //fwd declaration



// undefine to disable range checking
#define RANGE_CHECK


class overdetermined : public std::domain_error{

   public:
     overdetermined() 
        : std::domain_error("solution is over-determined")
     {}
};

class underdetermined : public std::domain_error{

   public:
      underdetermined() 
         : std::domain_error("solution is under-determined")
      {}
};



//bracket_proxy is parameterized with Array2D
template <typename ArrayClass, typename Result>
class bracket_proxy{
    public:
        bracket_proxy(ArrayClass& A, size_t r): A(A), r(r){}

        Result& operator[](size_t c){return A(r,c); }
    private:
        ArrayClass& A;
        size_t r;
};






template <class T>
class Array2D{

    void check_indices(size_t i, size_t j) const{
        assert(i >= 0 && i < nrows);
        assert(j >= 0 && j < ncols);
    }

    void check_size(size_t other_nrows,size_t other_ncols) const { 
        assert(nrows == other_nrows);
        assert(ncols == other_ncols); 
    }

    void check_index(size_t i) const { assert(i >= 0 && i < nrows); }

    void check_size(size_t i) const { assert(i >= 0 && i < storage_size); }

    private:
        size_t nBytes;

    public:

        // set up data size of matrix
        size_t nrows, ncols;
        size_t storage_size;

        // malloc host memory
        T* array;
        
        // explicit constructor declaring size nrow,ncol:
        explicit Array2D(size_t numrows, size_t numcols): 
                        nrows(numrows), ncols(numcols){
            //cout << "building \n" << endl;
            //buildWithParameters(numrows, numcols);
            build();
            //cout << "built \n" << endl;
            //initialize();
            //cout << "initialized \n" << endl;
        }
            
        Array2D();
        
        //copy constructor 
        Array2D(const Array2D& A);

        // destructor
        ~Array2D ();

        //methods:
        void build();
        void buildWithParameters(size_t, size_t);
        //void initialize();
        void setonce( T data);
        void prsize_t();

       
        void cache() const {}

        // Array2D& val() const {
        //     return *this;
        // }
        Array2D<T> val() const {
            return *this;
        }

        //
        size_t getnrows() const {
            return nrows;
        }
        size_t getncols() const {
            return ncols;
        }
        // return size
        size_t size() const {
            return storage_size;
        }
        
        // Operators:
        T& operator() (size_t row, size_t col);        // Subscript operators in pairs
        const T&  operator() (size_t row, size_t col) const;  
        
        T& operator() (size_t i);        // Subscript operator
        const T&  operator() (size_t i) const;  
        
        
        Array2D operator = (const Array2D&);
        Array2D operator = (const T a);


        // for linear algebra operations see: arrayops.hpp
        
        // array[][] access:
        bracket_proxy<Array2D, T> operator[](size_t r){
            return bracket_proxy<Array2D, T>(*this, r);
        }
};


template<class T>
Array2D<T>::~Array2D(){
    delete[] array;
}

template <class T>
Array2D<T>::Array2D(){
    //nrows = 4;
    //ncols = 4;
    cout << "build \n" << endl;
    //build();
    // cout << "initialize\n" << endl;

    //memset(array, 0, nBytes);
}




// new array:
template <class T>
void Array2D<T>::build(){
    storage_size = nrows*ncols;
    nBytes = storage_size * sizeof(T);
    array = new T[storage_size];
    //print("\n build  \n");

    size_t i = 0;
    for(i=0; i < storage_size; i++) {
        array[i] = 0.;
    }

}


template <class T>
void Array2D<T>::buildWithParameters(size_t numrows, size_t numcols){
    nrows = numrows;
    ncols = numcols;
    cout << "build with parameters \n" << endl;
    build();
}


// copy constructor:
template <class T>
Array2D<T>::Array2D(const Array2D& other)
    : nrows(other.nrows), ncols(other.ncols){
    storage_size = nrows*ncols;
    nBytes = storage_size * sizeof(T);

    array = new T[storage_size];

    //print("\narray copy constructor\n");
    size_t i = 0;
    for(i=0; i < storage_size; i++) {
       array[i] = other.array[i];
    }
}



template <class T>
T& Array2D<T>::operator()(size_t i, size_t j) {
	check_indices(i,j);
    return array[i*ncols + j];
}
template <class T>
const T& Array2D<T>::operator()(size_t i, size_t j) const {
	check_indices(i,j);
    return array[i*ncols + j];
}


template <class T>
T& Array2D<T>::operator()(size_t i) {
	check_size(i);
    return array[i];
}
template <class T>
const T& Array2D<T>::operator()(size_t i) const {
	check_size(i);
    return array[i];
}


template <class T>
Array2D<T> Array2D<T>::operator=(const Array2D& that) {
    /*not using this check  allows delayed allocation 
    of this array type when using it within another class*/
	assert(that.nrows == nrows);
	assert(that.ncols == ncols);

    size_t i;
    for(i=0; i < storage_size; i++) {
    	array[i] = that.array[i];
    }
    return *this;
}
template <class T>
Array2D<T> Array2D<T>::operator=(const T a) {
    size_t i;
    for(i=0; i < storage_size; i++) {
    	array[i] = a;
    }
    return *this;
}





/**/  //TODO, use this: 
template <class T>
void Array2D<T>::setonce(T data){
    size_t i = 0;
    size_t j = 0;

    for(i=0; i<nrows; i++){
        for(j=0; j<ncols; j++) {
            array[i*ncols + j] = data;
            data++;
        }
    }
}
/**/





template <class T>
void Array2D<T>::prsize_t(){
    size_t i,j;
    size_t oldp = cout.precision(numeric_limits<T>::digits10 + 1);
    for( i=0; i<nrows; i++) {
        for(j=0; j<ncols; j++) {
            cout << i << " " << j << " " << &array[i*ncols + j] << endl;
            cout << array[i*ncols + j] << endl;
        }
    }
    cout << "\n" << endl;
    cout.precision(oldp);
}



template <class T>
T sum (T a, T b){
  T result;
  result = a + b;
  return result;
}





#endif //__ARRAY_TEMPLATE_INCLUDED__
