#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

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
    cout << "Usage: " << argv[0] << " <x0> <tolerance?> <max-iterations?>" << endl;
    return 1;
  }

  double x = stod(argv[1]);
  double tolerance = argc > 2 ? stod(argv[2]) : 1e-7;
  int maxIterations = argc > 3 ? stoi(argv[3]) : 1000;
  double error = 1;

  cout << setprecision(15);

  for (int i = 0; i < maxIterations; i++)
  {
    x = x - (f(x) / df(x));
    error = -(ddf(x) / (2 * df(x))) * pow(error, 2);

    cout << x << " | " << error << endl;

    if (error < tolerance)
    {
      cout << "f(" << x << ") = " << f(x) << '\n';
      return 0;
    }
  }

  cout << "Max iterations reached" << endl;

  return 1;
}
