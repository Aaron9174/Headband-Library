#include "classifier.h"
#include <stdio.h>
// void getInputFileName(char *input){
//   printf("Please enter a file name for the dataset.\n");
//   scanf("%s", input);
// }

 int performClassification(int time_elapsed, int time_threshold, int peak_num, clenchType type)
{
  //all points below threshold
  if(time_elapsed == 0)
  {
    printf("No recorded data above the threshold.\n");
    if(type == noClench)
      return 1;
    else
      return 0;
  }
  //points above threshold, but for short periood indicates a single clench
  else if(time_elapsed < time_threshold)
  {
    printf("This is a single clench\n");
    if(type == singleClench)
      return 1;
    else
      return 0;
  }
  //otherwise we are in the case of double clench vs a clench and hold
  else
  {
    if(peak_num == 1)
    {
      printf("This is a clench and hold\n");
      if(type == clenchHold)
        return 1;
      else
        return 0;
    }
    else if(peak_num == 2)
    {
      printf("This is a double clench\n");
      if(type == doubleClench)
        return 1;
      else
        return 0;
    }
    else
    {
      printf("Unclassifiable\n");
      return -1;
    }
  }

}

int performReadings(int threshold, int time_threshold, FILE *file, clenchType type)
{
  //we want to read in data until we hit the end of the file
  int data = -1;
  int time_elapsed = 0;
  int data_temp = data;
  int peak_num = 0;
  int decreasing_seq = 0;

  // we will loop through the data, find peaks, and measure time
  while(fscanf(file, "%d", &data) != EOF)
  {
    //this gives use the length of time above the threshold above the data point, however
    //we will use the implementation that is curently resides in the arduino code

    if(data >= threshold) {
      time_elapsed++;
    }

    //now we check for peaks
    //there are a couple of implentations that we could go with, but we will use the increasing
    //and decreasing sequence with a match of exactly two peaks (no more or less)
    if(data_temp > threshold)
    {
      //this indicates a decreasing sequence of two numbers
      if(data_temp < data && !decreasing_seq)
      {
        peak_num++;
        decreasing_seq = 1;
      }

      //this ensures we do not double count an already counting decreasing sequence
      if(data_temp > data)
          decreasing_seq = 0;
    }


    data_temp = data;
  }

  return performClassification(time_elapsed, time_threshold, peak_num, type);
}

int begin_function(char *input_name, clenchType type) {
  //these are the variables that we need
  FILE *file;
  char input[10];
  int threshold = 18;
  int time_threshold = 4;
  int answer;

  //here is the file construction
  file = fopen(input_name, "r");

  //check to make sure we have opened the file, in this case we haven't
  if(file == NULL)
  {
    printf("The file was not found. Please make sure the file is the same directory, and has the correct name and extension.\n");
    return 0;
  }

  //we have opened the file correctly
  else {
    answer = performReadings(threshold, time_threshold, file, type);
  }

  fclose(file);

  return answer;
}
