
struct X
{
	int x;
};

int main(void)
{
	const int a = 0;
	int const *b = &a;
	const int **c = &b;
	struct X const d = {4};
	int *const b;
	(**c)++;
		
	return (0);
}

