#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Timer.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <IRsend.h>



uint16_t OFF[295] = {4388, 4414,  522, 1646,  522, 1666,  498, 1644,  522, 1642,  522, 554,  528, 560,  524, 1642,  524, 560,  524, 584,  498, 582,  500, 558,  524, 558,  522, 1644,  524, 1642,  522, 562,  522, 1642,  522, 558,  524, 558,  522, 558,  524, 558,  524, 558,  524, 584,  500, 1666,  498, 1642,  524, 1642,  526, 1664,  498, 1644,  688, 1476,  524, 1642,  524, 1640,  524, 560,  522, 560,  524, 556,  524, 558,  524, 558,  524, 562,  524, 556,  524, 558,  524, 584,  500, 1642,  524, 558,  524, 558,  524, 560,  524, 558,  524, 582,  500, 558,  524, 558,  524, 560,  524, 582,  500, 560,  524, 560,  522, 562,  524, 558,  524, 1664,  500, 1668,  500, 1642,  524, 558,  524, 560,  524, 558,  524, 584,  498, 562,  524, 558,  524, 558,  522, 558,  526, 558,  522, 560,  522, 582,  500, 584,  498, 558,  524, 1644,  522, 1642,  522, 560,  524, 6728,  4382, 4414,  522, 1668,  498, 1642,  522, 1644,  524, 1642,  522, 582,  500, 562,  522, 1664,  500, 560,  522, 560,  522, 558,  524, 560,  522, 584,  500, 1644,  524, 1664,  500, 564,  520, 1642,  524, 560,  522, 560,  520, 584,  498, 558,  524, 560,  522, 562,  524, 1666,  498, 1642,  524, 1644,  524, 1640,  524, 1644,  522, 1642,  524, 1644,  524, 1640,  524, 560,  522, 584,  500, 582,  498, 586,  498, 556,  524, 562,  524, 558,  524, 558,  524, 582,  590, 1552,  522, 558,  524, 558,  524, 586,  498, 560,  522, 558,  524, 560,  524, 558,  524, 562,  604, 476,  606, 476,  606, 476,  524, 560,  524, 560,  522, 1642,  522, 1644,  524, 1642,  524, 560,  604, 476,  524, 560,  604, 476,  632, 452,  606, 476,  522, 560,  604, 480,  522, 558,  636, 446,  524, 582,  580, 478,  524, 558,  524, 1644,  606, 1560,  522, 562,  522};  // UNKNOWN 25BE8B6F
uint16_t ON17[295] = {4388, 4410,  528, 1640,  528, 1636,  528, 1640,  528, 1638,  526, 556,  528, 556,  528, 1636,  528, 554,  528, 554,  528, 554,  528, 554,  530, 552,  528, 1640,  528, 1636,  528, 558,  528, 1636,  528, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 556,  528, 1636,  528, 1638,  528, 1640,  528, 1636,  528, 1640,  528, 1634,  530, 1638,  528, 1636,  528, 554,  528, 556,  528, 552,  528, 554,  528, 554,  528, 558,  526, 554,  528, 554,  528, 552,  528, 1638,  528, 554,  528, 554,  528, 556,  528, 554,  528, 552,  528, 554,  528, 554,  528, 554,  530, 554,  526, 554,  528, 554,  528, 556,  530, 552,  528, 554,  528, 1636,  528, 556,  526, 554,  528, 552,  528, 558,  528, 556,  526, 554,  528, 554,  528, 554,  528, 556,  528, 552,  528, 554,  528, 554,  528, 556,  528, 554,  528, 554,  528, 1636,  528, 1638,  528, 6724,  4388, 4408,  528, 1640,  528, 1636,  528, 1640,  528, 1636,  528, 554,  528, 558,  526, 1636,  528, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 1640,  528, 1634,  528, 556,  528, 1638,  528, 554,  528, 552,  528, 554,  528, 554,  528, 554,  528, 556,  528, 1638,  526, 1638,  528, 1638,  528, 1636,  528, 1638,  528, 1636,  526, 1640,  528, 1636,  528, 554,  528, 554,  528, 556,  528, 554,  526, 554,  528, 556,  528, 554,  528, 554,  528, 554,  528, 1638,  530, 554,  528, 554,  528, 558,  528, 556,  526, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 556,  528, 554,  528, 554,  528, 1636,  528, 556,  528, 554,  528, 554,  528, 558,  528, 554,  528, 552,  528, 554,  528, 556,  526, 556,  528, 554,  528, 554,  528, 554,  528, 556,  528, 556,  526, 554,  528, 1634,  528, 1638,  528};  // UNKNOWN 5DDC4ABB
uint16_t ON18[295] = {4390, 4408,  528, 1638,  528, 1636,  530, 1638,  528, 1636,  528, 552,  530, 556,  530, 1636,  528, 554,  528, 554,  528, 554,  528, 554,  528, 552,  530, 1638,  528, 1634,  532, 556,  528, 1638,  528, 554,  528, 554,  528, 554,  528, 552,  530, 552,  528, 556,  528, 1634,  530, 1636,  530, 1638,  528, 1636,  528, 1638,  530, 1636,  528, 1638,  528, 1636,  528, 554,  528, 554,  530, 552,  528, 554,  528, 554,  528, 556,  530, 552,  528, 554,  528, 554,  528, 1638,  528, 554,  528, 554,  528, 558,  528, 1636,  528, 554,  528, 554,  530, 556,  528, 552,  528, 554,  528, 558,  528, 552,  528, 554,  528, 554,  528, 552,  530, 1638,  530, 552,  528, 556,  530, 552,  530, 554,  528, 554,  528, 554,  528, 554,  528, 556,  528, 552,  528, 552,  528, 556,  530, 552,  528, 1636,  528, 554,  528, 556,  528, 1636,  528, 1638,  528, 6722,  4390, 4408,  530, 1638,  528, 1636,  528, 1640,  528, 1636,  528, 554,  528, 556,  528, 1636,  530, 556,  528, 554,  528, 554,  528, 552,  530, 552,  528, 1640,  528, 1636,  528, 556,  528, 1638,  530, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 556,  528, 1636,  528, 1636,  530, 1638,  528, 1634,  530, 1638,  528, 1636,  530, 1638,  528, 1636,  530, 552,  528, 554,  528, 554,  528, 554,  528, 554,  528, 556,  530, 554,  528, 552,  530, 554,  526, 1638,  528, 554,  528, 552,  530, 556,  528, 1636,  528, 552,  530, 552,  528, 556,  530, 550,  530, 552,  530, 556,  528, 554,  528, 554,  528, 554,  530, 552,  528, 1640,  528, 552,  528, 556,  528, 554,  528, 554,  528, 554,  528, 554,  528, 552,  530, 556,  530, 552,  528, 554,  528, 556,  530, 554,  528, 1636,  528, 552,  530, 554,  530, 1634,  530, 1638,  528};  // UNKNOWN 9D54EBBB

