//C++ class for lower triangular matrix using stl vector
//(lower triangular matrix is a square matrix in which all the entries above the main diagonal are zero)
#include<iostream>
#include<vector>
#include<stdexcept>
#include<cassert>


class LowerTriangularMatrix
{
private:
    //in this class lower triangular matrix is represented by one-dimensional vector
    std::vector<int> matrix;
    int matrixSize ;
    int matrixDimension;

public:

    LowerTriangularMatrix(int rows, int columns)
    {
        //number of rows must be equal to the number of columns
        assert(rows==columns);
        // and both must be positive
        assert(rows>0 and columns>0);
      
        //the size of the matrix is 1 + 2 + 3 + ... + N, where N is the number of rows/columns
        //to find the size of the matrix, the formula for arithmetic series is used   
        matrixSize = (rows * (1 + rows)) / 2;

        //reserve appropriate vector
        matrix.reserve(matrixSize);
        
        //set matrix dimension
        matrixDimension = rows; 
    }


    //in this constructor, only one dimension is used to instantiate the matrix
    //it's implied that the other dimension is equal to this dimension
    LowerTriangularMatrix(int dimension)
    {
        //dimension must be greater than zero
        assert(dimension>0);
         
        matrixSize = (dimension * (1 + dimension)) / 2;

        //reserve appropriate vector
        matrix.reserve(matrixSize); 

        //set matrix dimension
        matrixDimension = dimension;
    }   

    void setElement (int row, int column, int value)
    {
        //checking for appropriate coordinates
        if (row < 1 or column < 1 or row > matrixDimension or column > matrixDimension)
        {
            throw std::out_of_range("Please enter appropriate coordinates for the element");
        }
        else if (row<column)
        {
           return;
        }
        else
        {
            //setting the element using row major mapping
            matrix[row * (row-1)/2+column-1] = value;             
        }
    }
    
    int getElement (int row, int column)
    {
        //checking for appropriate coordinates
        if (row < 1 or column < 1 or row > matrixDimension or column > matrixDimension)
        {
            throw std::out_of_range("Please enter appropriate coordinates for the element");
        }
        else if (row>=column)
        {
           return matrix[row * (row-1)/2+column-1];
        }
        else
        {
            return 0;             
        }
    }

    void showMatrix ()
    {
        for (int i = 1; i <= matrixDimension; i++)
        {
            for (int j = 1; j <= matrixDimension; j++)
            {
                if (i >= j) 
                {
                    std::cout << matrix[i * (i-1)/2+j-1] << " ";
                }
                else
                {
                    std::cout << "0 ";
                }
            }
            std::cout << '\n';    
        }
    }


};

int main ()
{
    LowerTriangularMatrix ltm1 (7);

    try
    {
        ltm1.setElement(3, 2, 200);

        std::cout << ltm1.getElement(3, 2) << std::endl;
        std::cout << ltm1.getElement(2, 3) << std::endl;
        std::cout << ltm1.getElement(11, 8) << std::endl;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    std::cout << "----------------------------\n\n";
    LowerTriangularMatrix ltm2 (5);
    try
    {
        ltm2.setElement(1,1,3);
        ltm2.setElement(2,1,2);
        ltm2.setElement(2,2,3);
        ltm2.setElement(3,1,4);
        ltm2.setElement(3,2,1);
        ltm2.setElement(3,3,1);
        ltm2.setElement(4,1,5);
        ltm2.setElement(4,2,1);
        ltm2.setElement(4,3,1);
        ltm2.setElement(4,4,1);
        ltm2.setElement(5,1,1);
        ltm2.setElement(5,2,8);
        ltm2.setElement(5,3,1);
        ltm2.setElement(5,4,1);
        ltm2.setElement(5,5,7);
    }
    catch(const std::exception& e)
    {
        
        std::cerr << e.what() << '\n';
    }
    
    std::cout << "new matrix: " << '\n';
    ltm2.showMatrix();
    

    return 0;
}