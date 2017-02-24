#ifndef HASH_H
#define HASH_H

struct hash_table
{
	void *m_data;
	int   m_key;
	struct hash_table *m_next;
};

struct hash
{
	int 		 m_count;
	int 	     m_cap;
	struct hash_table **m_datas;
};

void hash_init(struct hash *h);
void hash_insert(struct hash *h,int key,void *value);
void* hash_find(struct hash *h,int key);
void* hash_remove(struct hash *h,int key);

#endif