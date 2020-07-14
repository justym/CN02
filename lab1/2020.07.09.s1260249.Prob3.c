#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct incidence_pair
{
    char c[26];      // Letter in the cipher text
    double freq[26]; // Incidence percentage of each letter
};

struct pair
{
    char c;
    int count;
    double freq;
};

struct incidence_pair getIncidence(char *);        // Computing a histogram of the incidence each letter (ignoring all non alphabet characters)
char *monoalphabetic_substitution(char *, char *); // Takes a partial mono-alphabetic substitution (subs)  and a ciphertext and returns a potential plaintext
double getAvg(int, int);
int isAlphabet(char);
int indexOfAlphabet(char);
void initPairs(struct pair *, int);
char findKey(char, char *);

int main(int argc, char *argv[])
{

    char ciphertext[1024] = "ztmn pxtne cfa peqef kecnp cjt tmn zcwsenp ontmjsw ztnws tf wsvp xtfwvfefw, c feb fcwvtf, xtfxevqea vf gvoenwk, cfa aeavxcwea wt wse rntrtpvwvtf wscw cgg lef cne xnecwea eymcg";
    char ciphertextTest[1024] = "rnc qwr fv uwmrmgb eczwcr hceeqbce mgrcjjmbmajc rf rnfec unf qwc mg dfeeceemfg fv rnc kco qgx tgmgrcjjmbmajc rf qjj frncwe nqe accg ertxmcx vfw zcgrtwmce. rnc tecvtjgcee fv etzn hceeqbce, cedczmqjjo mg rmhc fv uqw, me faymfte ";
    char plaintext[1024] = "";
    char *subs = argv[1];

    struct incidence_pair ip = getIncidence(ciphertext);

    if (argc != 2)
    {
        printf("Not enough or too many arguments!\n");
        exit(1);
    }
    if (strcmp(subs, "") == 0)
    {
        for (int i = 0; i < 26; i++)
            printf("%c:%5f\n", ip.c[i], ip.freq[i]);
    }

    char *buff = monoalphabetic_substitution(ciphertext, subs);
    strcpy(plaintext, buff);
    printf("Potential Plaintext: %s\n", plaintext);

    return 0;
}

struct incidence_pair getIncidence(char *ciphertext)
{
    struct incidence_pair results;

    int indexAlphabet;
    struct pair pairs[26];
    int letterLength = 0;

    initPairs(pairs, 26);
    for (int i = 0; i < strlen(ciphertext); i++)
    {
        indexAlphabet = indexOfAlphabet(ciphertext[i]);
        if (indexAlphabet > -1)
        {
            pairs[indexAlphabet].count++;
            letterLength++;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        pairs[i].freq = getAvg(pairs[i].count, letterLength);
    }

    for (int i = 0; i < 26; i++)
    {
        int max = -1;
        int index = -1;
        for (int j = 0; j < 26; j++)
        {
            if (max < pairs[j].count)
            {
                max = pairs[j].count;
                index = j;
            }
        }
        results.c[i] = pairs[index].c;
        results.freq[i] = pairs[index].freq;
        pairs[index].count = -100; //this means already checked this letter out
    }

    return results;
}

char *monoalphabetic_substitution(char *ciphertext, char *subs)
{
    int length = strlen(ciphertext);
    char *plaintext = (char *)malloc(length);

    for (int i = 0; i < length; i++)
    {
        //char tmp = ciphertext[i];
        if (isAlphabet(ciphertext[i]) == 1)
        {
            plaintext[i] = findKey(ciphertext[i], subs);
        }
        else if (isAlphabet(ciphertext[i]) != 1)
        {
            plaintext[i] = ciphertext[i];
        }
    }
    return plaintext;
}

double getAvg(int count, int length)
{
    double c = (double)count;
    double l = (double)length;

    return c / l;
}

int isAlphabet(char c)
{
    if ('a' <= c && c <= 'z')
        return 1;
    return -1;
}

int indexOfAlphabet(char c)
{
    if (isAlphabet(c) > 0)
    {
        return c - 'a';
    }
    else
    {
        return -1;
    }
}

void initPairs(struct pair *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i].c = (char)('a' + i);
        array[i].count = 0;
        array[i].freq = 0;
    }
}

char findKey(char c, char *subs)
{
    char m = (int)(c - 'a');
    char check = subs[m];

    for (int i = 0; i < 26; i++)
    {
        if (isAlphabet(check) && check != '_')
        {
            return check;
        }
    }

    return toupper(c);
}