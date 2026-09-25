#include "notification_queue.hpp"
#include <stdexcept>

using namespace std;

NotificationQueue::NotificationQueue()
    : data(nullptr), capacity(0), first(0), count(0) {}

NotificationQueue::~NotificationQueue(){
    delete[] data;
}

void NotificationQueue::reallocate(){
    int new_capacity = count * 2;
    if (new_capacity < 4){
        new_capacity = 4;
    }
    Notification *new_data = new Notification[new_capacity];
    for (int i = 0; i < count; i++){
        new_data[i] = data[first + i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
    first = 0;
}

void NotificationQueue::push(const Notification &notification){
    if (first + count == capacity){
        reallocate();
    }
    data[first + count] = notification;
    count++;
}

Notification NotificationQueue::pop(){
    if (count == 0){
        throw out_of_range("NotificationQueue: queue is empty");
    }
    Notification result = data[first];
    first++;
    count--;
    if (count == 0){
        first = 0;
    }
    return result;
}

int NotificationQueue::size() const {
    return count;
}

const Notification* NotificationQueue::begin() const {
    return data + first;
}

const Notification* NotificationQueue::end() const {
    return data + first + count;
}

static bool is_urgent(const Notification &n){
    return n.type == NotificationType::System && n.system.severity == Severity::Urgent;
}

static int type_rank(const Notification &n){
    switch (n.type){
    case NotificationType::Message:
        return 0;
    case NotificationType::System:
        return 1;
    case NotificationType::App:
        return 2;
    }
    return 3;
}

static bool more_actual(const Notification &a, const Notification &b){
    if (is_urgent(a) != is_urgent(b)){
        return is_urgent(a);
    }
    if (a.timestamp != b.timestamp){
        return a.timestamp < b.timestamp;
    }
    return type_rank(a) < type_rank(b);
}

NotificationPriorityQueue::NotificationPriorityQueue()
    : data(nullptr), capacity(0), count(0) {}

NotificationPriorityQueue::~NotificationPriorityQueue(){
    delete[] data;
}

void NotificationPriorityQueue::push(const Notification &notification){
    if (count == capacity){
        int new_capacity = capacity * 2;
        if (new_capacity < 4){
            new_capacity = 4;
        }
        Notification *new_data = new Notification[new_capacity];
        for (int i = 0; i < count; i++){
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
    data[count] = notification;
    count++;
}

Notification NotificationPriorityQueue::pop(){
    if (count == 0){
        throw out_of_range("NotificationPriorityQueue: queue is empty");
    }

    int best = 0;
    for (int i = 1; i < count; i++){
        if (more_actual(data[i], data[best])){
            best = i;
        }
    }

    Notification result = data[best];


    for (int i = best; i < count - 1; i++){
        data[i] = data[i + 1];
    }
    count--;
    return result;
}

int NotificationPriorityQueue::size() const {
    return count;
}

const Notification* NotificationPriorityQueue::begin() const {
    return data;
}

const Notification* NotificationPriorityQueue::end() const {
    return data + count;
}