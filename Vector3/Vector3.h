#pragma once

#include <memory>

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& vector);
	~Vector3();

	void Normalize();
	double distance_to(const Vector3& vector);
	double dot_product(const Vector3& vector);
	Vector3& cross_product(const Vector3& vector);
	double angle_between(const Vector3& vector);

	Vector3& operator + (const Vector3& vector) const;
	
	float getX() const { return x_; }
	float getY() const { return y_; }
	float getZ() const { return z_; }
	double getModule() const { return module_; }

private:
	float x_;
	float y_;
	float z_;
	double module_;
};

