#include <stdio.h>

#define TRUE    1
#define FALSE   0
#define RED     "\033[38:5:88m"
#define SILVER  "\033[38:5:8m"
#define ORANGE  "\033[38:5:202m"
#define BLUE    "\033[38:5:21m"
#define GREEN   "\033[38:5:120m"
#define GOLD    "\033[38:5:11m"
#define BROWN   "\033[38:5:223m"
#define RESET   "\033[0m"

int leapYear(int year);
int converttoDays(int year, int month, int day);
int whatDay(int alldays);
void Calendar(int year, int month, int day, int n_day);

int main(void)
{
    int year, month, day;
    int totaldays, n_day;

    printf("Enter date (yyyy-mm-dd): ");

    // scanf returns an integer from which how many successful inputs were entered, in this case there are 3
    if (scanf("%d-%d-%d", &year, &month, &day) != 3)
    {
        fprintf(stderr, "Insufficient input\n");
        return 1;
    }

    totaldays = converttoDays(year, month, day);
    n_day = whatDay(totaldays);

    Calendar(year, month, day, n_day);

    return 0;
}

int leapYear(int year)
{
    // year is leap year if it is not divisible by 100 and divisible by 4, or divisible by 400
    if ((!(year % 100 == 0) && (year % 4 == 0)) || year % 400 == 0)
        return TRUE;
    else
        return FALSE;
}

int converttoDays(int year, int month, int day)
{
    int real_year = 0;
    int comp_year = 0;
    int totaldays_month = 0;
    int month_arr[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
    int cent = 0, leapcent = 0, noleapcent = 0;

    // since years don't start with zero, year is subracted into one;
    real_year = year - 1;

    // computes how many centuries since real_year
    cent = real_year / 100;

    // century years that are leap years occur every 400 years
    leapcent = cent / 4;
    noleapcent = cent - leapcent;

    // 365.25 days every year
    comp_year = 365.25 * real_year;

    // days are subtracted depending on the amount of non-leap year centurial years
    comp_year -= noleapcent;

    // if year is leap year, set days in February to 29
    if (leapYear(year) == TRUE)
        month_arr[2] = 29;
    
    // bugfix when months overflow above 12
    if (month > 12)
        month = 12;

    // add all days depending on month. If user entered March as month, it would total up to 59 (if February is not a leap year)
    for (int i = 0; i < month; i++)
        totaldays_month += month_arr[i];

    // total days
    return comp_year + totaldays_month + day;
}

/*
when date is converted into total days, its remainder when its divided to 7 gives the day of the week.
Example: 0 is Sunday, 1 is Monday, 2 is Tuesday, and respectively the rest.
*/

int whatDay(int alldays)
{
    return alldays % 7;
}

void Calendar(int year, int month, int day, int n_day)
{
    int month_arr[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char *days_of_week[] ={"Sun 日", "Mon 月", "Tue 火", "Wed 水 ", "Thu 木", "Fri 金", "Sat 土"};
    size_t s_days_of_week = sizeof(days_of_week) / sizeof(days_of_week[0]);

    if (month > 12)
        month = 12;

    else if (month < 1)
        month = 1;

    if (leapYear(year) == TRUE)
        month_arr[2] = 29;

    printf("\n                 %d年   ", year);


    if (month == 1)
        printf("January");

    else if (month == 2)
        printf("February");

    else if (month == 3)
        printf("March");

    else if (month == 4)
        printf("April");

    else if (month == 5)
        printf("May");

    else if (month == 6)
        printf("June");

    else if (month == 7)
        printf("July");

    else if (month == 8)
        printf("August");

    else if (month == 9)
        printf("September");

    else if (month == 10)
        printf("October");

    else if (month == 11)
        printf("November");

    else if (month == 12)
        printf("December");

    printf("\n\n");

    for (int i = 0; i < s_days_of_week; i++)
    {    
        if (i == 0 && i == n_day)
            printf("%s%s%s\t", RED, days_of_week[i], RESET);

        else if (i == 1 && i == n_day)
            printf("%s%s%s\t", SILVER, days_of_week[i], RESET);

        else if (i == 2 && i == n_day)
            printf("%s%s%s\t", ORANGE, days_of_week[i], RESET);

        else if (i == 3 && i == n_day)
            printf("%s%s%s\t", BLUE, days_of_week[i], RESET);

        else if (i == 4 && i == n_day)
            printf("%s%s%s\t", GREEN, days_of_week[i], RESET);

        else if (i == 5 && i == n_day)
            printf("%s%s%s\t", GOLD, days_of_week[i], RESET);

        else if (i == 6 && i == n_day)
            printf("%s%s%s\t", BROWN, days_of_week[i], RESET);


        else
            printf("%s\t", days_of_week[i]);
    }
    printf("\n");
    

    for (int i = 1, j = 1; j <= month_arr[month]; i++, j++)
    {
        // executes once, unless the mon, tue, wed line gets printed multiple times
        if (i == 1)
        {
            // manages the spaces on the first parts of the calendar. Depends on the first day of the month.
            for (int k = 0, n = whatDay(converttoDays(year, month, 1)); k < n; k++)
            {
                printf("\t");
                i++;
            }
        }

        // highlights the specified day entered by the user
        if (j == day)
            printf("\033[100m%d\t\033[0m", j);
        else
            printf("%d\t", j);


        // prints new line
        if (i % 7 == 0)
            printf("\n");
    }

    printf("\n");
}
