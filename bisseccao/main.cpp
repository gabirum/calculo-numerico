#include <iostream>
#include <cmath>

using namespace std;

double func(double r)
{
  return exp(-(0.05 * r) / 10) * cos(0.05 * sqrt(2000 - (pow(r, 2) / 100))) - 0.01;
}

int main(int argc, char const *argv[])
{
  double maxIterations = 100;
  double tolerance = 1e-7;
  double inferiorInterval = 0;
  double superiorInterval = 400;
  double inferiorResult = func(inferiorInterval);
  double superiorResult = func(superiorInterval);

  if ((inferiorResult * superiorResult) >= 0)
  {
    cout << "Invalid interval" << endl;
    return 0;
  }

  for (int i = 0; i < maxIterations; i++)
  {
    double error = (superiorInterval - inferiorInterval) / 2;
    double estimate = (inferiorInterval + superiorInterval) / 2;
    inferiorResult = func(inferiorInterval);
    superiorResult = func(estimate);
    double result = inferiorResult * superiorResult;

    if (result == 0 || error <= tolerance)
    {
      cout << "Raiz encontrada: " << estimate << endl;
      cout << "Resultado da função: " << func(estimate) << endl;
      cout << "Erro: " << error << endl;
      cout << "Iterações: " << i << endl;

      return 0;
    }

    if (result < 0)
    {
      superiorInterval = estimate;
    }

    if (result > 0)
    {
      inferiorInterval = estimate;
    }
  }

  cout << "Não foi possível encontrar a raiz" << endl;

  return 0;
}
