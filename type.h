#include <string>
#include <iostream>
#include <math.h>
#include <vector>

class Variable
{
	public:
		std::string name; 
		float min;
		float max;
		float value = 0;
		bool fixed = false;
	
	Variable(std::string name_, float min_, float max_)
	{
		name = name_;
		min = min_;
		max = max_;
	}
	
	~Variable(){
	}

	void showName(){
		std::cout<<name;
	}
	
	virtual void showType(){
		std::cout<<"generic";
	}
	
	virtual void setValue(float value_){
		value = value_;
		fixed = true;
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
		if (new_value>max)
		{
			min = max;
			value = min;
			fixed = true;
			return true;
		}
		else
		{
			min = new_value;
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
		if (new_value<min)
		{
			max = min;
			value = max;
			fixed = true;
			return true;
		}
		else
		{
			max = new_value;
			if(max == min)
			{
				value = max;
				fixed = true;
				return true;
			}
		}
		return false;
	}
	
};

class intVar: public Variable
{	
	public:
		intVar(std::string name_, float min_, float max_): Variable(name_, min_, max_){}
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
		binVar (std::string name_) : intVar (name_, 0, 1){}
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
		floatVar(std::string name_, float min_, float max_): Variable(name_, min_, max_){}
	virtual void showType(){
		std::cout<<"float";
	}
	virtual int returnType(){
		return 3;
	}
	
};

struct Parameters
{
		int numOfVar;
		int numRow;
		int maxVal;
		int minVal;
		int seed1;
		std::string namefiledat1;
		std::string namefiledat2;
		int bin;
		int max_tn;
		int min_tn;
};


