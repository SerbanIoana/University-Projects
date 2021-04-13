
#include <stdio.h>
#include <string.h>

void get_birth_date(char* date, int *day, int *month, int *year)
{	
	const int decade = 10, century = 100, millennia = 1000;
	*day = (date[0] - '0') * decade + (date[1] - '0');
	*month = (date[3] - '0') * decade + (date[4] - '0');
	*year = (date[6] - '0') * millennia + (date[7] - '0') * century + (date[8] - '0') * decade + (date[9] - '0');
}

int is_leap(int year)
{
	/*
		a given year is a leap year if it is divisible by 400, or only by 4
	*/

	const int leap_check = 400;
	if (year % leap_check == 0)
		return 1;
	return (year % 4 == 0 && year % 100 != 0);
}

int days_of_month(int month)
{
	/*
		returns the number of days of a given month accordingly
		february: 28 days
		april, june, september, november: 30 days
		the rest: 31 days
	*/

	const int february = 2, april = 4, june = 6, september = 9, november = 11;
	if (month == february)
		return 28;
	if (month == april || month == june || month == september || month == november)
		return 30;
	return 31;
}

int number_of_days(int current_day,int current_month,int current_year)
{
	/*
		returns the number of days that have passed since the beginning od the current_year
	*/

	int days = current_day;
	if (current_month > 2 && is_leap(current_year) == 1)
		days += 1;
	for (int month = 1; month < current_month; month++)
		days += days_of_month(current_month);
	return days;
}

int compute_age(int birth_day, int birth_month, int birth_year, int current_day, int current_month, int current_year)
{
	int age_in_days = number_of_days(current_day, current_month, current_year);

	for (int year = birth_year; year < current_year; year++)
	{
		age_in_days = age_in_days + 365;
		if (is_leap(year) == 1)
			age_in_days += 1;
	}
	return age_in_days - number_of_days(birth_day, birth_month, birth_year);
}

void process_date(char date[11], char persons[100][11], int *number_persons)
{
	const int days_limit = 10000;
	const int min_days = 1, max_days = 31, min_months = 1, max_months = 12, max_year = 2020;
	int day = 0, month = 0, year = 0, age_in_days;
	int current_day = 11, current_month = 3, current_year = 2020;
	//int number_persons = 0;

	get_birth_date(date, &day, &month, &year);
	if (day < min_days || day > max_days || month < min_months || month > max_months || year > max_year)
		printf("Incorrect data");
	else
	{
		age_in_days = compute_age(day, month, year, current_day, current_month, current_year);
		if (age_in_days < days_limit)
		{
			strcpy(persons[*number_persons], date);
			*number_persons++;
		}
			
	}
	//return number_persons;
}

void start_run(char persons[100][11], int *number_persons)
{	
	char date[11];

	//const int days_limit = 10000;
	//const int min_days = 1, max_days = 31, min_months = 1, max_months = 12, max_year = 2020;
	//int number_persons;
	//char persons[100][11];
	//int number_persons = 0;
	//int day = 0, month = 0, year = 0, age_in_days;
	//int current_day = 11, current_month = 3, current_year = 2020;

	printf("date: ");
	while (scanf("%s", date))
	{
		if (strcmp(date, "exit") == 0)
			break;
		else
		{
			process_date(date, persons, number_persons);
		}
		printf("\ndate: ");
	}
}

int main()
{
	/*
		For a list of birth dates, determine the persons who have not lived more than 10.000 days.
	*/

	char persons[100][11];
	int number_persons = 0;
	
	start_run(persons, &number_persons);



	if (number_persons != 0)
		for(int i=0; i<number_persons; i++)
			printf("%s\n", persons[i]);

}
