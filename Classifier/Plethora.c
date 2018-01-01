#include <stdio.h>
#include "classifier.h"
#include <string.h>

//this is responsible for calling the classifier file by invoking the starting method in that class
void classify(char names[100][20], int total, clenchType *types)
{
  //these are the variables that we need to output all of the percentages as neccessary
  int successValue = 0, i;
  int totalSuccessCnt = 0, ncCnt = 0, scCnt = 0, dcCnt = 0, chCnt = 0;
  int ncSuccessCnt = 0, scSuccessCnt = 0, dcSuccessCnt = 0, chSuccessCnt = 0;

  //loops through total number of different datasets
  for(i = 0; i < total; i++)
  {
    //so we call the classify begin function which returns true or false
    //true if it passed, false if it failed
    successValue = begin_function(names[i], types[i]);

    //this is the total incrementer for all passed events
    if(successValue)
      totalSuccessCnt++;

    //incrementer for passed events of type no clench
    if(types[i] == noClench)
    {
      ncCnt++;
      if(successValue)
        ncSuccessCnt++;
    }

    //incrementer for passed events of type single clench
    else if(types[i] == singleClench)
    {
      scCnt++;
      if(successValue)
        scSuccessCnt++;
    }

    //incrementer for the passed events of type double clench
    else if(types[i] == doubleClench)
    {
      dcCnt++;
      if(successValue)
        dcSuccessCnt++;
    }

    //incrementer for the passed events of type clench and hold
    else
    {
      chCnt++;
      if(successValue)
        chSuccessCnt++;
    }
  }

  //print all of the percentages
  if(total != 0)
    printf("Total Percentage Correct: %d%%\n", (totalSuccessCnt/total)*100);
  if(ncCnt != 0)
    printf("No Clench Success Rate: %d%%\n", (ncSuccessCnt/ncCnt)*100);
  if(scCnt != 0)
    printf("Single Clench Success Rate: %d%%\n", (scSuccessCnt/scCnt)*100);
  if(dcCnt != 0)
    printf("Double Clench Success Rate: %d%%\n", (dcSuccessCnt/dcCnt)*100);
  if(chCnt != 0)
    printf("Clench and Hold Success Rate: %d%%\n", (chSuccessCnt/chCnt)*100);
}

void readNames()
{
  //keeps all the names of the files that we want to read
  char names[100][20];
  clenchType types[100];
  int cnt = 0;

  //basically just read the in file names until thje user wants to end
  while(1)
  {
    //use these to store later data
    char temp[20];
    char temp2[20];

    //enter each individual file name
    printf("Enter the file name.\n");
    scanf("%s", &temp);


    //check tot see if the user is done
    int answer = strcmp(temp, "end");

    if(answer == 0)
      break;

    else
    {
      while(1)
      {
        //now for every file, have the user associate a type
        printf("This dataset has what type? (SC, DC, CH, NC)\n");
        scanf("%s", &temp2);

        //copy the file name
        strcpy(names[cnt], temp);

        //this checks the type and associates the correct enum to it
        if(strcmp(temp2, "SC") == 0)
        {
          types[cnt++] = singleClench;
          break;
        }

        else if(strcmp(temp2, "DC") == 0)
        {
          types[cnt++] = doubleClench;
          break;
        }

        else if(strcmp(temp2, "CH") == 0)
        {
          types[cnt++] = clenchHold;
          break;
        }

        else if(strcmp(temp2, "NC") == 0)
        {
          types[cnt++] = noClench;
          break;
        }

        else
          printf("The code you entered was incorrect, please use the exact nomenclature as listed in the question.\n");
      }
    }
  }

  //now we want to run the classifiy algorithm on each on
  classify(names, cnt, types);
}

int main()
{
  readNames();
  return 0;
}
