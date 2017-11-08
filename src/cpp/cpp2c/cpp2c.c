#include <stdio.h>
#include <stdlib.h>

//TODO: fix inline function.
//TODO: finish LegendaryAnimal.

/*************************FUNC DECLARATIONS************************************/
typedef struct Animal Animal;
typedef struct Centipede Centipede;
typedef struct Squirl Squirl;
typedef struct FlyingSquirl FlyingSquirl;
typedef struct LegendaryAnimal LegendaryAnimal;

Animal *rd_33_Animal_heap_init(void);
void rd_33_Animal_Ctor(Animal *this);
void rd_33_Animal_CCtor(Animal *this, const Animal *other);
void rd_33_Animal_Dtor(Animal *this);
void rd_33_Animal_Display(Animal *this);
int rd_33_Animal_GetID(Animal *this);
void rd_33_Animal_PrintCount(void);

Centipede *rd_33_Centipede_heap_init(void);
void rd_33_Centipede_Ctor(Centipede *this);
void rd_33_Centipede_CCtor(Centipede *this, const Centipede *other);
void rd_33_Centipede_Dtor(Centipede *this);
void rd_33_Centipede_Display(Centipede *this);
void rd_33_Centipede_BuyShues(Centipede *this);

Squirl *rd_33_Squirl_heap_init(void);
void rd_33_Squirl_Ctor(Squirl *this);
void rd_33_Squirl_CCtor(Squirl *this, const Squirl *other);
void rd_33_Squirl_Dtor(Squirl *this);
void rd_33_Squirl_Display(Squirl *this);

FlyingSquirl *rd_33_Flying_Squirl_heap_init(void);
void rd_33_Flying_Squirl_Ctor(FlyingSquirl *this);
void rd_33_Flying_Squirl_CCtor(FlyingSquirl *this, const FlyingSquirl *other);
void rd_33_Flying_Squirl_Dtor(FlyingSquirl *this);
void rd_33_Flying_Squirl_Display(FlyingSquirl *this);

LegendaryAnimal *rd_33_LegendaryAnimal_heap_init(void);
void rd_33_LegendaryAnimal_Ctor(LegendaryAnimal *this);
void rd_33_LegendaryAnimal_CCtor(LegendaryAnimal *this, const LegendaryAnimal *other);
void rd_33_LegendaryAnimal_Dtor(LegendaryAnimal *this);
void rd_33_LegendaryAnimal_Display(LegendaryAnimal *this);

/********************************STRUCTS***************************************/
typedef struct
{
    void (*Dtor_ptr)(Animal *this);
    void (*Display_ptr)(Animal *this);
}AnimalVtable;
AnimalVtable g_avt =
{
    rd_33_Animal_Dtor,
    rd_33_Animal_Display
};

typedef struct
{
    void (*Dtor_ptr)(Centipede *this);
    void (*Display_ptr)(Centipede *this);
    void (*BuyShues_ptr)(Centipede *this);
}CentipedeVtable;
CentipedeVtable g_cvt =
{
    rd_33_Centipede_Dtor,
    rd_33_Centipede_Display
};

typedef struct
{
    void (*Dtor_ptr)(Squirl *this);
    void (*Display_ptr)(Squirl *this);
}SquirlVtable;
SquirlVtable g_svt =
{
    rd_33_Squirl_Dtor,
    rd_33_Squirl_Display
};

typedef struct
{
    void (*Dtor_ptr)(FlyingSquirl *this);
    void (*Display_ptr)(FlyingSquirl *this);
}FlyingSquirlVtable;
FlyingSquirlVtable g_fsvt =
{
    rd_33_Flying_Squirl_Dtor,
    rd_33_Flying_Squirl_Display
};

typedef struct
{
    void (*Dtor_ptr)(LegendaryAnimal *this);
    void (*Display_ptr)(LegendaryAnimal *this);
}LegendaryAnimalVtable;
LegendaryAnimalVtable g_lavt =
{
    rd_33_LegendaryAnimal_Dtor,
    rd_33_LegendaryAnimal_Display
};

