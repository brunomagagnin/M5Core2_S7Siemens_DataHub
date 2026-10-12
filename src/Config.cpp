#include "Config.h"

// Endereço do CLP
IPAddress PLC(192, 168, 0, 12);

// Configuração de rede
IPAddress Gateway(192, 168, 0, 1);
IPAddress Subnet(255, 255, 255, 0);

// Credenciais Wi-Fi
char ssid[] = "SEU_WIFI";
char pass[] = "SUA_SENHA";


/*
Adaptador de Rede sem Fio Wi-Fi:

   Sufixo DNS específico de conexão. . . . . . :
   Endereço IPv6 de link local . . . . . . . . : fe80::2a8e:bcf0:b339:3f1f%15
   Endereço IPv4. . . . . . . .  . . . . . . . : 192.168.0.107
   Máscara de Sub-rede . . . . . . . . . . . . : 255.255.255.0
   Gateway Padrão. . . . . . . . . . . . . . . : 192.168.0.1
*/