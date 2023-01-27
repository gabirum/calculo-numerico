#include <stdio.h>
#include <math.h>

double f(double r)
{
  return exp(-(0.05 * r) / 10) * cos(0.05 * sqrt(2000 - (pow(r, 2) / 100))) - 0.01;
}

int main(int argc, char const *argv[])
{
  double max_iterations = 100;
  double tolerance = 1e-7;
  double inferior_interval = 0;
  double superior_interval = 400;
  double inferior_result = f(inferior_interval);
  double superior_result = f(superior_interval);

  if ((inferior_result * superior_result) >= 0)
  {
    printf("Invalid interval\n");
    return 0;
  }

  for (int i = 0; i < max_iterations; i++)
  {
    double error = (superior_interval - inferior_interval) / 2;
    double estimate = (inferior_interval + superior_interval) / 2;
    inferior_result = f(inferior_interval);
    superior_result = f(estimate);
    double result = inferior_result * superior_result;

    if (result == 0 || error <= tolerance)
    {
      printf("Root found: %.15f\nFunction result: %.15f\nError: %.15f\nIterations: %d\n", estimate, f(estimate), error, i + 1);

      return 0;
    }

    if (result < 0)
      superior_interval = estimate;

    if (result > 0)
      inferior_interval = estimate;
  }

  printf("No solution found\n");

  return 0;
}
