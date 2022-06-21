#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30

 int findSubString (char* str, char* substr);
 unsigned int bankAccountNumber(char * bankAccountNumber);
 
 int main() {
	char str[SIZE], sub[SIZE];
	unsigned int return_number;
	int return_value;
	char n;
	
	printf("Write 1 for function 1 or 2 for function 2\n");
	scanf("%c", &n);
	if ( n == '1')	{
	
		printf("Write a string\n");
		scanf("%s",str);
		printf("Write a substring\n");
		scanf("%s",sub);
		if (strlen(str)<strlen(sub))
		{
			printf("Error: Substring is larger than string");
			return -1;
		}
		return_value = findSubString(str,sub);
		if(return_value == -1)	{
			printf("Substring is not in string\n");
			return -1;
		}
	
		printf("Return: %i\n",return_value);
		return return_value;
	
	} else if (n == '2')	{
		printf("Write a 10 digits bank account:\n");
		scanf("%s",str);
		if (strlen(str)!=10)
		{
			printf("Wrong number of elements in the bank account number");
			return -1;
		}
		return_number = bankAccountNumber(str);
		printf("return %u\n",return_number);
		return 0;
	} else {
		printf("Unknown function number\n");
		return 0;
	}
}