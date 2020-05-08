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

    //this function prints the matrix in the console
    //the time complexity of this function is O(n^3)
    void showMatrix() const;

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
    SparseMatrix sm1(10, 10, 3);

    std::cout << "There are " << sm1.getNumberOfNotZeros() << " not zero matrix elements" << std::endl;
    

    std::cout<<std::endl;

    sm1.showMatrix();

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
        throw std::invalid_argument("The number of elements (third argument) must not be greater than the product of rows * columns");

    this->rows = rows;
    this->columns = columns;
    numberOfNotZeros = elementNumber;
    arrayPointer = new Element [numberOfNotZeros];
    int i = 1; 
    if(numberOfNotZeros > 0)
    {
        std::cout << "Please enter the " << numberOfNotZeros << " element" << (numberOfNotZeros > 1 ? "s" : "") << std::endl;
        std::cout << "The values of the row number, column number and the element's value must be separated by an empty space" << std::endl;
        
        while( i != (numberOfNotZeros + 1))
        {
            std::cout << i << "s" << " element: ";
            if(std::cin.good())
               std::cin >> arrayPointer[i].rowNumber >> arrayPointer[i].columnNumber >> arrayPointer[i].value;
            else
                std::cout << "Sorry, for some reason the input isn't working properly" << std::endl;
            i++;
        } 

        std::cout << "All the elements have just been included to the matrix" << std::endl;  
    }
}

int SparseMatrix::getNumberOfNotZeros() const
{
    return numberOfNotZeros;
}

void SparseMatrix::showMatrix() const
{
    int i, j, k;
    bool flag = true;
    for(i=0; i<rows; i++)
    {
        for(j=0; j<columns; j++)
        {
            flag = true;
            k = 1;
            while( k != (numberOfNotZeros + 1))
            {
                if(arrayPointer[k].rowNumber == i && arrayPointer[k].columnNumber == j)
                {
                    std::cout << arrayPointer[k].value << " ";
                    flag = false;
                    break;
                }
                k++;
            }
            if(flag) 
                std::cout << "0 ";
            
        }
        std::cout << std::endl;
    }
}

