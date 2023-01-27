#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x)
{
  return exp(-x) - x;
}

double df(double x)
{
  return -exp(-x) - 1;
}

double ddf(double x)
{
  return exp(-x);
}

int main(int argc, char const *argv[])
{
  if (argc < 2)
  {
    printf("Usage: %s <x0> <tolerance?> <max-iterations?>\n", argv[0]);
    return 1;
  }

  double x = atof(argv[1]);
  double tolerance = argc > 2 ? atof(argv[2]) : 1e-7;
  int max_iterations = argc > 3 ? atoi(argv[3]) : 1000;
  double error = 1;

  for (int i = 0; i < max_iterations; i++)
  {
    x = x - (f(x) / df(x));
    error = -(ddf(x) / (2 * df(x))) * pow(error, 2);

    if (error <= tolerance)
    {
      printf("f(%.15f) = %.15f\n", x, f(x));
      return 0;
    }
  }

  printf("Max iterations reached\n");

  return 0;
}
