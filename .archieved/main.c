/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:15:31 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/01 15:29:11 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_mat
{
	int	nrows;
	int	ncols;
	double	*data;
}	t_mat;

t_mat	*ft_init_mat(int a, int b);
void	rm_mat(t_mat *matrix);
void	ft_print_mat(t_mat *matrix);
t_mat	*ft_matadd(t_mat *A, t_mat *B);
t_mat	*ft_matmut(t_mat *A, t_mat *B);

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (-1);
	int	row;
	int	col;
	t_mat	*first;
	t_mat	*second;
	t_mat	*res;
	double	*tmp_data;
	int	i;

	i = 0;
	row = atoi(argv[1]);
	col = atoi(argv[2]);
	first = NULL;
	tmp_data = NULL;
	printf("--- Start program ---\n\n");
	printf("Initialize\n");
	first = ft_init_mat(row,col);
	printf("Matrix A(%d, %d)\t", first->nrows, first->ncols);
	second = ft_init_mat(row,col);
	printf("Matrix B(%d, %d)\n", second->nrows, second->ncols);
	while (i < first->nrows * first->ncols)
	{
		first->data[i] = i + 2;
		i++;
	}
	i = 0;
	while (i < second->nrows * second->ncols)
	{
		second->data[i] = i + 1;
		i++;
	}
	ft_print_mat(first);
	printf("\n");
	ft_print_mat(second);
	res = ft_matadd(first, second);
	printf("\n");
	ft_print_mat(res);
	rm_mat(first);
	rm_mat(second);
	rm_mat(res);
	return (0);
}

void	ft_print_mat(t_mat *matrix)
{
	int	i;
	double	*tmp_data;

	i = 0;
	tmp_data = matrix->data;
	while (i < matrix->nrows * matrix->ncols)
	{
		printf("%.2lf ,", *tmp_data);
		if (i != 0 && (i+1) % (matrix->ncols) == 0)
			printf("\n");
		i++;
		tmp_data++;
	}
}

t_mat	*ft_init_mat(int i, int j)
{
	t_mat	*ptr_mat;
	int	n;
	double	*elements;

	n = 0;
	elements = malloc(sizeof(double)*(i*j));
	if (!elements)
		return (NULL);
	ptr_mat = (t_mat *)malloc(sizeof(t_mat));
	if (!ptr_mat)
		return (NULL);
	ptr_mat->nrows = i;
	ptr_mat->ncols = j;
	while (n < i*j)
		elements[n++] = 0;
	ptr_mat->data = elements;
	return (ptr_mat);
}

void	rm_mat(t_mat *matrix)
{
	free(matrix->data);
	free(matrix);
}

t_mat	*ft_matadd(t_mat *A, t_mat *B)
{
	t_mat	*ptr;
	int	i;

	i = 0;
	if (!(A->nrows == B->nrows && A->ncols == B->ncols))
		return (NULL);
	ptr = ft_init_mat(A->nrows, A->ncols);
	while (i < ptr->nrows * ptr->ncols)
	{
		ptr->data[i] = A->data[i] + B->data[i];
		i++;
	}
	return (ptr);
}

t_mat	*ft_matsub(t_mat *A, t_mat *B)
{
	t_mat	*ptr;
	int	i;

	i = 0;
	if (!(A->nrows == B->nrows && A->ncols == B->ncols))
		return (NULL);
	ptr = ft_init_mat(A->nrows, A->ncols);
	while (i < ptr->nrows * ptr->ncols)
	{
		ptr->data[i] = A->data[i] - B->data[i];
		i++;
	}
	return (ptr);
}
/*
void	ft_mat_scale(t_mat *matrix, int scalar)
{
	while (i < matrix->nrows * matrix->ncols)
	{
		matrix->
	}
}

t_mat	*ft_matmut(t_mat *A, t_mat *B)
{
	t_mat	*ptr;

	if (
}
*/
