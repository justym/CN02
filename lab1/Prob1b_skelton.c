#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Caesar Decryption */
char *CaesarDecrypt(int, char *);
/* BruteForceAttack */
void BruteForceAttack(char *, char *);

int isAlphabet(char);

int main()
{

    char ciphertext[1024];
    char keyword[1024];

    printf("Input plain text: ");
    scanf("%[^\n]%*c", ciphertext);
    printf("Input keyword: ");
    scanf("%[^\n]%*c", keyword);
    /*
    Input ciphertext and keyword. 
    If keyword is not specified (no keyword), press ENTER
    */

    BruteForceAttack(ciphertext, keyword);
    return 0;
}

char *CaesarDecrypt(int key, char *ciphertext)
{
    int length = strlen(ciphertext);
    char *plain = (char *)malloc(length);

    for (int i = 0; i < length; i++)
    {
        int ok = isAlphabet(ciphertext[i]);

        //Decrypt
        if (ok == 1 && isupper(ciphertext[i]))
        {
            plain[i] = (char)((ciphertext[i] - 'Z' - key) % 26) + 'Z';
        }
        else if (ok == 1 && !isupper(ciphertext[i]))
        {
            plain[i] = (char)((ciphertext[i] - 'z' - key) % 26) + 'z';
        }
        else
        {
            plain[i] = ciphertext[i];
        }
    }

    return plain;
}

void BruteForceAttack(char *ciphertext, char *keyword)
{
    //If no keyword, List up the expect value
    //If there is keyword, Search the expected value using keywords
    if (keyword[0] == '\0' || keyword == NULL)
    {
        for (int i = 0; i < 26; i++)
        {
            char *str = CaesarDecrypt(i, ciphertext);
            printf("Key %d: %s\n", i, str);
            free(str);
        }
    }
    else
    {
        int count = 0;

        for (int i = 0; i < 26; i++)
        {
            char *str = CaesarDecrypt(i, ciphertext);

            //Check "str" is contains substring(keywords)
            //If Yes, print the value and increment count
            //If Not, continue the loops
            if (strstr(str, keyword) != NULL)
            {
                printf("Key %d: %s\n", i, str);
                count++;
            }
            else
            {
                continue;
            }

            free(str);
        }

        if (count == 0)
        {
            printf("There is no decryption for keyword %s\n", keyword);
        }
    }
}

int isAlphabet(char c)
{
    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
        return 1;
    return 0;
}
