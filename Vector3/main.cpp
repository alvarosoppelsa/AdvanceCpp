#include <iostream>
#include "Vector3.h"

template<typename T>
void printVector(Vector3<T>& vector)
{
    std::cout << "\n";
    std::cout << "X: " << vector.getX() << "\n";
    std::cout << "Y: " << vector.getY() << "\n";
    std::cout << "Z: " << vector.getZ() << "\n";
    std::cout << "Module: " << vector.getModule() << "\n";
}

template<typename T>
void testVector(Vector3<T>& vecA, Vector3<T>& vecB)
{
    printVector(vecA);
    printVector(vecB);

    double angleBetween = vecA.angle_between(vecB);
    std::cout << "Angle Between A & B: " << angleBetween << "\n";

    Vector3<T> vecC = vecA + vecB;
    std::cout << "\nAddition C: ";
    printVector(vecC);
    Vector3<double> normC = vecC.Normalize();
    std::cout << "\nNormalized C: ";
    printVector(normC);

    Vector3<T> crossVector = vecA.cross_product(vecB);
    std::cout << "\nCross Vector A & B: ";
    printVector(crossVector);

    double dotProduct = vecA.dot_product(vecB);
    std::cout << "\nDot Product A & B: " << dotProduct << "\n";

    double distance = vecA.distance_to(vecB);
    std::cout << "\nDistance A & B: " << distance << "\n";

}

int main()
{
    std::cout << "Testing integer Vector3\n";
    Vector3<int>* vecIntA = new Vector3<int>(1,0,0);
    Vector3<int>* vecIntB = new Vector3<int>(0,1,0);

    testVector(*vecIntA, *vecIntB);
    delete vecIntA;
    delete vecIntB;

    std::cout << "\nTesting float Vector3\n";
    Vector3<float>* vecFloatA = new Vector3<float>(1.5,1.3,1.2);
    Vector3<float>* vecFloatB = new Vector3<float>(0.1,0.5,3.2);

    testVector(*vecFloatA, *vecFloatB);
    delete vecFloatA;
    delete vecFloatB;

    std::cout << "\nTesting double Vector3\n";
    Vector3<double>* vecDoubleA = new Vector3<double>(0.5,0.6,0.4);
    Vector3<double>* vecDoubleB = new Vector3<double>(1.0,1.2,1.99999);

    testVector(*vecDoubleA, *vecDoubleB);
    delete vecDoubleA;
    delete vecDoubleB;
}

