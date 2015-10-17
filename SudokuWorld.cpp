#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<time.h>
#include<ctype.h>
#include<simplecpp>
using namespace std;
#define UNASSIGNED 0
#define N 9
struct person
{
    char name[48];
    float score;
};
void GenerateRandomSolvedGrid(int gridprob[N][N]);
bool generateSudoku2(int gridprob[N][N],int numberstoremove,int fillednumbers);
void leaderboard(float);
void newResultWindow(int gridprob[N][N],int gridprob1[N][N],int n);
void ScoreWindow(int[N][N],int[N][N],float score,float time);
void GenerateWindow(int[N][N]);
void UserInputWindow(int[N][N]);
bool FindMaxFilledRowCol(int grid[N][N], int &row, int &col);
bool isValid(int grid[N][N], int row, int col, int num);
bool SolveSudoku1(int grid[N][N]);
bool SolveSudoku2(int grid[N][N]);
bool checkRow(int grid[N][N], int row, int num);
bool checkCol(int grid[N][N], int col, int num);
bool checkBox(int grid[N][N], int boxStartRow, int boxStartCol, int num);
void MainSolve(int grid[N][N]);
int numberSolve(int grid[N][N]);//1 for more than 1 solution, 0 for unique solution, -1 for no solution
int getMax(int grid[N][N],int ans[3]);
int GetRandomNumber();//random number from 0 to 8
void picksudokufromfile(int gridprob[N][N]);
main_program//main function
{
    srand(time(0));//for generating random sudokus
    //declarations
    int flag=0,i,j,cntr=0;
    int gridprob[N][N];
    int griduser[N][N];
    int cx,cy,cval,n;
    for(;;)//infiniite loop, breaks only if exit is clicked
    {
    if(cntr==0)//counter for number of times the main window is generated
                {
                initCanvas("Main Window",500,500);//canvas for main window
                Rectangle r[3],r1[3],r2[3];//declarations
                for(i=0;i<3;i++)
                {//creating 3 closely spaced rectangles
                r[i].reset(250,150+(100*i),102,42);
                r1[i].reset(250,150+(100*i),100,40);r1[i].setColor(COLOR(235,235,235));r1[i].setFill(1);r1[i].imprint();r1[i].moveTo(1000,1000);
                r2[i].reset(250,150+(100*i),106,46);
                }
                //text to be printed on the canvas
                Text t(250,50,"Welcome to SudokuWorld!!!");
                Text t1(250,150,"Give Sudoku");
                Text t2(250,250,"Generate Sudoku");
                Text t3(250,350,"Exit");

                //infinite loop, breaks only when one of the button is clicked
                do
                    {
                    cval=getClick();//gets position of the click
                    cx=cval/65536;
                    cy=cval%65536;
                    if((cy>=130)&&(cy<=170)&&(cx>=200)&&(cx<=300))
                    break;
                    if((cy>=230)&&(cy<=270)&&(cx>=200)&&(cx<=300))
                    break;
                    if((cy>=330)&&(cy<=370)&&(cx>=200)&&(cx<=300))
                    break;
                    }while(1);
                for(i=0;i<9;i++)
                {
                    for(j=0;j<9;j++)
                    {
                    griduser[i][j]=0;//initializing the sudoku grid
                    }
                }
                for(i=0;i<3;i++)
                {
                if((cy>=(130+(100*i))) && (cy<=(170+(100*i))))
                                                                {
                                                                flag=i;//flag has the information of the button being clicked
                                                                }
                }
                switch(flag)
                        {

                        case 0://user inputs a sudoku
                                closeCanvas();//closing the main window
                                UserInputWindow(griduser);//calls the appropriate func.
                                for(i=0;i<9;i++)
                                {
                                    for(j=0;j<9;j++)
                                    {
                                    gridprob[i][j]=griduser[i][j];//copies the user inputted grid in the problem grid.
                                    }
                                }
                                n=numberSolve(griduser);//n gives the number of solution of the problem grid.

                                if(n!=-1)SolveSudoku1(griduser);//solves if it has atleast one solution

                                        switch(n)
                                            {//outputting the solved grid
                                            case 1:newResultWindow(gridprob,griduser,1);break;
                                            case 0:newResultWindow(gridprob,griduser,0);break;
                                            case -1:newResultWindow(gridprob,griduser,-1);break;
                                            }

                                break;
                        case 1://generation of sudoku
                                closeCanvas();//closing  the main window
                                GenerateWindow(gridprob);//calls the appropriate function
                                break;
                        case 2:return 0;//case when user wants to exit
                        }
                }
    else//the same code is repeated when the second time main window is opened.The difference being that the previous canvas must be closed.
    {
    //code repeated
    closeCanvas();
    initCanvas("Main Window",500,500);
    Rectangle r1[3],r2[3],r3[3];
    Text t22(250,50,"Welcome to SudokuWorld!!!");
    Text t122(250,150,"Give Sudoku");
    Text t222(250,250,"Generate Sudoku");
    Text t322(250,350,"Exit");
    for(i=0;i<3;i++)
    {
         r3[i].reset(250,150+(100*i),102,42);
        r1[i].reset(250,150+(100*i),100,40);r1[i].setColor(COLOR(235,235,235));r1[i].setFill(1);r1[i].imprint();r1[i].moveTo(1000,1000);
        r2[i].reset(250,150+(100*i),106,46);;
    }
    do
        {
        cval=getClick();
        cx=cval/65536;
        cy=cval%65536;
        if((cy>=130)&&(cy<=170)&&(cx>=200)&&(cx<=300))
            break;
        if((cy>=230)&&(cy<=270)&&(cx>=200)&&(cx<=300))
            break;
        if((cy>=330)&&(cy<=370)&&(cx>=200)&&(cx<=300))
            break;
        }while(1);
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            griduser[i][j]=0;
        }
    }
    for(i=0;i<3;i++)
    {
        if((cy>=(130+(100*i))) && (cy<=(170+(100*i))))
        {
            flag=i;
        }
    }
    switch(flag)
    {

        case 0:
                closeCanvas();
                UserInputWindow(griduser);
                for(i=0;i<9;i++)
                {
                    for(j=0;j<9;j++)
                    {
                    gridprob[i][j]=griduser[i][j];
                    }
                }
                n=numberSolve(griduser);
                if(n!=-1)SolveSudoku1(griduser);

                switch(n)
                {
                case 1:newResultWindow(gridprob,griduser,1);break;
                case 0:newResultWindow(gridprob,griduser,0);break;
                case -1:newResultWindow(gridprob,griduser,-1);break;
                }

                break;
        case 1:
                closeCanvas();
                GenerateWindow(gridprob);
                break;
        case 2:return 0;
    }
    }

    cntr++;
}
}
void UserInputWindow(int griduser[N][N])//updates the griduser
{
    initCanvas("User Input Window",500,500);//initiates the canvas for user input
    int i=-1;int x=70,y=70;//initializations
    //creating the shaded rectangles present in the main grid
    Rectangle r1(x+180,y+60,120,120);r1.setColor(COLOR(255,255,215));r1.setFill(1);r1.imprint();r1.moveTo(1000,1000);
    Rectangle r2(x+60,y+180,120,120);r2.setColor(COLOR(255,255,215));r2.setFill(1);r2.imprint();r2.moveTo(1000,1000);
    Rectangle r3(x+300,y+180,120,120);r3.setColor(COLOR(255,255,215));r3.setFill(1);r3.imprint();r3.moveTo(1000,1000);
    Rectangle r4(x+180,y+300,120,120);r4.setColor(COLOR(255,255,215));r4.setFill(1);r4.imprint();r4.moveTo(1000,1000);
    //declaring array of lines
    Line l1[10];
    Line l2[10];
    Line l3[10];
    Line l4(70,440,430,440);
    Line l5(70,490,430,490);

    //creating the submitbutton and the delete buttons. Also giving the inner rectangles a greyish shade.
    Rectangle submitbutton(350,35,80,40);
    Rectangle rb1,rb2;
    rb2.reset(350,35,84,44);rb2.imprint();
    rb1.reset(350,35,78,38);rb1.setColor(COLOR(235,235,235));rb1.setFill(1);rb1.imprint();rb1.moveTo(1000,1000);
    Rectangle deletebutton(150,35,80,40);
    rb2.reset(150,35,84,44);
    rb1.reset(150,35,78,38);rb1.setColor(COLOR(235,235,235));rb1.setFill(1);rb1.imprint();rb1.moveTo(1000,1000);
    Text t[9][9];//a 2-d array for storing the objects of type text.
    int j,n,n1=-1,n2;
    int c1x,c1y,c2x,c2y,c1,c2;//store the value of the click being made.
    char ch[2];
    Rectangle rbox[9];//declaration.
    for(i=0;i<9;i++)
        {
        rbox[i].reset(90+(40*i),465,35,45);//creating the rectangles needed for making the lower pallet.
        }
//loop for printing the sudoku grid with the help of lines
    for(i=-1;i<9;i++)
        {
        //if else statement creates lines of different shades.
        if(!((i%3==2)||(i%3==-1)))
                                {
                                l1[i+1].setColor(COLOR(205,201,201));
                                l2[i+1].setColor(COLOR(205,201,201));
                                l1[i+1].reset(110+(40*i),70,110+(40*i),430);
                                l2[i+1].reset(70,110+(40*i),430,110+(40*i));
                                l3[i+1].reset(110+(40*i),440,110+(40*i),490);
                                }
        else
            {
            l1[i+1].reset(110+(40*i),70,110+(40*i),430);
            l2[i+1].reset(70,110+(40*i),430,110+(40*i));
            l3[i+1].reset(110+(40*i),440,110+(40*i),490);
            }
        }
    //printing the numbers in the pallet.
    Text t1(90,465,"1");
    Text t2(130,465,"2");
    Text t3(170,465,"3");
    Text t4(210,465,"4");
    Text t5(250,465,"5");
    Text t6(290,465,"6");
    Text t7(330,465,"7");
    Text t8(370,465,"8");
    Text t9(410,465,"9");
    //printing the appropriate text.
    Text t0(350,35,"Submit");
    Text t10(150,35,"Delete");

    for(;;)//infinite loop,breaks only when submit button is clicked.
    {
    n1=-1;n2=-1;
    do//loop for getting the  clicks in the buttons.
        {
        c1=getClick();
        c1x=c1/65536;c1y=c1%65536;
        if((c1x>=110)&&(c1x<=190)&&(c1y>=15)&&(c1y<=55))
                                                        break;
        if((c1x>=310)&&(c1x<=390)&&(c1y>=15)&&(c1y<=55))
                                                        return;//submit button clicked
        if((c1x>=70)&&(c1x<=430)&&(c1y>=440)&&(c1y<=490))
                                                        break;
        }while(1);
    if((c1x>=110)&&(c1x<=190)&&(c1y>=15)&&(c1y<=55))//start of delete function
                {
                c2=getClick();//gets position of the click.
                c2x=c2/65536;c2y=c2%65536;
                for(i=0;i<9;i++)
                {
                for(j=0;j<9;j++)
                        {
                        if((c2x>=(70+(40*i))) && (c2x<=(110+(40*i))) && (c2y>=(70+(40*j))) && (c2y<=(110+(40*j))))
                                {
                                //detects the position of the numbeer to be deleted.
                                n1=i;
                                n2=j;
                                griduser[i][j]=0;//number deleted.
                                break;
                                }
                        }
                if(n1==i)
                break;
                }
                t[n1][n2].reset(90+(40*n1),90+(40*n2)," ");//text replaced by blank on the canvas.
                }//end of delete function
    else if((c1x>=70)&&(c1x<=430)&&(c1y>=440)&&(c1y<=490))//pallet being clicked
                        {
                        do{
                            c2=getClick();//whether the click is made on the grid or not
                            c2x=c2/65536;c2y=c2%65536;
                            if((c2x>=70)&&(c2x<=430)&&(c2y>=70)&&(c2y<=430)){break;}
                            }while(1);

                        //exact position of the click being made on the pallet.
                        for(i=0;i<9;i++)
                            {
                            if((c1x>=(70+(40*i))) && (c1x<=(110+(40*i))))
                                    {
                                    n=i+1;
                                    break;
                                    }
                            }

                        //number to be inputted in the grid.
                        switch(n)
                        {
                        case 1:strcpy(ch,"1");break;
                        case 2:strcpy(ch,"2");break;
                        case 3:strcpy(ch,"3");break;
                        case 4:strcpy(ch,"4");break;
                        case 5:strcpy(ch,"5");break;
                        case 6:strcpy(ch,"6");break;
                        case 7:strcpy(ch,"7");break;
                        case 8:strcpy(ch,"8");break;
                        case 9:strcpy(ch,"9");break;

                        }
                        //exact position of the click being made on the pallet.
                        for(i=0;i<9;i++)
                            {
                            for(j=0;j<9;j++)
                                {
                                if((c2x>=(70+(40*i))) && (c2x<=(110+(40*i))) && (c2y>=(70+(40*j))) && (c2y<=(110+(40*j))))
                                {
                                n1=i;
                                n2=j;
                                griduser[i][j]=n;
                                break;
                                }
                                }
                            if(n1==i)
                            break;
                            }
                        t[n1][n2].reset(90+(40*n1),90+(40*n2),ch);//print the appropriate number on the canvas.
                        }
    }
    return;
}
int getMax(int grid[N][N],int ans[3])//gets the row or column with the maximum number of filled entries.
{
    int num,row,col;//declaration
    int nummax=0;//initialization

    //checking rows

    for(row=0;row<N;row++)
    {
        num=0;
        for(col=0;col<N;col++)
        {
            if(grid[row][col]!=0){num++;}//num is increased on encountering a filled cell.
        }
        if(num>=nummax && num!=9){ans[0]=1;ans[1]=row;ans[2]=0;nummax=num;}

    }
    //checking cols
    for(col=0;col<N;col++)
    {
        num=0;
      for(row=0;row<N;row++)
        {
            if(grid[row][col]!=0){num++;}//num is increased on encountering a filled cell.
        }
        if(num>=nummax && num!=9){ans[0]=2;ans[1]=col;ans[2]=0;nummax=num;}

    }
    return nummax;

}
int numberSolve(int grid[N][N])//calculates the number of solution of the problem sudoku.
{
    int grid1[N][N],grid2[N][N];
    //copying problem grid to grid1.
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            grid1[i][j]=grid[i][j]%10;

     //copying problem grid to grid2.
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            grid2[i][j]=grid[i][j]%10;

    if(SolveSudoku1(grid2)==true)//decides whether the problem grid has atleast one solution.
    {
        SolveSudoku2(grid1);//grid1 obtained by solvesudoku2
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
                {
                    if(grid1[i][j]!=grid2[i][j]){return 1;}//if both bont match then more than one solution.
                }

        }
        return 0;//unique solution
    }
    else return -1;//no solution
}

