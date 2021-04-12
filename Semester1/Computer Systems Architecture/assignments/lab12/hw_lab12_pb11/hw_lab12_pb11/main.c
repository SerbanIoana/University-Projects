#include <stdio.h>
#include <string.h>

//Multiple numbers in base 2 are read from the keyboard. Display these numbers in the base 16.

extern int conversie(char n[], int len);	

int main()
{
	int nr10;
	char n[30] = { 0 };

	printf("n = ");
	scanf("%s", n);

	while (n[0] != '$')
	{
		nr10 = conversie(n, strlen(n));
		printf("%x\n", nr10);

		printf("n = ");
		scanf("%s", &n);
	}

	return 0;
}