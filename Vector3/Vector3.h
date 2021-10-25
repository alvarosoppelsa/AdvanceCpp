#pragma once

#include <memory>

template<typename T>
class Vector3
{
public:
	Vector3();
	Vector3(T x, T y, T z);
	Vector3(const Vector3& vector);
	~Vector3();

	// Client has to delete returned pointer
	Vector3<double>* Normalize();
	double distance_to(const Vector3& vector);
	double dot_product(const Vector3& vector);
	// Client has to delete returned pointer
	Vector3<T>* cross_product(const Vector3& vector);
	double angle_between(const Vector3& vector);

	Vector3 operator + (const Vector3& vector) const;
	
	T getX() const { return x_; }
	T getY() const { return y_; }
	T getZ() const { return z_; }
	double getModule() const { return module_; }

private:
	T x_;
	T y_;
	T z_;
	double module_;
};

