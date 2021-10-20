#include <iostream>
#include "Vector3.h"

void printVector(Vector3& vector)
{
    std::cout << "\n";
    std::cout << "X: " << vector.getX() << "\n";
    std::cout << "Y: " << vector.getY() << "\n";
    std::cout << "Z: " << vector.getZ() << "\n";
    std::cout << "Module: " << vector.getModule() << "\n\n";
}

int main()
{
    Vector3 vecA = Vector3(1, 1, 0);
    std::cout << "A: ";
    printVector(vecA);

    Vector3 vecB = Vector3(2,1,0);
    std::cout << "B: ";
    printVector(vecB);

    Vector3 vecC = vecA + vecB;
    std::cout << "Addition C: ";
    printVector(vecC);
    vecC.Normalize();
    std::cout << "Normalized C: ";
    printVector(vecC);

    Vector3 crossVector = vecA.cross_product(vecB);
    std::cout << "Cross Vector A & B: ";
    printVector(crossVector);

    float dotProduct = vecA.dot_product(vecB);
    std::cout << "Dot Product A & B: " << dotProduct << "\n";

    float distance = vecA.distance_to(vecB);
    std::cout << "Distance A & B: " << distance << "\n";
}

