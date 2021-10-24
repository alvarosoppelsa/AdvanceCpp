#include "Vector3.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <cassert>

template<typename T>
Vector3<T>::Vector3() :
	x_(0),
	y_(0),
	z_(0),
	module_(0)
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
	module_ = sqrt( pow(static_cast<double>(x_), 2) + 
					pow(static_cast<double>(y_), 2) +
					pow(static_cast<double>(z_), 2));
}

// What happen when types are different?
template<typename T>
Vector3<T>::Vector3(const Vector3& vector) :
	x_(static_cast<T>(vector.getX())),
	y_(static_cast<T>(vector.getY())),
	z_(static_cast<T>(vector.getZ())),
	module_(vector.getModule())
{
}

template<typename T>
Vector3<T>::~Vector3()
{
}

template<typename T>
Vector3<double>* Vector3<T>::Normalize()
{
	assert(module_);

	return new Vector3<double>(
		(double)x_ / module_,
		(double)y_ / module_,
		(double)z_ / module_);

}

template<typename T>
double Vector3<T>::distance_to(const Vector3& vector)
{
	return sqrt(pow((static_cast<double>(x_) - static_cast<double>(vector.getX())), 2) +
			    pow((static_cast<double>(y_) - static_cast<double>(vector.getY())), 2) +
				pow((static_cast<double>(z_) - static_cast<double>(vector.getZ())), 2));
}

template<typename T>
double Vector3<T>::dot_product(const Vector3& vector)
{
	return (static_cast<double>(x_) * static_cast<double>(vector.getX()) +
			static_cast<double>(y_) * static_cast<double>(vector.getY()) +
			static_cast<double>(z_) * static_cast<double>(vector.getZ()));
}

template<typename T>
Vector3<T>* Vector3<T>::cross_product(const Vector3& vector)
{
	return new Vector3<T>(
		y_ * vector.getZ() - z_ * vector.getY(),
		x_ * vector.getZ() - z_ * vector.getX(),
		x_ * vector.getY() - y_ * vector.getX());
}

template<typename T>
double Vector3<T>::angle_between(const Vector3& vector)
{
	double dot = this->dot_product(vector);
	double product = module_ * vector.getModule();
	assert(product);
	double cosAngle = (dot / (product));
	// from radians to degrees
	return acos(cosAngle) * 180 / M_PI;
}

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3& vector) const
{
	return Vector3(
		x_ + static_cast<T>(vector.getX()),
		y_ + static_cast<T>(vector.getY()),
		z_ + static_cast<T>(vector.getZ()));
}

// Available types:
template class Vector3<int>;
template class Vector3<long>;
template class Vector3<double>;
template class Vector3<long long>;
template class Vector3<float>;
template class Vector3<double>;

