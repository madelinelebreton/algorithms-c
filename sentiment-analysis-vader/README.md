# VADER Sentiment Analysis, Implemented from Scratch in C
My implementation of [VADER](https://github.com/cjhutto/vaderSentiment)
(Valence Aware Dictionary and sEntiment Reasoner) — a lexicon- and rule-based sentiment
analysis method. Rather than calling an existing sentiment analysis library, I
parsed VADER's lexicon directly and reimplemented its scoring rules: intensifiers
("very"), negation ("not"), punctuation and capitalization boosts, and compound score
normalization.

## What's here
- **`vaderSentiment.c`**: loads the VADER lexicon into memory and scores sentences:
  tokenizing text, looking up each word's valence, and applying VADER's modifier
  rules (negation, intensifiers, exclamation points, ALL CAPS) before normalizing
  to a compound score in [-1, 1].
- **`utility.h`**: shared structures, constants, and function prototypes.
- **`main.c`** — runs the scorer against a set of test sentences (the same examples
  used in the original VADER paper) and prints each compound score.
- **`Makefile`**: builds the `vaderSentiment` executable.

## How it works
Each word in a sentence is looked up in the VADER lexicon for a base valence score.
That score is then adjusted based on context:
- **Negation** ("not", "isn't", "without", ...) flips and dampens the following word's
  score.
- **Intensifiers** ("very", "extremely", "totally", ...) boost the following word's
  score.
- **ALL CAPS** and **exclamation points** add an additional emphasis boost.

The per-word scores are summed and normalized by the square root of the sum of
squares, producing a compound score bounded between -1 (most negative) and +1 (most
positive).

##Running it

This implementation needs VADER's lexicon file, `vader_lexicon.txt`, in the working
directory at runtime. It isn't included here since it's a third-party dataset:
(MIT licensed) from the
[original VADER repo](https://github.com/cjhutto/vaderSentiment/blob/master/vaderSentiment/vader_lexicon.txt).

```bash
make
./vaderSentiment
```
