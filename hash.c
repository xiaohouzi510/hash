#include <stdlib.h>
#include <time.h>
#include "hash.h"
#include <string.h>

#define ARRAY_COUNT 4

void hash_init(struct hash *h)
{
	h->m_datas  = malloc(sizeof(struct hash_table*) * ARRAY_COUNT);
	h->m_cap    = ARRAY_COUNT;
	h->m_count  = 0;
	memset(h->m_datas,0,sizeof(struct hash_table*) * ARRAY_COUNT);
}

void hash_extend(struct hash *h)
{
	struct hash_table **new_data = malloc(sizeof(struct hash_table*) * h->m_cap * 2);
	memset(new_data,0,sizeof(struct hash_table*) * h->m_cap * 2);
	int new_cap = h->m_cap * 2;
	struct hash_table *temp = NULL;
	struct hash_table *cur  = NULL;
	int i = 0;
	for(i = 0;i < h->m_cap;++i)
	{
		temp = h->m_datas[i];
		while(temp != NULL)
		{
			int key = temp->m_key % new_cap;
			cur     = temp;
			temp    = temp->m_next;
			cur->m_next = NULL;
			if(new_data[key] == NULL)
			{
				new_data[key] = cur;
			}
			else
			{
				cur->m_next = new_data[key];
				new_data[key] = cur;
			}
		}
	}
}

void hash_insert(struct hash *h,int key,void *value)
{
	int hash_key 	  = h->m_cap % key;
	struct hash_table *data  = malloc(sizeof(struct hash_table));
	memset(data,0,sizeof(struct hash_table));

	data->m_data = value;
	data->m_key  = key;

	struct hash_table *old_data = h->m_datas[hash_key];

	if(old_data == NULL)
	{
		h->m_datas[hash_key] = data;
	}
	else
	{
		data->m_next = old_data;
		h->m_datas[hash_key] = data;
	}
	++h->m_count;

	float p = h->m_count / h->m_cap;
	if(p >= 0.8f)
	{
		hash_extend(h);
	}
}

void* hash_find(struct hash *h,int key)
{
	int hash_key = h->m_cap % key;
	struct hash_table *old_data = h->m_datas[hash_key];
	if(old_data == NULL)
	{
		return NULL;
	}

	while(old_data != NULL)
	{
		if(old_data->m_key == key)
		{
			return old_data->m_data;
		}
		old_data = old_data->m_next;
	}

	return NULL;
}

void* hash_remove(struct hash *h,int key)
{
	int hash_key = h->m_cap % key;
	struct hash_table *old_data = h->m_datas[hash_key];
	if(old_data == NULL)
	{
		return NULL;
	}
	if(old_data->m_key == key)
	{
		h->m_datas[hash_key] = old_data->m_next;
		void *result_data    = old_data->m_data;
		free(old_data);
		--h->m_count;
		return result_data;
	}

	struct hash_table *before_data = NULL;
	do
	{
		before_data = old_data;
		old_data 	= old_data->m_next;
		if(old_data->m_key == key)
		{
			void *result_data   = old_data->m_data;
			before_data->m_next = old_data->m_next;
			free(old_data);
			--h->m_count;
			return result_data;
		}
	}while(old_data != NULL);

	return NULL;
}