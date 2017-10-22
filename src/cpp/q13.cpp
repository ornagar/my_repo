#include <iostream>
#include <dlfcn.h>

using namespace std;

int main(void)
{
	int x = 14;
	
    cout << "Opening shared.so..." << endl;
    
    void* handle = dlopen("./shared.so", RTLD_LAZY);
    
    if (!handle) 
    {
        cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }
    
    typedef int (*func_t)(int);
	typedef int (*func2_t)(int);
    // reset errors
    dlerror();
    func_t func = (func_t) dlsym(handle, "_Z3Fooi");
    func2_t func2 = (func2_t) dlsym(handle, "_Z3Bari");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol 'Foo': " << dlsym_error << endl;
        dlclose(handle);
        return 1;
    }
    
    cout << "Calling Foo...\n";
    cout << "x before Foo = " << x << endl;
    x = func(x);
    cout << "x after Foo = " << x << endl;

	cout << "Calling Bar...\n";
    cout << "x before Bar = " << x << endl;
    x = func2(x);
    cout << "x after Foo = " << x << endl;

    dlclose(handle);
	
	return (0);
}
