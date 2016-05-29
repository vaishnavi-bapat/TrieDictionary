//dict.c

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>

#define FALSE 0
#define TRUE 1

//Probably won't need these anymore..
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8
#define J 9
#define K 10
#define L 11
#define M 12
#define N 13
#define O 14
#define P 15
#define Q 16
#define R 17
#define S 18
#define T 19
#define U 20
#define V 21
#define W 22
#define X 23
#define Y 24
#define Z 25

typedef int boolean;

typedef struct _trie *Trie;

typedef struct _trie
{
	boolean flag;
	Trie *next[26];
} trie;

void addword(Trie t, char *s);
boolean checkword(Trie t, char *s);
void delword(Trie t, char *s);

void truncate (char *s);
Trie newEmptyTrie();
int convertToIndex(char c);

int main(int argc, char const *argv[])
{

	//intialising dictionary (initDictA = <Flag:B, ntla>)
	Trie dictionary = newEmptyTrie();//malloc(sizeof(Trie));
	
	char type = 'x';
	
	while (type != 'q') {

		char *word = malloc(sizeof(char)*100);

		scanf(" %c %s", &type, word);

		if (type == 'a') {
			addword(dictionary, word);
		} 
		if (type == 'c') {
			boolean b = FALSE;
			b = checkword(dictionary, word);
			if (b == FALSE) {
				printf("%s is not known\n", word);
			}
		} 
		if (type == 'd') {
			delword(dictionary, word);
		}

		free(word);

	}

	//free(dictionary);

	return 0;
}

void addword(Trie t, char *s) {
	//printf("%s\n", s);
	if (s[0] != '\0') {
		int index = convertToIndex(s[0]);
		truncate(s);
		s++;
		if (t->next[index] == NULL) {
			//printf("got here");
			Trie newT = newEmptyTrie();//malloc(sizeof(Trie));
			t->next[index] = &newT;
			printf("After calling: %p\n", &newT);
			assert(*t->next[index] == newT);
			addword(*t->next[index], s);
		}
	} else {
		t->flag = TRUE;
	}
}

boolean checkword(Trie t, char *s) {
	
	printf("%s\n", s);
	
	boolean b = FALSE;

	if (s[0] != '\0') {
		int index = convertToIndex(s[0]);
		printf("got here\n");
		if (t == NULL) {
			printf("null trie..\n");
		} else {
			printf("not null..\n");
		}
		if (t->next[index] == NULL) {
			printf("cond1\n");
			b = FALSE;
		} else {
			printf("cond2\n");
			//truncate(s);
			s++;
			b = checkword(*t->next[index], s);
		}
	} else {
		if (t->flag == TRUE) { 
			b = TRUE; 
		} else {
			b = FALSE;
		}
	}
	return b;
}

Trie newEmptyTrie() {
	Trie newEmptyTrie = malloc(sizeof(*newEmptyTrie));
	int i = 0;
	for (i = 0; i < 26; i++) {
		newEmptyTrie->next[i] = NULL;
	}
	printf("Within call: %p\n", newEmptyTrie);
	return newEmptyTrie;
}

void delword(Trie t, char *s) {
	printf("%s\n", s);
	if (s[0] != '\0') {
		int index = convertToIndex(s[0]);
		truncate(s);
		s++;
		printf("got here!\n");
		delword(*t->next[index], s);
	} else {
		t->flag = FALSE;
		printf("Deleted!\n");
	}
}

void truncate (char *s) {
	s[0] = '\0';
}

/*
//Returns a new string - same as s but with its first character removed
char * truncate(char *s) {
	return substring(s, 1, strlen(s));
}
*/

/*
//Returns substring of s from startingIndex to the end of the string
char * substring(char *s, int startingIndex, int length) {
	char *subString = NULL;
	strncpy(subString, s + startingIndex, length);
	return subString;
}
*/

int convertToIndex(char c) {
	int index = 0;
	if (c == 'a' || c == 'A') { index = 0; }
	if (c == 'b' || c == 'B') { index = 1; }
	if (c == 'c' || c == 'C') { index = 2; }
	if (c == 'd' || c == 'D') { index = 3; }
	if (c == 'e' || c == 'E') { index = 4; }
	if (c == 'f' || c == 'F') { index = 5; }
	if (c == 'g' || c == 'G') { index = 6; }
	if (c == 'h' || c == 'H') { index = 7; }
	if (c == 'i' || c == 'I') { index = 8; }
	if (c == 'j' || c == 'J') { index = 9; }
	if (c == 'k' || c == 'K') { index = 10; }
	if (c == 'l' || c == 'L') { index = 11; }
	if (c == 'm' || c == 'M') { index = 12; }
	if (c == 'n' || c == 'N') { index = 13; }
	if (c == 'o' || c == 'O') { index = 14; }
	if (c == 'p' || c == 'P') { index = 15; }
	if (c == 'q' || c == 'Q') { index = 16; }
	if (c == 'r' || c == 'R') { index = 17; }
	if (c == 's' || c == 'S') { index = 18; }
	if (c == 't' || c == 'T') { index = 19; }
	if (c == 'u' || c == 'U') { index = 20; }
	if (c == 'v' || c == 'V') { index = 21; }
	if (c == 'w' || c == 'W') { index = 22; }
	if (c == 'x' || c == 'X') { index = 23; }
	if (c == 'y' || c == 'Y') { index = 24; }
	if (c == 'z' || c == 'Z') { index = 25; }
	return index;
}

