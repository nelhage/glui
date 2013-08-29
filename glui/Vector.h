#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "SDL_opengl.h"
/*******************************************************
***********************VECTOR3D*************************
********************************************************
A class for the definition and manipulation of 3d vectors
********************************************************/

class Vector3D
{
	public:
		double V[3];
			
			
		Vector3D();
		Vector3D(double x,double y,double z);
		~Vector3D();

		void Set(double x, double y, double z);

		void Normalize(); 		//reduce to a unit vector
		Vector3D Norm();		//return the norm (unit vector of the same direction)
		double Mag();					//returns the magnitude

		Vector3D operator*(double rhs);
		Vector3D operator/(double rhs);

		Vector3D operator+(double rhs);
		Vector3D operator+(const Vector3D &rhs);
		Vector3D operator-(double rhs);
		Vector3D operator-(const Vector3D &rhs);
		
		Vector3D operator*=(double rhs);
		Vector3D operator/=(double rhs);

		Vector3D operator+=(double rhs);
		Vector3D operator+=(const Vector3D &rhs);
		Vector3D operator-=(double rhs);
		Vector3D operator-=(const Vector3D &rhs);

		Vector3D operator-();

		bool operator == (const Vector3D &rhs);
		bool operator != (const Vector3D &rhs);

		double dot(Vector3D &rhs); 	  //dot product
		Vector3D cross(Vector3D &rhs);	 //cross product

			//char* CharPtr(char * Str);			//return a string "(X,Y,Z)" for easy output

		void SendOGLVertex(){glVertex3dv(V);}
		void SendOGLNormal(){glNormal3dv(V);}

		static Vector3D RandV(Vector3D Min, Vector3D Max); 	//return a vector between the two
};

#endif
