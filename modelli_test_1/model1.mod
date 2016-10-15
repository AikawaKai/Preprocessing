set num_var;
set num_vinc;
set num_varx;
set num_vary;
set num_varz;
set min_max;
param coeff_x{num_vinc, num_varx};
param coeff_y{num_vinc, num_vary};
param coeff_z{num_vinc, num_varz};
param bounds_x{num_varx, min_max};
param bounds_y{num_vary, min_max};
param bounds_z{num_varz, min_max};
param b{num_vinc};

var x{num_varx};
var y{num_vary} integer;
var z{num_varz} binary;

maximize max_:
   sum {i in num_varx} x[i] + sum{j in num_vary} y[j] + sum{k in num_varz} z[k];

subject to constraints{i in num_vinc}:
	sum{j in num_varx} x[j]*coeff_x[i, j] + sum{k in num_vary} y[k]*coeff_y[i, k] + sum{g in num_varz} z[g]*coeff_z[i, g] <= b[i];

subject to bound_x{i in num_varx}:
	bounds_x[i,'min']<=x[i]<=bounds_x[i,'max'];

subject to bound_y{i in num_vary}:
	bounds_y[i,'min']<=y[i]<=bounds_y[i,'max'];