#ifndef GPRINT_H_
#define GPRINT_H_

#include "Arduino.h"

// function to print trivial char*
void gprintf(const char* format) // base function
{
    Serial.print(format);
}

// using template
template<typename T, typename... Targs>
void gprintf(const char* format, T value, Targs... Fargs) // recursive variadic function
{
    for (; *format != '\0'; format++)
    {
        if (*format == '%')
        {
            // printing value instead of %
            Serial.print(value);
            gprintf(format + 1, Fargs...); // recursive call
            return;
        }
        // if no %
        Serial.print(*format);
    }
}


#endif // GPRINT_H_
