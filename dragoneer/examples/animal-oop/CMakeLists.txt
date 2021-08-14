add_executable(example-animal-oop main.c IAnimal.h)

target_link_libraries(example-animal-oop Dragoneer)

EnableOOP(example-animal-oop)

ScanInterface(IAnimal)