uint16_t ON19[295] = {4390, 4408,  528, 1638,  528, 1638,  526, 1640,  528, 1636,  530, 552,  528, 556,  528, 1636,  530, 554,  528, 554,  528, 552,  530, 554,  528, 552,  530, 1638,  528, 1636,  528, 558,  528, 1636,  530, 554,  528, 552,  530, 554,  528, 554,  528, 552,  530, 556,  528, 1636,  528, 1636,  530, 1638,  528, 1636,  528, 1638,  528, 1636,  528, 1638,  528, 1636,  530, 554,  528, 554,  528, 554,  528, 554,  528, 554,  654, 430,  528, 552,  528, 552,  530, 554,  528, 1638,  528, 554,  528, 554,  528, 1638,  530, 552,  528, 554,  528, 554,  528, 558,  528, 552,  528, 552,  528, 556,  530, 552,  528, 552,  530, 552,  528, 554,  528, 1638,  528, 554,  528, 556,  528, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 556,  530, 550,  530, 552,  530, 556,  528, 1636,  528, 552,  528, 554,  528, 558,  528, 1636,  528, 1638,  530, 6722,  4388, 4410,  526, 1638,  528, 1636,  528, 1640,  528, 1636,  528, 554,  528, 556,  528, 1636,  530, 556,  528, 552,  528, 554,  528, 554,  530, 554,  528, 1638,  528, 1636,  530, 556,  528, 1638,  528, 554,  528, 554,  528, 554,  528, 552,  528, 554,  528, 556,  528, 1636,  528, 1638,  528, 1640,  528, 1636,  528, 1638,  528, 1636,  528, 1638,  528, 1636,  528, 554,  528, 554,  528, 554,  526, 554,  528, 554,  528, 556,  528, 554,  528, 554,  528, 554,  528, 1636,  528, 554,  528, 554,  528, 1638,  528, 556,  526, 554,  528, 552,  528, 556,  528, 552,  528, 552,  528, 556,  530, 552,  528, 554,  528, 554,  528, 554,  528, 1640,  528, 552,  528, 556,  528, 554,  528, 554,  528, 554,  528, 552,  530, 554,  528, 556,  528, 552,  528, 552,  530, 556,  530, 1636,  528, 554,  528, 554,  528, 558,  526, 1636,  528, 1638,  528};  // UNKNOWN 6783618D

