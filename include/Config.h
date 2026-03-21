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

/***************************************************
 *         LIMITE DE VARIÁVEIS MONITORADAS 
 ***************************************************/
#define MAX_NUMBER_BOOL 10
#define MAX_NUMBER_ANALOG 5 

/***************************************************
 *         ESTRUTURAS UTILIZADAS PARA DADOS
 ***************************************************/
// Struct para variáveis booleanas
struct plcBoolVar {
    String nome;      // Nome variável
    int dbNumber;     // Numero da DB
    int byteOffset;   // Endereço na DB
    int bitOffset;    // Endereço do bit
    bool valorAtual;  // Valor
};

// Struct para variáveis analógicas (Inteiros e Reais)
struct plcAnalogVar {
    String nome;      // Nome variável
    int dbNumber;     // Numero da DB
    int offset;       // Endereço na DB
    float valorAtual; // Valor
};

// Declaração dos arrays
extern plcBoolVar listaBool[MAX_NUMBER_BOOL];
extern plcAnalogVar listaAnalog[MAX_NUMBER_ANALOG];


