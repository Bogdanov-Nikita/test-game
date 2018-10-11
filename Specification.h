#pragma once
#include <windows.h>
#include <vector>
#include "Array2D.h"
//Класс игровых правил и игровй механики
#define SKIP_COLUMN -1	//Игнорирование столбца
class Specification
{
public:
	//Номера игровых элементов на карте
    int blockMapId;
	int EmptyFieldMapId;
    vector<int> gameChipsMapId;
    //Порядок цветов в соответствии с игровой картой
    vector<int> gameChipOderId;
    //Индекс массива номер столбца,
    //значение явлется идеентификатром фишки, 
    //значение -1 игнорирование столбца. 
	Specification::Specification(void);
	Specification(int blockMapId, int emptyFieldMapId, 
		int *gameChipOderId, size_t gameChipOderSize,
		int *gameChipsMapId, size_t gameChipsMapSize);
	~Specification(void);
	//Это игровая фишка
	bool isGameChip(POINT i,Array2D map);
	//Блоки
	bool isBlock(POINT i,Array2D map);
	//Это пустое поле
	bool isEmptyField(POINT i,Array2D map);
	//Соседие игровые объекты (фишки, блоки, свободные поля)
	bool isNeighbors(POINT from, POINT to, Array2D map);
	//Проверка на возможность перемещения.
	bool isCanMove(POINT from, POINT to, Array2D map);
	//Проверка успешного конца игры,
	//подразумевается квадратный размер массива, 
	//но может считать и рваную матрицу
	bool isGamePass(Array2D map);

};

