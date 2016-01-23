#ifndef _VECMAT_H_
#define _VECMAT_H_
#include <stdio.h>

class Vector4
{
 public:
 double data[4];
 Vector4();
 Vector4(Vector4 &copy);
 void Print(void);
 void Set(double d1,double d2,double d3);
 double GetX();
 double GetY();
 double GetZ();
};

class Matrix4
{
 public:
 double data[4][4];
 Matrix4();
 void Print(void);
 Matrix4 operator*(const Matrix4);
 friend Vector4 operator*(const Matrix4,const Vector4);
};


#endif 