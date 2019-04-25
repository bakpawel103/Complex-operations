#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct complex_t
{
	float re;
	float im;
}zesp1, zesp2, result;

struct complex_t* set(struct complex_t* cp, float re, float im, int *err_code)
{
	if(err_code == NULL)
	{
		if(cp != NULL)
		{
			cp->re = re;
			cp->im = im;
			return cp;
		}else
		{
			return NULL;
		}
	}
	if(cp == NULL)
	{
		*err_code = 1;
		return NULL;
	}
	
	cp->re = re;
	cp->im = im;
	
	*err_code = 0;
	return cp;
}

int read(struct complex_t *cp)
{
	if(cp == NULL)
	{
		return 0;
	}
	
	float re, im;
	
	if(scanf("%f", &re) == 0)
	{
		return 0;
	}
	
	int error;
	char sign;
	char sign_zesp;
	
	sign = fgetc(stdin);
	if(sign != '+' && sign != '-')
	{
		return 0;
	}
	scanf("%1c", &sign_zesp);
	if(sign_zesp != 'i')
	{
		return 0;
	}
	
	int change_sign = -1;
	
	if(sign == '+')
	{
		if(scanf("%f", &im) == 0)
		{
			return 0;
		}
		if(im < 0)
		{
			return 0;
		}
	}else
	{
		if(scanf("%f", &im) == 0)
		{
			return 0;
		}
		if(im < 0 )
		{
			return 0;
		}
		im *= change_sign;
	}

	set(cp, re, im, &error);
	if(!error)
	{
		return 1;
	}else
	{
		return 0;
	}
}

void show(const struct complex_t* cp)
{
	if(cp != NULL)
	{
		if(cp->im < 0)
			printf("%f - i%f\n", cp->re, (cp->im)*(-1));
		else
		{
			printf("%f + i%f\n", cp->re, cp->im);
		}
	}
}

float complex_abs(struct complex_t* cp, int *err_code)
{
	if(err_code == NULL)
	{
		if(cp != NULL)
		{
			return sqrt((cp->im)*(cp->im)+(cp->re)*(cp->re));
		}else
		{
			return -1;	
		}
	}	
	if(cp == NULL)
	{
		*err_code = 1;
		return -1;
	}
	
	*err_code = 0;
	return sqrt((cp->im)*(cp->im)+(cp->re)*(cp->re));
}

int add(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
	if(first == NULL || second == NULL || result == NULL)
	{
		return 0;
	}
	
	result->re = first->re + second->re;
	result->im = first->im + second->im;
	
	return 1;
}

int subtract(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
	if(first == NULL || second == NULL || result == NULL)
	{
		return 0;
	}
	
	result->re = first->re - second->re;
	result->im = first->im - second->im;
	
	return 1;
}

int multiply(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
	if(first == NULL || second == NULL || result == NULL)
	{
		return 0;
	}
	
	result->re = (first->re * second->re) - (first->im * second->im);
	result->im = (first->re * second->im) + (first->im * second->re);
	
	return 1;
}

int divide(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
	if(first == NULL || second == NULL || result == NULL)
	{
		return 0;
	}
	
	if((pow(second->re, 2) + pow(second->im, 2)) == 0)
	{
		return 0;
	}
	
	result->re = (first->re * second->re + first->im * second-> im)/(pow(second->re, 2) + pow(second->im, 2));
	result->im = (first->im * second->re - first->re * second-> im)/(pow(second->re, 2) + pow(second->im, 2));
	
	return 1;
}

int main(void)
{
	
	printf("Podaj pierwsza liczbe zespolona: \n");
	if(read(&zesp1) == 0)
	{
		printf("Error");
		return 1;
	}
	
	printf("Podaj druga liczbe zespolona: \n");
	if(read(&zesp2) == 0)
	{
		printf("Error");
		return 1;
	}
	
	add(&zesp1, &zesp2, &result);
	show(&result);
	
	subtract(&zesp1, &zesp2, &result);
	show(&result);
	
	multiply(&zesp1, &zesp2, &result);
	show(&result);
	
	if(divide(&zesp1, &zesp2, &result) == 1)
	{
		show(&result);
	}else
	{
		printf("Error");
	}
	
	return 0;
}
