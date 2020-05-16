//Sparse matrix representation with C++

#include<iostream>
#include<stdexcept>
#include<cstdlib>
#include<vector>
#include<tuple>
#include<utility>


//this class uses so-calles three column sparse matrix representation 
//this way of sparse matrix representation allows saving space
class SparseMatrix
{
public:
    //this constructor creates a matrix using three column sparse matrix representation
    //the constructor takes 3 arguments: number of rows, number of columns, and number of not zero elements 
    //if the third argument is greater than the product of the two other arguments, the program terminates
    SparseMatrix(int, int, int);

    //default constructot sets number of rows, number of columns, and number of not zero elements to zero
    SparseMatrix();

    SparseMatrix(const SparseMatrix&);

    SparseMatrix& operator=(const SparseMatrix&);

    SparseMatrix(SparseMatrix&&) noexcept;

    SparseMatrix& operator=(SparseMatrix&&) noexcept;

    ~SparseMatrix();

    //if the dimensions of the argument matrix differs from the caller matrix, 
    //the invalid_argument exception is thrown
    SparseMatrix operator+(const SparseMatrix&) const;

    //if the dimensions of the argument matrix differs from the caller matrix, 
    //the invalid_argument exception is thrown
    SparseMatrix operator-(const SparseMatrix&) const;

    int getNumberOfNotZeros() const;

    //this function prints the matrix to the console
    //the time complexity of this function is O(n^3)
    void showMatrix() const;

    int getRows() const;

    int getColumns() const;

    int getTotalNumberOfElements() const;

    std::vector<std::tuple<int, int, int>> getElements () const;

private:
    struct Element;
    int rows;
    int columns;
    int numberOfNotZeros;

    Element* arrayPointer = nullptr;

    //helper method which is used in + and - operator overloads
    int combinedNumberOfNotZeros(const SparseMatrix&, const SparseMatrix&) const; 

    //helper method which is used in assignment operator
    void swap(SparseMatrix&, SparseMatrix&) noexcept;

    void cleanup() noexcept;

    void moveFrom(SparseMatrix&) noexcept; 
};

int main ()
{
    SparseMatrix sm1(10, 10, 5);
    std::cout << "Matrix sm1: \n";
    sm1.showMatrix();
    std::cout<<std::endl;

    SparseMatrix sm2(sm1);
    std::cout << "Matrix sm2: \n";
    sm2.showMatrix();
    std::cout<<std::endl; 

    SparseMatrix sm3;
    sm3 = sm2;
    std::cout << "Matrix sm3: \n";
    sm3.showMatrix();
    std::cout<<std::endl;   

    SparseMatrix sm4(10, 10, 5);
    std::cout<<"sm4 is entered"<<std::endl;
    std::cout << "Matrix sm4: \n";
    sm4.showMatrix();
    std::cout<<std::endl;       

    SparseMatrix sm5 = sm4 - sm1;
    std::cout << "Matrix sm5(sm4-sm1): \n";
    sm5.showMatrix();
    std::cout<<std::endl;  

    SparseMatrix sm6(10, 10, 4);
    std::cout<<"sm6 is entered"<<std::endl;
    std::cout << "Matrix sm6: \n";
    sm6.showMatrix();
    std::cout<<std::endl; 

    SparseMatrix sm7 = sm5 + sm6;
    std::cout << "Matrix sm7(sm5+sm6): \n";
    sm7.showMatrix();
    std::cout<<std::endl;                   
   
    return 0;
}

struct SparseMatrix::Element
{
    int rowNumber;
    int columnNumber;
    int value;
};

SparseMatrix::SparseMatrix(): rows{0}, columns{0}, numberOfNotZeros{0}, arrayPointer{nullptr}{}

SparseMatrix::SparseMatrix(int rows, int columns, int elementNumber)
{
    if(elementNumber > (rows * columns))
    {
        std::cout<<"The number of elements (third argument) must not be greater than the product of the rows and columns"<<std::endl;
        exit(1); 
    }
    this->rows = rows;
    this->columns = columns;
    numberOfNotZeros = elementNumber;  
    arrayPointer = new Element [numberOfNotZeros];   
    int i, j;
    i = 0; 
    bool appropriateRecord;

    if(numberOfNotZeros > 0)
    {
        std::cout << "Please enter the " << numberOfNotZeros << " element" << (numberOfNotZeros > 1 ? "s" : "") << std::endl;
        std::cout << "The values of the row number, column number and the element's value must be separated by an empty space" << std::endl;
        while(i<numberOfNotZeros)
        {
            appropriateRecord = true;
            std::cout << i+1 << "s" << " element: ";
            if(std::cin.good())
            {
                
                std::cin >> arrayPointer[i].rowNumber >> arrayPointer[i].columnNumber >> arrayPointer[i].value;
                if((arrayPointer[i].rowNumber > (rows - 1)) || arrayPointer[i].columnNumber > (columns - 1) ||
                   (arrayPointer[i].rowNumber < 0) || (arrayPointer[i].columnNumber < 0))
                {
                    std::cout << "You entered an inappropriate row number or/and column number\n";
                    std::cout << "Please enter the values correctly" << std::endl;
                    appropriateRecord = false;
                }
                else if (i != 0)
                {   
                    for(int k = i - 1; k != -1; k--)
                    {
                        if((arrayPointer[i].rowNumber == arrayPointer[k].rowNumber) &&
                        (arrayPointer[i].columnNumber == arrayPointer[k].columnNumber))
                        {
                            appropriateRecord = false;
                            std::cout<<"This element has been already entered"<<std::endl;
                            break;
                        }                        
                    }

                } 
            }  
            else
            {
                std::cout << "Sorry, for some reason the input isn't working properly" << std::endl;
                exit(1);
            }

            if(appropriateRecord)
            {
                i++;
            }            
        }
    }
}

