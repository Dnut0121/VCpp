#include "yuhan_stack.h"

int main() {
    y_stack myStack;

    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    while (!myStack.isEmpty()) {
        printf("Popped: %d\n",myStack.pop());
    }

    return 0;
}