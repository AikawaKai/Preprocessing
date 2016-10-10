#include <string>
#include <iostream>
#include <math.h>

class Variable
{
	public:
		std::string name; 
		float min;
		float max;
		float value;
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
	
	virtual void setMin(float new_value){
		min = new_value;
	}
	
	virtual void setMax(float new_value){
		max = new_value;
	}
	
};

class intVar: public Variable
{
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
	
	virtual void setMin(float new_value){
		min = ceil(new_value);
	}
	
	virtual void setMax(float value){
		max = floor(new_value);
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
	
	virtual void setMin(float new_value){
		min = ceil(new_value);
	}
	
	virtual void setMax(float new_value){
		max = floor(new_value);
	}
	
};

class floatVar: public Variable
{
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
	
	virtual void setMin(float new_value){
		min = new_value;
	}
	
	virtual void setMax(float new_value){
		max = new_value;
	}
	
};