/*
 class Animal
{
public:
    Animal()
    : m_id(++s_count)
    {
        cout << "Animal::Ctor()"  << m_id << endl;
    }

    virtual ~Animal(){ --s_count; cout << "Animal::Dtor()" << m_id  << endl; }

    Animal(const Animal &other)
    : m_id(++s_count)
    {
        cout << "Animal::CCtor() "  << m_id << endl;
    }

    virtual void Display()
    {
        cout << "Animal::Display() : " << m_id << endl;
    }

    static void PrintCount() { cout << "s_count: " << s_count << endl;}
protected:
    int GetID() { return m_id; }

private:
    static int s_count;
    int m_id;
    Animal &operator=(const Animal &); // disabled
};
 */
struct Animal
{
    AnimalVtable *vtable;
    int m_id;
};


/*
class Centipede: public Animal
{
public:
    Centipede()
    : m_numLegs(46)
    {
        cout << "Centipede::Ctor()" << endl;
    }
    Centipede(const Centipede &other )
    : Animal(other),
      m_numLegs(other.m_numLegs)
    {
        cout << "Centipede::CCtor()" << endl;
    }
    ~Centipede() { cout << "Centipede::dtor()" << endl; }
    void Display() { cout << "Centipede::Display() ID:"<<GetID()<<"  num legs:" << m_numLegs << endl; }
    virtual void BuyShues() { cout << "Centipede::BuyShues() ID:"<<GetID() << endl; }

private:
    int m_numLegs;
};
*/
struct Centipede
{
    Animal animal;
    int m_numLegs;
};

/*
class Squirl: public Animal
{
public:
    Squirl() { cout << "Squirl::Ctor()" << endl; }
    Squirl(const Squirl &other ): Animal(other) { cout << "Squirl::CCtor()" << endl; }
    ~Squirl() { cout << "Squirl::dtor()" << endl; }
    void Display() { cout << "Squirl::Display() ID:"<<GetID()<< endl; }

private:
};
 */
struct Squirl
{
    Animal animal;
};

/*
class FlyingSquirl : public Squirl
{
public:
    FlyingSquirl() { cout << "FlyingSquirl::Ctor()" << endl; }
    FlyingSquirl(const FlyingSquirl &other): Squirl(other) { cout << "FlyingSquirl::CCtor()" << endl; }
    ~FlyingSquirl(){ cout << "FlyingSquirl::dtor()" << endl; }
    void Display() { cout << "FlyingSquirl::Display() ID:"<<GetID()<<endl;}
private:
};
 */
struct FlyingSquirl
{
    Squirl squirl;
};

/*
class LegendaryAnimal: public Animal
{
public:
  LegendaryAnimal() : m_a1(new Centipede()),
            m_a2(new Squirl())
  {
  }

  LegendaryAnimal(const LegendaryAnimal& other) :
         Animal(other), m_a1(new Animal(other)), m_a2(new Animal(other)),
                                             m_c(other.m_c), m_sq(other.m_sq) {}
  ~LegendaryAnimal()
  {
    delete m_a1;
    delete m_a2;
  }

  void Display()
  {
    m_a1->Display();
    m_a2->Display();
    m_c.Display();
    m_sq.Display();
  }

private:
  Animal *m_a1;
  Animal *m_a2;
  Centipede m_c;
  Squirl m_sq;
};
 */
struct LegendaryAnimal
{
    Animal animal;
    Animal *m_a1;
    Animal *m_a2;
    Centipede m_c;
    Squirl m_sq;
};
/********************************STRUCTS***************************************/

/****************************ANIMAL********************************************/
static int rd_33_Animal_s_count = 0;

Animal *rd_33_Animal_heap_init(void)
{
    Animal *this = malloc(sizeof(*this));
    this->m_id = ++rd_33_Animal_s_count;
    printf("Animal::Ctor()%d\n", this->m_id);

    this->vtable = &g_avt;

    return this;
}

void rd_33_Animal_Ctor(Animal *this)
{
    this->m_id = ++rd_33_Animal_s_count;
    printf("Animal::Ctor()%d\n", this->m_id);

    this->vtable = &g_avt;
    return;
}

void rd_33_Animal_CCtor(Animal *this, const Animal *other)
{
    this->m_id = ++rd_33_Animal_s_count;
    printf("Animal::CCtor() %d\n", this->m_id);

    this->vtable = &g_avt;
    return;
}

