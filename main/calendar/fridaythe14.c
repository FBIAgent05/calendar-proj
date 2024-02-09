#include <stdio.h>

#define TRUE 1
#define FALSE 0

int onlyDays (int year, int month, int day);
int leapYear (int year);
int fridayOnlydays (int onlydays);
void printDate (int onlydays);

int main(void)
{
    int lo_year, lo_month, lo_day;
    int hi_year, hi_month, hi_day;
    int lo_total, hi_total;
    int fri_array[1000000];
    int fri14_array[1000000];
    int fri_count = 0;
    int fri14_count = 0;
    int tmp;


    printf("This program generates Friday the 14th dates\n");
    printf("depending on the ranges given by the human\n\n");

    printf("Enter lower range date (yyyy-mm-dd): ");
    scanf("%d-%d-%d", &lo_year, &lo_month, &lo_day);

    printf("Enter upper range date (yyyy-mm-dd): ");
    scanf("%d-%d-%d", &hi_year, &hi_month, &hi_day);

    lo_total = onlyDays(lo_year, lo_month, lo_day);
    hi_total = onlyDays(hi_year, hi_month, hi_day);

    for (int i = lo_total; i < hi_total; i++)
    {
        if (i % 7 == 5)
        {
            fri_array[fri_count] = i; //stores dates that are friday
            fri_count++;
        }
    }


    for (int i = 0; i < fri_count; i++)
    {
        tmp = fri_array[i];

        if (fridayOnlydays(tmp) == 14)
        {
            fri14_array[fri14_count] = fri_array[i];
            fri14_count++;
        }
    }

    printf("\n");

    for (int i = 0; i < fri14_count; i++)   // print friday 14th dates
    {
        tmp = fri14_array[i];
        printf("%d:\t", i + 1); // i counts the number of friday 14 dates
        printDate(tmp);
        printf("\n");
    }

    printf("\nThere are %d Friday the 14ths between ", fri14_count);
    printDate(lo_total); 
    printf(" and ");
    printDate(hi_total);
    printf("\n");

    return 0;
}


int onlyDays (int year, int month, int day)
{
    int real_year = 0;
    int comp_year = 0;
    int cent = 0, leap_cent = 0, noleap_cent = 0;
    int month_array[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
    int month_total = 0;
    int days_total = 0;

    if (leapYear(year) == TRUE)
    {
        month_array[2] = 29;
    }

    real_year = year - 1;
    comp_year = year - 1;

    cent = comp_year / 100;
    leap_cent = cent / 4;
    noleap_cent = cent - leap_cent;

    comp_year *= 365.25;
    comp_year -= noleap_cent;


    for (int i = 0; i < month; i++)
    {
        month_total += month_array[i];
    }

    days_total = comp_year + month_total + day;

    return days_total;
}


int leapYear (int year)
{
    if (year % 100 == 0 && !(year % 4 == 0 || year % 400 == 0))
    {
        return FALSE;
    }

    else if (year % 4 == 0 || year % 400 == 0)
    {
        return TRUE;
    }

    else
    {
        return FALSE;
    }
}


int fridayOnlydays (int onlydays)
{
    int year = 0, month = 0, day = 0;   //almost all values reset to zero as previous values interfere// i counts the number of friday 14 dates
    int comp_year = 0, only_year = 0;
    int true_total = 0;
    int month_diff = 0;
    int month_add = 0;
    int tmp_month_add = 0;
    int month_arr_count = 0;
    int cent, leap_cent, no_leap_cent;
    int month_array[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
    int arr_size = sizeof(month_array) / sizeof(month_array[0]);

    comp_year = onlydays / 365.25;
    cent = comp_year / 100;
    leap_cent = cent / 4;
    no_leap_cent = cent - leap_cent;

    true_total = onlydays + no_leap_cent;
    year = true_total / 365.25;
    only_year = year * 365.25;
    month_diff = true_total - only_year;
    
    if (leapYear(year + 1) == TRUE) // years start at zero
    {
        month_array[2] = 29;
    }

    // largest less than machine
    while (month_add < month_diff)
    {
        tmp_month_add += month_array[month_arr_count];

        if (tmp_month_add > month_diff)
        {
            break;
        }

        month_add = tmp_month_add;
        month_arr_count++;
        month++;
    }

    year += 1;
    day = month_diff - month_add;


    if (month_diff == month_add)
    {
        month -= 1;
        day = month_array[month];
    }

    return day;
}


void printDate (int onlydays)
{
    int year = 0, month = 0, day = 0;
    int comp_year = 0, only_year;
    int true_total;
    int month_diff = 0;
    int month_add = 0;
    int month_add_tmp = 0;
    int month_array_count = 0;
    int cent, leap_cent, noleap_cent;
    int month_array[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    comp_year = onlydays / 365.25;
    cent = comp_year / 100;
    leap_cent = cent / 4;
    noleap_cent = cent - leap_cent;

    true_total = onlydays + noleap_cent;

    year = true_total / 365.25;
    only_year = year * 365.25;
    month_diff = true_total - only_year;


    if (leapYear(year + 1) == TRUE)
    {
        month_array[2] = 29;
    }

    while (month_add < month_diff)
    {
        month_add_tmp += month_array[month_array_count];

        if (month_add_tmp > month_diff)
        {
            break;
        }

        month_add = month_add_tmp;
        month_array_count++;
        month++;
    }

    year += 1;                      // years start with 1
    day = month_diff - month_add;

    if (month_add == month_diff)
    {
        month -= 1;                 // allows days to start in 1, not zero
        day = month_array[month];
    }

    if (month < 0)  //some weird but that monthks become negative when last day of year
    {
        month = 12;
        day = month_array[month];
    }

    printf("%.4d-%.2d-%.2d", year, month, day);
}
    
