//C++ class for square diagonal matrix (N x N) using stl vector

#include<iostream>
#include<vector>
#include <cassert> 
#include <stdexcept>


class SquareDiagonalMatrix
{

private:

    //square diagonal matrix is represented by one-dimensional vector
    std::vector<int> matrix;

public:

    
    SquareDiagonalMatrix (int rows, int columns)
    {
       //number of rows must be equal to the number of columns
       assert(rows==columns);
       // and both must be positive
       assert(rows>0 and columns>0);

       matrix.reserve(rows); 
    }
    
    //in this constructor, only one dimension is used to instantiate the matrix
    //it's implied that the other dimension is equal to this dimension
    explicit SquareDiagonalMatrix (int dimension)
    {
        //dimension must be greater than zero
        assert(dimension>0);

        matrix.reserve(dimension);
    }
    
    
    int getElement (int row, int column)
    {   
        if (row < 1 or column < 1 or row > matrix.capacity() or column > matrix.capacity())
        {
            throw std::out_of_range("Please enter appropriate coordinates for the element");
        }
        else if (row==column)
        {
            return matrix[row - 1];
        }
        else
        {
            return 0;
        }
    }
    
    int getElement (int row)
    {
        if (row < 1 or row > matrix.capacity())
        {
            throw std::out_of_range("Please enter appropriate row");
        }

        return matrix[row - 1];
    }
    

    void setElement (int row, int value)
    {
        if (row < 1 or row > matrix.capacity())
        {
            throw std::out_of_range("Please enter appropriate row");
        }

        matrix[row-1] = value; 
    } 

    void showMatrix ()
    {
        for (int i = 0; i < matrix.capacity(); i++)
        {
            for (int j = 0; j < matrix.capacity(); j++)
            {
                if (i==j)
                {
                    std::cout << matrix[i] << " ";
                } 
                else
                {
                    std::cout << "0 ";
                }
                
            }
            std::cout << std::endl;
        }
    }

};

int main ()
{
    SquareDiagonalMatrix dm1(10, 10);
    
    
    try
    {
    dm1.setElement(1, 25);
    std::cout << dm1.getElement(1) << std::endl;
    std::cout << dm1.getElement(9) << std::endl;
    std::cout << dm1.getElement(12, 12) << std::endl;
    }
    catch(std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "--------------\n";
    SquareDiagonalMatrix dm2 (5);
    try
    {
    dm2.setElement(1, 5);
    dm2.setElement(2, 7);
    dm2.setElement(3, 4);
    dm2.setElement(4, 5);
    dm2.setElement(5, 7);
    }
    catch(std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }  

    dm2.showMatrix();  

    return 0;
}