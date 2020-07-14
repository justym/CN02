#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Caesar Encryption */
char *CaesarEncrypt(int, char *);
/* Caesar Decryption */
char *CaesarDecrypt(int, char *);

int isAlphabet(char);

int main(int argc, char *argv[])
{
    char plaintext[1024];
    char ciphertext[1024];
    char decrypttext[1024];

    int key;

    if (argc <= 1)
    {
        printf("Please add arguments e or d\n");
        printf("e: encrypt function\n");
        printf("d: decrypt function\n");
        return 0;
    }

    //Input plaintex and key.
    //Check the validity of key (key must be an interger number between 0 ~ 25)
    if (*argv[1] == 'e')
    {
        printf("Input plain text: ");
        scanf("%[^\n]%*c", plaintext);
        printf("Input key (an interger from 1 to 25): ");
        scanf("%d", &key);

        //Perform Caesar Encryption: CaesarEncrypt(key, plaintext) and print out the ciphertext*/
        char *buff = CaesarEncrypt(key, plaintext);
        strcpy(ciphertext, buff);
        printf("Cipher Text: %s\n", ciphertext);
    }
    else if (*argv[1] == 'd')
    {
        //Perform Caesar Decryption: CaesarDecrypt(key, ciphertext) and print out the decryted ciphertext (decrypttext)
        printf("Input cipher text: ");
        scanf("%[^\n]%*c", ciphertext);
        printf("Input key (an interger from 1 to 25): ");
        scanf("%d", &key);
        char *buff = CaesarDecrypt(key, ciphertext);
        strcpy(decrypttext, buff);
        printf("Decrypted Text: %s\n", decrypttext);
    }

    return 0;
}

char *CaesarEncrypt(int key, char *plaintext)
{
    int length = strlen(plaintext);
    char *cipher = (char *)malloc(length);

    for (int i = 0; i < length; ++i)
    {
        int ok = isAlphabet(plaintext[i]);

        //Encrypt Alphabet into cipher
        if (ok == 1 && isupper(plaintext[i]))
        {
            cipher[i] = (char)((plaintext[i] - 'A' + key) % 26) + 'A';
        }
        else if (ok == 1 && !isupper(plaintext[i]))
        {
            cipher[i] = (char)((plaintext[i] - 'a' + key) % 26) + 'a';
        }
        else
        {
            cipher[i] = plaintext[i];
        }
    }

    return cipher;
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

int isAlphabet(char c)
{
    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
        return 1;
    return 0;
}
