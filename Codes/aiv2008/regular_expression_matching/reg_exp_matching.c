#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAP_SIZE 7

typedef struct {
	char key;
	int val;
	struct Entry* this;
	struct Entry* next;
} Entry;

typedef struct {
	Entry entry[MAP_SIZE];
	//Entry *entry;
	int size;
} HashMap;


int hash(char c) {
	return ((int)c) % MAP_SIZE;
}

void push(HashMap **map, char key, int val) {
	printf("key=%c, val=%d\n", key, val);
	if(map == NULL) { return ;}
	if(*map == NULL) {
		*map = (HashMap*)calloc(1, sizeof(HashMap));
		(*map)->size = MAP_SIZE;
		//(*map)->entry = (Entry*)calloc(MAP_SIZE, sizeof(Entry));
	}
	//printf("aaaa\n");
	int hashCode = hash(key);
	Entry *entry = &((*map)->entry)[hashCode];
	if(entry->this == NULL) {
		entry->key = key;
		entry->val = val;
		entry->this = entry;
		entry->next = NULL;
	} else {
		Entry *pEntry = entry;
		//Entry *pEntry = entry.this;
		while(pEntry->next != NULL) {
			if(pEntry->key == key) {
				printf("11key=%c, val=%d\n", key, val);
				pEntry->val = val;
				break;
			}
			pEntry = pEntry->next;
		}
		//最后一个节点
		if(pEntry->key == key) {
	//		printf("22key=%c, val=%d\n", key, val);
			pEntry->val = val;
	//		printf("val1===%d\n", pEntry->val);
		} else {
	//		printf("33key=%c, val=%d\n", key, val);
			Entry *newEntry = (Entry*)calloc(1, sizeof(Entry));
			newEntry->key = key;
			newEntry->val = val;
			newEntry->this = newEntry;
			newEntry->next = NULL;
			pEntry->next = newEntry;
		}
		//entry.next = newEntry;
	}
	//printf("wait...\n");
}

int get(HashMap *map, char key) {
	if(map == NULL) return -1;
	int val = -1;
	int hashCode = hash(key);
//	printf("hashCode=%d\n", hashCode);
	Entry entry = (map->entry)[hashCode];
//	Entry *entry = map->entry + hashCode;
	Entry *pEntry = &entry;
	while(pEntry != NULL) {
		if(pEntry->key == key) {
			val = pEntry->val;
			break;
		}
		pEntry = pEntry->next;
	}
	return val;
}

void test(HashMap *map[]) {
	if(map == NULL)printf("map is null\n");
	printf("map1 size=%d\n", sizeof(map)/sizeof(map[0]));
	printf("map2 size=%d\n", sizeof(map[0]));
	//map[0] = (HashMap*)calloc(1, sizeof(HashMap));
//	printf("size=%p\n",map[0]);
}

int main(void) {
	HashMap *map = NULL;;
	int b[] = {'a','b','c','d','e','f','g','h', 'a', 'c'};
	int i;
	int size = sizeof(b)/sizeof(b[0]);
	for(i=0;i<size;i++) {
		int val = get(map, b[i]);
//		printf("key=%c, val=%d\n", b[i], val);
		push( &map, b[i], val == -1 ? 1 : (val + 1));
	}
	for(i=0;i<size;i++) {
		printf("%d,", get(map, b[i]));
	}
	printf("\n");	
	return 0;
}
