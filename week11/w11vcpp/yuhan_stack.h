#pragma once
#include <iostream>

class Node {
public:
    int data;
    Node* next;

    // 持失切
    Node(int value);
};

class y_stack {
private:
    Node* top;

public:
    // 持失切
    y_stack();

    // 社瑚切
    ~y_stack();

    bool isEmpty() const;

    void push(int value);

    int pop();
};
