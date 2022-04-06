#pragma once

template<typename T>
struct Node {
    Node(T value = T(), Node *next = nullptr) {
        this->value = value;
        this->next = next;
    }

    Node *next;
    T value;
};
