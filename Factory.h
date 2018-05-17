#include <iostream>
#include "Enemy.h"
#include <math.h>
using namespace std ;

class Factory{
private :
	
	float color ;
	float pos;
	Enemy myEnemy;
public :
	void createMore();
};
