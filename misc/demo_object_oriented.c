#include <stdio.h>

typedef struct Computer Computer;

struct Computer{
    double cost;
    const char* name;
    void (*show)(const Computer*);
};

typedef enum {
    Red = 0,
    Black,
    Blue,
} Color;

typedef struct AppleComputer AppleComputer;
struct AppleComputer {
    Computer computer;
    Color color;
    void (*show)(const AppleComputer*);
    void (*getColor)(const AppleComputer*);
};

void ComputerShow(const Computer* computer) {
    printf("cost: %f\t name: %s\n", computer->cost, computer->name);
}

void AppleComputerShow(const AppleComputer* apple) {
    apple->computer.show(&apple->computer);
}

void AppleComputerGetColor(const AppleComputer* computer) {
    switch (computer->color) {
        case Red:
          printf("computer is red\n");
          break;
        case Black:
          printf("computer is black\n");
          break;
        case Blue:
          printf("computer is blue\n");
        default:
          break;
    }
}

int main() {

    Computer computer = {
        12344.56,
        "Computer",
        ComputerShow,
    };

    AppleComputer apple = {
        computer,
        Blue,
        AppleComputerShow,
        AppleComputerGetColor,
    };

    apple.show(&apple);

    printf("sizeof computer: %d\n", sizeof(apple));
    printf("sizeof Color: %d\n", sizeof(Color));
}

// yes
// you can write object-oriented using C!