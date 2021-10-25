#include "Vector3.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <cassert>

template<typename T>
Vector3<T>::Vector3() :
	x_(0),
	y_(0),
	z_(0),
	module_(0),
	isModuleCalculated_(true)

{
}

template<typename T>
Vector3<T>::Vector3(T x, T y, T z) :
	x_(x),
	y_(y),
	z_(z),
	module_(0),
	isModuleCalculated_(false)
{
}

template<typename T>
Vector3<T>::Vector3(const Vector3& vector) :
	x_(static_cast<T>(vector.getX())),
	y_(static_cast<T>(vector.getY())),
	z_(static_cast<T>(vector.getZ())),
	module_(vector.getModule()),
	isModuleCalculated_(false) // I don't trust anybody :(
{
}

template<typename T>
Vector3<T>::~Vector3()
{
}

template<typename T>
Vector3<double>* Vector3<T>::Normalize() const
{
	assert(module_);

	return new Vector3<double>(
		static_cast<double>(x_) / this->getModule(),
		static_cast<double>(y_) / this->getModule(),
		static_cast<double>(z_) / this->getModule());
}

template<typename T>
double Vector3<T>::distance_to(const Vector3& vector) const
{
	return sqrt(pow((static_cast<double>(x_) - static_cast<double>(vector.getX())), 2) +
			    pow((static_cast<double>(y_) - static_cast<double>(vector.getY())), 2) +
				pow((static_cast<double>(z_) - static_cast<double>(vector.getZ())), 2));
}

template<typename T>
double Vector3<T>::dot_product(const Vector3& vector) const
{
	return (static_cast<double>(x_) * static_cast<double>(vector.getX()) +
			static_cast<double>(y_) * static_cast<double>(vector.getY()) +
			static_cast<double>(z_) * static_cast<double>(vector.getZ()));
}

template<typename T>
Vector3<T>* Vector3<T>::cross_product(const Vector3& vector) const
{
	return new Vector3<T>(
		y_ * vector.getZ() - z_ * vector.getY(),
		x_ * vector.getZ() - z_ * vector.getX(),
		x_ * vector.getY() - y_ * vector.getX());
}

template<typename T>
double Vector3<T>::angle_between(const Vector3& vector) const
{
	double dot = this->dot_product(vector);
	double product = this->getModule() * vector.getModule();
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

template<typename T>
double Vector3<T>::getModule() const
{
	if (!isModuleCalculated_)
	{
		module_ = sqrt(pow(static_cast<double>(x_), 2) +
					pow(static_cast<double>(y_), 2) +
					pow(static_cast<double>(z_), 2));
		isModuleCalculated_ = true;
	}
	return module_;
}

// Available types:
template class Vector3<int>;
template class Vector3<long>;
template class Vector3<double>;
template class Vector3<long long>;
template class Vector3<float>;
template class Vector3<double>;

