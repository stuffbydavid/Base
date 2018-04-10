#include "util/datefunc.hpp"


string Base::getDateTimeNow()
{
    time_t now = time(0);
    struct tm *tstruct = localtime(&now);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tstruct);
    return buf;
}