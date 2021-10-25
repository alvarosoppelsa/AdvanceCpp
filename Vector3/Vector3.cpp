#include "Vector3.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <cassert>

// Vector3 doesn't initialize its members because usually 
// it's call for a huge amount of times.
// Avoiding initializing to 0 save a lot of time
template<typename T>
Vector3<T>::Vector3() :
	x_(T(0)),
	y_(T(0)),
	z_(T(0)),
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
	module_ = sqrt( square((double)x_) + 
					square((double)y_) +
					square((double)z_));
}

template<typename T>
Vector3<T>::Vector3(const Vector3<T>& vector) :
	x_(vector.getX()),
	y_(vector.getY()),
	z_(vector.getZ()),
	module_(vector.getModule())
{
}

template<typename T>
Vector3<T>::~Vector3()
{
}

template<typename T>
Vector3<double> Vector3<T>::Normalize() const
{
	assert(module_);
	// Avoid dividing. Use factor instead
	return Vector3<double>(
		(double)x_ / module_,
		(double)y_ / module_,
		(double)z_ / module_);

}

template<typename T>
double Vector3<T>::distance_to(const Vector3<T>& vector) const
{
	return sqrt(square(x_ - (double)vector.x_) +
				square(y_ - (double)vector.y_) +
				square(z_ - (double)vector.z_));
}

template<typename T>
double Vector3<T>::dot_product(const Vector3<T>& vector) const
{
	return ((double)x_ * (double)vector.x_ +
			(double)y_ * (double)vector.y_ +
			(double)z_ * (double)vector.z_);
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
	double product = module_ * vector.getModule();
	assert(product);
	double cosAngle = (dot / (product));
	// Internally we always work in radians
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

