#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<string.h>

#define MAX_TOKENS 50

using namespace std;

/* Check if 'c' is a delimitor as specified in 'delim' string */
bool isDelim(const char c, const char *delim)
{
    int i = 0;
    int len = strlen(delim);

    while (i < len)
    {
        if (c == delim[i])
        {
            return true;
        }
        i++;
    }

    return false;
}

/* Tokenize string 'str' on the basis of 'delim' delimitors. Returns
   a vector of tokens */
vector<char *> tokenizeString(const char *str, const char *delim)
{
    vector<char *> tokens;

    int i = 0;
    int j = 0;
    int len = strlen(str);
    int tokenCount = 0;
    char *token = (char *)malloc(len);
    bool prevDelim = false;
    
    while (1)
    {
        if (i == len)
        {
            /* Reached end of string */
            token[j] = '\0'; // Append 0 to mark end.
            char *token_tmp = (char *)malloc(strlen(token));
            strcpy(token_tmp, token);
            memset(token, 0, sizeof(token));

            /* This is a valid token only if its length is > 0 */
            if (strlen(token_tmp) > 0)
            {
                tokens.push_back(token_tmp);
                tokenCount++;
            }

            /* Free the memory used by token */
            if (strlen(token))
            {
                free(token);
                token = NULL;
            }

            /* All tokens have been saved, break */
            break;
        }
        else if (isDelim(str[i], delim))
        {
            token[j] = '\0'; // Append 0 to mark end.
            char *token_tmp = (char *)malloc(strlen(token));
            strcpy(token_tmp, token);
            memset(token, 0, sizeof(token));

            /* This is a valid token only if its length is > 0 */
            if (strlen(token_tmp) > 0)
            {
                tokens.push_back(token_tmp);
                tokenCount++;
                j = 0;
            }

            prevDelim = true;
        }
        else
        {
            token[j] = str[i];
            j++;
            prevDelim = false;
        }

        i++;
    }/* End of while loop */
    
    return tokens;
}

/* M A I N */
int main()
{
    const char *str = "* * * * This   i *****, d****,is the, * ,tokenizer!   *** * ehllo **";
    //const char *str = "* * *This    J**";
    //const char *str = " Welcome    to C++   pro* gramming** **";
    const char *delim = ",* ";
    vector<char *> tokens;

    printf("String      :  %s\n", str);
    printf("Delimitors  : '%s'\n\n", delim);

    tokens = tokenizeString(str, delim);

    int i = 0;
    int totalTokens = tokens.size();
    while (i < totalTokens)
    {
        printf("Token [%d]: %s\n", i+1, tokens[i]);
        free(tokens[i]);
        tokens[i] = NULL;
        i++;
    }


    return 0;
}
