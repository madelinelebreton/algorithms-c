// vaderSentiment.c
// written by Madeline with help from ChatGPT
// this file defines functions to process the lexicon, parse sentences, and implement
// sentiment analysis logic, applying VADER's rules to calculate sentiment scores

#include "utility.h"

// function to load lexicon data from vader_lexicon.txt into an array of WordData
WordData* loadLexicon(const char* filename, int* lexiconSize) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open lexicon file");
        exit(EXIT_FAILURE);
    }

    int capacity = 50;
    *lexiconSize = 0;
    WordData* lexicon = malloc(capacity * sizeof(WordData));
    if (lexicon == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // remove the newline character
        if (strlen(line) == 0) continue;  // skip empty lines

        WordData wordData;

        // parse the first three values (word, value1, value2)
        int numItems = sscanf(line, "%s %f %f", wordData.word, &wordData.value1, &wordData.value2);
        if (numItems < 3) {
            fprintf(stderr, "Error parsing line: %s\n", line);
            continue;
        }

        // find the starting point for the distribution ratings in the line
        char* ratingsStart = strchr(line, ' ');
        if (ratingsStart) {
            ratingsStart = strchr(ratingsStart + 1, ' ');
            if (ratingsStart) {
                ratingsStart = strchr(ratingsStart + 1, ' ');
                if (ratingsStart) ratingsStart++; // position after third whitespace
            }
        }

        // parse the distribution ratings array from the rest of the line
        if (ratingsStart) {
            for (int i = 0; i < ARRAY_SIZE; i++) {
                if (sscanf(ratingsStart, "%d", &wordData.intArray[i]) != 1) {
                    fprintf(stderr, "Error reading distribution rating for word '%s' on line: %s\n", wordData.word, line);
                    break;
                }
                ratingsStart = strchr(ratingsStart + 1, ' '); // move to the next integer in the line
                if (!ratingsStart) break;                     // end of distribution ratings
            }
        }

        // grow the array if needed, then store the parsed word
        if (*lexiconSize >= capacity) {
            capacity *= 2;
            WordData* lexiconTemp = realloc(lexicon, capacity * sizeof(WordData));
            if (lexiconTemp == NULL) {
                perror("Memory reallocation failed");
                free(lexicon);
                fclose(file);
                exit(EXIT_FAILURE);
            }
            lexicon = lexiconTemp;
        }
        lexicon[*lexiconSize] = wordData;
        (*lexiconSize)++;
    }

    fclose(file);
    return lexicon;
}

// function to apply the exclamation-point intensifier boost
float isExclamation(const char* word) {
    int exclamationCount = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == '!') exclamationCount += 1;
    }

    // exclamation marks add a small boost to sentiment, increasing for 2 and >=3 marks
    if (exclamationCount == 1) return EXCLAMATION;
    else if (exclamationCount == 2) return EXCLAMATION + .01;
    else if (exclamationCount >= 3) return EXCLAMATION + .02;
    else return 1;
}

// function to remove punctuation from a word
void removePunctuation(char* word) {
    int i = 0, j = 0;
    while (word[i]) {
        if (isalpha(word[i])) { // keep alphabetic characters
            word[j++] = word[i];
        }
        i++;
    }
    word[j] = '\0'; // null-terminate the cleaned word
}

// function to search the lexicon for a word's score
float findWordScore(const char* word, WordData* lexicon, int lexiconSize) {
    for (int i = 0; i < lexiconSize; i++) {
        char wordLower[MAX_STRING_LENGTH] = {0};

        // copy and convert `word` to lowercase
        int wordLen = strnlen(word, MAX_STRING_LENGTH - 1);
        for (int j = 0; j < wordLen; j++) {
            wordLower[j] = tolower(word[j]);
        }
        wordLower[wordLen] = '\0';

        // compare the lowercase versions
        if (strcmp(wordLower, lexicon[i].word) == 0) {
            return lexicon[i].value1;
        }
    }
    return 0; // word not found in lexicon
}

