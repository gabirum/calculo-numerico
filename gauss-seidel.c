#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int count_items(const char *str)
{
  int items_sum = 1;

  for (int i = 0; str[i] != 0; i++)
  {
    char current_char = str[i];
    char next_char = str[i + 1];

    if (current_char == ' ' && next_char != ' ' && next_char != 0)
      items_sum++;
  }

  return items_sum;
}

double *parse_array(const char *str, const int size)
{
  double *data = malloc(sizeof(double) * size);
  int data_index = 0;
  int item_string_size = 16;
  int item_string_index = 0;
  char *item_string = malloc(sizeof(char) * item_string_size);

  for (int i = 0; str[i] != 0; i++)
  {
    char current_char = str[i];

    if ((current_char >= '0' && current_char <= '9') || current_char == '.' || current_char == '-')
    {
      if (item_string_size == (item_string_index + 1))
      {
        item_string_size += 16;
        item_string = realloc(item_string, sizeof(char) * item_string_size);
      }
      item_string[item_string_index++] = current_char;
      item_string[item_string_index] = 0;
    }

    if (current_char == ' ' || str[i + 1] == 0)
    {
      data[data_index++] = atof(item_string);
      item_string[0] = 0;
      item_string_index = 0;
    }
  }

  free(item_string);

  return data;
}

int converge(const double *x, const double *_x, int size, double tolerance)
{
  int count = 0;

  for (int i = 0; i < size; i++)
  {
    double error = (x[i] - _x[i]) / x[i];
    double absolute_error = fabs(error);

    if (absolute_error <= tolerance)
      count++;
  }

  return count == size;
}

int main(int argc, char const *argv[])
{
  if (argc < 4)
  {
    printf("Usage: %s  <size> \"<matrix-inline>\" \"<b-array>\" <relaxation?> <tolerance?> <max-iterations?>\n", argv[0]);
    return 1;
  }

  int size = atoi(argv[1]);
  int matrix_size = size * size;
  double relaxation = argc > 4 ? atof(argv[4]) : 1;
  double tolerance = argc > 5 ? atof(argv[5]) : 1e-2;
  int max_iterations = argc > 6 ? atoi(argv[6]) : 1000ul;

  if (count_items(argv[2]) != matrix_size || count_items(argv[3]) != size)
  {
    printf("Invalid inputs\n");
    return -1;
  }

  double *a = parse_array(argv[2], matrix_size);
  double *b = parse_array(argv[3], size);
  double *x = calloc(size, sizeof(double));
  double *_x = calloc(size, sizeof(double));

  for (int iteration = 0; iteration < max_iterations; iteration++)
  {
    memcpy(_x, x, size * sizeof(double));

    for (int i = 0; i < size; i++)
    {
      double decrement = 0;

      for (int j = 0; j < size; j++)
        if (j != i)
          decrement += a[i * size + j] * x[j];

      x[i] = ((1 - relaxation) * x[i]) + ((relaxation / a[i * size + i]) * (b[i] - decrement));
    }

    if (converge(x, _x, size, tolerance))
    {
      for (int i = 0; i < size; i++)
      {
        printf("x[%d]: %.15f\n", i + 1, x[i]);
      }

      return 0;
    }
  }

  printf("No solution found\n");

  free(x);
  free(_x);
  free(a);
  free(b);

  return 0;
}
