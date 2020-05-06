//Sparse matrix representation with C++
#include<iostream>


//this class uses so-calles three column sparse matrix representation 
//this way of sparse matrix representation allows saving space
class SparseMatrix
{
public:
    //this constructor creates a matrix using three column sparse matrix representation
    //the constructor takes 3 arguments: number of rows, number of columns, and number of not zero elements 
    SparseMatrix(int, int, int);

    SparseMatrix operator+(const SparseMatrix&);
    SparseMatrix operator-(const SparseMatrix&);

private:
    struct Element;
    int rows;
    int columns;
    int numberOfNotZeros;

    Element* arrayPointer;

    void clear(Element*);
};


int main ()
{



    return 0;
}

struct SparseMatrix::Element
{
    int rowNumber;
    int columnNumber;
    int value;
};

SparseMatrix::SparseMatrix(int r, int c, int nNZ): rows{r}, columns{c},
numberOfNotZeros{nNZ}, arrayPointer{new Element [nNZ]} {}


