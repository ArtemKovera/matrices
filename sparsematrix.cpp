//Sparse matrix representation with C++
#include<iostream>
#include<stdexcept>
#include<cstdlib>


//this class uses so-calles three column sparse matrix representation 
//this way of sparse matrix representation allows saving space
class SparseMatrix
{
public:
    //this constructor creates a matrix using three column sparse matrix representation
    //the constructor takes 3 arguments: number of rows, number of columns, and number of not zero elements 
    //it throws invalid_argument exeption if the third argument is greater than the product of the two other arguments
    SparseMatrix(int, int, int);

    //default constructot sets number of rows, number of columns, and number of not zero elements to zero
    SparseMatrix();

    SparseMatrix operator+(const SparseMatrix&) const;

    SparseMatrix operator-(const SparseMatrix&) const;

    int getNumberOfNotZeros() const;

    //this function prints the matrix in the console
    //the time complexity of this function is O(n^3)
    void showMatrix() const;


private:
    struct Element;
    int rows;
    int columns;
    int numberOfNotZeros;

    Element* arrayPointer = nullptr;

    void clear(Element*);

    //helper function which is used in + and - operator overloads
    int combinedNumberOfNotZeros(const SparseMatrix&, const SparseMatrix&) const;

};




int main ()
{
    SparseMatrix sm1(10, 10, 3);

    //std::cout<<"There are "<<sm1.getNumberOfNotZeros()<<" not zero matrix elements"<<std::endl;

    std::cout<<std::endl;

    std::cout<<"Matrix sm1: " << std::endl;
    sm1.showMatrix();

    std::cout<<std::endl;
    SparseMatrix sm2(10, 10, 2);
    std::cout<<"Matrix sm2: " << std::endl;
    sm2.showMatrix();
    std::cout<<std::endl;

    SparseMatrix sm3 = sm1 + sm2;

    std::cout<<"Matrix sm3: " << std::endl;
    sm3.showMatrix();
    std::cout<<"There are "<<sm3.getNumberOfNotZeros()<<" not zero matrix elements"<<std::endl;

    //std::cout<<std::endl;




    return 0;
}

struct SparseMatrix::Element
{
    int rowNumber;
    int columnNumber;
    int value;
};

SparseMatrix::SparseMatrix(): rows{0}, columns{0}, numberOfNotZeros{0}, arrayPointer{nullptr} {}

SparseMatrix::SparseMatrix(int rows, int columns, int elementNumber)
{
    if(elementNumber > (rows * columns))
        throw std::invalid_argument("The number of elements (third argument) must not be greater than the product of rows * columns");

    this->rows = rows;
    this->columns = columns;
    numberOfNotZeros = elementNumber;
    arrayPointer = new Element [numberOfNotZeros];
    int i = 0; 
    if(numberOfNotZeros > 0)
    {
        std::cout << "Please enter the " << numberOfNotZeros << " element" << (numberOfNotZeros > 1 ? "s" : "") << std::endl;
        std::cout << "The values of the row number, column number and the element's value must be separated by an empty space" << std::endl;
        
        while( i != (numberOfNotZeros))
        {
            std::cout << i+1 << "s" << " element: ";
            if(std::cin.good())
               std::cin >> arrayPointer[i].rowNumber >> arrayPointer[i].columnNumber >> arrayPointer[i].value;
            else
            {
                std::cout << "Sorry, for some reason the input isn't working properly" << std::endl;
                exit(1);
            }
                
            i++;
        } 

        std::cout << "All the not elements have just been included to the matrix" << std::endl;  
    }
}

int SparseMatrix::getNumberOfNotZeros() const
{
    return numberOfNotZeros;
}

void SparseMatrix::showMatrix() const
{
    int i, j, k;
    bool flag;
    for(i=0; i<rows; i++)
    {
        for(j=0; j<columns; j++)
        {
            flag = true;
            k = 0;
            while( k != numberOfNotZeros)
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

SparseMatrix SparseMatrix::operator+(const SparseMatrix& other) const
{
    if((rows != other.rows) || (columns != other.columns))
        throw std::invalid_argument("The dimensions of both matrices must be the same");

    SparseMatrix result;
    result.rows = rows;
    result.columns = columns;
    int count = combinedNumberOfNotZeros(*this, other);
    int i, j, k, t;

    result.numberOfNotZeros = count;
    result.arrayPointer = new Element [count];
    
    
    if(count == (numberOfNotZeros + other.numberOfNotZeros))
    {
        for(i = 0; i<numberOfNotZeros; i++)
            result.arrayPointer[i] = arrayPointer[i];

        for(i = numberOfNotZeros, j = 0; i<count; i++, j++)
            result.arrayPointer[i] = other.arrayPointer[j];

        return result;
    }    
    
    bool match;

    for(i=0; i<numberOfNotZeros; i++)
    {
        match = false;
        for(j=0; j<other.numberOfNotZeros; j++)
        {
            if((arrayPointer[i].rowNumber == other.arrayPointer[j].rowNumber) &&
               (arrayPointer[i].columnNumber == other.arrayPointer[j].columnNumber))
            {
                result.arrayPointer[i] = arrayPointer[i];
                result.arrayPointer[i].value = arrayPointer[i].value + other.arrayPointer[i].value;
                match = true;
                break;
            }

        }
        if(!match)
        {
            result.arrayPointer[i] = arrayPointer[i];
        }
    }

    for(i = 0; i<numberOfNotZeros; i++)
    {
        for(j = 0, t = numberOfNotZeros; j<other.numberOfNotZeros; j++, t++)
        {
            if((result.arrayPointer[i].rowNumber != other.arrayPointer[j].rowNumber) || 
               (result.arrayPointer[i].columnNumber != other.arrayPointer[j].columnNumber))
            {
                result.arrayPointer[t] = other.arrayPointer[j];
            }
        }
    } 

    return result;
}

int SparseMatrix::combinedNumberOfNotZeros(const SparseMatrix& src1, const SparseMatrix& src2) const
{
    int i, j, count;
    count = src1.numberOfNotZeros + src2.numberOfNotZeros;
    for(i=0; i<src1.numberOfNotZeros; i++)
    {
        for(j=0; j<src2.numberOfNotZeros; j++)
        {
            if((src1.arrayPointer[i].rowNumber == src2.arrayPointer[j].rowNumber) &&
               (src1.arrayPointer[i].columnNumber == src2.arrayPointer[j].columnNumber))
               {
                   count--;
               }
        }
    }
    return count;
}



