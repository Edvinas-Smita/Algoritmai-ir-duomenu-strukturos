//Autoriai: Šmita Edvinas ir Šaulys Teodoras - VU MIF PS 1k. 2gr. 2pogr. 2017-2018m.m.
#include <stdio.h>
#include "LongIntegerHeader.h"

int main()
{
	char ch;
	verylong a, b, sum, diff, mul, quot, rem, exp;
	long long regularLongLong;
	int treatRegularAsSigned;
	printf("Enter two integers to be converted to verylong format!:\n");
	if(readToStruct(stdin, &a))
	{
		printf("Something went wrong with reading the value! Terminating...\n");
		return -1;
	}
	if(readToStruct(stdin, &b))
	{
		printf("Something went wrong with reading the value! Terminating...\n");
		return -1;
	}
	
	while(1)
	{
		printf("Arithmetic:\n\t'+' Sum,\n\t'-' Difference,\n\t'*' Multiplication,\n\t'/' Division with remainder,\n\t'^' Exponentiation;\nOther:\n\t'=' Signed compare between verylong values,\n\t'L' Compare verylong with long long,\n\t'a' / 'b' Print entered values,\n\t'R' Reenter integers to convert to verylong,\n\t'0' Exit;\n");
		ch = getc(stdin);
		if (ch == 0xFF)
		{
			return 0;
		}

		if (ch!=0xA && ch!=0xD)
		{
			while(getc(stdin)!=0xA);
		}
		while (ch == 0xA)
		{
			ch = getc(stdin);
		}
		switch(ch)
		{
			case '+':
			{
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("Sum: ");
				if (longSum(a, b, &sum))
				{
					printf("Something went wrong while calculating! Terminating...\n");
					return 1;
				}
				if (printVerylong(stdout, sum))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return 1;
				}
				freeStruct(&sum);
				break;
			}
			case '-':
			{
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("Diff: ");
				if (longDiff(a, b, &diff))
				{
					printf("Something went wrong while calculating! Terminating...\n");
					return 1;
				}
				if (printVerylong(stdout, diff))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return 1;
				}
				freeStruct(&diff);
				break;
			}
			case '*':
			{
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("Product: ");
				if (longMul(a, b, &mul))
				{
					printf("Something went wrong while calculating! Terminating...\n");
					return 1;
				}
				if (printVerylong(stdout, mul))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return 1;
				}
				freeStruct(&mul);
				break;
			}
			case '/':
			{
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				if (longDiv(a, b, &quot, &rem))
				{
					printf("Something went wrong while calculating! Terminating...\n");
					return 1;
				}
				
				printf("Quotient: ");
				if (printVerylong(stdout, quot))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return 1;
				}
				printf("Remainder: ");
				if (printVerylong(stdout, rem))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return 1;
				}
				
				freeStruct(&quot);
				freeStruct(&rem);
				break;
			}
			case '^':
			{
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("Result: ");
				if (longExp(a, b, &exp))
				{
					printf("Something went wrong while calculating! Terminating...\n");
					return 1;
				}
				if (printVerylong(stdout, exp))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return 1;
				}
				freeStruct(&exp);
				break;
			}
			
			case '=':
			{
				if (verylongA_EQUALS_verylongB_Bool(a, b))
				{
					printf("a == b\n");
				}
				if (verylongA_IS_GREATER_THAN_verylongB_Bool(a, b))
				{
					printf("a > b\n");
				}
				if (verylongA_IS_LESS_THAN_verylongB_Bool(a, b))
				{
					printf("a < b\n");
				}
				break;
			}
			case 'L':
			{
				printf("Enter 0 to treat the following input as unsigned and 1 for signed:\n");
				scanf("%d", &treatRegularAsSigned);
				if (treatRegularAsSigned)
				{
					printf("Enter a signed long long to compare to:\n");
					printf("(Min: %lld;		Max: %lld)\n", (-1LLU >> 1) + 1, -1LLU >> 1);
					scanf("%lld", &regularLongLong);
				}
				else
				{
					printf("Enter an unsigned long long to compare to:\n");
					printf("(Min: 0;	Max: %llu)\n", -1LLU);
					scanf("%llu", &regularLongLong);
				}
				if (verylongA_EQUALS_longlongB_Bool(a, regularLongLong, treatRegularAsSigned))
				{
					printf("a == b\n");
				}
				if (verylongA_IS_GREATER_THAN_longlongB_Bool(a, regularLongLong, treatRegularAsSigned))
				{
					printf("a > b\n");
				}
				if (verylongA_IS_LESS_THAN_longlongB_Bool(a, regularLongLong, treatRegularAsSigned))
				{
					printf("a < b\n");
				}
				break;
			}
			
			case 'R':
			{
				freeStruct(&a);
				freeStruct(&b);
				if(readToStruct(stdin, &a))
				{
					return -1;
				}
				if(readToStruct(stdin, &b))
				{
					return -1;
				}
				break;
			}
			
			case 'a':
			{
				if (printVerylong(stdout, a))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return -1;
				}
				break;
			}
			case 'b':
			{
				if (printVerylong(stdout, b))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return -1;
				}
				break;
			}
			
			case '0':
			{
				return 0;
			}
			default:
			{
				printf("Unrecognised choise!\n");
				break;
			}
		}
	}
	
}