uint16_t ON20[295] = {4388, 4410,  526, 1640,  528, 1638,  526, 1640,  528, 1636,  528, 556,  526, 558,  526, 1638,  526, 558,  526, 556,  526, 556,  654, 428,  526, 556,  526, 1640,  526, 1638,  526, 558,  526, 1640,  526, 556,  526, 554,  526, 556,  526, 556,  526, 556,  526, 558,  526, 1638,  526, 1640,  526, 1640,  528, 1636,  528, 1638,  528, 1638,  692, 1474,  526, 1638,  528, 554,  526, 556,  526, 556,  526, 556,  526, 554,  528, 558,  526, 556,  526, 556,  526, 558,  524, 1638,  526, 554,  528, 556,  526, 1640,  526, 1638,  526, 558,  526, 556,  526, 554,  526, 558,  526, 556,  526, 556,  526, 556,  526, 556,  526, 556,  526, 558,  526, 1638,  526, 556,  526, 554,  526, 556,  526, 556,  526, 556,  528, 558,  526, 556,  526, 556,  526, 558,  526, 556,  526, 556,  526, 1638,  526, 1640,  528, 554,  526, 556,  526, 1640,  528, 1640,  526, 6724,  4386, 4410,  526, 1640,  528, 1636,  528, 1638,  528, 1638,  526, 556,  526, 558,  526, 1638,  526, 556,  526, 556,  526, 554,  526, 556,  526, 554,  528, 1640,  528, 1638,  526, 558,  526, 1638,  528, 554,  526, 556,  526, 554,  526, 582,  500, 556,  526, 560,  526, 1638,  528, 1638,  528, 1642,  526, 1638,  526, 1640,  526, 1638,  526, 1642,  524, 1638,  526, 556,  526, 556,  526, 556,  526, 556,  526, 554,  526, 558,  526, 556,  526, 556,  526, 556,  526, 1640,  526, 554,  526, 556,  528, 1640,  528, 1638,  526, 558,  526, 556,  526, 554,  528, 556,  526, 556,  526, 554,  528, 556,  526, 554,  526, 556,  526, 558,  528, 1638,  526, 556,  528, 556,  526, 554,  528, 554,  526, 556,  526, 558,  526, 556,  526, 556,  526, 556,  528, 554,  528, 556,  526, 1638,  526, 1640,  528, 554,  526, 556,  526, 1642,  526, 1640,  528};  // UNKNOWN 19F0E2F3
uint16_t ON21[295] = {4390, 4408,  528, 1638,  528, 1636,  528, 1638,  530, 1636,  528, 554,  528, 556,  528, 1636,  528, 554,  528, 554,  530, 554,  528, 554,  528, 554,  530, 1638,  528, 1636,  528, 558,  528, 1638,  528, 554,  528, 554,  528, 552,  528, 554,  528, 554,  528, 556,  530, 1636,  528, 1638,  528, 1638,  528, 1636,  528, 1638,  530, 1634,  528, 1638,  528, 1636,  528, 554,  528, 556,  528, 554,  528, 554,  528, 554,  528, 556,  528, 554,  528, 554,  530, 552,  528, 1638,  528, 554,  528, 1638,  528, 554,  528, 552,  528, 554,  528, 552,  530, 556,  530, 554,  528, 552,  528, 556,  528, 552,  528, 554,  528, 554,  528, 552,  528, 1640,  528, 552,  528, 556,  528, 554,  528, 554,  528, 554,  528, 552,  530, 552,  528, 556,  528, 552,  528, 552,  528, 1638,  530, 552,  530, 554,  528, 552,  528, 558,  528, 1636,  528, 1636,  530, 6724,  4388, 4408,  528, 1638,  528, 1636,  528, 1638,  528, 1636,  530, 554,  528, 556,  528, 1636,  530, 556,  528, 554,  530, 552,  528, 554,  528, 554,  526, 1638,  530, 1636,  530, 556,  528, 1638,  528, 552,  528, 554,  528, 554,  528, 554,  528, 554,  528, 556,  528, 1636,  528, 1638,  528, 1638,  528, 1636,  528, 1640,  528, 1634,  530, 1638,  528, 1636,  528, 554,  528, 554,  530, 554,  528, 554,  528, 556,  526, 556,  528, 554,  528, 554,  528, 554,  528, 1638,  528, 554,  528, 1638,  528, 554,  528, 554,  528, 554,  528, 552,  530, 556,  528, 554,  528, 552,  530, 556,  528, 552,  530, 554,  528, 552,  528, 554,  528, 1640,  528, 552,  528, 558,  528, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 558,  528, 552,  528, 554,  528, 1640,  528, 554,  530, 552,  528, 554,  528, 556,  528, 1636,  528, 1636,  528};  // UNKNOWN E2109FBB

