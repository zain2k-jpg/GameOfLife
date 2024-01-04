/* Name: MUHAMMAD ZAIN
   Roll no. 19I-0414
   Section: E    
   PF Semester Project */

#include <iostream>
#include <fstream>
using namespace std;

/*INITIALIZATION AND DECLARATION OF VARIABLES*/

int x, y, NumOfGenerations, NumOfCells=0, Generation=0, cells=0;
const int RowsOfGrid = 20, ColumnsOfGrid = 20; 

/*
     x- represents row-coordinates
     y - represents column-coordinates
     NumOfGenerations - represents the number of generation till which the game will continue
     NumOfCells - represents the initial number of living cells with which the game will begin
     Generation - this will act as a Counter which will increase each time the next generation comes
     cells - this will act as a Counter to count and output the number of cells in the final generation
     RowsOfGrid - the number of Rows in our grid
     ColumnsOfGrid - the number of Columns in our grid 
*/

char Grid[RowsOfGrid][ColumnsOfGrid], secArray[RowsOfGrid][ColumnsOfGrid], neiArray[RowsOfGrid][ColumnsOfGrid], answer ; 

/*
     Grid[][] - the array which will give the output of our whole grid with both living and dead cells in each generation
     secArray[][] - contains coordinates of living cells and helps in updating our grid
     neiArray - contains the coordinates of the dead neighbours of our living cells
     answer - it will tell whether to go to the next generation or start a continuous show of generations
*/



/*   FUNCTIONS THAT WILL BE USED   */


/*1. InputFromFile() - will take the input of No. of generations, 
     No. of initial living cells and their coordinates from file    */
void InputFromFile()    
{
     fstream fileReading;
  
     fileReading.open("inputFAN.txt",ios::in); 
     fileReading >> NumOfGenerations;                    /*Taking input of number of generations from file*/
     fileReading >> NumOfCells;                          /*Taking input of number of living cells of gen 0 from file*/
  
     for (int i = 0; i < NumOfCells; i++)         
	                                              /*Taking input of coordinates of gen 0 from file*/
	 {                 
         fileReading >> x;   
         fileReading >> y; 
         Grid[x][y] = 1;                           /*here "1" means living*/
     }
     fileReading.close();
}

/*2. MakingGrid() - This will allow us to print the initial grid 
    as well as the grids to come    */
void MakingGrid(char Grid[][ColumnsOfGrid], int RowsOfGrid, int ColumnsOfGrid) 
{
	
    for (x = 0; x < RowsOfGrid ; x++)                   /* Searching for Living Cells */
	{
        for (y = 0; y < ColumnsOfGrid ; y++)
	    {
             if (Grid[x][y] == 1) 
			 {
                  cout << "*";                    /* "*" represents living cells */
             } 
	         else 
			 {
                  cout << ".";                    /* "." represents dead cells  */
             }
        }
    cout <<"\n";
    }

}

/*3. CountingLiveNeighbours() - will count live cells adjacent to each cell by using a counter.
     The counter will increase by one every time a living neighbour is found. This live neighbour
	 count will decide the future of each cell.   */
void CountingLiveNeighbours(char Grid[][ColumnsOfGrid], int x, int y, int & Count) 
{
     if (Grid[x][y+1]==1)                         /*Checking Neighbour to the right*/
     
          Count++;
     
     if (Grid[x][y-1]==1)                         /*Checking Neighbour to the left*/
     
          Count++; 
     
     if (Grid[x+1][y+1]==1)                       /*Checking Neighbour to the bottom-right*/
     
          Count++; 
     
     if (Grid[x-1][y+1]==1)                       /*Checking Neighbour to top-right*/
     
          Count++; 
     
     if (Grid[x+1][y-1]==1)                       /*Checking Neighbour to the bottom-left*/
     
          Count++; 
     
     if (Grid[x+1][y]==1)                         /*Checking Neighbour to the bottom*/
      
          Count++; 
     
     if (Grid[x-1][y]==1)                         /*Checking Neighbour to the top*/
     
          Count++; 
     
     if (Grid[x-1][y-1]==1)                       /*Checking Neighbour to the top-left*/
     
          Count++; 
        
}
/*4. CellPropogation() - will determine the status of cell i.e whether it 
     is going to die, become alive or stay alive.     */
