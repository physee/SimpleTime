/*
  SimpleTime.c - simple low level time and date functions
  Copyright (c) Pim Rutgers 2017
  pim@physee.eu

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  ---

  This library is heavily inspired by the TimeLib library by Michael Margolis. 
  It is not as extensive and only provides:
    Year
    Month
    Day
    Weekday
    Hour
    Minute
    Seconds
  No other fancy macros are added to keep, as the name suggests, it simple.

  This library uses the date/time algorithms found here:
  http://howardhinnant.github.io/date_algorithms.html

*/

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include <time.h>
#include "SimpleTime.h"

static stElements_t st;
static time_t cacheTime;

void refreshCache(time_t t) {
  if (t != cacheTime) {
    breakTime(t, st); 
    cacheTime = t; 
  }
}

int hour() { // the hour now 
  return hour(time(NULL)); 
}

int hour(time_t t) { // the hour for the given time
  refreshCache(t);
  return st.Hour;  
}

int minute() {
  return minute(time(NULL)); 
}

int minute(time_t t) { // the minute for the given time
  refreshCache(t);
  return st.Minute;  
}

int second() {
  return second(time(NULL)); 
}

int second(time_t t) {  // the second for the given time
  refreshCache(t);
  return st.Second;
}

int day() {
  return day(time(NULL)); 
}

int day(time_t t) { // the day given for the given time
  refreshCache(t);
  return st.Day;
}

int weekday() {   // Sunday is day 1
  return weekday(time(NULL)); 
}

int weekday(time_t t) {
  refreshCache(t);
  return st.Weekday;
}
   
int month(){
  return month(time(NULL)); 
}

int month(time_t t) {  // the month for the given time
  refreshCache(t);
  return st.Month;
}

int year() {  // 
  return year(time(NULL)); 
}

int year(time_t t) { // the year for the given time
  refreshCache(t);
  return st.Year;
}

void breakTime(time_t timeInput, stElements_t &st) {
  // This is where the magic happens.
  // For extensive explanations about the algorithm visit the url:
  // http://howardhinnant.github.io/date_algorithms.html
  
  uint32_t z;
  z = (uint32_t)timeInput;

  st.Second = z % 60;
  z /= 60;
  st.Minute = z % 60;
  z /= 60;
  st.Hour = z % 24;
  z /= 24;
  // From here, z is in days from 1970-01-01
  // weekday_from_days
  st.Weekday = (uint32_t)(z >= -4 ? (z + 4) % 7 : (z + 5) % 7 + 6);

  // civil_from_days
  z += 719468;
  const int era = (z >= 0 ? z : z - 146096) / 146097;
  const uint32_t doe = (uint32_t)(z - era * 146097);                      // [0, 146096]
  const uint32_t yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;   // [0, 399]
  const int y = (int)yoe + era * 400;
  const uint32_t doy = doe - (365*yoe + yoe/4 - yoe/100);                 // [0, 365]
  const uint32_t mp = (5*doy + 2)/153;                                    // [0, 11]
  const uint32_t d = doy - (153*mp+2)/5 + 1;                              // [1, 31]
  const uint32_t m = mp + (mp < 10 ? 3 : -9);                             // [1, 12]
  st.Day = d;
  st.Month = m;
  st.Year = y + (m <= 2);
}