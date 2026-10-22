#include "print_module.h"

#include <stdio.h>
#include <time.h>

static void print_string(char (*print)(char), const char* str);
static void print_two_digits(char (*print)(char), int value);
static void print_current_time(char (*print)(char));

char print_char(char ch) { return (char)putchar(ch); }

void print_log(char (*print)(char), char* message) {
    if (print != NULL && message != NULL) {
        print_string(print, Log_prefix);
        print(' ');
        print_current_time(print);
        print(' ');
        print_string(print, message);
    }
}

static void print_string(char (*print)(char), const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        print(str[i]);
    }
}

static void print_two_digits(char (*print)(char), int value) {
    print((char)('0' + value / 10 % 10));
    print((char)('0' + value % 10));
}

// Prints local time in HH:MM:SS format
static void print_current_time(char (*print)(char)) {
    time_t now = time(NULL);
    const struct tm* local = localtime(&now);
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    if (local != NULL) {
        hours = local->tm_hour;
        minutes = local->tm_min;
        seconds = local->tm_sec;
    }
    print_two_digits(print, hours);
    print(':');
    print_two_digits(print, minutes);
    print(':');
    print_two_digits(print, seconds);
}
