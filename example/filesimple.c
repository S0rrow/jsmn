#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../jsmn.h"

typedef struct filedata* pfiledata;
typedef struct filedata{
	int size;
	char* data;
}filedata;

pfiledata readJSONFile() {
	pfiledata data_json;
	FILE* fp = fopen("data.json","r");
	int size = 0;
	while(!feof(fp)){
		char cache[100];
		fgets(cache, 100, fp);
		size = size + strlen(cache);
	}
	fclose(fp);
	data_json = (pfiledata)malloc(size+sizeof(int));
	data_json->size = size;
	FILE* fp2 = fopen("data.json","r");
	char* oneline = (char*)malloc(size);
	while(!feof(fp2)) {
		char cache[100];
		fgets(cache, 100, fp2);
		strcat(oneline, cache);
	}
	fclose(fp2);
	data_json->data = oneline;
	free(oneline);
	return data_json;
}

int main(){
	pfiledata JSONdata = readJSONFile();
	printf("%s", JSONdata->data);
	return 0;
}
