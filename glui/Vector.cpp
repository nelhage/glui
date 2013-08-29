#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ABS(x) ((x)<0 ? (-(x)) : (x))
//returns a random float 0 <= RAND <= 1
#define RAND ABS((float)(rand() - rand())/RAND_MAX)
//returns a random float x <= f <= y
#define RANDFLOAT(x,y) (RAND * ABS((y)-(x)) + x)

//#include "Macros.h"
#include "Vector.h"

Vector3D::Vector3D() {V[0] = V[1] = V[2] = 0;}

Vector3D::Vector3D(double x, double y, double z){V[0] = x; V[1]=y; V[2]=z;};

void Vector3D::Set(double x, double y, double z){V[0] = x; V[1]=y; V[2]=z;}

Vector3D::~Vector3D(){}

void Vector3D::Normalize(){*this /= this->Mag();}
Vector3D Vector3D::Norm(){return *this / this->Mag();}

double Vector3D::Mag(){return sqrt(V[0]*V[0]+V[1]*V[1]+V[2]*V[2]);}

Vector3D Vector3D::operator*(double rhs){return Vector3D(V[0]*rhs,V[1]*rhs,V[2]*rhs);}

Vector3D Vector3D::operator/(double rhs){return Vector3D(V[0]/rhs,V[1]/rhs,V[2]/rhs);}

Vector3D Vector3D::operator+(double rhs){return Vector3D(V[0]+rhs,V[1]+rhs,V[2]+rhs);}

Vector3D Vector3D::operator+(const Vector3D &rhs){return Vector3D(V[0]+rhs.V[0],V[1]+rhs.V[1],V[2]+rhs.V[2]);}

Vector3D Vector3D::operator-(double rhs){return Vector3D(V[0]-rhs,V[1]-rhs,V[2]-rhs);}

Vector3D Vector3D::operator-(const Vector3D &rhs){return Vector3D(V[0]-rhs.V[0],V[1]-rhs.V[1],V[2]-rhs.V[2]);}

Vector3D Vector3D::operator-(){return Vector3D(-V[0],-V[1],-V[2]);}
//delegate is the keyword for the op= functions :)
Vector3D Vector3D::operator*=(double rhs){return (*this = this->operator*(rhs));}

Vector3D Vector3D::operator/=(double rhs){return (*this = this->operator/(rhs));}

Vector3D Vector3D::operator+=(double rhs){return (*this = this->operator+(rhs));}

Vector3D Vector3D::operator+=(const Vector3D &rhs){return (*this = this->operator+(rhs));}

Vector3D Vector3D::operator-=(double rhs){return (*this = this->operator-(rhs));}

Vector3D Vector3D::operator-=(const Vector3D &rhs){return (*this = this->operator-(rhs));}

bool Vector3D::operator==(const Vector3D &rhs){ return V[0] == rhs.V[0] && V[1] == rhs.V[1] && V[2] == rhs.V[2];}

bool Vector3D::operator!=(const Vector3D &rhs){ return !(this->operator==(rhs));}

double Vector3D::dot(Vector3D &rhs){return V[0]*rhs.V[0] + V[1]*rhs.V[1] + V[2]*rhs.V[2];}

Vector3D Vector3D::cross(Vector3D &rhs){return Vector3D((V[1]*rhs.V[2])-(V[2]*rhs.V[1]),(V[2]*rhs.V[0])-(V[0]*rhs.V[2]),(V[0]*rhs.V[1])-(V[1]*rhs.V[0]));}

Vector3D Vector3D::RandV(Vector3D Min, Vector3D Max)
{
	return Vector3D(RANDFLOAT(Min.V[0],Max.V[0]),RANDFLOAT(Min.V[1],Max.V[1]),RANDFLOAT(Min.V[2],Max.V[2]));
}