uint16_t ON22[295] = {4388, 4410,  528, 1640,  526, 1636,  528, 1640,  528, 1636,  528, 556,  526, 558,  528, 1638,  526, 556,  528, 554,  526, 554,  528, 556,  526, 556,  526, 1640,  528, 1638,  526, 558,  528, 1640,  526, 556,  526, 554,  528, 556,  526, 556,  526, 558,  524, 558,  526, 1638,  528, 1640,  526, 1640,  526, 1638,  526, 1640,  526, 1638,  526, 1640,  526, 1638,  526, 558,  524, 558,  526, 554,  526, 556,  526, 554,  528, 558,  526, 554,  526, 556,  528, 556,  526, 1638,  528, 554,  528, 1640,  528, 554,  528, 1636,  526, 560,  526, 556,  526, 556,  526, 558,  526, 556,  526, 556,  526, 556,  528, 554,  526, 556,  526, 558,  526, 1636,  528, 558,  524, 556,  526, 556,  526, 556,  526, 556,  526, 558,  634, 448,  526, 556,  526, 558,  524, 556,  526, 1638,  526, 554,  528, 1640,  652, 432,  526, 556,  526, 1640,  528, 1638,  528, 6724,  4386, 4410,  526, 1640,  526, 1638,  526, 1642,  526, 1638,  526, 556,  526, 558,  528, 1636,  528, 556,  526, 556,  526, 556,  528, 554,  526, 554,  528, 1640,  528, 1638,  526, 558,  528, 1640,  526, 558,  524, 554,  528, 554,  526, 556,  528, 556,  524, 558,  526, 1638,  526, 1638,  526, 1642,  526, 1638,  528, 1640,  528, 1638,  526, 1640,  528, 1638,  526, 554,  526, 558,  526, 556,  526, 554,  526, 556,  526, 558,  526, 554,  528, 554,  526, 556,  524, 1640,  526, 558,  524, 1640,  526, 556,  526, 1640,  524, 560,  526, 554,  528, 556,  526, 558,  526, 558,  524, 556,  524, 556,  526, 556,  526, 556,  526, 558,  526, 1638,  526, 556,  526, 556,  526, 556,  526, 556,  698, 382,  528, 558,  526, 554,  528, 556,  524, 558,  526, 556,  526, 1640,  526, 554,  528, 1642,  524, 556,  526, 556,  528, 1640,  528, 1638,  528};  // UNKNOWN 285D4B5A
uint16_t ON23[295] = {4390, 4410,  528, 1640,  528, 1636,  528, 1642,  526, 1636,  528, 554,  526, 558,  528, 1636,  528, 556,  526, 554,  528, 554,  528, 556,  526, 556,  526, 1638,  528, 1638,  528, 556,  528, 1640,  526, 556,  526, 556,  528, 554,  526, 556,  526, 556,  526, 560,  526, 1636,  526, 1638,  528, 1640,  528, 1636,  528, 1640,  528, 1636,  530, 1640,  528, 1636,  528, 558,  524, 556,  526, 556,  526, 556,  526, 554,  528, 558,  528, 556,  526, 556,  526, 554,  528, 1638,  526, 554,  528, 1640,  526, 1638,  528, 554,  528, 556,  528, 554,  528, 554,  528, 556,  528, 556,  526, 554,  528, 554,  528, 556,  526, 556,  526, 558,  528, 1636,  528, 558,  526, 556,  526, 556,  526, 554,  528, 556,  526, 558,  528, 554,  526, 554,  528, 558,  526, 554,  528, 1636,  528, 1640,  526, 554,  528, 554,  528, 554,  528, 1640,  528, 1640,  526, 6726,  4386, 4408,  528, 1638,  528, 1638,  528, 1640,  528, 1638,  526, 554,  528, 558,  526, 1638,  526, 556,  526, 556,  526, 554,  528, 554,  526, 556,  526, 1642,  526, 1636,  528, 558,  528, 1638,  528, 556,  526, 554,  528, 554,  526, 556,  526, 556,  528, 556,  528, 1638,  526, 1640,  526, 1640,  528, 1636,  528, 1638,  528, 1636,  528, 1638,  528, 1636,  528, 554,  528, 558,  526, 554,  528, 554,  526, 554,  528, 556,  530, 554,  526, 556,  526, 554,  528, 1636,  530, 554,  528, 1638,  528, 1638,  526, 556,  528, 556,  528, 554,  526, 556,  526, 556,  526, 556,  526, 554,  528, 554,  528, 556,  526, 556,  526, 558,  528, 1638,  526, 556,  528, 554,  528, 554,  528, 554,  528, 554,  528, 558,  526, 556,  526, 556,  528, 556,  526, 556,  526, 1636,  528, 1640,  528, 554,  526, 554,  528, 554,  528, 1640,  528, 1638,  528};  // UNKNOWN B6078F3B
uint16_t ON24[295] = {4386, 4410,  528, 1638,  528, 1636,  528, 1640,  526, 1638,  526, 554,  528, 558,  528, 1636,  528, 556,  528, 554,  526, 556,  528, 556,  526, 554,  526, 1640,  526, 1638,  526, 558,  526, 1638,  528, 554,  528, 556,  526, 556,  526, 554,  528, 556,  526, 556,  528, 1638,  526, 1638,  528, 1640,  528, 1638,  658, 1508,  528, 1636,  528, 1642,  526, 1636,  528, 556,  526, 556,  656, 424,  528, 554,  526, 556,  526, 558,  528, 554,  526, 556,  526, 554,  528, 1638,  528, 554,  526, 1640,  526, 1638,  526, 1640,  528, 554,  528, 554,  528, 556,  526, 556,  526, 554,  528, 556,  526, 556,  526, 556,  528, 554,  528, 554,  528, 1638,  526, 558,  526, 556,  526, 556,  526, 558,  526, 554,  526, 556,  526, 556,  526, 554,  528, 556,  528, 554,  528, 1640,  526, 1636,  528, 1640,  528, 554,  528, 554,  528, 1636,  528, 1640,  528, 6724,  4386, 4408,  526, 1640,  528, 1636,  528, 1640,  528, 1636,  528, 554,  528, 558,  526, 1638,  526, 556,  528, 556,  526, 556,  528, 554,  528, 556,  526, 1640,  526, 1638,  526, 558,  528, 1640,  526, 556,  526, 554,  528, 556,  526, 554,  528, 556,  526, 558,  526, 1638,  526, 1640,  526, 1640,  528, 1636,  528, 1640,  528, 1638,  526, 1640,  528, 1638,  526, 556,  526, 556,  528, 554,  526, 554,  528, 556,  526, 558,  526, 556,  526, 554,  528, 554,  528, 1638,  528, 554,  526, 1640,  528, 1636,  528, 1638,  528, 556,  526, 556,  526, 556,  526, 556,  526, 554,  528, 556,  526, 554,  528, 558,  526, 554,  528, 556,  526, 1638,  526, 556,  528, 556,  526, 556,  526, 556,  528, 554,  528, 556,  526, 556,  526, 556,  526, 556,  528, 554,  526, 1640,  526, 1638,  526, 1640,  528, 554,  526, 556,  526, 1636,  528, 1638,  528};  // UNKNOWN DBF1F4B1
uint16_t ON25[295] = {4388, 4410,  528, 1640,  528, 1638,  528, 1640,  528, 1638,  526, 554,  528, 556,  528, 1638,  526, 558,  526, 556,  528, 554,  528, 556,  526, 554,  528, 1640,  526, 1636,  528, 558,  526, 1638,  528, 554,  528, 554,  528, 554,  526, 554,  528, 556,  526, 558,  526, 1638,  526, 1638,  528, 1640,  528, 1636,  528, 1640,  528, 1638,  526, 1640,  526, 1638,  528, 554,  528, 556,  526, 556,  526, 556,  526, 556,  526, 560,  526, 556,  528, 554,  528, 554,  526, 1640,  526, 1640,  528, 554,  528, 554,  526, 554,  528, 552,  528, 556,  526, 558,  528, 554,  526, 556,  526, 558,  526, 554,  528, 556,  526, 556,  526, 554,  526, 1642,  526, 554,  526, 558,  526, 556,  526, 554,  528, 554,  528, 554,  528, 556,  526, 558,  526, 554,  526, 1640,  528, 554,  528, 554,  528, 554,  526, 556,  526, 558,  526, 1636,  528, 1638,  528, 6724,  4388, 4410,  528, 1640,  528, 1638,  526, 1640,  528, 1638,  526, 556,  526, 558,  528, 1636,  528, 556,  528, 556,  526, 554,  528, 556,  526, 556,  526, 1640,  528, 1636,  528, 558,  526, 1640,  528, 554,  526, 556,  526, 556,  526, 554,  528, 554,  528, 558,  528, 1636,  528, 1638,  528, 1640,  528, 1638,  526, 1640,  526, 1638,  528, 1640,  526, 1636,  528, 554,  528, 556,  526, 556,  526, 554,  528, 556,  526, 558,  528, 554,  528, 554,  528, 556,  526, 1640,  526, 1640,  528, 556,  526, 554,  528, 554,  528, 556,  526, 554,  528, 558,  526, 554,  526, 556,  528, 558,  526, 554,  528, 554,  528, 556,  526, 556,  526, 1640,  528, 552,  526, 558,  526, 556,  526, 554,  528, 554,  528, 554,  528, 556,  526, 560,  526, 554,  526, 1640,  526, 556,  526, 554,  528, 556,  526, 556,  526, 558,  528, 1638,  528, 1638,  528};  // UNKNOWN 15660573
uint16_t ON26[295] = {4388, 4408,  530, 1640,  528, 1636,  528, 1640,  528, 1636,  528, 554,  528, 556,  528, 1636,  528, 556,  528, 554,  528, 554,  528, 554,  528, 554,  528, 1640,  528, 1638,  526, 558,  528, 1636,  528, 554,  528, 554,  528, 554,  526, 554,  528, 554,  528, 556,  528, 1638,  528, 1638,  528, 1640,  528, 1636,  528, 1638,  530, 1634,  528, 1640,  526, 1636,  528, 554,  528, 556,  528, 554,  528, 554,  528, 554,  530, 556,  528, 554,  528, 554,  528, 554,  528, 1638,  528, 1638,  528, 554,  528, 554,  528, 1636,  528, 556,  528, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 552,  530, 556,  526, 558,  528, 1636,  528, 556,  528, 554,  528, 554,  528, 554,  528, 554,  528, 556,  528, 554,  528, 554,  528, 556,  528, 1636,  528, 554,  526, 554,  528, 1640,  528, 554,  526, 554,  528, 1640,  528, 1638,  528, 6724,  4388, 4408,  528, 1638,  528, 1636,  528, 1638,  528, 1636,  528, 554,  528, 558,  528, 1636,  530, 556,  528, 554,  528, 554,  528, 554,  528, 554,  528, 1638,  528, 1636,  528, 556,  610, 1556,  528, 554,  528, 554,  528, 554,  610, 472,  528, 554,  528, 556,  610, 1554,  610, 1554,  528, 1640,  528, 1636,  670, 1496,  528, 1636,  528, 1640,  528, 1636,  530, 552,  528, 554,  528, 554,  610, 472,  528, 554,  528, 556,  528, 554,  610, 472,  528, 554,  528, 1636,  530, 1638,  608, 474,  528, 554,  528, 1636,  564, 520,  528, 552,  528, 556,  526, 556,  528, 554,  528, 554,  528, 554,  526, 556,  528, 552,  528, 556,  528, 1636,  530, 556,  528, 554,  528, 554,  530, 554,  528, 552,  528, 556,  528, 554,  528, 554,  528, 554,  528, 1636,  528, 554,  530, 552,  528, 1640,  528, 554,  528, 554,  528, 1640,  528, 1636,  528};  // UNKNOWN 76A3AAE5
uint16_t ON27[295] = {4390, 4408,  530, 1638,  530, 1636,  528, 1638,  528, 1636,  530, 552,  530, 556,  528, 1634,  530, 556,  528, 554,  528, 554,  528, 554,  528, 554,  528, 1638,  528, 1636,  528, 556,  528, 1636,  530, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 556,  528, 1636,  528, 1636,  528, 1640,  528, 1634,  530, 1638,  530, 1634,  528, 1638,  528, 1636,  528, 554,  528, 556,  528, 552,  528, 554,  528, 554,  528, 556,  528, 554,  528, 554,  528, 554,  528, 1638,  528, 1638,  530, 554,  528, 1636,  530, 552,  528, 558,  528, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 554,  528, 556,  528, 1636,  528, 554,  528, 554,  528, 554,  528, 552,  530, 554,  528, 556,  528, 554,  528, 554,  528, 554,  528, 1636,  530, 552,  528, 1638,  530, 552,  530, 554,  528, 554,  528, 1638,  530, 1638,  528, 6722,  4388, 4408,  530, 1638,  528, 1634,  528, 1638,  528, 1636,  528, 552,  528, 556,  528, 1636,  528, 554,  528, 554,  528, 554,  612, 470,  528, 556,  526, 1638,  528, 1636,  528, 556,  528, 1638,  528, 554,  528, 554,  608, 472,  528, 554,  528, 554,  608, 476,  638, 1526,  528, 1636,  610, 1558,  610, 1554,  528, 1640,  528, 1634,  608, 1558,  528, 1636,  528, 552,  528, 554,  528, 554,  528, 554,  528, 554,  530, 554,  530, 552,  530, 552,  530, 552,  528, 1638,  528, 1638,  530, 554,  528, 1636,  528, 554,  528, 556,  530, 552,  528, 552,  528, 556,  528, 554,  528, 552,  530, 552,  528, 554,  528, 554,  528, 556,  530, 1634,  528, 556,  528, 554,  528, 554,  528, 554,  528, 554,  528, 556,  528, 554,  528, 554,  528, 556,  528, 1636,  528, 554,  528, 1640,  528, 554,  530, 552,  530, 552,  528, 1638,  530, 1636,  528};  // UNKNOWN 159FEB73
uint16_t ON28[295] = {4388, 4410,  526, 1640,  528, 1638,  526, 1642,  526, 1638,  526, 554,  528, 558,  526, 1638,  528, 556,  526, 556,  526, 556,  526, 556,  526, 556,  526, 1640,  528, 1638,  524, 560,  526, 1640,  526, 556,  526, 556,  526, 556,  526, 554,  528, 556,  526, 562,  522, 1640,  524, 1640,  526, 1640,  528, 1638,  526, 1642,  526, 1638,  526, 1640,  528, 1636,  528, 556,  526, 558,  524, 556,  528, 556,  526, 554,  526, 558,  528, 554,  526, 554,  528, 556,  526, 1638,  526, 1642,  526, 556,  524, 1638,  528, 1640,  526, 556,  526, 556,  526, 558,  524, 556,  526, 556,  526, 554,  526, 556,  526, 558,  526, 556,  526, 556,  526, 1638,  526, 558,  526, 554,  528, 554,  528, 556,  528, 556,  526, 556,  526, 556,  526, 556,  526, 558,  528, 1638,  526, 558,  528, 1636,  526, 1640,  526, 556,  526, 556,  526, 1638,  526, 1638,  528, 6724,  4388, 4410,  526, 1640,  528, 1636,  528, 1640,  526, 1636,  528, 554,  528, 556,  528, 1638,  528, 556,  526, 554,  528, 556,  526, 558,  524, 554,  528, 1642,  526, 1638,  526, 558,  526, 1640,  526, 556,  526, 556,  526, 556,  526, 556,  526, 556,  526, 558,  526, 1638,  526, 1640,  526, 1642,  526, 1638,  526, 1640,  528, 1636,  528, 1640,  526, 1638,  526, 556,  526, 558,  526, 556,  526, 556,  526, 556,  526, 558,  526, 556,  526, 554,  528, 556,  526, 1638,  526, 1642,  526, 554,  528, 1638,  526, 1640,  526, 556,  526, 556,  526, 556,  526, 556,  526, 556,  526, 556,  526, 556,  526, 558,  526, 556,  526, 554,  526, 1638,  526, 556,  526, 556,  526, 556,  524, 560,  526, 556,  526, 556,  526, 556,  526, 556,  526, 556,  528, 1636,  528, 558,  528, 1636,  528, 1640,  526, 554,  528, 554,  526, 1638,  666, 1500,  528};  // UNKNOWN 3C48EC81

