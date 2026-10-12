#include "HELPERS/Split.h"

namespace getPart {
String ofString(const String& str, char delimiter, int partIndex) {
    if (partIndex < 0) return "";

    int start = 0;
    for (int index = 0; index < partIndex; ++index) {
        const int separator = str.indexOf(delimiter, start);
        if (separator < 0) return "";
        start = separator + 1;
    }

    const int end = str.indexOf(delimiter, start);
    return end < 0 ? str.substring(start) : str.substring(start, end);
}
}  // namespace getPart
