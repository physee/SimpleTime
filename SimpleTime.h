/*
  SimpleTime.h - low level time and date functions
*/


#ifndef _SimpleTime_h
#ifdef __cplusplus
#define _SimpleTime_h

#include <inttypes.h>
#ifndef __AVR__
#include <sys/types.h> // for __time_t_defined, but avr libc lacks sys/types.h
#endif


#if !defined(__time_t_defined) // avoid conflict with newlib or other posix libc
typedef unsigned long time_t;
#endif

typedef struct { 
  uint8_t Second; 
  uint8_t Minute; 
  uint8_t Hour; 
  uint8_t Weekday;  
  uint8_t Day;
  uint8_t Month; 
  uint32_t Year;  
} 	stElements_t, SimpleTimeElements, *stElementsPtr_t;


/*============================================================================*/
/*  time and date functions   */
int hour();            // the hour now 
int hour(time_t t);    // the hour for the given time
int minute();          // the minute now 
int minute(time_t t);  // the minute for the given time
int second();          // the second now 
int second(time_t t);  // the second for the given time
int day();             // the day now 
int day(time_t t);     // the day for the given time
int weekday();         // the weekday now (Sunday is day 1) 
int weekday(time_t t); // the weekday for the given time 
int month();           // the month now  (Jan is month 1)
int month(time_t t);   // the month for the given time
int year();            // the full four digit year: (2009, 2010 etc) 
int year(time_t t);    // the year for the given time

void breakTime(time_t time, stElements_t &st);  // break time_t into elements

#endif // __cplusplus
#endif /* _SimpleTime_h */