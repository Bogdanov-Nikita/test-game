#include "Array2D.h"

Array2D::Array2D(void){
}

Array2D::Array2D(int **map, int size, int *sizeInner){
	this->map = vector<vector<int>>();
	for(int i = 0; i < size; i++){
		this->map.push_back(vector<int>());
		for(int j = 0; j < sizeInner[i]; j++){
			this->map[i].push_back(map[i][j]);
		}
	}
}

Array2D::~Array2D(void){
	for(size_t i = 0; i < map.size(); i++){
		map[i].clear();
	}
	map.clear();
}
  
size_t Array2D::getLength(void){
	return map.size();
}

size_t Array2D::getLineLength(int line){
	return map[line].size();
}
    
size_t Array2D::getMaxLineLength(){
    size_t val = 0;
    for(size_t i = 0; i < map.size(); i++){
        val =   max(val , getLineLength(i));
    }
    return val;
}
    
int Array2D::getValue(size_t i, size_t j){
    if(i >= 0  && i < map.size()){
        if(j >= 0 && j < map[i].size()){
            return map[i][j];
        }else{
            return NULL_VALUE;
        }
    }else{
        return NULL_VALUE;
    }
}
    
/* “очка указывает положение в двухмерном массиве,
    мен€ет значени€ указанные в from и to местами
*/
bool Array2D::excangeValue(POINT from, POINT to){
	if(getValue(from.x, from.y) != NULL_VALUE && 
			getValue(to.x, to.y)!= NULL_VALUE){
		int tempValue = map[to.x][to.y];
		map[to.x][to.y] = map[from.x][from.y];
		map[from.x][from.y] = tempValue;
		return true;
	}else{
		return false;
	}
}