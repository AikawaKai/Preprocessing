#include <string>

typedef struct intType {
  std::string str;
  int value;
  int coeff;
  int max;
  int min;
};

typedef struct binType {
  std::string str;
  int value;
  int coeff;
  int max=1;
  int min=0;
} ;

typedef struct floatType{
  std::string str;
  int value;
  int coeff;
  float max;
  float min;
};
