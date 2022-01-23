//Giovanny Encinia 15/08/2021
//Algoritmo para el problema 4, media, varianza

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZEOF(total) (sizeof(total)/sizeof(total[0]))

double mean(double vector[], int size);
double variance_alpha(double vector[], int size, double mean_v);
double variance_omega(double vector[], int size, double mean_v);
void print_result(double mean_, double var_a, double var_0, char *array_);

double mean(double vector[], int size)
{

    /*Calculate the mean of one array
    Parameters
    ==========
    float vector: the array
    int size: the size of the array

    Return
    ======
    double sum: the mean value of the array*/

    int i = 0;
    double sum = 0.0;

    while(i < size)
    {
        sum = sum + vector[i];
        i++;
    }

    sum = sum / size;// really is the mean value of the array
    return sum;
}

double variance_alpha(double vector[], int size, double mean_v)
{
    /*To evaluate the sample variance using a two-pass algorithm.
      In this case, you need to evaluate the mean first, so you have
      to loop through the x i once to get the mean and a second time
      time to get the sample variance.

      Parameters
      ==========
      float vector: the principal array
      int size: size of the array
      Return
      ======
      float sum: the variance of the array*/

    int i = 0;
    double sum = 0.0;

    while(i < size)
    {
        sum = sum + pow(vector[i] - mean_v, 2);
        i++;
    }

    sum = sum/size;

    return sum;
}

double variance_omega(double vector[], int size, double mean_v)
{
    /*To evaluate the sample variance using the one-pass
      algorithm
      Parameters
      ==========
      float vector: the principal array
      int size: size of the array
      Return
      ======
      float sum: the variance of the array**/

    int i = 0;
    double sum = 0.0;

    while(i < size)
    {
        sum += pow(vector[i], 2);
        i++;
    }

    sum = sum / size;
    sum = sum - pow(mean_v, 2);

    return sum;


}

void print_result(double mean_, double var_a, double var_o, char *array_)
{

    printf("AREGLO: %s\n", array_);
    printf("======================================\n\n");
    printf("Mean value: %f\n", mean_);
    printf("Variance two-pass algorithm: %f\n", var_a);
    printf("Variance one-pass algorithm: %f\n", var_o);
    printf("======================================\n\n\n");
}

int main()
{
    double mean_value_1, mean_value_2, var_1_alpha, var_2_alpha;
    double var_1_omega, var_2_omega;
    double x_1[] = {
                   0.0, 0.01, 0.02,
                   0.03, 0.04, 0.05,
                   0.06, 0.07, 0.08, 0.09
                   };
    double x_2[] = {
                123456789.0, 123456789.01, 123456789.02,
                123456789.03, 123456789.04, 123456789.05,
                123456789.06, 123456789.07, 123456789.08,
                123456789.09
                };

    mean_value_1 = mean(x_1, SIZEOF(x_1));
    mean_value_2 = mean(x_2, SIZEOF(x_2));

    var_1_alpha = variance_alpha(x_1, SIZEOF(x_1), mean_value_1);
    var_1_omega = variance_omega(x_1, SIZEOF(x_1), mean_value_1);

    var_2_alpha = variance_alpha(x_2, SIZEOF(x_2), mean_value_2);
    var_2_omega = variance_omega(x_2, SIZEOF(x_2), mean_value_2);

    print_result(mean_value_1, var_1_alpha, var_1_omega, \
                 "{0.0, 0.01, ... , 0.09}");
    print_result(mean_value_2, var_2_alpha, var_2_omega, \
                 "{123456789.0, 123456789.01, ... , 123456789.09}");


    return 0;
}
