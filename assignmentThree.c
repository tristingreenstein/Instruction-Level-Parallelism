#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define structure for instruction containing fields for instruction string,
destination register, 2 source registers
and a variable as pointer to structure for creating a dynamic array of instructions */
struct node
{
   char instr_string[13];
   int dest_reg;
   int srcOne;
   int srcTwo;
} *instr_set = NULL;

typedef struct node instr_type;
/* global var's */
int num_instr=0;//total number of instructions

/*************************************************************/
void option_one()
{
    /* Declare local variables*/
    int i;
    int loop = 0;
    /* Prompt for total number of instructions */
    while(loop==0)
    {
       printf("Enter total number of instructions: ");
       scanf("%d",&num_instr);
       if(num_instr>-1)
       {
           break;
       }
       printf("\nSorry that value is not accepted, try again.");
    }
    /* Allocate memory to hold a set of instructions */
    instr_set = (instr_type*)malloc((3*num_instr+1)*sizeof(instr_type));
    /* Initialize instruction 0's destination register to -1 to
    prevent false RAW dependency w/ instruction 2 */
    instr_set[0].dest_reg = -1;
    /* For each instruction, prompt for user input and read instruction as a string
    and store at proper field of appropriate index within dynamic array of instructions */
    for(i=1;i<= num_instr;i++)
    {
        scanf("%s",instr_set[i].instr_string);
        instr_set[i].dest_reg = instr_set[i].instr_string[5]-'0';
        instr_set[i].srcOne = instr_set[i].instr_string[8]-'0';
        instr_set[i].srcTwo = instr_set[i].instr_string[11]-'0';
    }
    return;
}

/*****************************************************/
void option_two()
{
    /* Declare local variables */
    int i, j, n;
    int dependent_delay;
    int overlap=0;
    int tabbing=0;
    int total_cycles;
    /* For each instruction i from 2 to total number of instructions
	initialize delay as 0 and check for dependency
	between instruction (i-2) and i, as well as between instruction (i-1) and i */
    for(i=2;i<=num_instr;i++)
    {
        dependent_delay=0;
        if((instr_set[i-2].dest_reg==instr_set[i].srcOne)||(instr_set[i-2].dest_reg==instr_set[i].srcTwo))
        {
            if(overlap==0)
            {
                dependent_delay=1;
                overlap=1;
            }
            else
            {
                dependent_delay=0;
                overlap=0;
            }
        }
        else
        {
            dependent_delay=0;
            overlap=0;
        }
        if((instr_set[i-1].dest_reg==instr_set[i].srcOne)||(instr_set[i-1].dest_reg==instr_set[i].srcTwo))
        {
                dependent_delay=2;
                overlap=1;
        }
        /* If dependency, add NOPs appropriately by shifting remaining instructions down
        and set delay & flag to check for possible overlap between dependent instructions,
        and increase total number of instructions appropriately*/
        if(dependent_delay==2)
        {
            for(n=num_instr+2;n>=i+2;n--)
            {
                instr_set[n]=instr_set[n-2];
            }
            strcpy(instr_set[i].instr_string,"NOP         ");
            strcpy(instr_set[i+1].instr_string,"NOP         ");
            num_instr+=2;
            i+=2;
        }
        if(dependent_delay==1)
        {
            for(n=num_instr+1;n>=i+1;n--)
            {
                instr_set[n]=instr_set[n-1];
            }
            strcpy(instr_set[i].instr_string,"NOP         ");
            num_instr+=1;
            i+=1;
        }
    }/* end for-loop */

    /* Calculate and print total cycles (include overhead from instruction 1*/
    printf("\nTotal Cycles: %d",num_instr+4);
    /* Print Instruction string & Gantt chart
    by tabbing each instruction's cycles appropriately
    */
    printf("\n");
    for(i=1;i<num_instr+1;i++)
    {
        printf("%s:\t",instr_set[i].instr_string);
        for(j=1;j<=tabbing;j++)
        {
            printf("\t");
        }
        printf("IF\tID\tEX\tME\tWB\n");
        tabbing++;
    }

    return;
}

/****************************************************************/
int main()
{
      /* declare local var's */
      int user_input;
      int loop = 0;
      /* until program exits, print menu, select choice via switch statement and call appropriate function*/
      while(loop == 0)
      {
         printf("\nInstruction-level parallelism");
         printf("\n-----------------------------");
         printf("\n1) Enter instructions\n2) Calculate total cycle count on a 5-stage pipeline processer\n3) Quit program");
         printf("\nEnter Selection: ");
         scanf("%d",&user_input);
         if(user_input == 1)
         {
            option_one();
         }
         if(user_input == 2)
         {
            option_two();
         }
         if(user_input == 3)
         {
            break;
         }
         if(user_input != 1 && user_input != 2 && user_input != 3)
         {
            printf("\n Sorry, your input is invalid, please try again.");
         }
      }
      return 1;
}
