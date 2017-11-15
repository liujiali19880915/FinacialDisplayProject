#include <iostream>
#include"UserInterface.h"
using namespace std;

void main() {
	system("mode con cols=500"); //把控制台宽度变大
	UserInterface mainInterface;
	mainInterface.run();
		
}

