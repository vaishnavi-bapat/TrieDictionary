//dict.c

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>

#define FALSE 0
#define TRUE 1

typedef int boolean;

typedef struct _trie *Trie;
typedef struct _trie
{
	boolean flag;
	Trie next[26];
}trie;

void addword(Trie t, char *s);
boolean checkword(Trie t, char *s);
void delword(Trie t, char *s);

void emptyTrieArray(Trie t);
int convertToIndex(char c);

int main(int argc, char const *argv[])
{

	//intialising dictionary (initDictA = <Flag:B, ntla>)
	Trie dictionary = malloc(sizeof(trie));
	emptyTrieArray(dictionary);
	dictionary->flag = FALSE;
	
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

	return 0;
}


//Procedure to add a word to the Trie dictionary
void addword(Trie t, char *s) {
	if (s[0] != '\0') {
		int index = convertToIndex(s[0]);
		if (t->next[index] == NULL) {
			//create the new trie structure, X, that gets added onto t''
			//see predicate unchangedAdd(t,t_0,s)
			t->next[index] = malloc(sizeof(trie));
			emptyTrieArray(t->next[index]);
			t->next[index]->flag = FALSE;
		} 
		s++;
		addword(t->next[index], s);
	} else {
		t->flag = TRUE;
	}
}

//Function to check if a word exists in the Trie dictionary
boolean checkword(Trie t, char *s) {
		
	boolean b = FALSE;

	if (s[0] != '\0') {
		int index = convertToIndex(s[0]);
		if (t->next[index] == NULL) {
			b = FALSE;
		} else {
			s++;
			b = checkword(t->next[index], s);
		}
	} else {
		//P(t,s) is true if t->flag == true
		if (t->flag == TRUE) { 
			b = TRUE; 
		} else {
			b = FALSE;
		}
	}
	return b;
}

//Procedure to delete a word from the Trie dictionary
void delword(Trie t, char *s) {
	if (s[0] != '\0') {
		int index = convertToIndex(s[0]);
		s++;
		delword(t->next[index], s);
	} else {
		//changing the flag to flase
		//see lastTrieOfString(t,s)
		t->flag = FALSE;
	}
}

//procedure to initialise 
void emptyTrieArray(Trie t) {
	//{I[0/i]}
	int i = 0;
	//{I}
	while (i != 26) {
		//{I && i < 26} 
		//{I[i+1/i][t->next:i\mapsto NULL]}
		t->next[i] = NULL;
		//{I[i+1/i]}
		i = i + 1;
		//{I}
	}

	// {I && i == 26}
	// Invariant I is: 
	// I = forall j\in[0,i) t->next[j] = NULL
	// So by the end of the loop, when it exits, forall j\in[0,26), t->next[j] = NULL.
}

//function to return a letter's corresponding number between 0 and 26
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

