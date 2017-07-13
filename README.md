# SimpleTime
Simple time library for Arduino / ESP8266 to make human readable output from unix time stamps.

Make sure that the time is set before using the library(by NTP, RTC, etc.)

The functions available in the library include:

    time_t t = time(NULL);  // store the current time in time variable t 
    hour(t);                // returns the hour for the given time t
    minute(t);              // returns the minute for the given time t
    second(t);              // returns the second for the given time t 
    day(t);                 // the day for the given time t 
    weekday(t);             // day of the week for the given time t  
    month(t);               // the month for the given time t 
    year(t);                // the year for the given time t  

**Calling a function without a time object, eg `hour()`, will return the current time** 

No other fancy macros are added to keep it, as the name suggests, simple.
To use the library, copy the download to the Library directory.

This library is inspired by the TimeLib library by Michael Margolis. 

SimpleTime library uses the date/time algorithms found here:
http://howardhinnant.github.io/date_algorithms.html