void CellPropogation(char Grid[][ColumnsOfGrid], int x, int y, int Count) 
{
     if (Grid[x][y]==1 && (Count==3 || Count==2))  
      
         secArray[x][y]=1;                        /*1 = living...remains alive due to having 2 or 3 live neighbours*/
     
     if (Grid[x][y]==0 && Count==3) 
      
         secArray[x][y] = 1;                      /*1 = living...becomes alive due to 3 live neighbours*/
     
     if (Grid[x][y]==1 && Count<2) 
      
         secArray[x][y]=0;                        /*0 = death...dies due to underpopulation*/
     
     if (Grid[x][y]==1 && Count>3) 
     
         secArray[x][y]=0;                        /*0 = death...dies due to overcrowding*/
     
}

/*5. PuttingDeadNeighboursInNeiArray() - checks if a neighbour of a living cell is dead
     and then places it in neiArray without duplication */
void PuttingDeadNeighboursInNeiArray()
{
      int duplication=0;
      int g=0, h=0;
      for (x=0; x<RowsOfGrid ; x++) 
	  {
          for (y=0; y<ColumnsOfGrid ; y++)
	      {
             	if ((Grid[x-1][y-1]!=1)&&(Grid[x][y]==1)&&(duplication<1))    
	            {/*this condition will only allow a non-living cell with a living neighbour and zero duplication to ener the nei-array*/
                     neiArray[g][h]=Grid[x-1][y-1];
                     g++;
                     h++;
                     duplication++;                /*check to avoid duplication*/
                }     
                if ((Grid[x + 1][y + 1] != 1) && (Grid[x][y]==1)&&(duplication<1)) 
                {/*this condition will only allow a non-living cell with a living neighbour and zero duplication to ener the nei-array*/
                     neiArray[g][h]=Grid[x + 1][y + 1];
                     g++;
                     h++;
                     duplication++;                /*check to avoid duplication*/
                }
                if ((Grid[x - 1][y + 1] != 1)&& (Grid[x][y]==1)&&(duplication<1))
                {/*this condition will only allow a non-living cell with a living neighbour and zero duplication to ener the nei-array*/
                     neiArray[g][h]=Grid[x - 1][y + 1];
                     g++;
                     h++;
                     duplication++;                /*check to avoid duplication*/
                }
                if ((Grid[x + 1][y - 1] != 1)&& (Grid[x][y]==1)&&(duplication<1)) 
                {/*this condition will only allow a non-living cell with a living neighbour and zero duplication to ener the nei-array*/
                     neiArray[g][h]=Grid[x + 1][y - 1];
                     g++;
                     h++;
                     duplication++;                /*check to avoid duplication*/
                }
                if ((Grid[x - 1][y] != 1)&& (Grid[x][y]==1)&&(duplication<1))
                {/*this condition will only allow a non-living cell with a living neighbour and zero duplication to ener the nei-array*/
                     neiArray[g][h]=Grid[x - 1][y];
                     g++;
                     h++;
                     duplication++;                /*check to avoid duplication*/
                }
                if ((Grid[x + 1][y] != 1)&& (Grid[x][y]==1)&&(duplication<1))
                {/*this condition will only allow a non-living cell with a living neighbour and zero duplication to ener the nei-array*/
                    neiArray[g][h]=Grid[x + 1][y];
                    g++;
                    h++;
                    duplication++;                 /*check to avoid duplication*/
                }
                if ((Grid[x][y - 1] != 1)&& (Grid[x][y]==1)&&(duplication<1)) 
                {/*this condition will only allow a non-living cell with a living neighbour and zero duplication to ener the nei-array*/
                    Grid[x][y - 1]=neiArray[g][h];
                    g++;
                    h++;
                    duplication++;                 /*check to avoid duplication*/
                }
                if ((Grid[x][y + 1] != 1)&& (Grid[x][y]==1)&&(duplication<1))
                {/*this condition will only allow a non-living cell with a living neighbour and zero duplication to ener the nei-array*/
                    neiArray[g][h]=Grid[x][y + 1];
                    g++;
                    h++;
                    duplication++;                 /*check to avoid duplication*/
                }
          }
      }
}

/*6. SucceedingGridMaker() - assists in making the grid of next generation */
void SucceedingGridMaker(char Grid[][ColumnsOfGrid], int Count) 
{
      for ( x = 0; x < RowsOfGrid ; x++)                            /*Applying loop to search each and every column*/
	  {
          for ( y = 0; y < ColumnsOfGrid ; y++) 
		  {
                Count = 0;
                CountingLiveNeighbours(Grid, x, y, Count);  /*the function that searches for alive neighbours in the present Grid*/ 
                CellPropogation(Grid, x, y, Count);         /*the funtion which decides the propogation of each cell is being called*/
          }
      }
}

/*7. transferGrid() - it will allow us to transfer data from secArray to our
        main Grid which will then be printed  */
