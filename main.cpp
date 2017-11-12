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
 ^           in the MSc Nanosciences & Nanotechnologies.
 *                              ***
 ^ Demo Version - this is intended purely for reviewing
 *                              ***
 * */
#include <iostream>
#include <windows.h>
#include <random>
#include <iomanip>
#include "functions.h"

using namespace std;

int main()
{
    int menu_item=0, x=7, i=0;
    bool running = true;
    srand(5285);
    string saveLocation = ExePath();

    gotoXY(18,5); cout << "Main Menu";
    gotoXY(18,7); cout << "->";

    while(running)
    {
        gotoXY(20,7);  cout << "1) Average of N random  numbers  taken  from ";
        gotoXY(20,8);  cout << "   a uniform random number distribution.";
        gotoXY(20,9);  cout << "   N =[10,100,1000,10000,100000,1000000]";
        gotoXY(20,10); cout << "2) 1000 steps a) 1 dimensional b) 2 dimensional & ";
        gotoXY(20,11); cout << "   calculate the square displacement R^2. Find the";
        gotoXY(20,12); cout << "   mean square displacement, namely <R^2> for 10000 runs.";
        gotoXY(20,13); cout << "3) Find <R2> every 100 steps, from 0 to 1000, perform 10000 runs";
        gotoXY(20,14); cout << "   and find 10 points (one every 100 steps) of which every point will";
        gotoXY(20,15); cout << "   be the average of 10000 runs.";
        gotoXY(20,16); cout << "4) ... ";
        gotoXY(20,17); cout << "   ... ";
        gotoXY(20,18); cout << "   ... ";
        gotoXY(20,19); cout << "5) ... ";
        gotoXY(20,20); cout << "   ... ";
        gotoXY(20,21); cout << "   ... ";
        gotoXY(20,22); cout << "6)Generate a 2D lattice with random positioned traps & concentration c.";
        gotoXY(20,23); cout << "  One particle performs a random walk & will stop when it will fall on a trap";
        gotoXY(20,24); cout << "  Save the trapping times and make the distribution for 100000 runs.";
        gotoXY(20,25); cout << "7)Quit Program";

        system("pause>nul"); // the >nul bit causes it the print no message

        if(GetAsyncKeyState(VK_DOWN) && x != 25) //down button pressed
        {
            gotoXY(18,x); cout << "  ";
            x=x+3;
            gotoXY(18,x); cout << "->";
            menu_item++;
            continue;

        }

        if(GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
        {
            gotoXY(18,x); cout << "  ";
            x=x-3;
            gotoXY(18,x); cout << "->";
            menu_item--;
            continue;
        }

        if(GetAsyncKeyState(VK_RETURN)){ // Enter key pressed

            switch(menu_item){

                case 0: {
                    clear_screen();
                    double avgtable[6];
                    for(i = 0; i < 6; i++)
                    {
                        double power=i+1,resultpp;
                        unsigned int resultp=0;int tstvar=0;
                        //--------------------------- path and name ----------------------------------------------------
                        stringstream ss;
                        string location, filename;
                        location = saveLocation + "\\1stEx_rand-10^";
                        ss << location << power << ".txt";
                        filename = ss.str();
                        //----------------------------------------------------------------------------------------------
                        std::ofstream outputFile(filename);
                        //outputFile.open(filename);
                        //pow() returns a floating point value, and due to floating point arithmetic,
                        //100 (etc) is estimated ~ 99.999...& due to integer truncation it gets truncated down to 99.
                        // + 0.5; would do the trick.
                        resultpp=pow(10.0,power)+0.5;
                        resultp= (unsigned int)resultpp;
                        std::vector<double> grid = fillGridURandom(resultp);
                        for(auto it = grid.begin(); it != grid.end(); it++)
                        {
                            if(*it == grid[resultp])
                            {
                                avgtable[i]=*it;
                                outputFile << "This is the Average value" << endl;
                            }
                            outputFile << tstvar << ")"<< setprecision (6) << fixed << *it << endl; tstvar++;
                        }
                        outputFile.close();
                        cout << "\nOutput File 10^" << i+1 <<" Done! Waiting..";
                    }
                    string location = saveLocation + "\\1stEx_average_results_file.txt";
                    std::ofstream outputFile(location);
                    for(i = 0; i < 6; i++)
                    {
                        outputFile << setprecision (6) << fixed << avgtable[i] << endl;
                    }
                    outputFile.close();
                    cout << "Process complete! You may continue.\n Output files can be found at:"<< saveLocation << endl;

                    break;
                }
                case 1: {
                    clear_screen();
                    cout << "Exercise 2 running." << endl;
                    int nSteps=1000,two_step=1 ,Run=10000, displacement=1, Dimensions=2; bool Fixed=false;//MAX 2
                    vector<vector <unsigned int>> squareD;
                    double sdSam[2];
                    double msd=0;

                    squareD = squareDisplacement(nSteps,two_step , Run, displacement, Dimensions, Fixed);

                    for( i=0; i<2; i++)
                    {
                        sdSam[i]=0;
                        for(int j=0; j<Run; j++)
                        {
                            sdSam[i]=sdSam[i]+squareD[i][j];
                        }
                    }
                    ofstream f("2ndEx_output.txt");
                    msd=sdSam[1]/Run;
                    f << "Mean Sqr Disp 2d" <<endl;
                    f << msd <<endl;
                    msd=sdSam[0]/Run;
                    f << "Mean Sqr Disp 1d" <<endl;
                    f << msd <<endl;
                    f.close();
                    cout << "Done" << endl;
                    break;
                }

                case 2: {
                    clear_screen();
                    cout << "Exercise 3 running "<<endl;

                    FILE *outputFile;//myfilename;
                    int j,t;
                    int pos[NP+5][2];
                    double msd,xhelp;
                    int xdummy;

                    /* Set up output file */
                    if((outputFile=fopen("3rdEx_RandomWalk.txt","w"))== nullptr){
                        cout <<"File 'RandomWalk.txt' didn't succeed to open."<<endl;
                        cout << "Exiting..."<<endl;
                        exit(0);
                    }
                    fprintf(outputFile,"  Time     MSD    \n");
                    fprintf(outputFile,"==================\n");

                    /* Set initial position to zero */
                    for(i=0;i<NP;i++){
                        for(j=0;j<2;j++){
                            pos[i][j]=0;
                        }
                    }

                    /* Start of main loop */
                    xdummy=0;
                    for(t=1;t<=TIME;t++){
                        xdummy++;
                        for(i=0;i<NP;i++){
                            /* Move particle to the right or to the left */
                            xhelp=dis(gen);//rndm();
                            if(xhelp<0.25){
                                pos[i][0]--;
                            }
                            else{
                                if(xhelp<0.50){
                                    pos[i][1]--;
                                }
                                else{
                                    if(xhelp<0.75){
                                        pos[i][0]++;
                                    }
                                    else{
                                        pos[i][1]++;
                                    }
                                }
                            }
                        }
                        if(xdummy==FLAG){
                            /* Calculate mean square displacement (MSD) */
                            msd=0.0;
                            for(i=0;i<NP;i++){
                                msd=msd+(pos[i][0]*pos[i][0])+(pos[i][1]*pos[i][1]);
                            }
                            msd=msd/((double)(NP));
                            fprintf(outputFile," %5d \t %10.6lf\n",t,msd);
                            xdummy=0;
                        }
                    }

                    fclose(outputFile);
                    cout << "Done!" <<endl;
                    break;
                }

                case 3: {
                    clear_screen();
                    DisplayMessage();
                    break;
                }

                case 4: {
                    clear_screen();
                    DisplayMessage();
                    break;
                }

                case 5: {
                    clear_screen();
                    cout << "Exercise 6   Loading... ";
                    //c = 10^-2 and 10^-3 aka 0.01 & 0.001
                    int j=0,k=0,steps=0,chanceCounter=0;
                    //i=0;
                    double unreal;
                    vector<vector<unsigned int>> lattice;
                    //-------------------------------- Maps ------------------------------------------------------------
                    map <int, int> clickMap;
                    map <int, int> stepMap;
                    map <double, int> msMap;
                    pair<map<int, int>::iterator, bool> result0;
                    pair<map<double, int>::iterator, bool> result1;
                    //--------------------------------------------------------------------------------------------------

                    while(chanceCounter<2)
                    {
                        stringstream ss;
                        string location, filename;
                        location = saveLocation + "\\6thEx_TimedTraps_v";
                        ss << location << chanceCounter << ".txt";
                        filename = ss.str();
                        ofstream outputFile6(filename);
                        outputFile6 << fixed << setprecision(6) << endl;

                        if(chanceCounter!=0)
                        {
                            lattice = fillboard(Height, Width, Chance2);
                            outputFile6 << " Run \t Clicks \t Time(s) \t Steps" << " \t Concentration:" << Chance2 << endl;
                        }
                        else
                        {
                            lattice = fillboard(Height, Width, Chance);
                            outputFile6 << " Run \t Clicks \t Time(s) \t Steps" << " \t Concentration:" << Chance <<endl;
                        }

                        for (k = 0; k < Runs; k++)
                        {
                            const clock_t begin_time = clock();
                            clock_t time;

                            i = int(dis2(gen))%Height;//rand()%1000;//(Height / 2) - 1;
                            j = int(dis2(gen))%Width;//rand()%1000; //(Width / 2) - 1;

                            while (lattice[i][j] != 1) {

                                unreal = dis(gen);

                                if (unreal < 0.25)
                                    i++;//=i+1;
                                else if ((unreal < 0.5) && (unreal >= 0.25))
                                    i--;//=i-1;
                                else if ((unreal < 0.75) && (unreal >= 0.5))
                                    j++;//=j+1;
                                else if ((unreal <= 1.0) && (unreal >= 0.75))
                                    j--;//=j-1;

                                if (i > (Height - 1))
                                    i--;
                                else if (i < 0)
                                    i++;
                                else if (j > (Width - 1))
                                    j--;
                                else if (j < 0)
                                    j++;

                                steps++;
                                // << "position=>" << " X:" << i << " Y:" << j << ;
                            }
                            time = clock() - begin_time;
                            outputFile6 << " " << k + 1 << " \t " << time << " \t\t " << float(clock() - begin_time) / CLOCKS_PER_SEC << "\t " << steps << endl;
                            //----------------------------- mapping ----------------------------------------------------
                            result0 = stepMap.insert(pair<int, int>(steps, 1));
                            //cout << "result data" << result0.first << result0.second << endl;
                            if(result0.second){
                                //Duplicate added! Error!
                            }
                            else{
                                result0 = stepMap.insert(pair<int, int>(steps, 1));
                                stepMap[steps]=stepMap[steps]+1;
                            }

                            //------------------------------------------------------------------------------------------
                            steps = 0;
                        }
                        //---------------------------- insert map data to file -----------------------------------------
                        outputFile6 << "-------------------------" << endl;
                        outputFile6 << " Steps \t Times repeated " << endl;
                        map<int, int>::iterator itr;
                        for(itr=stepMap.begin(); itr != stepMap.end(); ++itr)
                            outputFile6 << " " << itr->first << "\t\t" << itr->second << endl;
                        //----------------------------------------------------------------------------------------------
                        outputFile6.close();cout << "\nOutput File 6thEx_TimedTraps Run" << chanceCounter+1 <<" is Complete! Waiting...\n";
                        stepMap.clear();
                        chanceCounter++;
                    }cout << "Process complete! You may continue.\n Output files can be found at:"<< saveLocation << endl;
                    break;
                }

                case 6: {
                    clear_screen();
                    cout << "The program has now terminated!!";
                    running = false;
                }
                default:
                    clear_screen();
                    cout << "Bad choice! Please try again later.\n";
                    break;
            }

        }

    }

    gotoXY(20,31);
    return 0;
}
