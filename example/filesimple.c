#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../jsmn.h"

/*
 * A small example of jsmn parsing when JSON structure is known and number of
 * tokens is predictable.
 */

char *readJSONFile() {
	FILE* fp = fopen("..\\data.json","r");
	if(f == NULL) return NULL;
	char* JSON_STRING;
	char oneline[255];
	while(!feof(fp)) {
		cache = fgets(JSON_STRING, count, fp);
		count = strlen(oneline);
		(char*)realloc(sizeof(count));
		strcat(JSON_STRING,)
	}
	return JSON_STRING;
	fclose(fp);
}

static const char *JSON_STRING = readJSONFile();
	//"{\"user\": \"johndoe\", \"admin\": false, \"uid\": 1000,\n  "
	//"\"groups\": [\"users\", \"wheel\", \"audio\", \"video\"]}";

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

int main() {
	int i;
	int r;
	jsmn_parser p;
	jsmntok_t t[128]; /* We expect no more than 128 tokens */

	jsmn_init(&p);
	r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[0]));
	if (r < 0) {
		printf("Failed to parse JSON: %d\n", r);
		return 1;
	}

	/* Assume the top-level element is an object */
	if (r < 1 || t[0].type != JSMN_OBJECT) {
		printf("Object expected\n");
		return 1;
	}

	/* Loop over all keys of the root object */
	for (i = 1; i < r; i++) {
		if (jsoneq(JSON_STRING, &t[i], "Name") == 0) {
			/* We may use strndup() to fetch string value */
			printf("\"Name\": %.*s\n", t[i+1].end-t[i+1].start,
					JSON_STRING + t[i+1].start);
			i++;
		} else if (jsoneq(JSON_STRING, &t[i], "keywords") == 0) {
			/* We may additionally check if the value is either "true" or "false" */
			printf("\"keywords\": %.*s\n", t[i+1].end-t[i+1].start,
					JSON_STRING + t[i+1].start);
			i++;
		} else if (jsoneq(JSON_STRING, &t[i], "description") == 0) {
			/* We may want to do strtol() here to get numeric value */
			printf("\"description\": %.*s\n", t[i+1].end-t[i+1].start,
					JSON_STRING + t[i+1].start);
			i++;
		} else if (jsoneq(JSON_STRING, &t[i], "exclude") == 0) {
                        printf("\"exclude\": %.*s\n", t[i+1].end-t[i+1].start,
                                        JSON_STRING + t[i+1].start);
                        i++;
		} else if (jsoneq(JSON_STRING, &t[i], "repository") == 0) {
			int j;
			printf("\"repository\":\n(");
			if (t[i+1].type != JSMN_ARRAY) {
				continue; /* We expect groups to be an array of strings */
			}
			for (j = 0; j < t[i+1].size; j++) {
				jsmntok_t *g = &t[i+j+3];
				if (jsoneq(JSON_STRING, &t[i+j+2], "type") == 0) {
                       		 printf("\"type\": %.*s\n", g->end - g->start,JSON_STRING + g->start);
				}
				else if (jsoneq(JSON_STRING, &t[i+j+2], "url") == 0) {
                                 printf("\"url\": %.*s\n", g->end - g->start,JSON_STRING + g->start);
                                }
				//jsmntok_t *g = &t[i+j+2];
				//printf("  * %.*s\n", g->end - g->start, JSON_STRING + g->start);
			}
			printf("),");
			i += t[i+1].size + 1;
		} else {
			printf("Unexpected key: %.*s\n", t[i].end-t[i].start,
					JSON_STRING + t[i].start);
		}
	}
	return EXIT_SUCCESS;
}
