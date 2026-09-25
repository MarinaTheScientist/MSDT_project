#pragma once
#include "notification.hpp"

class NotificationQueue
{
private:
    Notification *data;
    int capacity;
    int first;
    int count;

    void reallocate();

public:
    NotificationQueue();
    ~NotificationQueue();

    void push(const Notification &notification);
    Notification pop();
    int size() const;

    const Notification* begin() const;
    const Notification* end() const;
};

class NotificationPriorityQueue
{
private:
    Notification *data;
    int capacity;
    int count;

public:
    NotificationPriorityQueue();
    ~NotificationPriorityQueue();

    NotificationPriorityQueue(const NotificationPriorityQueue &other) = delete;
    NotificationPriorityQueue& operator=(const NotificationPriorityQueue &other) = delete;

    void push(const Notification &notification);
    Notification pop();
    int size() const;

    const Notification* begin() const;
    const Notification* end() const;
};