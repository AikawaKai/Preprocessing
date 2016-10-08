#include <string>
#include <iostream>  

class Variable
{
	public:
		std::string name; 
	void showName(){
		std::cout<<name;
	}
	
	void showType(){
		std::cout<<"generic";
	}
	
};

class intVar: public Variable
{
	public:
		int max;
		int min;
		int value;
	void showType(){
		std::cout<<"int";
	}
	
};

class binVar : public Variable
{
	public:
		int max = 1;
		int min = 0;
	void showType(){
		std::cout<<"binary";
	}
	
};

class floatVar: public Variable
{
	public:
		float max;
		float min;
		float value;
	void showType(){
		std::cout<<"float";
	}
	
};


