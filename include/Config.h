#pragma once

#include <Arduino.h>

#define SCREENS 3

/***************************************************
 *                     ADDRESS 
 ***************************************************/
extern IPAddress PLC;
extern IPAddress Gateway;
extern IPAddress Subnet;

/***************************************************
 *                      WIFI 
 ***************************************************/
extern char ssid[];
extern char pass[];

/***************************************************
 *                    PLC DATA 
 ***************************************************/
#define RACK 0
#define SLOT 2