bool SolveSudoku1(int grid[N][N])//parameter is the problem grid.
{
    int temp;//decflaration
    //for checking the no solution case.
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(grid[i][j]!=0)
            {
                temp=grid[i][j];
                grid[i][j]=0;
                if(!isValid(grid,i,j,temp)){return false;}//false if the problem grid is itself not safe.
                grid[i][j]=temp;
            }
        }

    }
    int row, col;
    if (!FindMaxFilledRowCol(grid, row, col))//updates row and col woth the most preferred unassigned cell.
       return true;//true if the entire grid is filled.
    for (int num = 1; num <=9; num++)//loops for each number
    {
        if (isValid(grid, row, col, num))//checks the validity of the number
            {
            grid[row][col] = num;//assignment
            if (SolveSudoku1(grid))//recursive call with the updated grid
                return true;//returns true if the updated grid has one solution for the most preferred cell.
            grid[row][col] = UNASSIGNED;//else the last updation is undone.
            }
    }
    return false;//false if none of the number is safe.
}
bool SolveSudoku2(int grid[N][N])//function is similar to SolveSudoku1 except that the numbers are tried out in reverse order.
{
    int temp;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(grid[i][j]!=0)
            {
                temp=grid[i][j];
                grid[i][j]=0;
                if(!isValid(grid,i,j,temp)){cout<<"here";return false;}
                grid[i][j]=temp;
            }
        }

    }
    int row, col;
    if (!FindMaxFilledRowCol(grid, row, col))
       return true;
    for (int num = 9; num >0; num--)
    {
    if (isValid(grid, row, col, num))
    {
        grid[row][col] = num;
        if (SolveSudoku2(grid))
            return true;
        grid[row][col] = UNASSIGNED;
    }
    }
    return false;
}
void GenerateRandomSolvedGrid(int gridprob[N][N])//generates random already completely filled sudokus.
{
    int num,row,col;
    int A[10]={0};//stores the number of times a number has been used in a particular grid
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                gridprob[i][j]=UNASSIGNED; //giving the value 0 to all elements of the grid

         for(int i=0;i<10;)//operate till number needed to be filled is achieveds
            {
                num=1+GetRandomNumber();//random number to input from 1 to 9
                if(A[num]>(2)){continue;}
                row=GetRandomNumber();// a random row to input the number
                col=GetRandomNumber();// a random column to input the number


                if(gridprob[row][col]==0)
                {
                    if(isValid(gridprob,row,col,num))
                    {
                        gridprob[row][col]=num;
                        i++;
                        A[num]++;
                    }
                }
                else{continue;}//if the location is already filled continue

            }
    int l=GetRandomNumber()%2;
    if(l==0){SolveSudoku1(gridprob);}
    else{SolveSudoku2(gridprob);}


}
bool generateSudoku2(int gridprob[N][N],int numberstoremove,int fillednumbers) //generates a problem grid of given level in gridprob array
{

    if(numberstoremove>57){picksudokufromfile(gridprob);//use pre-loaded sudokus for level 5.
                           return true;
                          }
    int row,col,num,count;//declaration
    if(numberstoremove==0)
        {return true;}//returns true only if the desired number of numbers are removed.

    for(count=0;count<=fillednumbers;)
    {



        for(;;) //get random row,col
            {
                row=GetRandomNumber();
                col=GetRandomNumber();

                if(gridprob[row][col]==0){continue;}

                else break;

            }


        num=gridprob[row][col];

        gridprob[row][col]=0;numberstoremove--;fillednumbers--;

        if(numberSolve(gridprob)==0){if(generateSudoku2(gridprob,numberstoremove,fillednumbers)){return true;}}

        gridprob[row][col]=num;numberstoremove++;fillednumbers++;

    }

    return false;

}
int GetRandomNumber()
{
    return (rand() % (9));//returns a random number in the range of 0 to 9.
}
bool FindMaxFilledRowCol(int grid[N][N], int &row, int &col)
{

    int ans[3]={0,0,0};
    getMax(grid,ans);
    if(ans[0]==0){return false;}
    else if(ans[0]==1)
    {
        row=ans[1];//finds unassigned location in the row returned by getmax
        for(col=0;col<N;col++)
            {
                if (grid[row][col] == UNASSIGNED){return true;}
            }
    }
    else if(ans[0]==2)
    {
        col=ans[1];
        for(row=0;row<N;row++)//finds unassigned location in the column returned by getmax
            {
                if (grid[row][col] == UNASSIGNED){return true;}
            }
    }

}
bool checkRow(int grid[N][N], int row, int num)//checks whether the number is already present in the row
{
    for (int col = 0; col < N; col++)
    if (grid[row][col] == (num%10))
        return true;
    return false;
}
bool checkCol(int grid[N][N], int col, int num)//checks whether the number is already present in the column
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == (num%10))
            return true;
    return false;
}
bool checkBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)//checks whether the number is already present in the box.
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == (num%10))
                return true;
    return false;
}
bool isValid(int grid[N][N], int row, int col, int num)//calls the appropriate functions to check whether the number is safe.
{
    return !checkRow(grid, row, num) && !checkCol(grid, col, num) &&
       !checkBox(grid, row - row % 3 , col - col % 3, num);
}
void GenerateWindow(int gridprob[N][N])//updates the grid and imprints it on canvas
{

    initCanvas("Generate Window",500,560);
    Text t[5];int i;
    char str[2];
    Rectangle r1[5];Rectangle rb1[5],rb2[5];//declarations
    for(i=0;i<5;i++)
    {
        r1[i].reset(250,130+(60*i),80,40);
        rb2[i].reset(250,130+(60*i),84,44);
        rb1[i].reset(250,130+(60*i),78,38);rb1[i].setColor(COLOR(235,235,235));rb1[i].setFill(1);rb1[i].imprint();rb1[i].moveTo(1000,1000);
    }
    //printing the buttons for levels
    t[0].reset(250,130,"Level 1");
    t[1].reset(250,190,"Level 2");
    t[2].reset(250,250,"Level 3");
    t[3].reset(250,310,"Level 4");
    t[4].reset(250,370,"Level 5");


    int j=0,numtoremove=0,level=0,c,cx,cy,gridprob1[N][N],completesol[N][N];
    float score;int numhints=0;bool allfilled=true;

    do//for getting the clicks in the correct buttons.
    {
    c=getClick();
    cx=c/65536;
    cy=c%65536;
    if((cy<=150) && (cy>=110) && (cx>=210) && (cx<=290))
    {
    numtoremove=44;
    level=1;
    break;
    }
    else if((cy<=210) && (cy>=170) && (cx>=210) && (cx<=290))
    {
    numtoremove=48;
    level=2;
    break;
    }
    else if((cy<=270) && (cy>=230) && (cx>=210) && (cx<=290))
    {
    numtoremove=52;
    level=3;
    break;
    }
    else if((cy<=330) && (cy>=290) && (cx>=210) && (cx<=290))
    {
    numtoremove=56;
    level=4;
    break;
    }
    else if((cy<=390) && (cy>=350) && (cx>=210) && (cx<=290))
    {
    numtoremove=60;
    level=5;
    break;
    }
    }while(1);

    Rectangle blank;
    blank.reset(250,280,500,560);blank.setColor(COLOR(255,255,255));blank.setFill(1);blank.imprint();blank.hide();
    for(i=0;i<5;i++)
    {
    t[i].hide();//for hiding the levels buttons.
    r1[i].hide();
    rb1[i].hide();
    rb2[i].hide();
    }
    GenerateRandomSolvedGrid(gridprob);
    if(level==5)
    {picksudokufromfile(gridprob);}//using pre-loaded sudokus for level 5
    else{generateSudoku2(gridprob,numtoremove,81);}
    Rectangle rbox[9];
    for(i=0;i<9;i++)
    {
        rbox[i].reset(90+(40*i),465,35,45);
    }
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            //copying one array into another
            gridprob1[i][j]=gridprob[i][j];
            completesol[i][j]=gridprob[i][j];
        }
    }
    SolveSudoku1(completesol);//completesol is the completely solved sudoku grid.
    int x=70,y=70;
    Rectangle r0(x+180,y+60,120,120);r0.setColor(COLOR(255,255,215));r0.setFill(1);r0.imprint();r0.moveTo(1000,1000);//printing different shades of rectangle.
    Rectangle r2(x+60,y+180,120,120);r2.setColor(COLOR(255,255,215));r2.setFill(1);r2.imprint();r2.moveTo(1000,1000);
    Rectangle r3(x+300,y+180,120,120);r3.setColor(COLOR(255,255,215));r3.setFill(1);r3.imprint();r3.moveTo(1000,1000);
    Rectangle r4(x+180,y+300,120,120);r4.setColor(COLOR(255,255,215));r4.setFill(1);r4.imprint();r4.moveTo(1000,1000);


    Rectangle r[3];


    for(i=0;i<3;i++)
    {
    r[i].reset(100+(150*i),35,100,40);
    }
    Text tt[3],nt[9][9];
    tt[0].reset(100,35,"Delete");//buttons for delete and hint func.
    tt[1].reset(250,35,"Hint");

    Rectangle rb11,rb12;
    rb12.reset(100,35,104,44);rb12.imprint();
    rb11.reset(100,35,98,38);rb11.setColor(COLOR(235,235,235));rb11.setFill(1);rb11.imprint();rb11.moveTo(1000,1000);//giving shades to the rectangular buttons.

    rb12.reset(250,35,104,44);rb12.imprint();
    rb11.reset(250,35,98,38);rb11.setColor(COLOR(235,235,235));rb11.setFill(1);rb11.imprint();rb11.moveTo(1000,1000);

    rb12.reset(400,35,104,44);rb12.imprint();
    rb11.reset(400,35,98,38);rb11.setColor(COLOR(235,235,235));rb11.setFill(1);rb11.imprint();rb11.moveTo(1000,1000);

    tt[2].reset(400,35,"Give up");
    Line l1[10];
    Line l2[10];
    Line l3[10];

    int c1x,c1y,c2x,c2y,c1,c2,n,n1=-1,n2;
    char ch[2];
    for(i=-1;i<9;i++)
    {
         if(!((i%3==2)||(i%3==-1)))
        {
        l1[i+1].setColor(COLOR(205,201,201));
        l2[i+1].setColor(COLOR(205,201,201));
        l1[i+1].reset(110+(40*i),70,110+(40*i),430);
        l2[i+1].reset(70,110+(40*i),430,110+(40*i));
        l3[i+1].reset(110+(40*i),440,110+(40*i),490);
        }
        else
        {
        l1[i+1].reset(110+(40*i),70,110+(40*i),430);//the same code for printing the grid and pallets.
        l2[i+1].reset(70,110+(40*i),430,110+(40*i));
        l3[i+1].reset(110+(40*i),440,110+(40*i),490);
        }
    }
    Line l4(70,440,430,440);
    Line l5(70,490,430,490);
    Text t1(90,460,"1");t1.imprint();
    Text t2(130,460,"2");t2.imprint();
    Text t3(170,460,"3");t3.imprint();
    Text t4(210,460,"4");t4.imprint();
    Text t5(250,460,"5");t5.imprint();
    Text t6(290,460,"6");t6.imprint();
    Text t7(330,460,"7");t7.imprint();
    Text t8(370,460,"8");t8.imprint();
    Text t9(410,460,"9");t9.imprint();
    Text terror(250,510,"Red: Incorrect filling!");terror.setColor(COLOR(255,0,0));terror.imprint();
    Text thint(250,530,"Green: Correctly filled for you!");thint.setColor(COLOR(0,255,0));thint.imprint();
    Text tuser(250,550,"Blue:Your fillings!");tuser.setColor(COLOR(0,0,255));tuser.imprint();
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            switch(gridprob[i][j])
            {
                case 0:break;
                case 1:t1.moveTo(90+(40*i),90+(40*j));t1.imprint();break;//printing different numbers in the problem grid.
                case 2:t2.moveTo(90+(40*i),90+(40*j));t2.imprint();break;
                case 3:t3.moveTo(90+(40*i),90+(40*j));t3.imprint();break;
                case 4:t4.moveTo(90+(40*i),90+(40*j));t4.imprint();break;
                case 5:t5.moveTo(90+(40*i),90+(40*j));t5.imprint();break;
                case 6:t6.moveTo(90+(40*i),90+(40*j));t6.imprint();break;
                case 7:t7.moveTo(90+(40*i),90+(40*j));t7.imprint();break;
                case 8:t8.moveTo(90+(40*i),90+(40*j));t8.imprint();break;
                case 9:t9.moveTo(90+(40*i),90+(40*j));t9.imprint();break;
            }
        }
    }
    clock_t tstart,tend;
    tstart=time(0);

    for(;;)
    {

    n1=-1;n2=-1;
    do//loop for getting clicks in the right buttons.
    {
    c1=getClick();
    c1x=c1/65536;c1y=c1%65536;
    if((c1x>=50)&&(c1x<=150)&&(c1y>=15)&&(c1y<=55))
    break;
    if((c1x>=200)&&(c1x<=300)&&(c1y>=15)&&(c1y<=55))
    break;
    if((c1x>=350)&&(c1x<=450)&&(c1y>=15)&&(c1y<=55))
    break;
    if((c1x>=70)&&(c1x<=430)&&(c1y>=440)&&(c1y<=490))
    break;
    }while(1);


    if((c1x>=350)&&(c1x<=450)&&(c1y>=15)&&(c1y<=55))
    {
        float diff=0;
        score=0;
        ScoreWindow(gridprob,gridprob1,score,diff);
        return;
    }
    else if((c1x>=50)&&(c1x<=150)&&(c1y>=15)&&(c1y<=55))//start of delete func
    {
        do
        {
        c2=getClick();
        c2x=c2/65536;c2y=c2%65536;
        if((c2x>=70)&&(c2x<=430)&&(c2y>=70)&&(c2y<=430))
        break;
        }while(1);
        for(i=0;i<9;i++)
        {
        for(j=0;j<9;j++)
        {
          if((c2x>=(70+(40*i))) && (c2x<=(110+(40*i))) && (c2y>=(70+(40*j))) && (c2y<=(110+(40*j))))
          {
             n1=i;
             n2=j;
             if(gridprob1[i][j]==0)//if it was not present in the problem grid
             {
             gridprob[i][j]=0;//delete the number
             break;
             }
             else
             {
                n2=-2;
                break;
             }
          }
        }
        if(n1==i || n2==-2)
            break;
        }
        if(n2==-2)
        continue;
        nt[n1][n2].reset(90+(40*n1),90+(40*n2)," ");
    }//end of delete func.
    else if((c1x>=70)&&(c1x<=430)&&(c1y>=440)&&(c1y<=490))
    {
    do
    {
    c2=getClick();
    c2x=c2/65536;c2y=c2%65536;
    if((c2x>=70)&&(c2x<=430)&&(c2y>=70)&&(c2y<=430))
    {
    break;
    }
    }while(1);
    for(i=0;i<9;i++)
    {
        if((c1x>=(70+(40*i))) && (c1x<=(110+(40*i))))
          {
             n=i+1;
             break;
          }
    }
    switch(n)
    {
        case 1:strcpy(ch,"1");break;
        case 2:strcpy(ch,"2");break;
        case 3:strcpy(ch,"3");break;
        case 4:strcpy(ch,"4");break;
        case 5:strcpy(ch,"5");break;
        case 6:strcpy(ch,"6");break;
        case 7:strcpy(ch,"7");break;
        case 8:strcpy(ch,"8");break;
        case 9:strcpy(ch,"9");break;

   }
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
          if((c2x>=(70+(40*i))) && (c2x<=(110+(40*i))) && (c2y>=(70+(40*j))) && (c2y<=(110+(40*j))))
          {
             n1=i;
             n2=j;
             if(gridprob1[i][j]==0)
             {
                gridprob[i][j]=n;
                break;
             }
             else
             {
                n1=-2;
                break;
             }
          }
        }
        if(n1==i)
            break;
        else if(n1==-2)
        {
            break;
        }
    }

    if(n1==-2)
    continue;
    nt[n1][n2].setColor(COLOR(0,0,255));
    nt[n1][n2].reset(90+(40*n1),90+(40*n2),ch);
    allfilled=true;
    for (i=0;i<N && allfilled;i++)//Auto-submit  begins
    {
    for (j=0;j<N && allfilled;j++)
                    {
                        if(gridprob[i][j]==0){allfilled=false;}
                    }
    }
    if (allfilled){
                tend=time(0);
                float diff=tend-tstart;

                /*score=1000+500*(level-1) */score=230 +80*level + (60*level*(level+1))/(pow(2.713,(diff/(120*(level)))))-(20/level)*(pow(2,numhints));
                ScoreWindow(gridprob,gridprob1,score,diff);
                return;
                }

    }
    else if((c1x>=200)&&(c1x<=300)&&(c1y>=15)&&(c1y<=55)&&numhints<level+2) //hint starts
    {
        numhints++;
        bool CorrectTillNow=true;

        for (i=0;i<9&&CorrectTillNow;i++)
        {
            for(j=0;j<9&&CorrectTillNow;j++)
            {
            if ((gridprob[i][j]!=0)&&(gridprob[i][j]!=completesol[i][j])) {CorrectTillNow=false;}

            }
        }
        if (!CorrectTillNow)
        {
        nt[i-1][j-1].setColor(COLOR(255,0,0));
        }
        else
        {

        do
        {
            i=GetRandomNumber();
            j=GetRandomNumber();

        }while(gridprob[i][j]!=0);

        gridprob[i][j]=completesol[i][j];
        int correctnumber=completesol[i][j];
        sprintf(str,"%d",correctnumber);
        nt[i][j].setColor(COLOR(0,255,0));
        nt[i][j].reset(90+(40*i),90+(40*j),str);
        }
    allfilled=true;
    for (i=0;i<N&&allfilled;i++)//Auto-submit  begins
    {
    for (j=0;j<N&&allfilled;j++)
                    {
                    if(gridprob[i][j]==0){allfilled=false;}
                    }
    }
    if (allfilled){
                tend=time(0);
                float diff=tend-tstart;

                /*score=1000+500*(level-1) */score=230 +80*level + (60*level*(level+1))/(pow(2.713,(diff/(120*(level)))))-(20/level)*(pow(2,numhints));
                ScoreWindow(gridprob,gridprob1,score,diff);//calling scorewindow
                return;
                }
    }
    }
}
void picksudokufromfile(int gridprob[N][N])//Problem:-ain!,no link to generate window?
{
    FILE *fin;
    int t=(rand()%3000),i,j,k=0;
    char str[82];
    fin=fopen("sudoku_17.txt","r");//opens up the sudoku file
    if(fin==NULL)
    {
        cout<<"Couldn't open file";
        return;
    }
    fscanf(fin,"%81s",str);
    while(!feof(fin))//reading into a string from the file
    {
        t--;//
        if(!t)//reading the particular sudoku
        {
            for(i=0;i<9;i++)
            {
                for(j=0;j<9;j++)
                {
                    gridprob[i][j]=((int)str[k])-48;//
                    k++;
                }
            }
            break;
        }
         fscanf(fin,"%81s",str);
    }
    fclose(fin);
    return;
}
void ScoreWindow(int gridprob[N][N],int gridprob1[N][N],float score,float time)
{
    closeCanvas();
    initCanvas("Scoresheet",1000,520);
    char str[40];

    Rectangle rb11,rb12;
    rb12.reset(500,450,104,44);rb12.imprint();
    rb11.reset(500,450,98,38);rb11.setColor(COLOR(235,235,235));rb11.setFill(1);rb11.imprint();rb11.moveTo(1000,1000);

    Text t,t11,t22,tleader;
    Rectangle rscore,rleader;
    rscore.reset(500,35,100,40);
    tleader.reset(500,450,"See Leaderboard");


    rleader.reset(500,450,100,40);
    int i,j,flag=0;
    int gridprob2[N][N];
    int x=70,y=70;
    Rectangle r1(x+180,y+60,120,120);r1.setColor(COLOR(255,255,220));r1.setFill(1);r1.imprint();r1.moveTo(1000,1000);
    Rectangle r2(x+60,y+180,120,120);r2.setColor(COLOR(255,255,220));r2.setFill(1);r2.imprint();r2.moveTo(1000,1000);
    Rectangle r3(x+300,y+180,120,120);r3.setColor(COLOR(255,255,220));r3.setFill(1);r3.imprint();r3.moveTo(1000,1000);
    Rectangle r4(x+180,y+300,120,120);r4.setColor(COLOR(255,255,220));r4.setFill(1);r4.imprint();r4.moveTo(1000,1000);
    int x1=570,y1=70;
    Rectangle r11(x1+180,y1+60,120,120);r11.setColor(COLOR(255,255,220));r11.setFill(1);r11.imprint();r11.moveTo(1000,1000);
    Rectangle r21(x1+60,y1+180,120,120);r21.setColor(COLOR(255,255,220));r21.setFill(1);r21.imprint();r21.moveTo(1000,1000);
    Rectangle r31(x1+300,y1+180,120,120);r31.setColor(COLOR(255,255,220));r31.setFill(1);r31.imprint();r31.moveTo(1000,1000);
    Rectangle r41(x1+180,y1+300,120,120);r41.setColor(COLOR(255,255,220));r41.setFill(1);r41.imprint();r41.moveTo(1000,1000);
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            gridprob2[i][j]=gridprob1[i][j];
        }
    }
    SolveSudoku1(gridprob1);
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(gridprob[i][j]==0){flag=1;break;}
            if((gridprob[i][j])!=gridprob1[i][j])
            {
                flag=1;
                break;
            }
        }
        if(flag)
        break;
    }
    if(flag)
    {
        t.reset(500,35,"SCORE = 0");t.imprint();
        score=0;
    }
    else
    {
        sprintf(str,"SCORE = %4.1f",score);
        t.reset(500,35,str);t.imprint();
    }
    t11.reset(250,35,"Submitted Sudoku");t11.imprint();
    t22.reset(750,35,"Solution Sudoku");t22.imprint();
    if(time!=0){
        cout<<"here";
        cout<<time;
        char elapsedtime[20];
        sprintf(elapsedtime,"Time taken = %4.0f",time);
        Text timetaken(500,70,elapsedtime);
        timetaken.imprint();
    }

    Line l1[10];
    Line l2[10];

    for(i=-1;i<9;i++)
    {
        if(!((i%3==2)||(i%3==-1)))
        {
        l1[i+1].setColor(COLOR(205,201,201));
        l2[i+1].setColor(COLOR(205,201,201));
        l1[i+1].reset(110+(40*i),70,110+(40*i),430);l1[i+1].imprint();
        l2[i+1].reset(70,110+(40*i),430,110+(40*i));l2[i+1].imprint();

        }
        else
        {
        l1[i+1].reset(110+(40*i),70,110+(40*i),430);l1[i+1].imprint();
        l2[i+1].reset(70,110+(40*i),430,110+(40*i));l2[i+1].imprint();

        }
    }

    Text t1(90,460,"1");
    Text t2(130,460,"2");
    Text t3(170,460,"3");
    Text t4(210,460,"4");
    Text t5(250,460,"5");
    Text t6(290,460,"6");
    Text t7(330,460,"7");
    Text t8(370,460,"8");
    Text t9(410,460,"9");
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(gridprob[i][j]==gridprob2[i][j]){
            switch(gridprob[i][j])//Problem:-Club 1 with 21 and so on
            {
                case 0:break;
                case 1:t1.moveTo(90+(40*i),90+(40*j));t1.imprint();break;
                case 2:t2.moveTo(90+(40*i),90+(40*j));t2.imprint();break;
                case 3:t3.moveTo(90+(40*i),90+(40*j));t3.imprint();break;
                case 4:t4.moveTo(90+(40*i),90+(40*j));t4.imprint();break;
                case 5:t5.moveTo(90+(40*i),90+(40*j));t5.imprint();break;
                case 6:t6.moveTo(90+(40*i),90+(40*j));t6.imprint();break;
                case 7:t7.moveTo(90+(40*i),90+(40*j));t7.imprint();break;
                case 8:t8.moveTo(90+(40*i),90+(40*j));t8.imprint();break;
                case 9:t9.moveTo(90+(40*i),90+(40*j));t9.imprint();break;


            }}
            else{
            switch(gridprob[i][j])
            {
                case 0:break;
                case 1:t1.setColor(COLOR(0,0,255));t1.moveTo(90+(40*i),90+(40*j));t1.imprint();t1.setColor(COLOR(0,0,0));break;
                case 2:t2.setColor(COLOR(0,0,255));t2.moveTo(90+(40*i),90+(40*j));t2.imprint();t2.setColor(COLOR(0,0,0));break;
                case 3:t3.setColor(COLOR(0,0,255));t3.moveTo(90+(40*i),90+(40*j));t3.imprint();t3.setColor(COLOR(0,0,0));break;
                case 4:t4.setColor(COLOR(0,0,255));t4.moveTo(90+(40*i),90+(40*j));t4.imprint();t4.setColor(COLOR(0,0,0));break;
                case 5:t5.setColor(COLOR(0,0,255));t5.moveTo(90+(40*i),90+(40*j));t5.imprint();t5.setColor(COLOR(0,0,0));break;
                case 6:t6.setColor(COLOR(0,0,255));t6.moveTo(90+(40*i),90+(40*j));t6.imprint();t6.setColor(COLOR(0,0,0));break;
                case 7:t7.setColor(COLOR(0,0,255));t7.moveTo(90+(40*i),90+(40*j));t7.imprint();t7.setColor(COLOR(0,0,0));break;
                case 8:t8.setColor(COLOR(0,0,255));t8.moveTo(90+(40*i),90+(40*j));t8.imprint();t8.setColor(COLOR(0,0,0));break;
                case 9:t9.setColor(COLOR(0,0,255));t9.moveTo(90+(40*i),90+(40*j));t9.imprint();t9.setColor(COLOR(0,0,0));break;


            }
            }
        }
    }
    Text tinform(250,460,"Black: Given Grid numbers");tinform.imprint();
    Text tinform1(250,480,"Blue: User Inputted numbers");tinform1.setColor(COLOR(0,0,255));tinform1.imprint();


    t1.reset(590,460,"1");
    t2.reset(630,460,"2");
    t3.reset(670,460,"3");
    t4.reset(710,460,"4");
    t5.reset(750,460,"5");
    t6.reset(790,460,"6");
    t7.reset(830,460,"7");
    t8.reset(870,460,"8");
    t9.reset(910,460,"9");
    for(i=-1;i<9;i++)
    {
         if(!((i%3==2)||(i%3==-1)))
        {
        l1[i+1].setColor(COLOR(205,201,201));
        l2[i+1].setColor(COLOR(205,201,201));
        l1[i+1].reset(610+(40*i),70,610+(40*i),430);l1[i+1].imprint();
        l2[i+1].reset(570,110+(40*i),930,110+(40*i));l2[i+1].imprint();

        }
        else
        {
        l1[i+1].reset(610+(40*i),70,610+(40*i),430);l1[i+1].imprint();
        l2[i+1].reset(570,110+(40*i),930,110+(40*i));l2[i+1].imprint();

        }
    }
    Text tcorrect(808,471,":   Correctly filled!");tcorrect.setColor(COLOR(0,255,0));tcorrect.imprint();
    Text correctans(778,448,"Blue: Correct Answers");correctans.setColor(COLOR(0,0,255));correctans.imprint();
    Text ticorrect(808,494," :   Incorrectly filled!");ticorrect.setColor(COLOR(255,0,0));ticorrect.imprint();
    Line correct1(718,471,724,477);Line correct2(724,477,734,467); correct1.setColor(COLOR(0,255,0));correct2.setColor(COLOR(0,255,0));correct1.imprint();correct2.imprint();
    Line incorrect1(721,490,729,498);Line incorrect2(721,498,729,490); incorrect1.setColor(COLOR(255,0,0));incorrect2.setColor(COLOR(255,0,0));incorrect1.imprint();incorrect2.imprint();
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(gridprob1[i][j]==gridprob2[i][j]){
            switch(gridprob1[i][j])
            {
                case 0:break;
                case 1:t1.moveTo(590+(40*i),90+(40*j));t1.imprint();break;
                case 2:t2.moveTo(590+(40*i),90+(40*j));t2.imprint();break;
                case 3:t3.moveTo(590+(40*i),90+(40*j));t3.imprint();break;
                case 4:t4.moveTo(590+(40*i),90+(40*j));t4.imprint();break;
                case 5:t5.moveTo(590+(40*i),90+(40*j));t5.imprint();break;
                case 6:t6.moveTo(590+(40*i),90+(40*j));t6.imprint();break;
                case 7:t7.moveTo(590+(40*i),90+(40*j));t7.imprint();break;
                case 8:t8.moveTo(590+(40*i),90+(40*j));t8.imprint();break;
                case 9:t9.moveTo(590+(40*i),90+(40*j));t9.imprint();break;


            }}
            else{
            switch(gridprob1[i][j])//Problem:-Club 1 with 21 and so on
            {
                case 0:break;
                case 1:t1.setColor(COLOR(0,0,255));t1.moveTo(590+(40*i),90+(40*j));t1.imprint();t1.setColor(COLOR(0,0,0));break;
                case 2:t2.setColor(COLOR(0,0,255));t2.moveTo(590+(40*i),90+(40*j));t2.imprint();t2.setColor(COLOR(0,0,0));break;
                case 3:t3.setColor(COLOR(0,0,255));t3.moveTo(590+(40*i),90+(40*j));t3.imprint();t3.setColor(COLOR(0,0,0));break;
                case 4:t4.setColor(COLOR(0,0,255));t4.moveTo(590+(40*i),90+(40*j));t4.imprint();t4.setColor(COLOR(0,0,0));break;
                case 5:t5.setColor(COLOR(0,0,255));t5.moveTo(590+(40*i),90+(40*j));t5.imprint();t5.setColor(COLOR(0,0,0));break;
                case 6:t6.setColor(COLOR(0,0,255));t6.moveTo(590+(40*i),90+(40*j));t6.imprint();t6.setColor(COLOR(0,0,0));break;
                case 7:t7.setColor(COLOR(0,0,255));t7.moveTo(590+(40*i),90+(40*j));t7.imprint();t7.setColor(COLOR(0,0,0));break;
                case 8:t8.setColor(COLOR(0,0,255));t8.moveTo(590+(40*i),90+(40*j));t8.imprint();t8.setColor(COLOR(0,0,0));break;
                case 9:t9.setColor(COLOR(0,0,255));t9.moveTo(590+(40*i),90+(40*j));t9.imprint();t9.setColor(COLOR(0,0,0));break;



            }
            t1.moveTo(1000,1000);
            t2.moveTo(1000,1000);
            t3.moveTo(1000,1000);
            t4.moveTo(1000,1000);
            t5.moveTo(1000,1000);
            t6.moveTo(1000,1000);
            t7.moveTo(1000,1000);
            t8.moveTo(1000,1000);
            t9.moveTo(1000,1000);
            }
            if(gridprob2[i][j]!=gridprob[i][j])
            {
                if(gridprob[i][j]==gridprob1[i][j])
                {
                    Line correct1(89+(40*i),79+(40*j),95+(40*i),85+(40*j));Line correct2(95+(40*i),85+(40*j),105+(40*i),75+(40*j)); correct1.setColor(COLOR(0,255,0));correct2.setColor(COLOR(0,255,0));correct1.imprint();correct2.imprint();
                }
                else
                {
                    Line incorrect1(92+(40*i),77+(40*j),100+(40*i),85+(40*j));Line incorrect2(92+(40*i),85+(40*j),100+(40*i),77+(40*j)); incorrect1.setColor(COLOR(255,0,0));incorrect2.setColor(COLOR(255,0,0));incorrect1.imprint();incorrect2.imprint();
                }
            }

}
}
    int c,cx,cy;
    do
    {
        c=getClick();
        cx=c/65536;
        cy=c%65536;
        if((cx>=450)&&(cx<=550)&&(cy>=430)&&(cy<=470))
        break;
    }while(1);
    leaderboard(score);
    return;
}
void newResultWindow(int gridprob[N][N],int gridprob1[N][N],int n)
{
    closeCanvas();
    if(n==-1)
    {
        initCanvas("NO !Solution",500,500);Text t10,t11;
        t10.reset(250,25,"Submitted Sudoku has NO SOLUTIONS!");
        t10.imprint();

        int x=70,y=70;
        Rectangle r1(x+180,y+60,120,120);r1.setColor(COLOR(255,255,220));r1.setFill(1);r1.imprint();r1.moveTo(1000,1000);
        Rectangle r2(x+60,y+180,120,120);r2.setColor(COLOR(255,255,220));r2.setFill(1);r2.imprint();r2.moveTo(1000,1000);
        Rectangle r3(x+300,y+180,120,120);r3.setColor(COLOR(255,255,220));r3.setFill(1);r3.imprint();r3.moveTo(1000,1000);
        Rectangle r4(x+180,y+300,120,120);r4.setColor(COLOR(255,255,220));r4.setFill(1);r4.imprint();r4.moveTo(1000,1000);
        t11.reset(250,45,"Submitted Sudoku");t11.imprint();

        Line l1[10];
    Line l2[10];



    int i,j;
    for(i=-1;i<9;i++)
    {
        if(!((i%3==2)||(i%3==-1)))
        {
        l1[i+1].setColor(COLOR(205,201,201));
        l2[i+1].setColor(COLOR(205,201,201));
        l1[i+1].reset(110+(40*i),70,110+(40*i),430);
        l2[i+1].reset(70,110+(40*i),430,110+(40*i));

        }
        else
        {
        l1[i+1].reset(110+(40*i),70,110+(40*i),430);
        l2[i+1].reset(70,110+(40*i),430,110+(40*i));

        }
    }

    Rectangle returnback(250,470,80,40);Rectangle rb1,rb2;
    rb2.reset(250,470,84,44);rb2.imprint();
    rb1.reset(250,470,78,38);rb1.setColor(COLOR(235,235,235));rb1.setFill(1);rb1.imprint();rb1.moveTo(1000,1000);
    Text returnback1(250,470,"Return Back!");
    Text t1(90,460,"1");
    Text t2(130,460,"2");
    Text t3(170,460,"3");
    Text t4(210,460,"4");
    Text t5(250,460,"5");
    Text t6(290,460,"6");
    Text t7(330,460,"7");
    Text t8(370,460,"8");
    Text t9(410,460,"9");
    for(int i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            switch(gridprob[i][j])
            {
                case 0:break;
                case 1:t1.moveTo(90+(40*i),90+(40*j));t1.imprint();break;
                case 2:t2.moveTo(90+(40*i),90+(40*j));t2.imprint();break;
                case 3:t3.moveTo(90+(40*i),90+(40*j));t3.imprint();break;
                case 4:t4.moveTo(90+(40*i),90+(40*j));t4.imprint();break;
                case 5:t5.moveTo(90+(40*i),90+(40*j));t5.imprint();break;
                case 6:t6.moveTo(90+(40*i),90+(40*j));t6.imprint();break;
                case 7:t7.moveTo(90+(40*i),90+(40*j));t7.imprint();break;
                case 8:t8.moveTo(90+(40*i),90+(40*j));t8.imprint();break;
                case 9:t9.moveTo(90+(40*i),90+(40*j));t9.imprint();break;


            }
        }
    }
    t1.moveTo(1000,1000);
    t2.moveTo(1000,1000);
    t3.moveTo(1000,1000);
    t4.moveTo(1000,1000);
    t5.moveTo(1000,1000);
    t6.moveTo(1000,1000);
    t7.moveTo(1000,1000);
    t8.moveTo(1000,1000);
    t9.moveTo(1000,1000);

    int getx;int gety;int get;
    do
    {
        get = getClick();
        getx=get/65536;
        gety=get%65536;
    }while(getx>290 || getx<210 ||gety>490 || gety<450);

    return;


    }

    if(n==0||n==1){
    initCanvas("Solution",1000,500);
    int x=70,y=70;
    Rectangle r1(x+180,y+60,120,120);r1.setColor(COLOR(255,255,220));r1.setFill(1);r1.imprint();r1.moveTo(1000,1000);
    Rectangle r2(x+60,y+180,120,120);r2.setColor(COLOR(255,255,220));r2.setFill(1);r2.imprint();r2.moveTo(1000,1000);
    Rectangle r3(x+300,y+180,120,120);r3.setColor(COLOR(255,255,220));r3.setFill(1);r3.imprint();r3.moveTo(1000,1000);
    Rectangle r4(x+180,y+300,120,120);r4.setColor(COLOR(255,255,220));r4.setFill(1);r4.imprint();r4.moveTo(1000,1000);
    int x1=570,y1=70;
    Rectangle r11(x1+180,y1+60,120,120);r11.setColor(COLOR(255,255,220));r11.setFill(1);r11.imprint();r11.moveTo(1000,1000);
    Rectangle r21(x1+60,y1+180,120,120);r21.setColor(COLOR(255,255,220));r21.setFill(1);r21.imprint();r21.moveTo(1000,1000);
    Rectangle r31(x1+300,y1+180,120,120);r31.setColor(COLOR(255,255,220));r31.setFill(1);r31.imprint();r31.moveTo(1000,1000);
    Rectangle r41(x1+180,y1+300,120,120);r41.setColor(COLOR(255,255,220));r41.setFill(1);r41.imprint();r41.moveTo(1000,1000);
    Text t,t11,t22,t10;
    int i,j;
    if(n==1)
    {

        t10.reset(550,15,"Submitted Sudoku has more than one solution! Here is one of the solutions.");
        t10.imprint();
    }
    if(n==0)
    {

        t10.reset(550,15,"Submitted Sudoku has exactly one solution!");
        t10.imprint();
    }




    t11.reset(250,35,"Submitted Sudoku");t11.imprint();
    t22.reset(750,35,"Solution Sudoku");t22.imprint();
    Line l1[10];
    Line l2[10];

    for(i=-1;i<9;i++)
    {
        if(!((i%3==2)||(i%3==-1)))
        {
        l1[i+1].setColor(COLOR(205,201,201));
        l2[i+1].setColor(COLOR(205,201,201));
        l1[i+1].reset(110+(40*i),70,110+(40*i),430);l1[i+1].imprint();
        l2[i+1].reset(70,110+(40*i),430,110+(40*i));l2[i+1].imprint();

        }
        else
        {
        l1[i+1].reset(110+(40*i),70,110+(40*i),430);l1[i+1].imprint();
        l2[i+1].reset(70,110+(40*i),430,110+(40*i));l2[i+1].imprint();

        }
    }

    Text t1(90,460,"1");
    Text t2(130,460,"2");
    Text t3(170,460,"3");
    Text t4(210,460,"4");
    Text t5(250,460,"5");
    Text t6(290,460,"6");
    Text t7(330,460,"7");
    Text t8(370,460,"8");
    Text t9(410,460,"9");
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            switch(gridprob[i][j])
            {
                case 0:break;
                case 1:t1.moveTo(90+(40*i),90+(40*j));t1.imprint();break;
                case 2:t2.moveTo(90+(40*i),90+(40*j));t2.imprint();break;
                case 3:t3.moveTo(90+(40*i),90+(40*j));t3.imprint();break;
                case 4:t4.moveTo(90+(40*i),90+(40*j));t4.imprint();break;
                case 5:t5.moveTo(90+(40*i),90+(40*j));t5.imprint();break;
                case 6:t6.moveTo(90+(40*i),90+(40*j));t6.imprint();break;
                case 7:t7.moveTo(90+(40*i),90+(40*j));t7.imprint();break;
                case 8:t8.moveTo(90+(40*i),90+(40*j));t8.imprint();break;
                case 9:t9.moveTo(90+(40*i),90+(40*j));t9.imprint();break;


            }
        }
    }



    t1.reset(590,460,"1");
    t2.reset(630,460,"2");
    t3.reset(670,460,"3");
    t4.reset(710,460,"4");
    t5.reset(750,460,"5");
    t6.reset(790,460,"6");
    t7.reset(830,460,"7");
    t8.reset(870,460,"8");
    t9.reset(910,460,"9");
    for(i=-1;i<9;i++)
    {
         if(!((i%3==2)||(i%3==-1)))
        {
        l1[i+1].setColor(COLOR(205,201,201));
        l2[i+1].setColor(COLOR(205,201,201));
        l1[i+1].reset(610+(40*i),70,610+(40*i),430);l1[i+1].imprint();
        l2[i+1].reset(570,110+(40*i),930,110+(40*i));l2[i+1].imprint();

        }
        else
        {
        l1[i+1].reset(610+(40*i),70,610+(40*i),430);l1[i+1].imprint();
        l2[i+1].reset(570,110+(40*i),930,110+(40*i));l2[i+1].imprint();

        }
    }
    Text some(750,450,"Blue:Correct solutions!");some.setColor(COLOR(0,0,255));some.imprint();
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(gridprob[i][j]==gridprob1[i][j]){
            switch(gridprob1[i][j])
            {
                case 0:break;
                case 1:t1.moveTo(590+(40*i),90+(40*j));t1.imprint();break;
                case 2:t2.moveTo(590+(40*i),90+(40*j));t2.imprint();break;
                case 3:t3.moveTo(590+(40*i),90+(40*j));t3.imprint();break;
                case 4:t4.moveTo(590+(40*i),90+(40*j));t4.imprint();break;
                case 5:t5.moveTo(590+(40*i),90+(40*j));t5.imprint();break;
                case 6:t6.moveTo(590+(40*i),90+(40*j));t6.imprint();break;
                case 7:t7.moveTo(590+(40*i),90+(40*j));t7.imprint();break;
                case 8:t8.moveTo(590+(40*i),90+(40*j));t8.imprint();break;
                case 9:t9.moveTo(590+(40*i),90+(40*j));t9.imprint();break;

            }}
            else{
            switch(gridprob1[i][j])//Problem:-Club 1 with 21 and so on
            {
                case 0:break;
                case 1:t1.setColor(COLOR(0,0,255));t1.moveTo(590+(40*i),90+(40*j));t1.imprint();t1.setColor(COLOR(0,0,0));break;
                case 2:t2.setColor(COLOR(0,0,255));t2.moveTo(590+(40*i),90+(40*j));t2.imprint();t2.setColor(COLOR(0,0,0));break;
                case 3:t3.setColor(COLOR(0,0,255));t3.moveTo(590+(40*i),90+(40*j));t3.imprint();t3.setColor(COLOR(0,0,0));break;
                case 4:t4.setColor(COLOR(0,0,255));t4.moveTo(590+(40*i),90+(40*j));t4.imprint();t4.setColor(COLOR(0,0,0));break;
                case 5:t5.setColor(COLOR(0,0,255));t5.moveTo(590+(40*i),90+(40*j));t5.imprint();t5.setColor(COLOR(0,0,0));break;
                case 6:t6.setColor(COLOR(0,0,255));t6.moveTo(590+(40*i),90+(40*j));t6.imprint();t6.setColor(COLOR(0,0,0));break;
                case 7:t7.setColor(COLOR(0,0,255));t7.moveTo(590+(40*i),90+(40*j));t7.imprint();t7.setColor(COLOR(0,0,0));break;
                case 8:t8.setColor(COLOR(0,0,255));t8.moveTo(590+(40*i),90+(40*j));t8.imprint();t8.setColor(COLOR(0,0,0));break;
                case 9:t9.setColor(COLOR(0,0,255));t9.moveTo(590+(40*i),90+(40*j));t9.imprint();t9.setColor(COLOR(0,0,0));break;


            }
            }
        }
    }
    t1.moveTo(1000,1000);
    t2.moveTo(1000,1000);
    t3.moveTo(1000,1000);
    t4.moveTo(1000,1000);
    t5.moveTo(1000,1000);
    t6.moveTo(1000,1000);
    t7.moveTo(1000,1000);
    t8.moveTo(1000,1000);
    t9.moveTo(1000,1000);
    Rectangle returnback(500,450,80,40);
    Rectangle rb1,rb2;
    rb2.reset(500,450,84,44);rb2.imprint();
    rb1.reset(500,450,78,38);rb1.setColor(COLOR(235,235,235));rb1.setFill(1);rb1.imprint();rb1.moveTo(1000,1000);
    Text returnback1(500,450,"Return Back!");
    int getx;int gety;int get;
    do
    {
        get = getClick();
        getx=get/65536;
        gety=get%65536;
    }while(getx>540 || getx<460 ||gety>470 || gety<430);
    return;

}
}
void leaderboard(float score)
{
    closeCanvas();
    initCanvas("Leader Board",500,500);//initiate canvas
    person p,p1,max[5];//declarations
    int i=0,j,rec_size=sizeof(p);
    FILE *f;
    f=fopen("lboard.bin","ab+");//opening a file for both reading and writing.
    if(f==NULL)
    {
        cout<<"Error";
        return;
    }
    //buttons creation on the leaderboard window
    Rectangle r,rback;
    Text t1,t2,t,tback;
    Rectangle rb11,rb12;
    rb12.reset(250,125,84,44);rb12.imprint();rb12.hide();
    rb11.reset(250,125,78,38);rb11.setColor(COLOR(235,235,235));rb11.setFill(1);rb11.imprint();rb11.moveTo(1000,1000);
    char ch[48],str[80];//declarations
    t1.reset(250,35,"Please Enter Your Name:");
    t2.reset(250,125,"Submit");
    r.reset(250,125,80,40);
    XEvent e;
    while(i<48)
    {
        nextEvent(e);
        if(mouseButtonPressEvent(e))//detects mouseclick
        {
            if((e.xbutton.x>=210 && e.xbutton.x<=290)&&(e.xbutton.y>=105 && e.xbutton.y<=145))
            {
                //leaderboard to be displayed
                Rectangle blank;
                blank.reset(250,250,500,500);blank.setColor(COLOR(255,255,255));blank.setFill(1);blank.imprint();blank.hide();
                Rectangle rb11,rb12;
                rb12.reset(250,450,104,44);rb12.imprint();


                tback.reset(250,450,"Main Menu");tback.imprint();
                rback.reset(250,450,100,40);

                j=0;
                ch[0]=toupper(ch[0]);//converts the first letter to uppercase.
                strcpy(p.name,ch);//copy the name entered into the internal variables
                p.score=score;//recording the score
                fwrite(&p,rec_size,1,f);
                t.hide();

                t1.reset(250,35,"Leaderboard");
                t2.hide();
                r.hide();
                fseek(f,0,SEEK_SET);
                max[0].score=max[1].score=max[2].score=max[3].score=max[4].score=0;
                //initialization
                strcpy(max[0].name," ");
                strcpy(max[1].name," ");
                strcpy(max[2].name," ");
                strcpy(max[3].name," ");
                strcpy(max[4].name," ");
                do
                {   //writing on to the file
                    fread(&p1,rec_size,1,f);
                    if(feof(f))
                    break;
                    //finding the top five scorers
                    if(p1.score>=max[0].score)
                    {
                        max[4]=max[3];
                        max[3]=max[2];
                        max[2]=max[1];
                        max[1]=max[0];
                        max[0]=p1;
                    }
                    else if(p1.score>=max[1].score)
                    {
                        max[4]=max[3];
                        max[3]=max[2];
                        max[2]=max[1];
                        max[1]=p1;
                    }
                    else if(p1.score>=max[2].score)
                    {
                        max[4]=max[3];
                        max[3]=max[2];
                        max[2]=p1;
                    }
                    else if(p1.score>=max[3].score)
                    {
                        max[4]=max[3];
                        max[3]=p1;
                    }
                    else if(p1.score>=max[4].score)
                    {
                        max[4]=p1;
                    }
                }while(!feof(f));
                for(j=0;j<5;j++)
                {
                    sprintf(str,"%4.1f",(max[j].score));
                    t.reset(200,75+(40*j),max[j].name);t.imprint();
                    t.reset(300,75+(40*j),str);t.imprint();
                }
                fclose(f);
    int c,cx,cy;//for getting click on the submit button
    do
    {
        c=getClick();
        cx=c/65536;
        cy=c%65536;
        if((cx>=200)&&(cx<=300)&&(cy>=430)&&(cy<=470))
        break;
    }while(1);
                return;
            }
        }
        else if(keyPressEvent(e))//detecting the keypress event
        {
            if (charFromEvent(e)==13)//enter key is preessed
            {
                Rectangle blank;
                blank.reset(250,250,500,500);blank.setColor(COLOR(255,255,255));blank.setFill(1);blank.imprint();blank.hide();
                Rectangle rb11,rb12;
                rb12.reset(250,450,104,44);rb12.imprint();

                tback.reset(250,450,"Main Menu");tback.imprint();
                rback.reset(250,450,100,40);
                j=0;
                ch[0]=toupper(ch[0]);
                strcpy(p.name,ch);
                p.score=score;
                fwrite(&p,rec_size,1,f);
                t.hide();
                t2.hide();
                r.hide();

                t1.reset(250,35,"Leaderboard");

                fseek(f,0,SEEK_SET);
                max[0].score=max[1].score=max[2].score=max[3].score=max[4].score=0;
                strcpy(max[0].name," ");
                strcpy(max[1].name," ");
                strcpy(max[2].name," ");
                strcpy(max[3].name," ");
                strcpy(max[4].name," ");
                do
                {
                    fread(&p1,rec_size,1,f);
                    if(feof(f))
                    break;

                    if(p1.score>=max[0].score)
                    {
                        max[4]=max[3];
                        max[3]=max[2];
                        max[2]=max[1];
                        max[1]=max[0];
                        max[0]=p1;
                    }
                    else if(p1.score>=max[1].score)
                    {
                        max[4]=max[3];
                        max[3]=max[2];
                        max[2]=max[1];
                        max[1]=p1;
                    }
                    else if(p1.score>=max[2].score)
                    {
                        max[4]=max[3];
                        max[3]=max[2];
                        max[2]=p1;
                    }
                    else if(p1.score>=max[3].score)
                    {
                        max[4]=max[3];
                        max[3]=p1;
                    }
                    else if(p1.score>=max[4].score)
                    {
                        max[4]=p1;
                    }
                }while(!feof(f));
                for(j=0;j<5;j++)
                {
                    sprintf(str,"%4.1f",(max[j].score));
                    t.reset(200,75+(40*j),max[j].name);t.imprint();
                    t.reset(300,75+(40*j),str);t.imprint();
                }
                fclose(f);
    int c,cx,cy;
    do
    {
        c=getClick();
        cx=c/65536;
        cy=c%65536;
        if((cx>=200)&&(cx<=300)&&(cy>=430)&&(cy<=470))
        break;
    }while(1);
                return;
            }
            else if (charFromEvent(e)==8)//backspace is pressed
            {
                ch[--i]='\0';
                t.reset(250,80,ch);
            }

            else if((charFromEvent(e)>47 && charFromEvent(e)<58)||(charFromEvent(e)>64 && charFromEvent(e)<91)||(charFromEvent(e)>96 && charFromEvent(e)<123)||(charFromEvent(e)==32))
            {
                ch[i++]=charFromEvent(e);//updating the name as the user types
                ch[i]='\0';
                t.reset(250,80,ch);
            }
        }
    }


}
