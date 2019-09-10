#include <stdio.h>

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

char *moth_name(int n) {
  static char *name[] = {
    "Illegal moth", "January", "February", "March", "April",
    "May", "June", "July", "August", "September", "October",
    "November", "December"
  };

  return (n < 1 || n > 12) ? name[0] : name[n];
}

/* month_day function's prototype*/
void month_day(int year, int yearday, int *pmonth, int *pday);


int main(int argc, char **argv) {
  // Place your magic here
  if (argc < 3) {
    printf("You need to send the year and the year day to calculete the month\n");
    printf("How to execute option one: ./month_day <year> <yearday>\n");
    return 1;
  }
  int year, yearday, month, day;
  year = atoi(argv[1]);
  yearday = atoi(argv[2]);
  month_day(year, yearday, &month, &day);
  char *mon = moth_name(month);
	if(day<10){
	  printf("%s 0%d, %d \n", mon, day, year);
	  return 0;
	}
	else{
	  printf("%s 0%d, %d \n", mon, day, year);
	  return 0;
	}
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
  int i, leap;
  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
