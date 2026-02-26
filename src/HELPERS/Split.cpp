#include <HELPERS/Split.h>

int startIndex = 0;
int endIndex = 0;
int currentPartIndex = 0;

namespace getPart
{
    String ofString(String str, char delimiter, int partIndex)
    {
        startIndex = 0;
        endIndex = 0;
        currentPartIndex = 0;

        while (currentPartIndex < partIndex && endIndex != -1)
        {
            endIndex = str.indexOf(delimiter, startIndex);

            if (currentPartIndex == partIndex - 1)
            {
                // Retorna a substring desejada
                if (endIndex == -1)
                {
                    return str.substring(startIndex);
                }
                else
                {
                    return str.substring(startIndex, endIndex);
                }
            }

            // Move para a próxima parte
            startIndex = endIndex + 1;
            currentPartIndex++;
        }

        // Se o índice for maior que o número de partes, retorna uma string vazia
        return "";
    }
}