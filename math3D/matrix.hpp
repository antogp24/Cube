#pragma once
#include <cstring>

// float evil[2][3];
// Matrix<float> good(2, 3);

// float evil[0][2] = 1;
// good(0, 2) = 1;

class Matrix
{
public:
  // constructor
  Matrix(unsigned wd, unsigned ht) // Width = Rows, Height = Columns
    :
    nWd(wd),
    nHt(ht),
    pAr(0) // Null at first
  {
    if (wd > 0 && ht > 0)
      pAr = new float[wd * ht]; // Initialized later;
  }

  // destructor
  ~Matrix()
  {
    delete[] pAr;
  }

  // indexing (parenthesis operator)

  float& operator()(unsigned x, unsigned y) // X = rows, Y = columns
  {
    return pAr[y * nWd + x];
  }

  // get dimensions

  unsigned& GetRows()
  {
    return nWd;
  }
  unsigned& GetColumns()
  {
    return nHt;
  }


  // private data members
private:
  unsigned nWd; // Array Width
  unsigned nHt; // Array Height
  float* pAr; // Array heap pointer

  // Referenced Copy Constructor
  Matrix(const Matrix& other)
    :
    nWd(other.nWd),
    nHt(other.nHt)
  {
    unsigned size = other.nWd * other.nHt;

    if (other.nWd > 0 && other.nHt > 0)
      this->pAr = new float[size];
    memcpy(this->pAr, other.pAr, size);
  }

  // Referenced Assignment Operator
  Matrix& operator=(const Matrix& other)
  {
    this->nWd = other.nWd;
    this->nHt = other.nHt;

    unsigned size = other.nWd * other.nHt;

    if (other.nWd > 0 && other.nHt > 0)
      this->pAr = new float[size];
    memcpy(this->pAr, other.pAr, size);
  }
};

/*

https://www.youtube.com/watch?v=Zbw58vTotok&ab_channel=ChiliTomatoNoodle

http://www.cplusplus.com/forum/articles/17108/

*/
