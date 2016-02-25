/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

NODE *table[HASHBASE];
unsigned int table_size = 0;

unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c;

    for (c = *str; c != '\0'; c = *(str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % HASHBASE;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    unsigned int word_len = strlen(word);
    char* lower_word = malloc(word_len + 1);
    for(int i = 0; i < word_len; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    lower_word[word_len] = '\0';
    unsigned long hash_code = hash(lower_word);
    NODE *list = table[hash_code];
    if(list == NULL)
    {
        free(lower_word);
        return false;
    }
    bool res = contains(list, lower_word);
    free(lower_word);
    return res;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    for(int i = 0; i < HASHBASE; i++)
    {
        table[i] = NULL;
    }
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        printf("Can't open dictionary file %s\n", dictionary);
        return false;
    }
    char word[LENGTH+1];
    int index = 0;
    for(int c = fgetc(inptr); c != EOF; c = fgetc(inptr))
    {
        if(c != '\n')
        {
            word[index++] = c;
        } else
        {
            word[index] = '\0';
            //insert_hash_table(word);
            index = 0;
        }
    }
    fclose(inptr);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return table_size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0; i < HASHBASE; i++)
    {
        if(table[i] != NULL)
        {
            free_list(table[i]);
        }
    }
    return true;
}

void insert_hash_table(char *word)
{
    table_size++;
    unsigned long hash_code = hash(word);
    NODE *list = table[hash_code];
    if(list == NULL)
    {
        list = new_node();
        table[hash_code] = list;
    }
    insert(list, word);
}

NODE *new_node(void)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        return NULL;
    }
    node->ele = NULL;
    node->next = NULL;
    return node;
}

void insert(NODE *list, char *character)
{
    if(list->ele == NULL)
    {
        list->ele = (char *)malloc(strlen(character) + 1);
        if (list->ele == NULL)
        {
            return;
        }
        strcpy(list->ele, character);
    } else if (list->next == NULL)
    {
        NODE *n = new_node();
        list->next = n;
        insert(list->next,character);
    } else
    {
        insert(list->next,character);
    }
}

bool contains(NODE *list, const char *character)
{
    if(list->ele == NULL)
    {
        return false;
    } else if (strcmp(list->ele, character) == 0) 
    {
        return true;
    } else if (list-> next == NULL)
    {
        return false;
    } else
    {
        return contains(list->next,character);
    }
}

void free_list(NODE *list)
{
    if (list->next != NULL) 
    {
        free_list(list->next);
    }
    if (list->ele != NULL)
    {
        free(list->ele);
    }
    free(list);
}