uint16_t ON29[295] = {4390, 4408,  528, 1640,  526, 1638,  526, 1640,  528, 1638,  526, 556,  526, 558,  528, 1636,  528, 558,  526, 554,  528, 554,  526, 556,  526, 556,  526, 1640,  526, 1636,  528, 558,  526, 1638,  528, 554,  528, 554,  528, 554,  526, 556,  528, 554,  526, 558,  526, 1636,  528, 1638,  526, 1640,  528, 1636,  528, 1638,  528, 1638,  526, 1640,  528, 1636,  528, 554,  528, 556,  528, 554,  528, 554,  528, 554,  526, 560,  526, 556,  526, 554,  528, 554,  528, 1638,  528, 1638,  528, 1638,  526, 556,  526, 554,  528, 558,  528, 554,  528, 554,  528, 556,  528, 554,  526, 556,  526, 554,  528, 554,  526, 558,  524, 558,  526, 1636,  528, 558,  526, 556,  526, 556,  528, 554,  528, 556,  526, 558,  526, 556,  526, 556,  526, 558,  526, 1638,  526, 1640,  528, 556,  526, 554,  526, 556,  526, 556,  526, 1640,  526, 1640,  528, 6724,  4388, 4408,  526, 1640,  528, 1636,  528, 1640,  658, 1506,  528, 554,  526, 558,  526, 1638,  526, 558,  526, 556,  526, 556,  526, 554,  526, 558,  524, 1640,  528, 1636,  528, 558,  528, 1640,  526, 554,  528, 556,  526, 556,  526, 556,  526, 554,  528, 558,  526, 1638,  528, 1638,  528, 1640,  526, 1636,  528, 1642,  526, 1638,  526, 1638,  528, 1636,  528, 554,  528, 556,  528, 554,  526, 556,  526, 554,  528, 558,  528, 554,  526, 556,  526, 556,  526, 1640,  526, 1640,  526, 1638,  526, 554,  528, 554,  528, 558,  526, 554,  528, 554,  528, 558,  526, 556,  526, 556,  526, 554,  526, 556,  526, 556,  526, 558,  528, 1636,  528, 556,  526, 556,  526, 556,  526, 556,  526, 556,  526, 558,  526, 556,  526, 556,  526, 556,  526, 1636,  528, 1640,  528, 556,  524, 556,  526, 556,  526, 554,  528, 1640,  526, 1640,  528};  // UNKNOWN 92D140F3
uint16_t ON30[295] = {4388, 4410,  528, 1640,  528, 1638,  526, 1640,  526, 1636,  528, 554,  528, 558,  526, 1636,  528, 556,  528, 556,  526, 556,  526, 554,  526, 556,  528, 1640,  528, 1638,  526, 558,  528, 1638,  528, 556,  526, 556,  526, 556,  526, 556,  526, 556,  526, 558,  528, 1638,  526, 1638,  528, 1640,  528, 1638,  526, 1640,  528, 1636,  528, 1640,  526, 1636,  528, 554,  528, 556,  526, 556,  526, 556,  526, 556,  526, 558,  526, 556,  526, 556,  528, 556,  526, 1638,  528, 1640,  528, 1636,  528, 556,  526, 1640,  528, 556,  526, 554,  526, 556,  528, 556,  526, 556,  526, 556,  526, 556,  526, 558,  526, 556,  526, 556,  526, 1636,  528, 556,  526, 556,  526, 556,  526, 558,  528, 556,  526, 556,  526, 556,  526, 556,  526, 558,  526, 1636,  528, 1640,  526, 556,  526, 1642,  526, 556,  526, 556,  526, 1638,  526, 1640,  528, 6724,  4386, 4408,  528, 1640,  526, 1638,  526, 1640,  528, 1638,  526, 554,  526, 558,  528, 1638,  526, 556,  528, 556,  526, 556,  526, 554,  528, 554,  526, 1642,  526, 1638,  528, 558,  526, 1642,  526, 556,  524, 556,  526, 556,  526, 556,  526, 552,  528, 558,  526, 1636,  528, 1638,  528, 1640,  528, 1636,  528, 1640,  526, 1638,  528, 1640,  528, 1636,  528, 554,  528, 556,  528, 554,  528, 556,  526, 554,  528, 558,  528, 554,  526, 556,  526, 556,  526, 1638,  528, 1640,  526, 1638,  526, 554,  528, 1640,  528, 554,  526, 556,  526, 556,  526, 556,  528, 554,  528, 554,  526, 556,  528, 556,  526, 556,  526, 554,  526, 1638,  528, 558,  526, 556,  526, 556,  526, 558,  528, 556,  526, 556,  526, 556,  526, 556,  526, 556,  526, 1638,  526, 1642,  526, 554,  528, 1640,  526, 556,  526, 556,  526, 1636,  528, 1638,  528};  // UNKNOWN 38AD74F3