// function to apply a sentiment intensifier boost for words like "very"
int isIntensifier(const char* word) {
    const char *intensifiers[] = {
        "absolutely", "completely", "extremely", "really", "so", "totally", "very",
        "particularly", "exceptionally", "incredibly", "remarkably",
        "ABSOLUTELY", "COMPLETELY", "EXTREMELY", "REALLY", "SO", "TOTALLY", "VERY",
        "PARTICULARLY", "EXCEPTIONALLY", "INCREDIBLY", "REMARKABLY"
    };
    int numIntensifiers = sizeof(intensifiers) / sizeof(intensifiers[0]);

    for (int i = 0; i < numIntensifiers; i++) {
        if (strcmp(word, intensifiers[i]) == 0) return 1;
    }
    return 0;
}

// function to apply negation
int isNegation(const char* word) {
    const char* negations[] = {
        "not", "isn't", "doesn't", "wasn't", "shouldn't", "won't", "cannot", "can't",
        "nor", "neither", "without", "lack", "missing",
        "NOT", "ISN'T", "DOESN'T", "WASN'T", "SHOULDN'T", "WON'T", "CANNOT", "CAN'T",
        "NOR", "NEITHER", "WITHOUT", "LACK", "MISSING"
    };
    int negationsLength = sizeof(negations) / sizeof(negations[0]);

    for (int i = 0; i < negationsLength; i++) {
        if (strcmp(word, negations[i]) == 0) return 1;
    }
    return 0;
}

// function to check whether a word is written in all caps (an intensity signal)
float isAllcaps(const char* word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isupper(word[i])) return 0;
    }
    return 1;
}

// function to calculate the compound sentiment score for a sentence, applying
// modifiers (negation, intensifiers, all-caps) to the following word
float calcCompound(const char* sentence, WordData* lexicon, const int lexiconSize) {
    int wordCount = 0;
    float totalScore = 0.0;
    int hasNegation = 0;
    int hasIntensifier = 0;
    int hasAllcaps = 0;

    char *sentenceCopy = strdup(sentence); // strdup allocates memory for sentence then copies 'sentence' there
    if (sentenceCopy == NULL) {
        perror("Memory allocation failed for sentence copy. Exiting the program.\n");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(sentenceCopy, " ");         // parse the sentence into words
    float wordScores[MAX_SENTENCE_LENGTH] = {0};     // scores for each word (0 if not in lexicon)

    while (token != NULL && wordCount < MAX_SENTENCE_LENGTH) {
        float wordScore = 1.0;
        wordScore *= isExclamation(token); // count exclamation marks before removing punctuation

        removePunctuation(token);
        wordScore *= findWordScore(token, lexicon, lexiconSize);

        // check if the current word is an intensifier or negation for the next word
        if (isIntensifier(token)) {
            hasIntensifier = 1;
            if (isAllcaps(token)) hasAllcaps = 1;
        } else if (isNegation(token)) {
            hasNegation = 1;
            if (isAllcaps(token)) hasAllcaps = 1;
        }

        if (wordScore != 0) { // word is in the lexicon
            // apply the all-caps modifier to the current word
            if (isAllcaps(token)) {
                wordScore *= ALLCAPS;
            }
            // if the previous word was an intensifier, apply it
            if (hasIntensifier) {
                if (hasAllcaps) {
                    wordScore += wordScore * INTENSIFIER * ALLCAPS;
                    hasAllcaps = 0;
                } else {
                    wordScore += wordScore * INTENSIFIER;
                }
                hasIntensifier = 0; // reset after applying
            }
            // otherwise, if the previous word was a negation, apply it
            else if (hasNegation) {
                if (hasAllcaps) {
                    wordScore += wordScore * NEGATION * ALLCAPS;
                    hasAllcaps = 0;
                } else {
                    wordScore += wordScore * NEGATION;
                }
                hasNegation = 0; // reset after applying
            }
            wordScores[wordCount] = wordScore; // store the modified score for the current word
        }

        token = strtok(NULL, " "); // move to the next word
        wordCount++;
    }

    // sum the modified word scores, then normalize the compound score to (-1, 1)
    float sumSq = 0.0;
    for (int i = 0; i < wordCount; i++) {
        totalScore += wordScores[i];
        sumSq += pow(wordScores[i], 2);
    }
    if (sumSq != 0) {
        totalScore /= sqrt(sumSq);
    }

    free(sentenceCopy);
    return totalScore;
}