void rd_33_Animal_Dtor(Animal *this)
{
    --rd_33_Animal_s_count;
    printf("Animal::Dtor()%d\n", this->m_id);

    return;
}

void rd_33_Animal_Display(Animal *this)
{
    printf("Animal::Display() : %d\n", this->m_id);

    return;
}

int rd_33_Animal_GetID(Animal *this)
{
    return this->m_id;
}

void rd_33_Animal_PrintCount(void)
{
    printf("s_count: %d\n", rd_33_Animal_s_count);

    return;
}
/************************ANIMAL************************************************/

/**************************CENTIPEDE*******************************************/
Centipede *rd_33_Centipede_heap_init(void)
{
    Centipede *this = malloc(sizeof(*this));
    rd_33_Animal_Ctor(&this->animal);
    this->m_numLegs = 46;

    printf("Centipede::Ctor()\n");

    this->animal.vtable = (AnimalVtable*)&g_cvt;
    return this;
}

void rd_33_Centipede_Ctor(Centipede *this)
{
    rd_33_Animal_Ctor(&this->animal);
    this->m_numLegs = 46;

    printf("Centipede::Ctor()\n");

    this->animal.vtable = (AnimalVtable*)&g_cvt;
    return;
}

void rd_33_Centipede_CCtor(Centipede *this, const Centipede *other)
{
    rd_33_Animal_CCtor(&this->animal, &other->animal);
    this->m_numLegs = other->m_numLegs;

    printf("Centipede::CCtor()\n");

    this->animal.vtable = (AnimalVtable*)&g_cvt;
    return;
}

void rd_33_Centipede_Dtor(Centipede *this)
{
    printf("Centipede::dtor()\n");
    rd_33_Animal_Dtor(&this->animal);

    return;
}

void rd_33_Centipede_Display(Centipede *this)
{
    printf("Centipede::Display() ID:%d", rd_33_Animal_GetID(&this->animal));
    printf("  num legs:%d\n", this->m_numLegs);
    return;
}

void rd_33_Centipede_BuyShues(Centipede *this)
{
    printf("Centipede::BuyShues() ID:%d\n", rd_33_Animal_GetID(&this->animal));
}

/**************************CENTIPEDE*******************************************/

/*******************************SQUIRL*****************************************/
Squirl *rd_33_Squirl_heap_init(void)
{
    Squirl *this = malloc(sizeof(*this));
    rd_33_Animal_Ctor(&this->animal);

    printf("Squirl::Ctor()\n");

    this->animal.vtable = (AnimalVtable*)&g_svt;


    return this;
}

void rd_33_Squirl_Ctor(Squirl *this)
{
    rd_33_Animal_Ctor(&this->animal);

    printf("Squirl::Ctor()\n");

    this->animal.vtable = (AnimalVtable*)&g_svt;
    return;
}

void rd_33_Squirl_CCtor(Squirl *this, const Squirl *other)
{
    rd_33_Animal_CCtor(&this->animal, &other->animal);

    printf("Squirl::CCtor()\n");

    this->animal.vtable = (AnimalVtable*)&g_svt;
    return;
}

void rd_33_Squirl_Dtor(Squirl *this)
{
    printf("Squirl::dtor()\n");
    rd_33_Animal_Dtor(&this->animal);
    return;
}

void rd_33_Squirl_Display(Squirl *this)
{
    printf("Squirl::Display() ID:%d\n", rd_33_Animal_GetID(&this->animal));

    return;
}

/*******************************SQUIRL*****************************************/

/*******************************FLYINGSQUIRL***********************************/
FlyingSquirl *rd_33_Flying_Squirl_heap_init(void)
{
    FlyingSquirl *this = malloc(sizeof(*this));
    rd_33_Squirl_Ctor(&this->squirl);

    printf("FlyingSquirl::Ctor()\n");

    this->squirl.animal.vtable = (AnimalVtable*)&g_fsvt;
    return this;
}

void rd_33_Flying_Squirl_Ctor(FlyingSquirl *this)
{
    rd_33_Squirl_Ctor(&this->squirl);
    printf("FlyingSquirl::Ctor()\n");

    this->squirl.animal.vtable = (AnimalVtable*)&g_fsvt;
    return;
}

