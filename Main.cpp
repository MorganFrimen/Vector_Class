#include <iostream>

#include "Array.h"
#include "Vector.h"

using namespace std;

struct Vector3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;
	int* m_MemoryBlock = nullptr;

	Vector3(){ m_MemoryBlock = new int[5]; }

	Vector3(float scalar)
		: x(scalar), y(scalar), z(scalar)
	{
		m_MemoryBlock = new int[5];
	}

	Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{
		m_MemoryBlock = new int[5];
	}

	Vector3(const Vector3& other) = delete;
	Vector3(Vector3&& other)
		: x(other.x), y(other.y), z(other.z)
	{
		m_MemoryBlock = other.m_MemoryBlock;
		other.m_MemoryBlock = nullptr;
		cout << "Move\n";
	}
	~Vector3()
	{
		cout << "Destroy\n";
		delete[] m_MemoryBlock;
	}
	Vector3& operator=(const Vector3& other) = delete;
	Vector3& operator=(Vector3&& other)
	{
		m_MemoryBlock = other.m_MemoryBlock;
		other.m_MemoryBlock = nullptr;
		cout << "Move\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
};
template<typename T>
void PrintVector(const Vector<T>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
		cout << vector[i] << endl;
	cout << "-------------------------------------\n";
}

template<>
void PrintVector(const Vector<Vector3>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
		cout << vector[i].x << " , " << vector[i].y << " , " << vector[i].z << endl;
	cout << "-------------------------------------\n";
}

int main() {
	Array<string, 2> data;
	data[0] = "Hello";
	data[1] = "World";
	{
		Vector<Vector3> vector;
		vector.EmplaceBack(1.0f);
		vector.EmplaceBack(2, 3, 4);
		vector.EmplaceBack(1, 3, 4);
		vector.EmplaceBack();
		PrintVector(vector);
		vector.PopBack();
		vector.PopBack();
		PrintVector(vector);
		vector.EmplaceBack(8, 3, 1);
		vector.EmplaceBack(9, 7, 8);
		PrintVector(vector);

		vector.Clear();
		PrintVector(vector);
		vector.EmplaceBack(8, 3, 1);
		vector.EmplaceBack(9, 7, 8);
		PrintVector(vector);
		PrintVector(vector);
	}

	Vector<int> intVector;
	intVector.PushBack(5);
	intVector.EmplaceBack(2);
	intVector.EmplaceBack(3);
	intVector.EmplaceBack(3);
	intVector.EmplaceBack(3);
	intVector.EmplaceBack(3);
	PrintVector(intVector);
	intVector.PopBack();
	PrintVector(intVector);
	intVector.Clear();

	cin.get();
}