SparseMatrix::SparseMatrix(const SparseMatrix& src)
{
    std::cout<<"Copy constructor is called"<<std::endl;
    rows = src.rows;
    columns = src.columns;
    numberOfNotZeros = src.numberOfNotZeros;
    arrayPointer = new Element [numberOfNotZeros];

    for(int i = 0; i<numberOfNotZeros; i++)
        arrayPointer[i] = src.arrayPointer[i];
}

SparseMatrix::~SparseMatrix()
{
    cleanup();
}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& src)
{
    std::cout<<"Copy assignment operator is called"<<std::endl;
    if(this == &src)
        return *this;
    
    SparseMatrix temp(src);
    swap(*this, temp);

    return *this;
}

SparseMatrix::SparseMatrix(SparseMatrix&& src) noexcept
{
    std::cout<<"Move constructor"<<std::endl;
    moveFrom(src);
}

SparseMatrix& SparseMatrix::operator=(SparseMatrix&& src) noexcept
{
    std::cout<<"Move assignment operator is called"<<std::endl;
    if(this == &src)
        return *this;   

    cleanup();

    moveFrom(src);
    return *this;
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

SparseMatrix SparseMatrix::operator-(const SparseMatrix& other) const
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
        {
            result.arrayPointer[i] = arrayPointer[i];
            result.arrayPointer[i].value = arrayPointer[i].value;
        }
            
        for(i = numberOfNotZeros, j = 0; i<count; i++, j++)
        {
            result.arrayPointer[i] = other.arrayPointer[j];
            result.arrayPointer[i].value = 0 - other.arrayPointer[j].value;
        }

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
                result.arrayPointer[i].rowNumber = arrayPointer[i].rowNumber;
                result.arrayPointer[i].columnNumber = arrayPointer[i].columnNumber;
                result.arrayPointer[i].value = arrayPointer[i].value - other.arrayPointer[j].value;
                match = true;
                break;
            }

        }
   
        if(!match)
        {
            result.arrayPointer[i].rowNumber = arrayPointer[i].rowNumber;
            result.arrayPointer[i].columnNumber = arrayPointer[i].columnNumber;
            result.arrayPointer[i].value = arrayPointer[i].value;
        }
    }
    
    if(result.numberOfNotZeros > numberOfNotZeros)
    {
        t = numberOfNotZeros;
        bool noMatch;
        for(i = 0; i<other.numberOfNotZeros; i++)
        {
            noMatch = true;
            for(j = 0; j<numberOfNotZeros; j++)
            {
                if((other.arrayPointer[i].rowNumber == result.arrayPointer[j].rowNumber) && 
                (other.arrayPointer[i].columnNumber == result.arrayPointer[j].columnNumber))
                {
                    noMatch = false;
                }
            }
            if(noMatch)
            {   
                result.arrayPointer[t] = other.arrayPointer[i];
                result.arrayPointer[t].value = 0 - other.arrayPointer[i].value;
                t++;
            }  
        } 
        
    }
    return result;   
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
        {
            result.arrayPointer[i] = arrayPointer[i];
        }

        for(i = numberOfNotZeros, j = 0; i<count; i++, j++)
        {
            result.arrayPointer[i] = other.arrayPointer[j];
        }
            
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
                result.arrayPointer[i].rowNumber = arrayPointer[i].rowNumber;
                result.arrayPointer[i].columnNumber = arrayPointer[i].columnNumber;
                result.arrayPointer[i].value = arrayPointer[i].value + other.arrayPointer[j].value;
                match = true;
                break;
            }
        }
   
        if(!match)
        {
            result.arrayPointer[i] = arrayPointer[i]; 
        }
    }    

    if(result.numberOfNotZeros > numberOfNotZeros)
    {
        t = numberOfNotZeros;
        bool noMatch;
        for(i = 0; i<other.numberOfNotZeros; i++)
        {
            noMatch = true;
            for(j = 0; j<numberOfNotZeros; j++)
            {
                if((other.arrayPointer[i].rowNumber == result.arrayPointer[j].rowNumber) && 
                (other.arrayPointer[i].columnNumber == result.arrayPointer[j].columnNumber))
                {
                    noMatch = false;
                }
            }
            if(noMatch)
            {   
                result.arrayPointer[t] = other.arrayPointer[i];
                t++;
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

int SparseMatrix::getNumberOfNotZeros() const
{
    return numberOfNotZeros;
}

std::vector<std::tuple<int, int, int>> SparseMatrix::getElements() const 
{
    std::vector<std::tuple<int, int, int>> vec;
    std::tuple<int, int, int> tup;
    for(int i=0; i<numberOfNotZeros; i++)
    {
        auto[a, b, c] = arrayPointer[i];
        tup = std::make_tuple(a, b, c);
        vec.push_back(tup);
    }
    return vec;
}

void SparseMatrix::swap(SparseMatrix& first, SparseMatrix& second) noexcept
{
    using std::swap;

    swap(first.rows, second.rows);
    swap(first.columns, second.columns);
    swap(first.numberOfNotZeros, second.numberOfNotZeros);
    swap(first.arrayPointer, second.arrayPointer);
}

void SparseMatrix::cleanup() noexcept
{
    if(arrayPointer)
        delete [] arrayPointer;

    arrayPointer = nullptr;
}

void SparseMatrix::moveFrom(SparseMatrix& src) noexcept
{
    rows = src.rows;
    columns = src.columns;
    numberOfNotZeros = src.numberOfNotZeros;
    arrayPointer = src.arrayPointer;
    
    src.rows = 0;
    src.columns = 0;
    src.numberOfNotZeros = 0; 
    src.arrayPointer = nullptr;
}





