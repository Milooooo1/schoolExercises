#include <iostream>
#include "Opdracht4_4_queue.hpp"
using std::cout;

int main () {
    Queue q;
    init_queue(q);
    enqueue(q, 5.43);
    enqueue(q, 7.2);
    enqueue(q, 3.90);

    cout << dequeue(q) << endl;
    cout << show(q) << endl;
    cout << dequeue(q) << endl;
    cout << dequeue(q) << endl;
}

