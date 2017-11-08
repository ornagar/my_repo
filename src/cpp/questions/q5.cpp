typedef struct List_t List;
typedef struct Person_t Person;

void foo(List *ll, int key, int age)
{
	void *vv = ll_find(ll, key);
	//we know that the list actually contains person data so we
	//want to convert the void pointer to Person to access it 
	Person *p = (Person *)ll;//accidentally used ll instead of vv
	p->age = age;
}

int main(void)
{
	
	return (0);
}

