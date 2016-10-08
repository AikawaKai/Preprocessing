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
	virtual float returnMin(){
		return min;
	}
	virtual float returnMax(){
		return max;
	}
	
};

class intVar: public Variable
{
	public:
		float max;
		float min;
		float value;
	virtual void showType(){
		std::cout<<"int";
	}
	virtual int returnType(){
		return 1;
	}
	virtual float returnMin(){
		return min;
	}
	virtual float returnMax(){
		return max;
	}
	
};

class binVar : public Variable
{
	public:
		float max = 1;
		float min = 0;
	virtual void showType(){
		std::cout<<"binary";
	}
	virtual int returnType(){
		return 2;
	}
	virtual float returnMin(){
		return min;
	}
	virtual float returnMax(){
		return max;
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
	
	virtual float returnMin(){
		return min;
	}
	
	virtual float returnMax(){
		return max;
	}
	
};


