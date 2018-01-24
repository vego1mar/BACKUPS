// A simple implementation of a hashing table
// Using Visual C (2010)

// CONSTRAINTS:
// Currently values placed between empty space and borders will be cut.

#include <stdio.h>
#include <string.h>

// -------------------------------------------------------------------------

typedef enum {FALSE, TRUE} BOOLEAN;

// -------------------------------------------------------------------------

#define	STR		(31)
#define	HT		(37)
#define	STSTR	(STR+26)

// -------------------------------------------------------------------------

struct HashTable
	{
	long int key;
	char string [STR];
	};

// -------------------------------------------------------------------------

void Clear_HashTable(struct HashTable *);
void Print_All(const struct HashTable *);
void Print(const struct HashTable *);
short int Add(const long int, const char * const, struct HashTable *);
long int Hash(const long int);
const char * Get(const long int, const struct HashTable *);
long int Delete(const long int, struct HashTable *);

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

int main(void)
{
struct HashTable ht [HT];

Clear_HashTable(ht);
Add(20L,"AAAA",ht); // 20 % 37 == 20
Add(40L,"BBBB",ht); // 40 % 37 == 3
Add(60L,"CCCC",ht); // 60 % 37 == 23
Add(80L,"DDDD",ht); // 80 % 37 == 6
Add(168L,"EEEE",ht); // 168 % 37 == 20
Add(131L,"FFFF",ht); // 131 % 37 == 20
Add(279L,"GGGG",ht); // 279 % 37 == 20
Add(97L,"HHHH",ht); // 97 % 37 == 23
Print(ht);
printf("\nGet(279) = %s\n",Get(279L,ht));
Delete(20L,ht);
printf("Delete(20)\nGet(279) = %s\n\n",Get(279L,ht));
Print(ht);

getchar();
return (0);
};

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

void Clear_HashTable(struct HashTable *ht_ptr)
{
long int i;
long int j;

for (i=0; i<HT; i++)
	{
	ht_ptr -> key = 0;

	for (j=0; j<STR; j++)
		{
		ht_ptr -> string[j] = 0;
		};

	ht_ptr++;
	};
};

// -------------------------------------------------------------------------

void Print_All(const struct HashTable *ht_ptr)
{
long int i;

for (i=0; i<HT; i++)
	{
	printf("%*.1ld%*.1ld",12,i,12,ht_ptr->key);
	printf("   <%s>\n",ht_ptr->string);
	ht_ptr++;
	};
};

// -------------------------------------------------------------------------

void Print(const struct HashTable *ht_ptr)
{
long int i;

for (i=0; i<HT; i++)
	{
	if ((ht_ptr->key) != 0)
		{
		printf("%*.1ld%*.1ld",12,i,12,ht_ptr->key);
		printf("   <%s>\n",ht_ptr->string);
		};

	ht_ptr++;
	};
};

// -------------------------------------------------------------------------

short int Add(const long int _key, const char * const _string, struct HashTable *_ht_ptr)
// 0	updated			an empty cell was reached
// 1	terminated		hash value is non-positive
// 2	terminated		hash value is out of bounds of the storing data structure
// 3	missed			a value at reached cell was already calculated
// 4	stopped			there are no empty cells in the structure storing data
{
const long int hash = Hash(_key);
long int len = 0;
long int idx = 0;
long int n = 0;
long int i;

if (hash < 0) return (1);
if (hash >= HT) return (2);

for (i=0; i<hash; i++) 
	{
	_ht_ptr++;
	idx++;
	};

if ((_ht_ptr->key) != 0)
	{
	while (n < HT)
		{
		idx++;
		_ht_ptr++;
	
		if (idx >= HT) 
			{
			idx--;
			_ht_ptr--;
			for (i=0; i<idx; i++) _ht_ptr--;
			idx = 0;
			};

		if (!(_ht_ptr->key))
			{
			_ht_ptr->key = _key;
			for (i=0; i<STR; i++) _ht_ptr->string[i] = 0;
			for (i=0; i<STR; i++) if (_string[i] != '\n') len++;
			for (i=0; i<len; i++) _ht_ptr->string[i] = _string[i];
			break;
			};

		n++;
		};

	if (n >= HT) return (4);
	return (3);
	};

_ht_ptr->key = _key;
for (i=0; i<STR; i++) _ht_ptr->string[i] = 0;
for (i=0; i<STR; i++) if (_string[i] != '\n') len++;
for (i=0; i<len; i++) _ht_ptr->string[i] = _string[i];

return (0);
};

// -------------------------------------------------------------------------

long int Hash(const long int _key)
{
return (_key % HT);
};

// -------------------------------------------------------------------------

