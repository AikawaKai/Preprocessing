#include <string>
#include <iostream>  

class Variable
{
	public:
		std::string name;
		std::string type = "generic var"; 
		int coeff;
	void showName(){
		std::cout<<coeff;
		std::cout<<name;
	}
	
};

class intVar: public Variable
{
	public:
		int max;
		int min;
		int value;
		std::string type = "intVar";
};

class binVar : public Variable
{
	public:
		int max = 1;
		int min = 0;
		std::string type = "binVar";
};

class floatVar: public Variable
{
	public:
		float max;
		float min;
		float value;
		std::string type = "floatVar";
};


