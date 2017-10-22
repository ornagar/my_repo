extern "C"
{
	int Foo(int x)
	{
		return (x - 2);
	}
	
	int Bar(char *x)
	{
		
		return (65);
	}
}

//g++ -fPIC -shared shared.cpp -o shared.so
