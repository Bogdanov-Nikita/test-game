#pragma once
#include <windows.h>
#include <vector>
#include "Array2D.h"
//����� ������� ������ � ������ ��������
#define SKIP_COLUMN -1	//������������� �������
class Specification
{
public:
	//������ ������� ��������� �� �����
    int blockMapId;
	int EmptyFieldMapId;
    vector<int> gameChipsMapId;
    //������� ������ � ������������ � ������� ������
    vector<int> gameChipOderId;
    //������ ������� ����� �������,
    //�������� ������� ��������������� �����, 
    //�������� -1 ������������� �������. 
	Specification::Specification(void);
	Specification(int blockMapId, int emptyFieldMapId, 
		int *gameChipOderId, size_t gameChipOderSize,
		int *gameChipsMapId, size_t gameChipsMapSize);
	~Specification(void);
	//��� ������� �����
	bool isGameChip(POINT i,Array2D map);
	//�����
	bool isBlock(POINT i,Array2D map);
	//��� ������ ����
	bool isEmptyField(POINT i,Array2D map);
	//������� ������� ������� (�����, �����, ��������� ����)
	bool isNeighbors(POINT from, POINT to, Array2D map);
	//�������� �� ����������� �����������.
	bool isCanMove(POINT from, POINT to, Array2D map);
	//�������� ��������� ����� ����,
	//��������������� ���������� ������ �������, 
	//�� ����� ������� � ������ �������
	bool isGamePass(Array2D map);

};

