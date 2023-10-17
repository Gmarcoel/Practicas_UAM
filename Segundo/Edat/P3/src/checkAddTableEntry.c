/*
// Created by roberto on 30/8/20.
*/
#include "tester.h"

void checkAddTableEntry(const char * tableName,const char * indexName)
/**
 *  check AddTableEntry
 */
{
    bool result;
    int nodeIDOrDataOffset;
    Book booktest;



    createTestDataFile(tableName);
    createTestIndexFile(indexName);



    /* 1) add existing book should complain*/
    result = addTableEntry(&(b[0]), tableName,indexName);
    if (result){
        fprintf(stderr,
                "Error in addTableEntry, inserted existing book %s",
                b[0].book_id);
        exit(EXIT_FAILURE);
    }
    /* add a new book using a existing deleted one*/
    booktest.title = (char*)malloc(64*sizeof(char));
    strcpy(booktest.title,"Titulo");
    strcpy(booktest.book_id,"MAR4");
    booktest.title_len = 6;
    
    result = addTableEntry(&booktest,tableName,indexName);
    printf("-----tree adding VAR2-------\n");
    printTree(4, indexName);
    findKey(booktest.book_id, indexName, &nodeIDOrDataOffset);
    if (nodeIDOrDataOffset!=71){
        fprintf(stderr,
                "Error in addTableEntry, inserted offset should be 71"
                " but I get %d", nodeIDOrDataOffset);
        exit(EXIT_FAILURE);
    }
    
    /*add a new book at the end of file*/

    strcpy(booktest.title,"Este es un titulo muy largo");
    strcpy(booktest.book_id,"ZAR4");
    booktest.title_len = 27;
    result = addTableEntry(&booktest,tableName,indexName);
    findKey(booktest.book_id, indexName, &nodeIDOrDataOffset);
    if (nodeIDOrDataOffset!=190){
        fprintf(stderr,
                "Error in addTableEntry, inserted offset should be 190"
                " but I get %d", nodeIDOrDataOffset);
        exit(EXIT_FAILURE);
    }
    printTree(4, indexName);
  printf("* checkAddTableEntry: OK\n");
  free(booktest.title);
}