const char * Get(const long int _key, const struct HashTable *_ht_ptr)
{
static char str[STSTR];
long int i;
char tmp[12] = {0};
BOOLEAN notin = TRUE;

for (i=0; i<STSTR; i++) str[i] = 0;

for (i=0; i<HT; i++)
	{
	if (_ht_ptr->key == _key)
		{
		sprintf(tmp,"%ld",i);
		strcpy(str,tmp);
		strcat(str," ");
		tmp[0] = '\0';
		sprintf(tmp,"%ld",_ht_ptr->key);
		strcat(str,tmp);
		strcat(str," <");
		strcat(str,_ht_ptr->string);
		strcat(str,">");
		notin = FALSE;
		break;
		};

	_ht_ptr++;
	};

if (notin == TRUE) strcpy(str,"Key not found.");

return (str);
};

// -------------------------------------------------------------------------

long int Delete(const long int _key, struct HashTable *_ht_ptr)
//	0	no interrupts		a key with unique hash was deleted
//	n	manipulated			the number of displacements needed
{
long int i;
long int j;
const long int hash = Hash(_key);
long int prev = -1L;
long int tmp1;
char tmp2[STR] = {0};
long int manip = 0;
long int tmp3;

for (i=0; i<hash; i++) _ht_ptr++;
_ht_ptr->key = 0;
for (j=0; j<STR; j++) _ht_ptr->string[j] = 0;
prev = i;

// Checking till the end.
for (i++; i<HT; i++)
	{
	_ht_ptr++;
	tmp3 = _ht_ptr->key;

	if ((Hash(tmp3)) == hash)
		{
		tmp1 = _ht_ptr->key;
		strcpy(tmp2,_ht_ptr->string);
		_ht_ptr->key = 0;
		_ht_ptr->string[0] = '\0';
		for (j=i; j>prev; j--) _ht_ptr--;
		_ht_ptr->key = tmp1;
		strcpy(_ht_ptr->string,tmp2);
		tmp1 = 0;
		tmp2[0] = '\0';
		for (j=prev; j<i ; j++) _ht_ptr++;
		prev = i;
		manip++;
		};
	};

// Checking at borders.
for (i=(HT-1); i>0; i--) _ht_ptr--;

for (i=0; i<hash; i++)
	{
	tmp3 = _ht_ptr->key;

	if ((Hash(tmp3)) == hash)
		{
		tmp1 = _ht_ptr->key;
		strcpy(tmp2,_ht_ptr->string);
		_ht_ptr->key = 0;
		_ht_ptr->string[0] = '\0';
		for (j=i; j<(HT-1); j++) _ht_ptr++;
		for (j=(HT-1); j>prev; j--) _ht_ptr--;
		_ht_ptr->key = tmp1;
		strcpy(_ht_ptr->string,tmp2);
		tmp1 = 0;
		tmp2[0] = '\0';
		for (j=prev; j<(HT-1); j++) _ht_ptr++;
		for (j=0; j<(i-1); j++) _ht_ptr++;
		prev = i;
		manip++;
		break;
		};

	_ht_ptr++;
	};

// Checking from the start.
for (i=hash; i>0; i--) _ht_ptr--;
for (i=0; i<prev; i++) _ht_ptr++;
j = i;

for (i=j; i<HT; i++)
	{
	tmp3 = _ht_ptr->key;

	if ((Hash(tmp3)) == hash)
		{
		tmp1 = _ht_ptr->key;
		strcpy(tmp2,_ht_ptr->string);
		_ht_ptr->key = 0;
		_ht_ptr->string[0] = '\0';
		for (j=i; j>prev; j--) _ht_ptr--;
		_ht_ptr->key = tmp1;
		strcpy(_ht_ptr->string,tmp2);
		tmp1 = 0;
		tmp2[0] = '\0';
		for (j=prev; j<i ; j++) _ht_ptr++;
		prev = i;
		manip++;
		};

	_ht_ptr++;
	};

// Checking the integrity for other hashes.
_ht_ptr--;
for (i=(HT-1); i>0; i--) _ht_ptr--;
prev = 0;

for (i=0; i<HT; i++)
	{
	tmp3 = _ht_ptr->key;
	tmp3 = Hash(tmp3);

	if (tmp3)
		{
		tmp1 = 0;
		prev = 0;

		while (!tmp1)
			{
			_ht_ptr++;
			tmp1 = _ht_ptr->key;
			if (!tmp1) prev++;
			};

		tmp1 = _ht_ptr->key;
		tmp1 = Hash(tmp1);

		if ((tmp1 == tmp3) && (prev))
			{
			tmp1 = _ht_ptr->key;
			strcpy(tmp2,_ht_ptr->string);
			_ht_ptr->key = 0;
			_ht_ptr->string[0] = '\0';
			for (j=0; j<prev; j++) _ht_ptr--;
			_ht_ptr->key = tmp1;
			strcpy(_ht_ptr->string,tmp2);
			tmp1 = 0;
			tmp2[0] = '\0';
			_ht_ptr--;
			manip++;
			}
		else
			{
			_ht_ptr--;
			for (j=0; j<prev; j++) _ht_ptr--;
			};
		};

	_ht_ptr++;
	};

if (manip == 1) return (0);
return (manip);
};

// -------------------------------------------------------------------------
