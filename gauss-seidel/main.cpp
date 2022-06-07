#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

bool converge(vector<double> x, vector<double> _x, double tolerance);
vector<double> parseArray(char const *str, size_t const size);

int main(int argc, char const *argv[])
{
  if (argc < 4)
  {
    cout << "Usage: " << argv[0] << " <size> \"<matrix-inline>\" \"<b-array>\" <relaxation?> <tolerance?> <max-iterations?>" << endl;
    cout << "The matrix must be entered in one line" << endl;
    return 1;
  }

  size_t size = stol(argv[1]);
  size_t matrixSize = (size_t)pow(size, 2);

  vector<double> a = parseArray(argv[2], matrixSize);
  vector<double> b = parseArray(argv[3], size);

  if (a.size() != matrixSize || b.size() != size)
  {
    cout << "Invalid inputs" << endl;
    return 1;
  }

  double relaxation = argc > 4 ? stod(argv[4]) : 1;
  double tolerance = argc > 5 ? stod(argv[5]) : 1e-2;
  size_t maxIterations = argc > 6 ? stol(argv[6]) : 1000ul;
  vector<double> x(size, 0);
  vector<double> _x(size, 0);

  for (size_t iteration = 0; iteration < maxIterations; iteration++)
  {
    _x = x;

    for (size_t i = 0; i < size; i++)
    {
      double decrement = 0;

      for (size_t j = 0; j < size; j++)
      {
        if (j != i)
        {
          decrement += a[i * size + j] * x[j];
        }
      }

      x[i] = ((1 - relaxation) * x[i]) + ((relaxation / a[i * size + i]) * (b[i] - decrement));
    }

    if (converge(x, _x, tolerance))
    {
      cout << setprecision(15);

      for (size_t i = 0; i < size; i++)
      {
        cout << "x" << i + 1 << ": " << x[i] << '\n';
      }

      return 0;
    }
  }

  cout << "No solution found" << endl;

  return 0;
}

bool converge(vector<double> x, vector<double> _x, double tolerance)
{
  size_t count = 0;

  for (size_t i = 0; i < x.size(); i++)
  {
    double error = (x[i] - _x[i]) / x[i];
    double absoluteError = abs(error);

    if (absoluteError < tolerance)
    {
      count++;
    }
  }

  return count == x.size();
}

vector<double> parseArray(char const *str, size_t const size)
{
  vector<double> result;
  stringstream ss(str);
  string buffer;

  for (size_t i = 0; ss >> buffer && i < size; i++)
  {
    result.push_back(stod(buffer));
  }

  return result;
}
