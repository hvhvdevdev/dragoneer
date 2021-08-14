#include <Utils.h>
#include <ImplIAnimal.h>
#include <stdio.h>
#include <malloc.h>

struct CDog {
    TCStrPtr name;
    TUint8   age;
};

struct CCat {
    TCStrPtr name;
    TUint8   age;
};

Implement_IAnimal( CDog );
Implement_IAnimal( CCat );

void CDog_Intro ( TVoidPtr _self, TCStrPtr message ) {
    struct CDog *self = _self;
    printf( "Dog said: %s %s\n", message, self->name );
}

void CCat_Intro ( TVoidPtr _self, TCStrPtr message ) {
    struct CCat *self = _self;
    printf( "Cat said: %s %s\n", message, self->name );
}

TUint8 CDog_GetAge ( TVoidPtr _self, TUint8 maxAge ) {
    struct CDog *self = _self;
    return self->age;
}

TUint8 CCat_GetAge ( TVoidPtr _self, TUint8 maxAge ) {
    struct CCat *self = _self;
    return self->age;
}

IAnimal CCat_Create ( TCStrPtr name ) {
    struct CCat *data = malloc( sizeof( struct CCat ));
    data->name = name;
    data->age  = 1;
    IAnimal animal = { .obj = data, .pVft = &CCat_IAnimal_Vft };
    return animal;
}

IAnimal CDog_Create ( TCStrPtr name ) {
    struct CDog *data = malloc( sizeof( struct CDog ));
    data->name = name;
    data->age  = 1;
    IAnimal animal = { .obj = data, .pVft = &CDog_IAnimal_Vft };
    return animal;
}

int main ( int argc, char **args ) {
    IAnimal animal;
    animal = CCat_Create(( TCStrPtr ) "Tom" );
    IAnimal_Intro( &animal, ( TCStrPtr ) "Meow~ " );
    animal = CDog_Create(( TCStrPtr ) "Spike" );
    IAnimal_Intro( &animal, ( TCStrPtr ) "Woof woof~ " );
}