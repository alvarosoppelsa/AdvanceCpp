#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <cassert>

// small number to compare floats & doubles
#define EPSILON 1e-5f;

// Template class should be implemented on the header
template<typename T>
class Vector3
{
public:
	Vector3();
	Vector3(T x, T y, T z);
	Vector3(const Vector3<T>& vector);
	~Vector3();

	Vector3<double> Normalize() const;
	double distance_to(const Vector3<T>& vector) const;
	T dot_product(const Vector3<T>& vector) const;
	Vector3<T> cross_product(const Vector3<T>& vector) const;
	double angle_between(const Vector3<T>& vector) const;

	Vector3 operator + (const Vector3<T>& vector) const;
	
	T getX() const { return x_; }
	T getY() const { return y_; }
	T getZ() const { return z_; }
	double getModule() const { return module_; }

private:
	T x_;
	T y_;
	T z_;
	double module_;
	// inline functions
	T square(const T& a) const { return a * a; }
	bool notNull(const T a) const { return a > EPSILON; }
};

// Vector3 doesn't initialize its members because usually 
// it's call for a huge amount of times.
// Avoiding initializing to 0 save a lot of time
template<typename T>
Vector3<T>::Vector3()
	//: x_(T(0)),
	//y_(T(0)),
	//z_(T(0)),
	//module_(0)
{
}

template<typename T>
Vector3<T>::Vector3(T x, T y, T z) :
	x_(x),
	y_(y),
	z_(z)
{
	// Do we need to calculate this here?
	// or is better to do it in getModule() function
	// Create a getModule() method is more flexible
	// for changing vector's parameters later on.
	module_ = sqrt(square((double)x_) +
				   square((double)y_) +
				   square((double)z_));
}

template<typename T>
Vector3<T>::Vector3(const Vector3<T>& vector) :
	x_(vector.x_),
	y_(vector.y_),
	z_(vector.z_),
	module_(vector.module_)
{
}

template<typename T>
Vector3<T>::~Vector3()
{
}

template<typename T>
Vector3<double> Vector3<T>::Normalize() const
{
	assert(notNull(module_));
	// One div + 3 mult -> instead 3 div
	double inv = T(1) / module_;
	return Vector3<double>(
		(double)x_ * inv,
		(double)y_ * inv,
		(double)z_ * inv);

}

template<typename T>
double Vector3<T>::distance_to(const Vector3<T>& vector) const
{
	return sqrt(square((double)x_ - (double)vector.x_) +
				square((double)y_ - (double)vector.y_) +
				square((double)z_ - (double)vector.z_));
}

template<typename T>
T Vector3<T>::dot_product(const Vector3<T>& vector) const
{
	return (x_ * vector.x_ +
			y_ * vector.y_ +
			z_ * vector.z_);
}

template<typename T>
Vector3<T> Vector3<T>::cross_product(const Vector3<T>& vector) const
{
	return Vector3<T>(
		y_ * vector.z_ - z_ * vector.y_,
		x_ * vector.z_ - z_ * vector.x_,
		x_ * vector.y_ - y_ * vector.x_);
}

template<typename T>
double Vector3<T>::angle_between(const Vector3& vector) const
{
	double dot = this->dot_product(vector);
	double product = module_ * vector.module_;
	assert(notNull(product));
	double cosAngle = (dot / product);
	// Internally we always work in radians
	return acos(cosAngle);// * 180 / M_PI;
}

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& vector) const
{
	return Vector3(
		x_ + vector.x_,
		y_ + vector.y_,
		z_ + vector.z_);
}


