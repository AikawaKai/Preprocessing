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
		bool fixed = false;
	void showName(){
		std::cout<<name;
	}
	
	virtual void showType(){
		std::cout<<"generic";
	}
	
	virtual float returnValue(){
		return value;
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
	
	virtual bool setMin(float new_value){
		min = new_value;
		if(min == max)
		{
			value = min;
			fixed = true;
			return true;
		}
		return false;

	}
	
	virtual bool setMax(float new_value){
		max = new_value;
		if(max == min)
		{
			value = max;
			fixed = true;
			return true;
		}
		return false;
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
	
	virtual bool setMin(float new_value){
		if(ceil(new_value)>max)
		{
			min = max;
			value = min;
			fixed = true;
			return true;
		}
		else
		{
			min = ceil(new_value);
			if(min == max)
			{
				value = min;
				fixed = true;
				return true;
			}
		}
		return false;
	}
	
	virtual bool setMax(float new_value){
		if(floor(new_value)<min)
		{
			max = min;
			value = min;
			fixed = true;
			return true;
		}else
		{
			max = floor(new_value);
			if(max == min)
			{
				value = min;
				fixed = true;
				return true;
			}
		}
		return false;
	}
	
};

class binVar : public intVar
{
	public:
		binVar () : intVar ()
 		{
  			min = 0;
  			max = 1;
		}
		
	virtual void showType(){
		std::cout<<"binary";
	}
	virtual int returnType(){
		return 2;
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
	
};


