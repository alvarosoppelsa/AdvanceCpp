#include <iostream>
#include "Vector3.h"

void printVector(Vector3& vector)
{
    std::cout << "\n";
    std::cout << "X: " << vector.getX() << "\n";
    std::cout << "Y: " << vector.getY() << "\n";
    std::cout << "Z: " << vector.getZ() << "\n";
    std::cout << "Module: " << vector.getModule() << "\n";
}

int main()
{
    Vector3 vecA = Vector3(1, 0, 0);
    std::cout << "A: ";
    printVector(vecA);

    Vector3 vecB = Vector3(0,1,0);
    std::cout << "B: ";
    printVector(vecB);

    float angleBetween = vecA.angle_between(vecB);
    std::cout << "Angle Between A & B: " << angleBetween << "\n";

    Vector3 vecC = vecA + vecB;
    std::cout << "\nAddition C: ";
    printVector(vecC);
    vecC.Normalize();
    std::cout << "\nNormalized C: ";
    printVector(vecC);

    Vector3 crossVector = vecA.cross_product(vecB);
    std::cout << "\nCross Vector A & B: ";
    printVector(crossVector);

    float dotProduct = vecA.dot_product(vecB);
    std::cout << "\nDot Product A & B: " << dotProduct << "\n";

    float distance = vecA.distance_to(vecB);
    std::cout << "\nDistance A & B: " << distance << "\n";
}

