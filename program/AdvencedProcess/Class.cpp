//
// Created by lsh on 20. 4. 2..
//

#include "Class.h"

long long int MonthToDay(int year, int month)
{
    switch (month) {
        case 1:
            return 0;
        case 2:
            return 31;
        case 3:
        {
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) return MonthToDay(year, 2) + 29;
            else return MonthToDay(year, 2) + 28;
        }
        case 4:
            return 31 + MonthToDay(year, 3);
        case 5:
            return 30 + MonthToDay(year, 4);
        case 6:
            return 31 + MonthToDay(year, 5);
        case 7:
            return 30 + MonthToDay(year, 6);
        case 8:
            return 31 + MonthToDay(year, 7);
        case 9:
            return 31 + MonthToDay(year, 8);
        case 10:
            return 30 + MonthToDay(year, 9);
        case 11:
            return 31 + MonthToDay(year, 10);
        case 12:
            return 30 + MonthToDay(year, 11);
        default:
            return 0;
    }
}