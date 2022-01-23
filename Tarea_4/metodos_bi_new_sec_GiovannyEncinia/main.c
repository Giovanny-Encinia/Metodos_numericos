//Giovanny Encinia
//26-06-2021
#include <stdio.h>
#include "function.h"
//constants
#define ZERO 0
#define ONE 1
#define TWO 2
#define EPSILON 0.000001
#define LIMIT 100000
#define test(x) (x+1)

int main(void)
{
    char option, next, method_sel;
    float a, b;
    _Bool true = ONE;
    float (*f)(float); // fucntion
    float (*f_p)(float);// derivate function

    printf("\t\tWhat function I will compute?\n");
    printf("\t\t1.- exp(x) + 2^(-x)+2cos(x)-6\n");
    printf("\t\t2.-ln(x - 1) + cos(x-1)\n");
    printf("\t\t3.-230x^4 + 18x^3+9x^2-221x-9\n");
    scanf(" %c", &option);

    switch(option)//select a function
    {
    case '1':
        f = &F_x;// exp(x) + 2^(-x)+2*cos(x)-6
        f_p = &F_p_x;// exp(x) + 2^(-x)*log(2)-2*sin(x)
        break;
    case '2':
        f = &G_x;// ln(x - 1) + cos(x-1)
        f_p = &G_p_x;// 1/(x - 1) - sin(x-1)
        break;
    case '3':
        f = &H_x;// 230*x^4 + 18*x^3+9*x^2-221*x-9
        f_p = &H_p_x; // 920*x^3+54*x^2+18*x-221
        break;
    default:
        printf("        Select a valid option\n");
        return ZERO;
    }

    while(true)//can select other method for compute the root
    {
        printf("        Select the method\n");
        printf("\t\t1. Bisection\n\t\t2. Newton\n\t\t3.Secant\n");
        scanf(" %c", &method_sel);

        printf("        Give me the point a\n");
        scanf(" %f", &a);
        printf("        Give me the point b\n");
        scanf(" %f", &b);
        printf("\n\n");


        switch(method_sel)
        {
        case '1'://Bisection
            printf("\t\t\tBisection Method\n\n");
            printf("\t\tInitial values (%f, %f)\n\n", a, b);
            printf("\t\tExist a root in x = %f\n", \
               bisection(a, b, f));
               break;
        case '2'://Newton Raphson
            printf("\t\t\tNewton Raphson Method\n\n");
            printf("\t\tx0 intermediate [a, b]: %f\n\n", (a+b)/2);
            printf("\t\tExist a root in x = %f\n", \
               newton((a + b)/2, f, f_p));
               break;
        case '3'://Secant
            printf("\t\t\tSecant Method\n\n");
            printf("\t\tInitial values (%f, %f)\n\n", a, b);
            printf("\n\t\tExist a root in x = %f\n", \
               secant(a, b, f));
               break;
        default:
            printf("Select a correct option\n");
            return ZERO;

        }

        printf("\n");
        printf("Do you want to find other root?(1:yes, 2:other)\n");
        scanf(" %c", &next);
        printf("\n\n");

        if(next!='1')
        {
            break;
        }

    }

    return ZERO;
}
