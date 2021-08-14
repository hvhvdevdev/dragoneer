#include <Utils.h>
#include <ImplIAnimal.h>
#include <ImplIMammal.h>
#include <stdio.h>
#include <malloc.h>

struct CDog {
    TCStrPtr name;
    TUint8   age;
    IAnimal  asIAnimal;
};

struct CCat {
    TCStrPtr name;
    TUint8   age;
    IAnimal  asIAnimal;
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

struct CCat *CCat_Create ( TCStrPtr name ) {
    struct CCat *data = malloc( sizeof( struct CCat ));
    data->name = name;
    data->age  = 1;
    IAnimal asIAnimal = { .pVft = &CCat_IAnimal_Vft, .obj = data };
    data->asIAnimal = asIAnimal;
    return data;
}

struct CDog *CDog_Create ( TCStrPtr name ) {
    struct CDog *data = malloc( sizeof( struct CDog ));
    data->name = name;
    data->age  = 1;
    IAnimal asIAnimal = { .pVft = &CDog_IAnimal_Vft, .obj = data };
    data->asIAnimal = asIAnimal;
    return data;
}

int main ( int argc, char **args ) {
    IAnimal animal;
    animal = CCat_Create(( TCStrPtr ) "Tom" )->asIAnimal;
    IAnimal_Intro( &animal, ( TCStrPtr ) "Meow~ " );
    animal = CDog_Create(( TCStrPtr ) "Spike" )->asIAnimal;
    IAnimal_Intro( &animal, ( TCStrPtr ) "Woof woof~ " );
}