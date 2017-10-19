
struct X
{
	int x;
};

int (*foo(void))(int a)
{
	return bar;
}


int main(void)
{
	const int a = 0;
	int const b = 0;
	struct X *const c = (struct X *)&a;
	struct X const d = {4};
	
	c++;
		
	return (0);
}

