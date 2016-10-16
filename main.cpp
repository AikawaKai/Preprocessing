#include <iostream>  
#include <limits>
#include <typeinfo>
#include <vector>
#include <random>
#include <chrono>
#include <ctime>
#include "type.h"
#include "preprocess.h"
#include "print_utility.h"
#include "write_utility.h"

int main(){
	std::random_device rd;
    std::mt19937 eng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> distr(1, 100);

	int num_var = distr(eng); 
	int num_row = distr(eng);
	std::uniform_int_distribution<> distr_x(1, num_var);
	int num_x = distr_x(eng);
	std::uniform_int_distribution<> distr_y(1, num_var-num_x);
	int num_y = distr_y(eng);
	int num_z = num_var - num_x - num_y;
	std::cout<<"tot: "<<num_var<<" x: "<<num_x<<" y: "<<num_y<<" z: "<<num_z;
}


