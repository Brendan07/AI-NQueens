
/*
 * File:   main.cpp
 * Author: j4-smith
 *N-Queens example in C
 * First Created on 25 April 2014, 18:42
 * Modified in light of student progress
 
 * Rewritten Oct 2015 to use more generic solution structures
 * and functions with NQueens-specific names that call the functions that modify the
 */


#include <stdio.h>
#include <stdlib.h>
#include "StructureDefinitions.h"
#include "SolutionListOperations.h"
#include "NQueensChecker.h"

#pragma warning(disable:4996)

typedef int bool;
#define true  1
#define false 0

//Variables workingCandidate, openList, closedList
candidateSolution workingCandidate;// this one will hold the soltion we arecurrently considering
candidateList  openList; // this list will store all the soltion we;ve created but not examined yet
candidateList closedList; // this is where we will store all the ones we're done with

int firstValueToAdd;

//************************ don't edit anything above this line***********************//



int main(int argc, const char * argv[])
{
    
    /* the next set of variables get used within our main function
     * but aren't declared globally becuase we don't want the other functions to change them inadvertently *///
    int indexOfSolutionWeAreLookingAt; //index in list of current solution being examined
    int currentRow; // used when we extend the working candidate
    bool goalReached = false; // used to indicate when to stop searching for new candidates
    int numRead=0;//used to read the inputs
    //start off by emptying the lists of candidate solutions
    CleanListsOfSolutionsToStart();
    CleanWorkingCandidate();
    
    /* So now let's start by creating our first solution
     * which we do by filling the values into the variable we declared as the workingCandidate
     * We'll begin by putting the first queen into column ), or specified from the command line
     */
    firstValueToAdd = 0;
    if(argc==2)
      {
          numRead=sscanf(argv[1],"%d",&firstValueToAdd);
          if (numRead != 1 || firstValueToAdd >=N || firstValueToAdd <0)
          {
#ifdef ONDEWIS
              extern void printInvalidInputFeedbackAndExit(void);
              printInvalidInputFeedbackAndExit();
#else
              PrintThisMessageAndExit("Invalid Input");
#endif
          }
      }
	   
    // we are using a constructive solution so first we have to add a queen.
    // There is a different function to move a queen.
    AddQueenToNextRowInColumn(firstValueToAdd);
    
    //this shows you how to print the current working cnadidae if you need to for debugging
    PrintWorkingCandidate();
    //this is the functgion that tests whether a partial solution is feasible or not
    CalculateNumberOfVulnerableQueensForWorkingCandidate(); //should score zero because there is only one queen :)
   
    //and we can put this as our first item in the list to start the process
    AddWorkingCandidateToOpenList();

    
    
    
    ///**********DONT CHANGE ANYTHING ABOVE THIS LINE
    
    //**** YOUR DEPTH_FIRST SEARCH CODE GOES HERE ***////
    
    int column;
    
    while (goalReached == false)
    {
        if (workingCandidate.score == 0)
        {
            PrintWorkingCandidate();
            
            if (workingCandidate.size == N)
            {
                goalReached = true;
                PrintWorkingCandidate();
                PrintFinalSolutionAndExit();
            }
            else
            {
                AddQueenToNextRowInColumn(0);
                
                for (column = 0; column < N; column++)
                {
                    MoveQueenInRowToNewCol(workingCandidate.size - 1, column);
                    AddWorkingCandidateToOpenList();
                }
            }
        }
        CopySolutionFromOpenListIntoWorkingCandidate(openList.size - 1);
        RemoveSolutionFromOpenList(openList.size - 1);
        CalculateNumberOfVulnerableQueensForWorkingCandidate();
        
    }
    
///**** YOU MUST CALL  PrintFinalSolutionAndExit() to get a mark from the system
    
    
    PrintFinalSolutionAndExit();
    return 0;
}