void rd_33_Flying_Squirl_CCtor(FlyingSquirl *this, const FlyingSquirl *other)
{
    rd_33_Squirl_CCtor(&this->squirl, &other->squirl);

    printf("FlyingSquirl::CCtor()\n");

    this->squirl.animal.vtable = (AnimalVtable*)&g_fsvt;
    return;
}

void rd_33_Flying_Squirl_Dtor(FlyingSquirl *this)
{
    printf("FlyingSquirl::dtor()\n");

    rd_33_Squirl_Dtor(&this->squirl);
    return;
}

void rd_33_Flying_Squirl_Display(FlyingSquirl *this)
{
    printf("FlyingSquirl::Display() ID:%d\n",
                                    rd_33_Animal_GetID(&this->squirl.animal));

    return;
}
/*******************************FLYINGSQUIRL***********************************/

/*******************************LegendaryAnimal********************************/
LegendaryAnimal *rd_33_LegendaryAnimal_heap_init(void)
{
    LegendaryAnimal *this = malloc(sizeof(*this));

    rd_33_LegendaryAnimal_Ctor(this);
    return this;
}

void rd_33_LegendaryAnimal_Ctor(LegendaryAnimal *this)
{
    rd_33_Animal_Ctor(&this->animal);

    this->m_a1 = (Animal *)rd_33_Centipede_heap_init();
    this->m_a2 = (Animal *)rd_33_Squirl_heap_init();
    rd_33_Centipede_Ctor(&this->m_c);
    rd_33_Squirl_Ctor(&this->m_sq);
    this->animal.vtable = (AnimalVtable*)&g_lavt;
    return;
}

void rd_33_LegendaryAnimal_CCtor(LegendaryAnimal *this, const LegendaryAnimal *other)
{
    rd_33_Animal_CCtor(&this->animal, &other->animal);

    this->m_a1 = malloc(sizeof(other->m_a1));
    this->m_a2 = malloc(sizeof(other->m_a2));

    rd_33_Animal_CCtor(this->m_a1, other->m_a1);
    rd_33_Animal_CCtor(this->m_a2, other->m_a2);

    rd_33_Centipede_CCtor(&this->m_c, &other->m_c);
    rd_33_Squirl_CCtor(&this->m_sq, &other->m_sq);

    this->animal.vtable = (AnimalVtable*)&g_lavt;
    return;
}

void rd_33_LegendaryAnimal_Dtor(LegendaryAnimal *this)
{
    free(this->m_a1);
    free(this->m_a2);
    rd_33_Animal_Dtor(&this->animal);
    return;
}

void rd_33_LegendaryAnimal_Display(LegendaryAnimal *this)
{
    this->m_a1->vtable->Display_ptr(this->m_a1);
    this->m_a2->vtable->Display_ptr(this->m_a2);
    ((CentipedeVtable *)this->m_c.animal.vtable)->Display_ptr(&this->m_c);
    ((SquirlVtable *)this->m_sq.animal.vtable)->Display_ptr(&this->m_sq);

    return;
}
/*******************************LegendaryAnimal********************************/

int maxFunc(int *t1, int *t2)
{
    return ((*t1 > *t2)? *t1: *t2);
}

void rd_33_Foo_an(Animal* a)
{
    ((AnimalVtable *)a->vtable)->Display_ptr(a);
}

void rd_33_Foo()
{
    rd_33_Animal_PrintCount();
}

Animal rd_33_Foo_in(int i)
{
    Centipede ret;
    rd_33_Centipede_Ctor(&ret);

    printf("Foo(int i)\n");
    ((CentipedeVtable *)ret.animal.vtable)->Display_ptr(&ret);

    Animal new;
    rd_33_Animal_CCtor(&new, (Animal*)&ret);
    ((CentipedeVtable *)ret.animal.vtable)->Dtor_ptr(&ret);
    
    return new;
}

void FiFi(Squirl s)
{
    Squirl temp;
    rd_33_Squirl_CCtor(&temp, &s);
    rd_33_Squirl_Display(&temp);
    rd_33_Squirl_Dtor(&temp);
}

