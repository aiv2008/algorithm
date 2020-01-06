#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAP_SIZE 7

typedef struct {
	int val;
	struct Entry* next;
} Entry;

typedef struct {
	struct Entry* entry;
	int size;
} HashMap;


int hash(char c) {
	return ((int)c) % MAP_SIZE;
}

void push(HashMap *(*map)[MAP_SIZE], char key, int val) {
	if(map == NULL) { return ;}
	if(*map == NULL) {
		HashMap *initMap[MAP_SIZE];
		int i;
		for(i=0;i<MAP_SIZE;i++) {
			initMap[i] = (int*)calloc(1, sizeof(HashMap));
		}
		map = initMap;
	}
	int hashCode = hash(c);
	if((map[hashCode])->val == NULL) {
		(map[hashCode])->entry = (Entry*)calloc(1, sizeof(Entry));
		Entry *entry = (map[hashCode])->entry;
		entry->val = val;
		entry->next = NULL;
	} else {
		Entry *entry = (Entry*)calloc(1, sizeof(Entry));
		entry->val = val;
		entry->next = NULL;
		Entry *mapEntry = (map[hashCode])->entry;
		mapEntry->next = entry;
	}
}

void test(HashMap *map[]) {
	if(map == NULL)printf("map is null\n");
	printf("map1 size=%d\n", sizeof(map)/sizeof(map[0]));
	printf("map2 size=%d\n", sizeof(map[0]));
	//map[0] = (HashMap*)calloc(1, sizeof(HashMap));
//	printf("size=%p\n",map[0]);
}

int main(void) {
	HashMap (*a)[8];
	int i;
	
	test(NULL);	
	return 0;
}
