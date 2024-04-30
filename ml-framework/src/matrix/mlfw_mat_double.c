#include <mlfw_matrix.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct __mlfw_mat_double
{
   double **data;
   dimension_t rows;
   dimension_t columns;
}mlfw_mat_double;

mlfw_mat_double * mlfw_mat_double_create_new(dimension_t rows, dimension_t columns)
{
	mlfw_mat_double *matrix;
	index_t r,k;
	if(rows < 0 || columns < 0) return NULL;
	matrix = (mlfw_mat_double *)malloc(sizeof(mlfw_mat_double));
	if(matrix == NULL) return NULL;
	matrix->data = (double **)malloc(sizeof(double *)*rows);
	if(matrix->data == NULL)
	{
		free(matrix);
		return NULL;
	}
	for(r=0;r<rows;r++)
	{
	   matrix->data[r] = (double *)malloc(sizeof(double) * columns);
	   if(matrix->data[r] == NULL)
	   {
	   	for(k=0;k<r;k++)
	   	{
	   		free(matrix->data[k]);
	   	}
	   	free(matrix->data);
	   	free(matrix);
	   	return NULL;
	   }
	}
	matrix->rows = rows;
	matrix->columns = columns;
	return matrix;
}

void mlfw_mat_double_destroy(mlfw_mat_double *matrix)
{
	index_t k;
	if(matrix == NULL) return; 
	for(k=0;k<matrix->rows;k++)
	{
		free(matrix->data[k]);
	}
	free(matrix->data);
	free(matrix);
}

double mlfw_mat_double_get(mlfw_mat_double * matrix, dimension_t row, dimension_t column)
{
	double value = 0.0;
	if(matrix == NULL) return value;
	if(row<0 || row>=matrix->rows) return value;
	if(column<0 || column>=matrix->columns) return value;
        return matrix->data[row][column];
}
void mlfw_mat_double_set(mlfw_mat_double *matrix, dimension_t row, dimension_t column, double value)
{
	double value = 0.0;
	if(matrix == NULL) return value;
	if(row<0 || row>=matrix->rows) return value;
	if(column<0 || column>=matrix->columns) return value;
        matrix->data[row][column] = value;
}

mlfw_mat_double * mlfw_mat_double_from_csv(const char * csv_file_name)
{
	mlfw_mat_double *matrix;
	dimension_t rows,columns;
	FILE *file;
	int index;
	char m;
	double value;
	char double_string[1025];
	index_t r,c;
	if(csv_file_name == NULL) return NULL;
	file = fopen(csv_file_name,"r");
	if(file == NULL) return NULL;
	rows = 0;
	columns = 0;
	while(1)
	{
		m=fgetc(file);
		if(feof(file)) break;
		if(rows == 0)
		{
		   if(m==',') columns++;
		}
		if(m == '\n') rows++;
	}
	columns++; // if 7 commas in a line means 8 columns
	matrix = mlfw_mat_double_create_new(rows,columns);
	if(matrix == NULL)
	{
		fclose(file);
		return NULL;
	}
	rewind(file); // move the internal pointer to start of the file
	r=0;
	c=0;
	index=0;
	while(1)
	{
		m=fgetc(file);
		if(feof(file)) break;
		if(m==',' || m=='\n')
		{
		    double_string[index] = '\0';
		    index=0;
		    value = strtod(double_string, NULL);
		    matrix->data[r][c] = value;
		    c++;
		    if(c == columns)
		    {
		    c = 0;
		    r++;
		    }
		}
		else
		{
			double_string[index] = m;
			index++;
		}
	}
	fclose(file);
	return matrix;
}
void test_new_and_destroy()
{
index_t r,c;
double value;
mlfw_mat_double *matrix;
matrix = mlfw_mat_double_create_new(3,4);
if(matrix == NULL) 
{
printf("Not able to create the matrix");
return;
}
value = 10.23;
for(r=0;r<matrix->rows;r++)
{
for(c=0;c<matrix->columns;c++)
{
matrix->data[r][c] = value;
value+=10.20;
}
}
for(r=0;r<matrix->rows;r++)
{
for(c=0;c<matrix->columns;c++)
{
printf("%20.10lf  ", matrix->data[r][c]);
value+=10.20;
}
printf("\n");
}
mlfw_mat_double_destroy(matrix);
}

void test_from_csv()
{
index_t r,c;
mlfw_mat_double *matrix;
matrix = mlfw_mat_double_from_csv("IceCreamSales.csv");
for(r=0;r<matrix->rows;r++)
{
for(c=0;c<matrix->columns;c++)
{
printf("%20.10lf  ", matrix->data[r][c]);
}
printf("\n");
}
mlfw_mat_double_destroy(matrix);
}

int main()
{
test_new_and_destroy();
test_from_csv();
return 0;
}














