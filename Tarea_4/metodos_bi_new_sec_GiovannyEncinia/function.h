#ifndef FUNCTION
#define FUNCTION
float bisection(float, float, float (*function)(float));
float secant(float, float, float (*function)(float));
float newton(float, float (*function)(float), float (*f_p)(float));
float F_x(float);
float F_p_x(float);
float G_x(float);
float G_p_x(float);
float H_x(float);
float H_p_x(float);
void print_iter(int, float);

#endif // FUNCTION
