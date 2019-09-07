//
// Created by mattan on 9/4/19.
//

#ifndef UNTITLED_BASE_H
#define UNTITLED_BASE_H

#endif //UNTITLED_BASE_H
#include<iostream>

using namespace std;

class Base
{

public:

	Base()
	{
		std::cout<< "Base ctor";
	}

};

class Derived : public Base
{

public:

	Derived()
	{
		std::cout<< "Derived ctor";
	}

	~Derived()
	{
		std::cout<< "Derived dtor";
	}

};


