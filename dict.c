//dict.c
//Clinton Hadinata and Vaishnavi Bapat
//cs2111 2016

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

	//intialising dictionary (initDictA = <Flag:B, NETA>)
	Trie dictionary = malloc(sizeof(trie));
	emptyTrieArray(dictionary);	//sets dictionary's next array to NETA
	dictionary->flag = FALSE; 	//sets the flag to FALSE
	
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
//pre: {TRUE}
//post: {P(t,s) && unchangedAdd(t,t0,s)}
void addword(Trie t, char *s) {
	if (s[0] != '\0') {
		int index = convertToIndex(s[0]); //index sets the path for recursion to go 
		//through since it is properly mapped to from s[0], this will ensure that 
		//only the correct sequence of trie nodes (based on the characters of s) 
		//will be travelled to /new nodes created for.
		if (t->next[index] == NULL) {
			t->next[index] = malloc(sizeof(trie));//Creates a new trie node 
			emptyTrieArray(t->next[index]);		//sets next array to NETA
			t->next[index]->flag = FALSE;		//sets flag to FALSE
				//flag is never set to true unless we've reached end of word
				//this ensures we are never adding any new words to the 
				//dictionary and thus unchangedAdd(t,t0,s) holds.
		} 
		s++;	//truncates s (using pointer arithmetic)
		addword(t->next[index], s); 
		//recurses down the right path, as explained above
	} else {
		// Only once s has been truncated to null character do we end up here
		t->flag = TRUE; //At this point, because of all the above assertions, we 
				//would be at the trie node that the last character's
				//associated node is pointing at. Setting the flag to 
				//true adds it to the dictionary and thus P(t,s) holds.
	}
}

//Function to check if a word exists in the Trie dictionary
//pre: {TRUE}
//post: {b <=> P(t,s)}
boolean checkword(Trie t, char *s) {
		
	boolean b = FALSE;

	if (s[0] != '\0') {
		int index = convertToIndex(s[0]);//index sets the path for recursion to go
		//through since it is properly mapped to from s[0], this will ensure 
		//that only the correct sequence of trie nodes (based on the characters 
		//of s) will be travelled to.
		if (t->next[index] == NULL) {
			b = FALSE;	//this is if we've hit a null, but the word hasn't ended yet, 
					//hence the word does not exist in this trie representation
					//and postcondition holds
		} else {
			s++;	//truncates s (using pointer arithmetic)
			b = checkword(t->next[index], s);	
			//if not yet hit null, keep recursing down the trie
		}
	} else {	//i.e. if (s[0] == '\0')
		// Only once s has been truncated to null character do we end up here
		if (t->flag == TRUE) { 
			b = TRUE; 	//this is if the representation of all the characters 
					//exists in the right sequence and the flag is true, hence
					//the word is in the dict and postcondition holds
		} else {
			b = FALSE;	//this is if the representation of all the characters 
					//exists in the right sequence and the flag is false, hence
					//the word is not in the dict and postcondition holds
		}
	}
	return b;
}

//Procedure to delete a word from the Trie dictionary
//Pre: {P(t,s)}
//Post: {~P(t,s) && unchangedDel(t,t0,s)}
void delword(Trie t, char *s) {
	if (s[0] != '\0') {
		int index = convertToIndex(s[0]);//index sets the path for recursion to go
        if (t->next[index] == NULL) {
            return;
        }
		//through since it is properly mapped to from s[0], this will ensure that
		//only the correct sequence of trie nodes (based on the characters of s) 
		//will be travelled to.
		s++;		//truncates s (using pointer arithmetic)
		delword(t->next[index], s); //recurses down correct path
	} else {
		t->flag = FALSE;	//At this point, because of all the above assertions, 
				//we would be at the trie node that s0's last character's associated
				//node is pointing at. Setting the flag to false removes it from the
				//dictionary and thus P(t,s) holds, and because we have only 
				//travelled down the right path and no other flags change except 
				//this one, unchangedDel(t,t0,s) holds.
	}
}

//Function to set t's next array to NETA
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

//function to return a letter's corresponding index between 0 and 26
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

