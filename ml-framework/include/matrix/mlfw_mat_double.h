#ifndef __mlfw__mat__double__
#define __mlfw__mat__double__

struct __mlfw_mat_double;
typedef struct __mlfw_mat_double mlfw_mat_double;
mlfw_mat_double * mlfw_mat_double_create_new(dimension_t rows, dimension_t columns);
void mlfw_mat_double_destroy(mlfw_mat_double *matrix);
mlfw_mat_double * mlfw_mat_double_from_csv(const char * csv_file_name);

double mlfw_mat_double_get(mlfw_mat_double * matrix, dimension_t row, dimension_t column);
void mlfw_mat_double_set(mlfw_mat_double *matrix, dimension_t row, dimension_t column, double value);


#endif
