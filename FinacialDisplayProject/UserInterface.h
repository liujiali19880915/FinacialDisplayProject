#ifndef _USERINTERFACE_H_
#define _USERINTERFACE_H_


#include<iostream>
#include<string>

#include"ThreadPool.h"
#include "HttpBoost.h"

using namespace std;

class UserInterface {
private:
	ThreadPool* threadPool;

public:
	UserInterface();
	~UserInterface();
	void run(); 

};








#endif // !_USERINTERFACE_H_