//define GPIO pin
uint16_t RECV_PIN = 5;//D1
IRsend irsend(4);  // D2 An IR LED is controlled by GPIO pin 4 (D2)
IRrecv irrecv(RECV_PIN);

#define light1 13 //D7
#define light2 15 //D8

#define btn1 14 //D5
#define btn2 12 //D6

boolean slight1, slight2;

decode_results results;

Timer timer;
int authenticate_timer;
int aValue;

char* air = "{\"deviceType\":\"LightingControl\",\"deviceCode\": \"air1\",\"numberOfPorts\": 1,\"lights\": [{\"portId\": 1, \"dimmable\": true, \"typeOfLight\": \"Air\"}]}";
String air_id = "";

const char* device = "{\"deviceType\":\"LightingControl\",\"deviceCode\": \"lt01\",\"numberOfPorts\": 2, \"lights\": [{\"portId\": 1, \"dimmable\": false},{\"portId\": 2, \"dimmable\":  false}]}";
String device_id = "";

const char* ssid     = "SmartHome";
const char* password = "smarthome";

//define mqtt parameters
#define host "192.168.0.100"
#define mqtt_topic_pub "presence"
#define mqtt_topic_sub "presence"
#define mqtt_topic_lwt "lwt"
#define mqtt_user "alice"
#define mqtt_pwd "secret"
const uint16_t mqtt_port = 1883;
const uint16_t http_port = 3000;

