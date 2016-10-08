#include <string>
#include <iostream>  

class Variable
{
	public:
		std::string name; 
		float min;
		float max;
	void showName(){
		std::cout<<name;
	}
	
	virtual void showType(){
		std::cout<<"generic";
	}
	
	virtual int returnType(){
		return 0;
	}
	
};

class intVar: public Variable
{
	public:
		int max;
		int min;
		int value;
	virtual void showType(){
		std::cout<<"int";
	}
	virtual int returnType(){
		return 1;
	}
	
};

class binVar : public Variable
{
	public:
		int max = 1;
		int min = 0;
	virtual void showType(){
		std::cout<<"binary";
	}
	virtual int returnType(){
		return 2;
	}
	
};

class floatVar: public Variable
{
	public:
		float max;
		float min;
		float value;
	virtual void showType(){
		std::cout<<"float";
	}
	virtual int returnType(){
		return 3;
	}
	
};


