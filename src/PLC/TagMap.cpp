#include "PLC/TagMap.h"

namespace PlcTags {

const plcBoolVar listOfBool[MAX_NUMBER_BOOL] = {
    {"Motor_1_ligado", 2, 0, 0},
    {"Motor_2_ligado", 2, 0, 1},
    {"Motor_3_ligado", 2, 0, 2},
    {"Motor_4_ligado", 2, 0, 3},
    {"Motor_5_ligado", 2, 0, 4},
    {"Motor_6_ligado", 2, 0, 5},
    {"Motor_7_ligado", 2, 0, 6},
    {"Motor_8_ligado", 2, 0, 7},
};

// Os offsets 0, 2, 4, 6 e 8 foram preservados: representam INT (2 bytes).
// Se as tags do PLC forem REAL, cada uma precisara de 4 bytes e offsets adequados.
const plcAnalogVar listOfAnalogs[MAX_NUMBER_ANALOG] = {
    {"Sensor_1", 1, 0, AnalogType::Int16},
    {"Sensor_2", 1, 2, AnalogType::Int16},
    {"Sensor_3", 1, 4, AnalogType::Int16},
    {"Sensor_4", 1, 6, AnalogType::Int16},
    {"Sensor_5", 1, 8, AnalogType::Int16},
};

}  // namespace PlcTags
