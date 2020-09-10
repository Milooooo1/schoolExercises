#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <vector>
#include <iostream>
using namespace std;
struct Queue {
    vector<int> v;
    int head;
    int tail;
};
void init_queue(Queue & pq);
void enqueue(Queue & pq, float data);
float dequeue(Queue & pq);
float show(const Queue & pq);
#endif /* QUEUE_HPP */