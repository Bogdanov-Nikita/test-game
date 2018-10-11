#pragma once
#include <windows.h>
#include <vector>
#define NULL_VALUE -1
using namespace std;
//2 мерный массив для карты
class Array2D{
	std::vector<std::vector<int>> map;
public:
	Array2D(void);
	Array2D(int **map, int size, int *sizeInner);
	~Array2D(void);
	size_t getLength(void);
	size_t getLineLength(int line);
	size_t getMaxLineLength();
	int getValue(size_t i, size_t j);
	bool excangeValue(POINT from, POINT to);
};