void transferGrid(char initial[][ColumnsOfGrid], char final[][ColumnsOfGrid]) 
{
  
      for ( x = 0; x < RowsOfGrid; x++)                             /*making of initial[] and final[] arrays which will assist in copying elements
	                                                            from sec to grid array*/
      {
          for ( y = 0; y < ColumnsOfGrid; y++)
		  {
               final[x][y] = initial[x][y]; 
          }
      }
}

/*8. InitialOutput() - function that will be used to display the introduction, 
        initial grid (generation 0) and the options of  whether to go to next 
		generation or see a continuous show of generations*/
void InitialOutput()
{
      cout<<"\n*******GAME OF LIFE*******"                         /*Outputting Introduction*/
          <<"\n\nYou have chosen to go with "<<NumOfCells<<" cells till "<<NumOfGenerations<<" Generations."   
	      <<"\nHere is your Generation 0 according to the co-ordinates you have provided:"<<endl<<endl;
      cout << "Generation "<<Generation<<":"<<endl;	               /*Outputting gen number*/
  
      MakingGrid(Grid, RowsOfGrid, ColumnsOfGrid);                             /*Outputting Grid of gen 0*/
 
      cout <<endl
           <<"1. Press \'N\' to go to the next Generation"<<endl<<endl      /*Giving Option to user*/
           <<"                      OR                    "<<endl<<endl
           <<"2. Press \'S\' to start a continuous show of genertions ";
}

/*9. answerN()- it will work if the user presses 'N'.
        It will display the immediate next generation */
void answerN()
{
     if ((answer == 'n') || (answer == 'N')) 
	 {
    
          for(int next = 1; next<=NumOfGenerations; next++) 
		  {
               int Count;                                           /*This will be used to tally no. of neghbours*/
               Generation++;                                        /*No. of Genrationn will be increased*/

               SucceedingGridMaker(Grid, Count); 
               transferGrid(secArray, Grid); 

               cout << "\nGeneration "<< Generation <<":"<<endl;
               MakingGrid(Grid, RowsOfGrid, ColumnsOfGrid); 
    
               while (next<NumOfGenerations)
			   {
                     cout << "Press \'N\' to go to the next Generation: ";
                     cin >> answer; 
                     break;
               }
          }
     }
}

/*10. answerS()- this function will work if the user presses 'S'.
        It will display a continuous show of generations     */
void answerS()
{
      if ((answer == 's') || (answer == 'S')) 
	  {
  
           for (int continuous=1; continuous<=NumOfGenerations ; continuous++) 
		   {
                 int Count;                                                 /*This will be used to tally no. of neghbours*/
                 Generation++;                                              /*No. of Genrationn will be increased*/
                 

                 SucceedingGridMaker(Grid, Count); 

                 transferGrid(secArray, Grid); 

                 cout << endl;
                 cout <<"Generation " << Generation << ":"<<endl;
                 MakingGrid(Grid, RowsOfGrid, ColumnsOfGrid);            }
      }
}


/*11. Answer() - This function helps in getting the answer from the user of
      whether he wants to see the next generation or a continuous show
	  of generations. It then displays according to the users wish   */
void Answer()       
{
      cin >> answer;                 
      answerN();
      answerS();    
}

/*12. outputFile() - Function that writes the number of generations, 
      number of living cells of final generation and their coordinates 
	  on the output file */
void outputFile()
{
  
      ofstream ofile;                     /*Performing File Handling*/
      ofile.open("output.txt");
  
      for ( x = 0; x < RowsOfGrid ; x++)
	  {
           for ( y = 0; y < ColumnsOfGrid ; y++) 
		   {
                if((Generation==NumOfGenerations)&&(Grid[x][y]==1))
                {
  	                cells++;
                }
                         
           }  
      }
      ofile<<NumOfGenerations<<endl             /*Displaying No of Generations*/
  	       <<cells<<endl;                       /*Displaying No of Cells*/
  	
      for ( x = 0; x < RowsOfGrid ; x++)              /*Loop to search for coordiantes of living cells in last generation*/
	  {
           for ( y = 0; y < ColumnsOfGrid ; y++) 
		   {
                if((Generation==NumOfGenerations)&&(secArray[x][y]==1))
                {	
  	                ofile<<x<<" "<<y            /*Displaying co ordiantes of living cells of final generation*/
  	                     <<endl;
                }
                         
           }  
      }
      ofile.close();
}

/*13. Start() - It compiles the functions in a pirticular sequence
      that is required to run the program */
void start()
{  
      InputFromFile();
  
      InitialOutput();
      
	  PuttingDeadNeighboursInNeiArray();
 
      Answer();
  
      outputFile();
}

int main()
{
     start();
     return 0;
}
 


