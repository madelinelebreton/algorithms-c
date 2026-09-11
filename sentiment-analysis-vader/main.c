// main.c
// written by Madeline with help from ChatGPT
// this file contains the main() function to run test cases and print results

#include "utility.h"

int main() {
    // test sentences (drawn from the original VADER paper's examples)
    const char* testSentences[] = {
        "VADER is smart, handsome, and funny.",
        "VADER is smart, handsome, and funny!",
        "VADER is very smart, handsome, and funny.",
        "VADER is VERY SMART, handsome, and FUNNY.",
        "VADER is VERY SMART, handsome, and FUNNY!!!",
        "VADER is VERY SMART, uber handsome, and FRIGGIN FUNNY!!!",
        "VADER is not smart, handsome, nor funny.",
        "At least it isn't a horrible book.",
        "The plot was good, but the characters are uncompelling and the dialog is not great.",
        "Make sure you :) or :D today!",
        "Not bad at all"
    };
    int numSentences = sizeof(testSentences) / sizeof(testSentences[0]);

    const char* filename = "vader_lexicon.txt"; // lexicon filename
    int lexiconSize;                            // set when the lexicon is loaded from file

    WordData* lexicon = loadLexicon(filename, &lexiconSize);
    if (lexicon == NULL) {
        perror("Error loading lexicon\n");
        return 1;
    }

    for (int i = 0; i < numSentences; i++) {
        printf("Analyzing sentence: %s\n", testSentences[i]);
        double compoundScore = calcCompound(testSentences[i], lexicon, lexiconSize);
        printf("Compound Score: %.4f\n\n", compoundScore);
    }

    free(lexicon);
    return 0;
}
