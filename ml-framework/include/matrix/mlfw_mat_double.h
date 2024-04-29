#ifndef __mlfw__mat__double__
#define __mlfw__mat__double__

struct __mlfw_mat_double;
typedef struct __mlfw_mat_double mlfw_mat_double;
mlfw_mat_double * mlfw_mat_double_create_new(dimension_t rows, dimension_t columns);
void mlfw_mat_double_destroy(mlfw_mat_double *matrix);
mlfw_mat_double * mlfw_mat_double_from_csv(const char * csv_file_name);

#endif
