#include "Specification.h"
Specification::Specification(void) {
}
Specification::Specification(int blockMapId, int emptyFieldMapId, 
	int *gameChipOderId, size_t gameChipOderSize,
	int *gameChipsMapId, size_t gameChipsMapSize) {
        this->blockMapId = blockMapId;
		this->EmptyFieldMapId = emptyFieldMapId;
        this->gameChipsMapId = vector<int>();
		for(size_t i = 0; i < gameChipsMapSize; i++){
			this->gameChipsMapId.push_back(gameChipsMapId[i]);
		}
        this->gameChipOderId = vector<int>();
		for(size_t i = 0; i < gameChipOderSize; i++){
			this->gameChipOderId.push_back(gameChipOderId[i]);
		}
}

Specification::~Specification(void){
}
//��� ������� �����
bool Specification::isGameChip(POINT i,Array2D map){
    for(size_t index = 0; index < gameChipsMapId.size(); index++){
        if(map.getValue(i.x,i.y) == gameChipsMapId[index]){
            return true;
        }
    }
    return false;
}
//�����
bool Specification::isBlock(POINT i,Array2D map){
    return map.getValue(i.x,i.y) == blockMapId;
}
//��� ������ ����
bool Specification::isEmptyField(POINT i,Array2D map){
    return map.getValue(i.x,i.y) == EmptyFieldMapId;
}
//������� ������� ������� (�����, �����, ��������� ����)
bool Specification::isNeighbors(POINT from, POINT to, Array2D map){
    return (abs(from.x - to.x) == 1) ^ 
            (abs(from.y - to.y) == 1);
}
//�������� �� ����������� �����������.
bool Specification::isCanMove(POINT from, POINT to, Array2D map){
    //������� �������� ������
    if(isNeighbors(from, to, map)){
        //������� ��� from �����, � t� ��������� ������.
        return isGameChip(from, map) && isEmptyField(to, map);
    }else {
        return false;
    }
        
}
//�������� ��������� ����� ����,
//��������������� ���������� ������ �������, 
//�� ����� ������� � ������ �������
bool Specification::isGamePass(Array2D map){
        
    bool flag = false;
          
    for(size_t y = 0; y < map.getMaxLineLength(); y++){
        for(size_t x = 0; x < map.getLength(); x++){
            if(y > map.getLineLength(x)){break;}//����� �������
            if(gameChipOderId[y] == SKIP_COLUMN){break;}//������������ �������
            if(map.getValue(x, y) == gameChipOderId[y]){//����������� �������
                flag = true;
            }else{
                flag = false;
                break;
            }
        }
		if(!flag){break;}
    }
    return flag;
}