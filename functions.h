/*
 * @Copyright Copyright (C) 2017 Chris Tzatzakis
 * @license GNU/GPL http://www.gnu.org/copyleft/gpl.html
 * Company:		Chris Tzatzakis
 + Contact:		Chris.Tzatzakis@hotmail.com
 ^
 + Project: 		Monte Carlo based simulations
 * File Name:	Models_&_Simulation_Techniques.cpp
 ^                              ***
 * Description: Simulation Exercises access point for result extraction.
 ^ The set of exercises, presented below is part of the curriculum in
 *       Models and Theories of Molecular and Atomic Processes
 ^            in the MSc Nanosciences & Nanotechnologies.
 *                              ***
 ^ Demo Version - this is intended purely for reviewing
 *                              ***
 * */
#include <iostream>
#include <windows.h>
#include <random>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <time.h>
#include <string.h>

using namespace std;
//========================================================== Project functions =========================================
// ====================================================== Parameters Declarations ============================================

// Exercise 3 variables
#define TIME 1000 /* number of time steps aka steps*/
#define FLAG 100  /* base step */
#define NP 10000  /* number of Runs */
//Exercise 6 variables
#define Height 1000
#define Width 1000
#define Chance 0.01
#define Chance2 0.001
#define Runs 100000

std::random_device rd;
std::mt19937_64 gen(rd()); //gen(5285);//Standard mersenne_twister_engine seeded with random device or a specified number.
std::uniform_real_distribution<> dis(0, 1);
std::uniform_real_distribution<> dis2(0, Height*Width);


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto
//============================================================== main ==================================================
void gotoXY(int x, int y)
{
    CursorPosition.X = (short)x;
    CursorPosition.Y = (short)y;
    SetConsoleCursorPosition(console,CursorPosition);
}

int DisplayMessage()
{
    MessageBox( nullptr, TEXT( "Have not updated current content yet." ), TEXT( "Message" ), MB_OK );
}

void clear_screen()
{
    gotoXY(20,30);
   for(int i=0; i < 10; i++)
   {
       cout << "                                                                                              " << endl;
   }
    gotoXY(20,30);
}

string ExePath(void) {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    return string( buffer ).substr( 0, pos);
}

std::vector<double> fillGridURandom(unsigned int X)
{
    double sum=0, avg=0;
    unsigned int Y=X+1;
    vector<double> grid(Y);

    for (int n = 0; n < X; ++n) {
        grid[n]=dis(gen);
        sum=sum+dis(gen);
    }
    avg=sum/X;
    grid[X]=avg;
    return grid;
}

std::vector<vector <unsigned int>> fillboard(unsigned int X, unsigned int Y, double C)
{
    vector <vector <unsigned int>> grid (X,vector<unsigned int>(Y,0));
    int i,j;
    int traps=0;
    for(i=0; i<X; i++)
    {
        for(j=0; j<Y; j++)
        {
            if(dis(gen)<C)
            {
                grid[i][j]=1;
                traps++;
            }
            else
                grid[i][j]=0;
        }
    }
    if(traps==0)
        grid[X-1][Y-1]=1;

    return grid;
}

std::vector<vector<unsigned int>> squareDisplacement(int nSteps,int two_step , int Repeats, int displacement, int Dimensions, bool FixedD) {
    int Si=0 ,Sj=0;
    std::mt19937_64 gen(5285);
    std::uniform_real_distribution<> dis(0, 1);
    int dCounter=0;// pos[Runs+5][2];
    double unreal;
    unsigned int X=4;
    vector<vector <unsigned int>> squareDis(X,vector< unsigned int>(unsigned (Repeats),0));

    while(dCounter<2)
    {
        for (int i = 0; i < Repeats; i = i + 1)
        {
            Si = Sj =  0;
            for (int j = 0; j < nSteps; j = j + two_step)
            {
                unreal=dis(gen);
                //for 2D run only
                if((FixedD==1)&&(Dimensions > 1))
                    dCounter=1;

                if(dCounter >0) //if else for 1D or 2D run
                {
                    if (unreal < 0.25)
                        Si = Si + displacement;
                    else if ((unreal < 0.5) && (unreal >= 0.25))
                        Si = Si - displacement;
                    else if ((unreal < 0.75) && (unreal >= 0.5))
                        Sj = Sj + displacement;
                    else if ((unreal <= 1.0) && (unreal >= 0.75))
                        Sj = Sj - displacement;
                }
                else{
                    if (unreal < 0.5)
                        Si = Si + 1;
                    else
                        Si = Si - 1;
                }

            }
            if(dCounter > 0 )
            {
                squareDis[dCounter][i]= int (pow(Si,2.0))+int (pow(Sj,2.0));
            }
            else
                squareDis[dCounter][i]= int (pow(Si,2.0));
        }
        if((Dimensions == 1))
            dCounter=dCounter+2;
        else
            dCounter++;
    }

    return squareDis;

}
