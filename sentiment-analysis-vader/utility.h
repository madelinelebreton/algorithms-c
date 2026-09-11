// utility.h
// written by Madeline with help from ChatGPT
// this header file contains declarations of helper functions, structures,
// and constants used across multiple files

#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h> // for memory
#include <string.h> // for strlen
#include <ctype.h>  // for isupper
#include <math.h>   // for operations

// constants for array size, boost factors, multipliers, normalization
#define ARRAY_SIZE 10
#define MAX_STRING_LENGTH 30 // changed because 5 was too short to accommodate some words in the lexicon
#define INTENSIFIER 0.293
#define EXCLAMATION 0.292
#define ALLCAPS 1.5
#define NEGATION -0.5
#define ALPHA 15
#define MAX_SENTENCE_LENGTH 100
#define MAX_LINE_LENGTH 512

// data structure to read lexicon.txt and store each word's data in a structured
// format, dynamically allocating an array of WordData where each element
// corresponds to one lexicon word
typedef struct {
    char word[MAX_STRING_LENGTH]; // word in lexicon
    float value1;                 // mean sentiment value
    float value2;                 // stdev
    int intArray[ARRAY_SIZE];     // array of sentiment ratings
} WordData;

// FUNCTION PROTOTYPES ////////////////////////////////////////////////////

// load lexicon data from a file
WordData* loadLexicon(const char* filename, int* lexiconSize);

// analyze sentiment of a single word (returns lexicon score, 0 if not found)
float findWordScore(const char* word, WordData* lexicon, int lexiconSize);

// sentiment calculation utility functions
int isIntensifier(const char* word);
int isNegation(const char* word);
float isAllcaps(const char* word);
float isExclamation(const char* word);
void removePunctuation(char* word);
float calcCompound(const char* sentence, WordData* lexicon, const int lexiconSize);

#endif // UTILITY_H
