#include <stdio.h>
#include "hash.h"
#include <string.h>
#include <assert.h>

#define MAX_COUNT 1000000

int main(int argc,char *argv[])
{
	int keys[MAX_COUNT];
	memset(keys,0,sizeof(keys));

	int values[MAX_COUNT];
	memset(values,0,sizeof(values));

	struct hash h;
	hash_init(&h);

	srand(time(NULL));
	int i = 0;
	int max = 100000000;
	for(i = 0;i < MAX_COUNT;++i)
	{
		while(true)
		{
			keys[i]   = rand() % max + 1;
			values[i] = rand() % max + 1;
			if(hash_insert(&h,keys[i],&values[i]))
			{
				break;
			}
		}
	}

	for(i = 0;i < MAX_COUNT;++i)
	{
		int *value = hash_find(&h,keys[i]);
		//printf("%d %d %d\n",keys[i],*value,values[i]);
		assert(*value==values[i]);
	}

	printf("all count is %d\n",h.m_count);

	return 0;
}