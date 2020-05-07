//Sparse matrix representation with C++
#include<iostream>
#include<stdexcept>


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

    int getNumberOfNotZeros() const;

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
    SparseMatrix sm1(10, 10, 7);

    std::cout << "There are " << sm1.getNumberOfNotZeros() << " not zero matrix elements" << std::endl;


    return 0;
}

struct SparseMatrix::Element
{
    int rowNumber;
    int columnNumber;
    int value;
};

SparseMatrix::SparseMatrix(int rows, int columns, int elementNumber)
{
    if(elementNumber > (rows * columns))
        throw std::invalid_argument("The number of elements (third argument) must be less than the product of rows * columns");

    this->rows = rows;
    this->columns = columns;
    numberOfNotZeros = elementNumber;
    arrayPointer = new Element [numberOfNotZeros];

    if(numberOfNotZeros > 0)
    {
        std::cout << "Please enter the " << numberOfNotZeros << " element" << (numberOfNotZeros > 1 ? "s" : "") << std::endl;
        std::cout << "The values of the row number, column number and the element's value must be separated by an empty space" << std::endl;
        
        for(int i = 1; i<=numberOfNotZeros; i++)
        {
            std::cout << i << "s" << " element: ";
            if(std::cin.good())
               std::cin >> arrayPointer[i].rowNumber >> arrayPointer[i].columnNumber >> arrayPointer[i].value;
            else
                std::cout << "Sorry, for some reason the input isn't working properly" << std::endl;
        } 

        std::cout << "All the elements have just been included to the matrix" << std::endl;  
    }
}

int SparseMatrix::getNumberOfNotZeros() const
{
    return numberOfNotZeros;
}


