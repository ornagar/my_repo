
namespace nsa
{
	void Foo(){}
namespace nsa_a
{
	void Foo(){}
}//namespace nsa_a
}//namespace nsa

namespace nsb
{
	void Foo(){}
	void Bar(){}
	void Fishi(){}
}//namespace nsb

namespace nsa 
{
	void AnotherFunc(){}
}

void A()
{
	nsa::Foo();
	using nsb::Foo;
	Foo();
}

using namespace nsa;
using namespace nsb;
namespace nsaaa=nsa::nsa_a;

void B()
{
	nsaaa::Foo();
	//Foo();//try uncommenting thes line, solve the error
	Bar();//why doesn't this line create an error?
}
/*
int main(void)
{
	int i = 15;
	cout << "ksjsdlfkj" << i << endl;
	cin >> i;
	cerr << "lsdfkjh" << i;
	
	return (0);
}
*/
