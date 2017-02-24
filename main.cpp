#include <stdio.h>
#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include <map>

using namespace std;
#define MAX_COUNT 1000000

int64_t get_time()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	int64_t t = tv.tv_sec * 1000000 + tv.tv_usec;
}

void hash_test()
{
	int64_t diff = get_time();
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
		int *value = (int*)hash_find(&h,keys[i]);
		//printf("%d %d %d\n",keys[i],*value,values[i]);
		assert(*value==values[i]);
	}
	diff = get_time() - diff;
	double sc = diff / 1000000.f;
	printf("hash 总个数 %d 总用时间 \033[1;31m%lf\033[0m 秒\n",h.m_count,sc);
}

void map_test()
{
	int64_t diff = get_time();
	int keys[MAX_COUNT];
	memset(keys,0,sizeof(keys));

	int values[MAX_COUNT];
	memset(values,0,sizeof(values));
	map<int,int> map_key;
	map<int,int>::iterator it;

	srand(time(NULL));
	int i = 0;
	int max = 100000000;

	for(i = 0;i < MAX_COUNT;++i)
	{
		while(true)
		{
			keys[i]   = rand() % max + 1;
			values[i] = rand() % max + 1;
			if(map_key.find(keys[i]) == map_key.end())
			{
				map_key[keys[i]] = values[i];
				break;
			}
		}
	}

	for(i = 0;i < MAX_COUNT;++i)
	{
		it = map_key.find(keys[i]);
		//printf("%d %d %d\n",keys[i],*value,values[i]);
		assert(it->second==values[i]);
	}
	diff = get_time() - diff;
	double sc = diff / 1000000.f;
	printf("map  总个数 %d 总用时间 \033[1;31m%lf\033[0m 秒\n",map_key.size(),sc);
}

int main(int argc,char *argv[])
{
	hash_test();
	map_test();
	return 0;
}