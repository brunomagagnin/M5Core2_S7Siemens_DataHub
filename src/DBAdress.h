#ifndef DBADRESS_H
#define DBADRESS_H
#include "Config.h"
#include "S7/S7Types/S7Type.h"

S7Type* S7DataBool[MAX_NUMBER_BOOL];
S7Type* S7DataAnalog[MAX_NUMBER_ANALOG];


/***************************************************
 *         DECLARAÇÃO DAS VARIÁVEIS
 ***************************************************/

//VARIÁVEIS BOOLEANAS  
//Nome da variável, número da DB, Endereço na DB, Endereço do bit, Valor inicial
plcBoolVar listOfBool[MAX_NUMBER_BOOL] = {
    {"Motor_1_ligado", 2, 0, 0, false},
    {"Motor_2_ligado", 2, 0, 1, false},
    {"Motor_3_ligado", 2, 0, 2, false},
    {"Motor_4_ligado", 2, 0, 3, false},
    {"Motor_5_ligado", 2, 0, 4, false},
    {"Motor_6_ligado", 2, 0, 5, false},
    {"Motor_7_ligado", 2, 0, 6, false},
    {"Motor_8_ligado", 2, 0, 7, false},
};

//VARIAVEIS ANALÓGICAS
// Nome da variável, número da DB, Endereço na DB e Valor inicial
plcAnalogVar listOfAnalogs[MAX_NUMBER_ANALOG] = {
    {"Sensor_1", 1, 0, 0.0},
    {"Sensor_2", 1, 2, 0.0},
    {"Sensor_3", 1, 4, 0.0},
    {"Sensor_4", 1, 6, 0.0},
    {"Sensor_5", 1, 8, 0.0}
};


#endif