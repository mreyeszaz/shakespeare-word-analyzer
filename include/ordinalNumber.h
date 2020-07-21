#ifndef ORDINALNUMBER_H
#define ORDINALNUMBER_H

#include <string>
#include <vector>


std::string ordinal(int n){
    int lastTwoDigits = n % 100;
    int lastDigit = n % 10;

    std::string suffix;
    switch(lastDigit){
        case 1:
            suffix = "st";
            break;
        case 2:
            suffix = "nd";
            break;
        case 3:
            suffix = "rd";
            break;
        default:
            suffix = "th";
            break;
    }

    if((11 <= lastTwoDigits) && (lastTwoDigits <= 13))
        suffix = "th";

    return std::to_string(n) + suffix;


}
#endif // ORDINALNUMBER_H
