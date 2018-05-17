#include "Factory.h"
using namespace std;

void Factory::createMore(){
	int position[] = {5,-5};
	int colour[] = {1,2,3,4,5};
	for (int i = 0; i<10; i++){
		int ran = rand() % 10;
        pos = position[ran]*0.1f;
        color = colour[ran];
		myEnemy.createEnemy(pos,color);
		//ran = rand() % 5;
	}
}
