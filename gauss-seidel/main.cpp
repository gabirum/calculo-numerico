#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;

bool converge(double *x, double *_x, int size, double tolerance);
vector<double> parseArray(const char *str, int size);

int main(int argc, char const *argv[])
{
  if (argc < 4)
  {
    cout << "Usage: " << argv[0] << " <size> \"<matrix-inline>\" \"<b-array>\" <tolerance?> <max-iterations?>" << endl;
    return 1;
  }

  int size = stoi(argv[1]);
  int matrixSize = size * size;

  vector<double> a = parseArray(argv[2], matrixSize);
  vector<double> b = parseArray(argv[3], size);

  if (a.size() != matrixSize || b.size() != size)
  {
    cout << "Invalid inputs" << endl;
    return 1;
  }

  double tolerance = argc > 4 ? stod(argv[4]) : 1e-4;
  int maxIterations = argc > 5 ? stoi(argv[5]) : 1000;
  double *x = new double[size]{0};
  double *_x = new double[size]{0};

  for (int iteration = 0; iteration < maxIterations; iteration++)
  {
    memcpy(_x, x, sizeof(double) * size);

    for (int i = 0; i < size; i++)
    {
      double decrement = 0;

      for (int j = 0; j < size; j++)
      {
        if (j != i)
        {
          decrement += a[i * size + j] * x[j];
        }
      }

      x[i] = (b[i] - decrement) / a[i * size + i];
    }

    if (converge(x, _x, size, tolerance))
    {
      cout << setprecision(15);

      for (int i = 0; i < size; i++)
      {
        cout << "x" << i + 1 << ": " << x[i] << endl;
      }

      return 0;
    }
  }

  cout << "No solution found" << endl;

  return 0;
}

bool converge(double *x, double *_x, int size, double tolerance)
{
  int count = 0;

  for (int i = 0; i < size; i++)
  {
    double error = (x[i] - _x[i]) / x[i];
    double absoluteError = abs(error);

    if (absoluteError < tolerance)
    {
      count++;
    }
  }

  return count == size;
}

vector<double> parseArray(const char *str, int size)
{
  vector<double> result;
  stringstream ss(str);
  string buffer;

  while (ss >> buffer)
  {
    result.push_back(stod(buffer));
  }

  return result;
}
