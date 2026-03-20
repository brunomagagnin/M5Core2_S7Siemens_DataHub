#ifndef DBADRESS_H
#define DBADRESS_H
#include "Config.h"

/*
struct plcBoolVar {
    String nome;      // Nome variável
    int dbNumber;     // Numero da DB
    int byteOffset;   // Endereço na DB
    int bitOffset;    // Endereço do bit
    bool valorAtual;  // Valor inicial

struct plcAnalogVar {
    String nome;      // Nome variável
    int dbNumber;     // Numero da DB
    int offset;       // Endereço na DB
    float valorAtual; // Valor inicial
};
*/

/***************************************************
 *         DECLARAÇÃO DAS VARIÁVEIS
 ***************************************************/

//VARIÁVEIS BOOLEANAS
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
plcAnalogVar listOfAnalogs[MAX_NUMBER_ANALOG] = {
    {"Sensor_1", 1, 0, 0.0},
    {"Sensor_2", 1, 2, 0.0},
    {"Sensor_3", 1, 4, 0.0},
    {"Sensor_4", 1, 6, 0.0},
    {"Sensor_5", 1, 8, 0.0}
};


#endif