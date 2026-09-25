#include "notification.hpp"
#include <cstring>

using namespace std;

static void copy_text(char *dest, const char *src, int size){
    if (src == nullptr){
        src = "";
    }
    strncpy(dest, src, size - 1);
    dest[size - 1] = '\0';
}

Notification make_system_notification(long timestamp, const char *message, Severity severity){
    Notification n;
    n.timestamp = timestamp;
    n.type = NotificationType::System;
    copy_text(n.system.message, message, sizeof(n.system.message));
    n.system.severity = severity;
    return n;
}

Notification make_message_notification(long timestamp, const char *contact, const char *text){
    Notification n;
    n.timestamp = timestamp;
    n.type = NotificationType::Message;
    copy_text(n.message.contact, contact, sizeof(n.message.contact));
    copy_text(n.message.text, text, sizeof(n.message.text));
    return n;
}

Notification make_app_notification(long timestamp, const char *app, const char *title, const char *text){
    Notification n;
    n.timestamp = timestamp;
    n.type = NotificationType::App;
    copy_text(n.app.app, app, sizeof(n.app.app));
    copy_text(n.app.title, title, sizeof(n.app.title));
    copy_text(n.app.text, text, sizeof(n.app.text));
    return n;
}

// Печатает число двумя цифрами: 5 -> "05"
static void print_two_digits(ostream &os, long value){
    if (value < 10){
        os << '0';
    }
    os << value;
}

ostream& operator<<(ostream &os, const Notification &n){
    long hours = n.timestamp / 3600 % 24;
    long minutes = n.timestamp / 60 % 60;
    long seconds = n.timestamp % 60;

    os << '[';
    print_two_digits(os, hours);
    os << ':';
    print_two_digits(os, minutes);
    os << ':';
    print_two_digits(os, seconds);
    os << "] ";

    switch (n.type){
    case NotificationType::System:
        if (n.system.severity == Severity::Urgent){
            os << "SYSTEM (URGENT): ";
        }
        else{
            os << "System: ";
        }
        os << n.system.message;
        break;
    case NotificationType::Message:
        os << "Message from " << n.message.contact << ": " << n.message.text;
        break;
    case NotificationType::App:
        os << n.app.app << " | " << n.app.title << ": " << n.app.text;
        break;
    }
    return os;
}

int count_notifications(const Notification *notifications, int size, NotificationType type){
    int count = 0;
    for (int i = 0; i < size; i++){
        if (notifications[i].type == type){
            count++;
        }
    }
    return count;
}