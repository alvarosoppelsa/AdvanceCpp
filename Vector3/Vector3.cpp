#include "Vector3.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <cassert>

Vector3::Vector3() :
	x_(0.0f),
	y_(0.0f),
	z_(0.0f),
	module_(0.0f)
{
}

Vector3::Vector3(float x, float y, float z) :
	x_(x),
	y_(y),
	z_(z)
{
	// Check if we need to calculate this here
	// or is better to do it in getModule() function
	module_ = sqrt( pow(x_, 2) + 
					pow(y_, 2) + 
					pow(z_, 2));
}

Vector3::Vector3(const Vector3& vector) :
	x_(vector.getX()),
	y_(vector.getY()),
	z_(vector.getZ()),
	module_(vector.getModule())
{
}

Vector3::~Vector3()
{
}

void Vector3::Normalize()
{
	assert(module_);

	x_ /= module_;
	y_ /= module_;
	z_ /= module_;
	module_ = 1;
}

double Vector3::distance_to(const Vector3& vector)
{
	return sqrt(pow((static_cast<double>(x_) - static_cast<double>(vector.getX())), 2) +
			    pow((static_cast<double>(y_) - static_cast<double>(vector.getY())), 2) +
				pow((static_cast<double>(z_) - static_cast<double>(vector.getZ())), 2));
}

double Vector3::dot_product(const Vector3& vector)
{
	return (static_cast<double>(x_) * static_cast<double>(vector.getX()) +
			static_cast<double>(y_) * static_cast<double>(vector.getY()) +
			static_cast<double>(z_) * static_cast<double>(vector.getZ()));
}

Vector3& Vector3::cross_product(const Vector3& vector)
{
	Vector3 result = Vector3(
		y_ * vector.getZ() - z_ * vector.getY(),
		x_ * vector.getZ() - z_ * vector.getX(),
		x_ * vector.getY() - y_ * vector.getX());
	return result;
}

double Vector3::angle_between(const Vector3& vector)
{
	float dot = this->dot_product(vector);
	double product = module_ * vector.getModule();
	assert(product);
	double cosAngle = (dot / (product));
	// convert from radians to degrees
	return acos(cosAngle) * 180 / M_PI;
}

Vector3& Vector3::operator+(const Vector3& vector) const
{
	Vector3 result = Vector3(
		x_ + vector.getX(),
		y_ + vector.getY(),
		z_ + vector.getZ());
	return result;
}

