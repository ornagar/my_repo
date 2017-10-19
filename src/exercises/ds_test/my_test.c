#include <stdio.h>
#include <stdlib.h>

int arr[6][6] = 
{
	{0, 1, 0, 0, 0, 1}, 
	{0, 1, 1, 1, 0, 0},
	{0, 0, 0, 1, 0, 1}, 
	{0, 0, 0, 0, 0, 1},
	{0, 0, 0, 1, 0, 1}, 
	{1, 0, 1, 0, 0, 1}
};

int find_soti(size_t *idx1, size_t *idx2, unsigned int *arr, 
				unsigned int sum_of_two, size_t n)
{
	size_t i = 0;
	*idx1 = 0;
	while (n > *idx1)
	{
		for (i = *idx1 + 1; i < n && arr[*idx1] <= sum_of_two; ++i)
		{
			if (arr[*idx1] + arr[i] == sum_of_two)
			{
				*idx2 = i;
				
				return 1;
			}
		}
		++(*idx1);
	}
	
	return 0;
}


void PaintIsland(size_t r_idx, size_t c_idx, size_t row, size_t col)
{
	if (1 != arr[r_idx][c_idx])
	{
		return;
	}
	
	arr[r_idx][c_idx] = 2;
	
	if (r_idx + 1 < row)
	{
		PaintIsland(r_idx + 1, c_idx, row, col);
	}
	
	if (c_idx + 1 < row)
	{
		PaintIsland(r_idx, c_idx + 1, row, col);
	}
	
	if (r_idx - 1 >= 0)
	{
		PaintIsland(r_idx - 1, c_idx, row, col);
	}
	
	if (c_idx - 1 >= 0)
	{
		PaintIsland(r_idx, c_idx - 1, row, col);
	}
	
	return;
}

size_t count_islands(size_t row, size_t col)
{
	size_t count = 0;
	size_t i = 0;
	size_t j = 0;
	
	for (i = 0; i < col; ++i)
	{
		for (j = 0; j < row; ++j)
		{
			if (arr[i][j] == 1)
			{
				PaintIsland(i, j, row, col);
				++count;
			}
		}
	}
	
	return count;
}

void rec_multiply(int *res, int x, int y)
{
	if (0 == y)
	{
		return;
	}
	
	*res += x;
	rec_multiply(res, x, y - 1);
}

int multiply(int x, int y)
{
	int r = abs(x);
	int z = abs(y);
	
	if (x == 0 || y == 0)
	{
		return 0;
	}
	
	rec_multiply(&r, r, z - 1);
	
	if (x < 0 && y < 0) return r;
	if (x < 0 || y < 0) return -r;
	
	return r;
}

int main(int argc, char **argv)
{
	size_t idx1 = 0;
	size_t idx2 = 0;
	int x = -3;
	int y = 0;
	
	unsigned int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
	unsigned int res = 9;
	printf("\nreturn status = %d\n", find_soti(&idx1, &idx2, arr, res, 8));
	
	printf("%u + %u = %u\n\n", arr[idx1], arr[idx2], res);
	
	printf("num of islands = %lu\n\n", count_islands(6, 6));
	
	printf("%d * %d = %d\n\n", x, y, multiply(x, y));
	return 0;
}
