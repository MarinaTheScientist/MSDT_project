#pragma once
#include <iostream>

enum class NotificationType
{
    System,
    Message,
    App
};

enum class Severity
{
    Normal,
    Urgent
};

struct SystemData
{
    char message[128];
    Severity severity;
};

struct MessageData
{
    char contact[32];
    char text[128];
};

struct AppData
{
    char app[32];
    char title[64];
    char text[128];
};

struct Notification
{
    long timestamp;
    NotificationType type;
    union
    {
        SystemData system;
        MessageData message;
        AppData app;
    };
};

Notification make_system_notification(long timestamp, const char *message, Severity severity);
Notification make_message_notification(long timestamp, const char *contact, const char *text);
Notification make_app_notification(long timestamp, const char *app, const char *title, const char *text);

std::ostream& operator<<(std::ostream &os, const Notification &n);

int count_notifications(const Notification *notifications, int size, NotificationType type);