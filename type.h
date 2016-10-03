#include <string>
#include <iostream>  

class Variable
{
	public:
		std::string name; 
		int coeff;
	void showName(){
		std::cout<<coeff;
		std::cout<<name;
		getchar();
	}
	
};

class intVar: public Variable
{
	public:
		int max;
		int min;
		int value;
};

class binVar : public Variable
{
	public:
		int max = 1;
		int min = 0;
};

class floatVar: public Variable
{
	public:
		float max;
		float min;
		float value;
};