int main(void)
{
    int i = 0;
    /* Centipede c; */
    Centipede c;
    rd_33_Centipede_Ctor(&c);

    /* Foo(c); */
    rd_33_Foo_an((Animal*)&c);

<<<<<<< .mine
	a.vtable->Display_ptr(&a);
	
    ((Squirl_table *)c.animal.vtable)->Dtor_ptr(&s);
    ((Centipede_table *)c.animal.vtable)->Dtor_ptr(&c);
    ((Animal_table *)a.vtable)->Dtor_ptr(&a);
=======
    /* Foo(3).Display() */
    Animal temp1;
    temp1 = rd_33_Foo_in(3);
    rd_33_Animal_Display(&temp1);
    rd_33_Animal_Dtor(&temp1);
>>>>>>> .r258

    /*
    Animal *array[] =
    {
        new Centipede(),
        new Squirl(),
        new Centipede()
    };
    */
    Animal *array[] =
    {
        (Animal*)rd_33_Centipede_heap_init(),
        (Animal*)rd_33_Squirl_heap_init(),
        (Animal*)rd_33_Centipede_heap_init()
    };

    /*
    for(int i = 0; i < 3; ++i) array[i]->Display();
    for(int i = 0; i < 3; ++i) delete array[i];
     */
    for (i = 0; i < 3; ++i) {
        array[i]->vtable->Display_ptr(array[i]);
    }
    for (i = 0; i < 3; ++i) {
        array[i]->vtable->Dtor_ptr(array[i]);
    }

    Animal arr2[3];
    Centipede cent;
    Squirl sqrl;
    Animal anml;

    rd_33_Centipede_Ctor((Centipede *) &cent);
    rd_33_Animal_CCtor(&arr2[0], (Animal *)&cent);
    rd_33_Centipede_Dtor(&cent);

    rd_33_Squirl_Ctor((Squirl *) &sqrl);
    rd_33_Animal_CCtor(&arr2[1], (Animal *) &sqrl);
    rd_33_Squirl_Dtor(&sqrl);

    rd_33_Animal_Ctor(&arr2[2]);

    for (i = 0; i < 3; ++i) {
        arr2[i].vtable->Display_ptr(&arr2[i]);
    }

    rd_33_Animal_PrintCount();
    Centipede c2;
    rd_33_Centipede_Ctor(&c2);
    rd_33_Animal_PrintCount();

    Centipede arr3[4];
    for (i = 0; i < 4; ++i) {
        rd_33_Centipede_Ctor(&arr3[i]);
    }

    Squirl *arr4[4];
    for (i = 0; i < 4; ++i) {
        arr4[i] = rd_33_Squirl_heap_init();
    }
    for (i = 3; i >= 0; --i) {
        ((SquirlVtable *)arr4[i]->animal.vtable)->Dtor_ptr(arr4[i]);
        free(arr4[i]);
    }

    int temp2 =1;
    int temp3 = 2;
    printf("%d\n", maxFunc(&temp2, &temp3));

    FlyingSquirl fs;
    rd_33_Flying_Squirl_Ctor(&fs);
    FiFi(*(Squirl *)&fs);
printf("---------------------------------------\n");

    LegendaryAnimal *la1 = rd_33_LegendaryAnimal_heap_init();
    LegendaryAnimal *la2 = malloc(sizeof(*la2));
    rd_33_LegendaryAnimal_CCtor(la2, la1);

    printf("-------------la1---------\n");
    ((LegendaryAnimalVtable *)la1->animal.vtable)->Display_ptr(la1);
    /*printf("-------------la2---------\n");
    ((LegendaryAnimalVtable *)la2->animal.vtable)->Display_ptr(la1);

    ((LegendaryAnimalVtable *)la1->animal.vtable)->Dtor_ptr(la1);
    free(la1);
*/

/**********************************DTORS********************************/
    rd_33_Flying_Squirl_Dtor(&fs);
    for (i = 3; i >= 0; --i) {
        rd_33_Centipede_Dtor(&arr3[i]);
    }
    rd_33_Centipede_Dtor(&c2);
    for (i = 2; i >= 0; --i) {
        arr2[i].vtable->Dtor_ptr(&arr2[i]);
    }
    ((CentipedeVtable *)c.animal.vtable)->Dtor_ptr(&c);

    return 0;
}