int delayTime = 8000;
int light = 0;
int ledValue = 0;

//MQTT client
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//Authenticate timer function
void authenticate_air() {
  Serial.println("authenticating air..");
  client.publish("authenticate", air);
}

void authenticate() {
  Serial.println("Authenticating lightingcontrol...");
  client.publish("authenticate", device);
}

//mqtt callback function
void callback(char* topic, byte* payload, unsigned int length) {
  String rmsg = "";
  //  Serial.println("Message arrived");
  //  Serial.println("Topic: " + (String)topic);
  //  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    rmsg += (char)payload[i];
  }
  Serial.println(rmsg);



  if ((String)topic == "authenticate/air1") {
    timer.stop(authenticate_timer);
    air_id = rmsg;
    String topic = "devices/" + air_id;
    client.subscribe(topic.c_str());
    Serial.println(topic.c_str());
    authenticate_timer = timer.every(1000, authenticate);

  }  else if ((String)topic == "devices/" + air_id) {
    char light = rmsg.charAt(0);
    if (light == '1') {
      String strValue;
      strValue += rmsg.charAt(1) - '0';
      strValue += rmsg.charAt(2) - '0';
      int coValue;
      coValue = strValue.toInt();
      //dieu khien
      char code;
      Serial.print("Server gui xuong la: ");
      Serial.println(coValue);
      switch (coValue) {
        case 17 :
          Serial.println("17");
          irsend.sendSony(0x17, 12, 2);
          break;
        case 18 :
          Serial.println("18");
          irsend.sendSony(0x18, 12, 2);
          break;
        case 0 :
          Serial.println("OFF");
          irsend.sendSony(0x00, 12, 2);
          break;
        case 19 :
          Serial.println("19");
          irsend.sendSony(0x19, 12, 2);
          break;
        case 20 :
          Serial.print("20");
          irsend.sendSony(0x20, 12, 2);
          break;
        case 21 :
          Serial.print("21");
          irsend.sendSony(0x21, 12, 2);
          break;
        case 22 :
          Serial.println("22");
          irsend.sendSony(0x22, 12, 2);
          break;
        case 23 :
          Serial.println("23");
          irsend.sendSony(0x23, 12, 2);
          break;
        case 24 :
          Serial.println("24");
          irsend.sendSony(0x24, 12, 2);
          break;
        case 25 :
          Serial.print("25");
          irsend.sendSony(0x25, 12, 2);
          break;
        case 26 :
          Serial.print("26");
          irsend.sendSony(0x26, 12, 2);
          break;
        case 27 :
          Serial.println("27");
          irsend.sendSony(0x27, 12, 2);
          break;
        case 28 :
          Serial.println("28");
          irsend.sendSony(0x28, 12, 2);
          break;
        case 29 :
          Serial.print("29");
          irsend.sendSony(0x29, 12, 2);
          break;
        case 30 :
          Serial.print("30");
          irsend.sendSony(0x30, 12, 2);
          break;
      }
    }
  } else  if ((String)topic == "authenticate/lt01") {
    timer.stop(authenticate_timer);
    device_id = rmsg;
    String topic = "devices/" + device_id;
    client.subscribe(topic.c_str());
    Serial.println(topic.c_str());
  } else  if ((String)topic == "devices/" + device_id) {
    char light = rmsg.charAt(0);
    switch (light) {
      case '1':
        if ((rmsg.charAt(1) - '0') == 1) {
          Serial.println("turn on 1");
          slight1 = 1;
        } else {
          Serial.println("turn off 1");
          slight1 = 0;
        }
        control(light1, slight1);
        break;
      case '2':
        if ((rmsg.charAt(1) - '0') == 1) {
          Serial.println("turn on 2");
          slight2 = 1;
        } else {
          Serial.println("turn off 2");
          slight2 = 0;
        }
        control(light2, slight2);
        break;
    }
  }
}

