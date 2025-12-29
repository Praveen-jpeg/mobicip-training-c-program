#include <stdio.h>

static char daytab[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

/* pointer-based day_of_year */
int day_of_year(int year, int month, int day)
{
    int leap;
    char *p;

    leap = year%4==0 && year%100!=0 || year%400==0;

    for (p = &daytab[leap][1]; p < &daytab[leap][month]; p++)
        day += *p;
    return day;
}

/* pointer-based month_day */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap;
    char *p;

    leap = year%4==0 && year%100!=0 || year%400==0;

    for (p = &daytab[leap][1]; yearday > *p; p++)
        yearday -= *p;

    *pmonth = p - &daytab[leap][0];
    *pday = yearday;
    return 0;
}

int main(void)
{
    int m, d;
    printf("Day of year: %d\n", day_of_year(2024, 3, 1));
    month_day(2024, 60, &m, &d);
    printf("Month=%d Day=%d\n", m, d);
    return 0;
}
