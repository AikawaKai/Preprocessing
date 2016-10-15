set num_var;
set num_vinc;
set num_var0;
set num_var1;
param coeff1_0{num_var0};
param coeff1_1{num_var1};
param coeff2_0{num_var0};
param coeff2_1{num_var1};

param b{num_vinc};

var x{num_var0};
var y{num_var1} integer;

maximize max_:
   sum {i in num_var0} x[i] + sum{j in num_var1} y[j];

subject to vinc_0:
	(sum{i in num_var0} coeff1_0[i]*x[i]) + (sum{j in num_var1}coeff1_1[j]*y[j]) <= b[0];

subject to vinc_1:
	(sum{i in num_var0} coeff2_0[i]*x[i]) + (sum{j in num_var1}coeff2_1[j]*y[j]) <= b[1];

subject to bound1:
	0<=x[0]<=10000000;

subject to bound2:
	0<=x[1]<=3;

subject to bound3:
	1<=x[2]<=5;

subject to bound4:
	2<=y[0]<=4;

subject to bound5:
	0<=y[1]<=10000000;