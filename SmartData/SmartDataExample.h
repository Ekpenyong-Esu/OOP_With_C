//
// Created by mahon on 2/8/2024.
//

#ifndef SMARTDATA_SMARTDATAEXAMPLE_H
#define SMARTDATA_SMARTDATAEXAMPLE_H

struct AlarmManager;
struct PatientDataClass;
struct SmartColor;
struct SmartDataClient;
struct SmartInt;

typedef enum ErrorCodeType {
    NO_ERRORS,
    BELOW_RANGE,
    ABOVE_RANGE,
    INCONSISTENT_VALUE,
    ILLEGAL_USE_OF_NULL_PTR,
    INDEX_OUT_OF_RANGE
} ErrorCodeType;

typedef enum ColorType {
    BLACK,
    BROWN,
    RED,
    PINK,
    BLUE,
    GREEN,
    YELLOW,
    WHITE
} ColorType;

#endif //SMARTDATA_SMARTDATAEXAMPLE_H
