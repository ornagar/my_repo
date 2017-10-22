#include <stdio.h>
#include <stdlib.h>

void BursaProblem(int *arr, size_t arr_size, int *final_buy, int *final_sell);

int main(void)
{
	int arr[] = {6, 12, 3, 5, 1, 4, 9, 2};
	int final_sell = 0;
	int final_buy = 0;

	BursaProblem(arr, 8, &final_buy, &final_sell);

	printf("final buy = %d\nfinal sell = %d\n", final_buy, final_sell);

	return(0);
}

void BursaProblem(int *arr, size_t arr_size, int *final_buy, int *final_sell)
{
	int buy_cand = 0;
	int sell_cand = 0;

	buy_cand = sell_cand = *final_buy = *final_sell = *arr;

	while (arr_size)
	{
		if (*arr < buy_cand)
		{
			buy_cand = *arr;
			sell_cand = *arr;
		}

		if (*arr > sell_cand)
		{
			sell_cand = *arr;
		}

		if ((sell_cand - buy_cand) > (*final_sell - *final_buy))
		{
			*final_buy = buy_cand;		
			*final_sell = sell_cand;
		}

		++arr;
		--arr_size;
	}
	
	return;
}