// Connect to mqtt broker
void checkMqttConnection() {
  // Loop until we're reconnected
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("air", "lwt", 0, false, "rgb")) {
      Serial.println("connected");
      client.subscribe("authenticate/air1");
      client.subscribe("authenticate/lt01");
      authenticate_timer = timer.every(5000, authenticate_air);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 3 seconds");
    }
  }
}

void readButtons() {
  if (digitalRead(btn1) == HIGH) {
    delay(100);
    while (digitalRead(btn1) == HIGH);
    slight1 = !slight1;
    control(light1, slight1);
  }
  if (digitalRead(btn2) == HIGH) {
    delay(100);
    while (digitalRead(btn2) == HIGH);
    slight2 = !slight2;
    control(light2, slight2);
  }
}

void control(int light, boolean stt) {
  digitalWrite(light, stt);
  int port = (light == light1) ? 1 : 2;
  String topic = "devices/lighting-control/" + device_id + "/" + port;
  char msg[10];
  sprintf(msg, "%d", stt);
  client.publish(topic.c_str(), msg);
}

void setup() {
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);

  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);

  Serial.begin(115200);
  delay(10);

  irrecv.enableIRIn();  // Start the receiver
  irsend.begin();
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);

  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(host, mqtt_port);
  client.setCallback(callback);
  timer.every(3000, checkMqttConnection);
}

void loop() {
  client.loop();
  timer.update();
  readButtons();
}
