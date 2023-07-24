//============================================================================
// Name        : Tetris.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
//#include<cstdlib>
#include<ctime>
#include<string>
//#include<sys/wait.h>
//#include<stdlib.h>
//#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath>      // for basic math functions such as cos, sin, sqrt
#include<fstream>
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * Main Canvas drawing function.
 * */
 
 
double startx = 320 , starty = 400;
double fruitx , fruitx2 , fruitx3 , fruitx4 , fruitx5 , fruity , fruity2 , fruity3 , fruity4 , fruity5;
double pfruitx , pfruity;
int score = 0;
bool Gameover = false;
int tailx[133] , taily[133];
int sizetail = 4; 
bool a = false;
bool Menu = false;
bool highscoreshower = false;
int box = 490;
int temp1 = 0 , temp2 = 0 , temp3 = 0 , temp4 = 0 , temp5 = 0 , temp6 = 0;

int key1 = rand()%4+1;
int endcounter = 0;


int counterline1 = 0;
int counterline2 = 0;
int counterline3 = 0;
int counterline4 = 0;
int linehorizontal = 1;
int linevertical = 1;
int linerandom = 1;
int lx1 , lx2 , lx3 , lx4 , lx5 , lx6 , ly1 , ly2 , ly3 , ly4 , ly5 , ly6;


int score1[30] = { 120 , 130 , 140 , 150 , 160 , 170 , 180 , 190 , 200 , 210 , 220 , 230 , 240 , 250 , 260 , 270 , 280 , 290 , 300 , 310 , 320 , 330 , 340 , 350 , 360 , 370 , 380 , 390 ,
		   400 , 410};
int array1[30] = { 5 , 10 , 15 , 20 , 25 , 30 , 35 , 40 , 45 , 50 , 55 , 60 , 65 , 70 , 75 , 80 , 85 , 90 , 95 , 100 , 105 , 110 , 115 , 120 , 125 , 
		   130 , 135 , 140 , 145 , 150}; //level 1
int array2[30] = { 155 , 160 , 165 , 170 , 175 , 180 , 185 , 190 , 195 , 200 , 205 , 210 , 215 , 220 , 225 , 230 , 235 , 240 , 245 , 250 , 255 , 260 , 265 , 270 ,
		   275 , 280 , 285 , 290 , 295 , 300}; // level 2
int array3[30] = { 305 , 310 , 315 , 320 , 325 , 330 , 335 , 340 , 345 , 350 , 355 , 360 , 365 , 370 , 375 , 380 , 385 , 390 , 395 , 400 , 405 , 410 , 415 , 420 , 425 , 430 , 440 , 445 , 450}; // level 3	
int array4[30] = { 455 , 460 , 465 , 470 , 475 , 480 , 485 , 490 , 495 , 500 , 505 , 510 , 515 , 520 , 525 , 530 , 535 , 540 , 545 , 550 , 555 , 560 , 565 , 570 , 575 , 580 , 585 , 590 , 595 , 			   600};// level 4	   


void corrector(int , int);
void corrector2(int , int);
void corrector3(int , int);
void corrector4(int , int);
void corrector5(int , int);
void pcorrector(int , int);


void showscore()
{
	string s1;
	s1 = to_string(score);
	DrawString( 590 , 600 , s1 , colors[127]);
}



void drawsnake()
{
	for (int i = 0 ; i < 650 ; i++)
	{
		for (int j = 0 ; j < 650 ; j++)
		{
			if (i == startx && j == starty)
			{
				DrawCircle(startx+5 , starty+5 , 6 , colors[67]);
			}
			else
			{
				for (int count1 = 1 ; count1 < sizetail ; count1++)
				{
					if (tailx[count1] == i && taily[count1] == j)
					{
						DrawSquare( i , j , 11 , colors[67]);
					}
				}
			}
		}
	}
}


int normalfood = 0;
int powerfood = 0;
int powerfood2  = 0;
int normalfood2 = 0;
int normalfood3 = 0;
int normalfood4 = 0;
int normalfood5 = 0;

void normalfoodtimer()
{
	normalfood++;
	if (normalfood == 75)
	{ 
		corrector(fruitx , fruity);
		normalfood = 0;
	}
}

void normalfoodtimer2()
{
	normalfood2++;
	if (normalfood2 == 75)
	{ 
		corrector2(fruitx2 , fruity2);
		normalfood2 = 0;
	}
}

void normalfoodtimer3()
{
	normalfood3++;
	if (normalfood3 == 75)
	{ 
		corrector3(fruitx3 , fruity3);
		normalfood3 = 0;
	}
}

void normalfoodtimer4()
{
	normalfood4++;
	if (normalfood4 == 75)
	{ 
		corrector4(fruitx4 , fruity4);
		normalfood4 = 0;
	}
}

void normalfoodtimer5()
{
	normalfood5++;
	if (normalfood5 == 75)
	{ 
		corrector5(fruitx5 , fruity5);
		normalfood5 = 0;
	}
}


void powerfoodtimer1()
{
	powerfood++;
	powerfood2++;
	if (powerfood == 375)
	{
		pcorrector(pfruitx , pfruity);
		powerfood = 0;
	}
}

void powerfooddisplayer()
{
        if (powerfood2 != 150 && powerfood > 300 && powerfood < 375 )
        {
        	DrawSquare(pfruitx , pfruity , 10 , colors[23]);
	} 
	else if (powerfood2 == 150)
	{
		powerfood2 = 0;
	} 	
}

void foodchecker2()
{
	if (fruitx == fruitx2 && fruity != fruity2)
	{
		corrector(0,0);
	}
	if (fruitx != fruitx2 && fruity == fruity2)
	{
		corrector2(0,0);
	}
	if (fruitx == fruitx3 && fruity != fruity3)
	{
		corrector(0,0);
	}
	if (fruitx != fruitx3 && fruity == fruity3)
	{
		corrector3(0,0);
	}
	if (fruitx == fruitx4 && fruity != fruity4)
	{
		corrector(0,0);
	}
	if (fruitx != fruitx4 && fruity == fruity4)
	{
		corrector4(0,0);
	}
	if (fruitx == fruitx5 && fruity != fruity5)
	{
		corrector(0,0);
	}
	if (fruitx != fruitx5 && fruity == fruity5)
	{
		corrector5(0,0);
	}
	
	if (fruitx2 == fruitx3 && fruity2 != fruity3)
	{
		corrector2(0,0);
	}
	if (fruitx2 != fruitx3 && fruity2 == fruity3)
	{
		corrector3(0,0);
	}
	if (fruitx2 == fruitx4 && fruity2 != fruity4)
	{
		corrector2(0,0);
	}
	if (fruitx2 != fruitx4 && fruity2 == fruity4)
	{
		corrector4(0,0);
	}
	if (fruitx == fruitx5 && fruity2 != fruity5)
	{
		corrector2(0,0);
	}
	if (fruitx2 != fruitx5 && fruity2 == fruity5)
	{
		corrector5(0,0);
	}
	
	if (fruitx3 == fruitx4 && fruity3 != fruity4)
	{
		corrector3(0,0);
	}
	if (fruitx3 != fruitx4 && fruity3 == fruity4)
	{
		corrector4(0,0);
	}
	if (fruitx3 == fruitx5 && fruity3 != fruity5)
	{
		corrector3(0,0);
	}
	if (fruitx3 != fruitx5 && fruity3 == fruity5)
	{
		corrector5(0,0);
	}
	
	if (fruitx4 == fruitx5 && fruity4 != fruity5)
	{
		corrector4(0,0);
	}
	if (fruitx4 != fruitx5 && fruity4 == fruity5)
	{
		corrector5(0,0);
	}
}

void foodchecker()
{
	foodchecker2();
	if (fruitx == fruitx2 && fruity == fruity2)
	{
		corrector2(0,0);
	}
	if (fruitx == fruitx3 && fruity == fruity3)
	{
		corrector3(0,0);
	}
	if (fruitx == fruitx4 && fruity == fruity4)
	{
		corrector4(0,0);
	}
	if (fruitx == fruitx5 && fruity == fruity5)
	{
		corrector5(0,0);
	}
        if (startx == fruitx && starty == fruity)
        {
        	normalfood = 0;
        	score += 5;
        	corrector(fruitx , fruity);
        	sizetail++;
        }
        if (startx == fruitx2 && starty == fruity2)
        {
        	normalfood2 = 0;
        	score += 5;
        	corrector2(fruitx2 , fruity2);
        	sizetail++;
        }
        if (startx == fruitx3 && starty == fruity3)
        {
        	normalfood3 = 0;
        	score += 5;
        	corrector3(fruitx3 , fruity3);
        	sizetail++;
        }
        if (startx == fruitx4 && starty == fruity4)
        {
        	normalfood4 = 0;
        	score += 5;
        	corrector4(fruitx4 , fruity4);
        	sizetail++;
        } 
        if (startx == fruitx5 && starty == fruity5)
        {
        	normalfood5 = 0;
        	score += 5;
        	corrector5(fruitx5 , fruity5);
        	sizetail++;
        }
        if (startx == pfruitx && starty == pfruity)
        {
        	powerfood = 0;
        	score += 20;
        	pcorrector(pfruitx , pfruity);
        	sizetail++;
        }	
}

void tempfruit()
{
	if (temp1 == 1)
	{
		corrector(fruitx , fruity);
		temp1 = 0;
	}
	
}

void tempfruit2()
{
	if (temp3 == 1)
	{
		corrector2(fruitx2 , fruity2);
		temp3 = 0;
	}
	
}

void tempfruit3()
{
	if (temp4 == 1)
	{
		corrector3(fruitx3 , fruity3);
		temp4 = 0;
	}
	
}

void tempfruit4()
{
	if (temp5 == 1)
	{
		corrector4(fruitx4 , fruity4);
		temp5 = 0;
	}
	
}

void tempfruit5()
{
	if (temp6 == 1)
	{
		corrector5(fruitx5 , fruity5);
		temp6 = 0;
	}
	
}


void temppfruit()
{
	if (temp2 == 1)
	{
		pcorrector(pfruitx , pfruity);
		temp2 = 0;
	}
}


void movesnake()
{

	if (key1 == 1)
	{
		startx -= 10;
	}
	else if (key1 == 2)
	{
		startx += 10;
	}
	else if (key1 == 3)
	{
		starty += 10;
	}
	else if (key1 == 4)
	{
		starty -= 10;
	}
	
	
	int prevx , prevy , prev2x , prev2y; 
	tailx[0] = startx;
	taily[0] = starty; 
	prevx = tailx[0];
	prevy = taily[0];
	for (int i = 1 ; i < sizetail ; i++)
	{
		 		
		prev2x=tailx[i];
		prev2y=taily[i];
		
		tailx[i]=prevx;
		taily[i]=prevy;
		
		prevx=prev2x;
		prevy=prev2y; 
	}
	if (startx > 640 || startx < 0 || starty > 580 || starty < 0)
        {
        	Gameover = true;
   		startx = 320;
   		starty = 400;
   		normalfood = 0;
   		normalfood2 = 0;
   		normalfood3 = 0;
   		normalfood4 = 0;
   		normalfood5 = 0;
   		powerfood = 0;
   		powerfood2 = 0;
   		endcounter = 0;
   		counterline1 = 0;
   		counterline2 = 0;
   		a = false;
   		sizetail = 4; 
   		temp1 = 0;
   		temp2 = 0;
   		temp3 = 0;
   		temp4 = 0;
   		temp5 = 0;
   		temp6 = 0;
   		tailx[0] = startx;
   		taily[0] = starty;
        } 		
		
}



void linerandomizer1()
{
	linehorizontal = rand()%2;
	lx1 = (rand()%53*10);
	lx2 = lx1+70;
	ly1 = (rand()%53*10);
	ly2 = ly1;
}

void linerandomizer2()
{
	linevertical = rand()%2;
	lx3 = (rand()%53*10);
	lx4 = lx3;
	ly3 = (rand()%45*10);
	ly4 = lx3+70;	
}

void linerandomizer3()
{
	linerandom = rand()%2;
	lx5 = (rand()%53*10);
	ly5 = (rand()%45*10);
	if (linerandom == 0)
	{
		lx6 = lx5+70;
		ly6 = ly5;
	}
	else
	{
		lx6 = lx5;
		ly6 = ly5+70;
	}	
}

void Checker()
{
	if (lx1 == startx && ly1 == starty)
	{
		linerandomizer1();
		linerandomizer2();
	}
	else if (lx2 == startx && ly2 == starty)
	{
		linerandomizer1();
		linerandomizer2();
	}
	else if (lx3 == startx && ly3 == starty)
	{
		linerandomizer1();
		linerandomizer2();
	}
	else if (lx4 == startx && ly4 == starty)
	{
		linerandomizer1();
		linerandomizer2();
	}
	else if (lx5 == startx && ly5 == starty)
	{
		linerandomizer3();
	}
	else if (lx6 == startx && ly6 == starty)
	{
		linerandomizer3();
	}
}

void collisiondetectorlines()
{
	Checker();
	if (linehorizontal == 1)
	{
		if (startx <= lx2 && startx >= lx1 && starty == ly1)
		{
			Gameover = true;
   			startx = 320;
   			starty = 400;
   			normalfood = 0;
   			normalfood2 = 0;
   			normalfood3 = 0;
   			normalfood4 = 0;
   			normalfood5 = 0;
   			powerfood = 0;
   			powerfood2 = 0;
   			endcounter = 0;
   			counterline1 = 0;
   			counterline2 = 0;
   			a = false;
   			sizetail = 4; 
   			temp1 = 0;
   			temp2 = 0;
   			temp3 = 0;
   			temp4 = 0;
   			temp5 = 0;
   			temp6 = 0;
   			tailx[0] = startx;
   			taily[0] = starty;	
		}
	}
	if (linevertical == 1)
	{
		if (startx == lx3 && starty >= ly3 && starty <= ly4)
		{
			Gameover = true;
   			startx = 320;
   			starty = 400;
   			normalfood = 0;
   			normalfood2 = 0;
   			normalfood3 = 0;
   			normalfood4 = 0;
   			normalfood5 = 0;
   			powerfood = 0;
   			powerfood2 = 0;
   			endcounter = 0;
   			counterline1 = 0;
   			counterline2 = 0;
   			a = false;
   			sizetail = 4; 
   			temp1 = 0;
   			temp2 = 0;
   			temp3 = 0;
   			temp4 = 0;
   			temp5 = 0;
   			temp6 = 0;
   			tailx[0] = startx;
   			taily[0] = starty;			
		}
	}
	if (linerandom == 0)
	{
		if (startx <= lx6 && startx >= lx5 && starty == ly5)
		{
			Gameover = true;
   			startx = 320;
   			starty = 400;
   			normalfood = 0;
   			normalfood2 = 0;
   			normalfood3 = 0;
   			normalfood4 = 0;
   			normalfood5 = 0;
   			powerfood = 0;
   			powerfood2 = 0;
   			endcounter = 0;
   			counterline1 = 0;
   			counterline2 = 0;
   			a = false;
   			sizetail = 4; 
   			temp1 = 0;
   			temp2 = 0;
   			temp3 = 0;
   			temp4 = 0;
   			temp5 = 0;
   			temp6 = 0;
   			tailx[0] = startx;
   			taily[0] = starty;			
		}
	}
	if (linerandom == 1)
	{
		if (startx == lx5 && starty >= ly5 && starty <= ly6)
		{
			Gameover = true;
   			startx = 320;
   			starty = 400;
   			normalfood = 0;
   			normalfood2 = 0;
   			normalfood3 = 0;
   			normalfood4 = 0;
   			normalfood5 = 0;
   			powerfood = 0;
   			powerfood2 = 0;
   			endcounter = 0;
   			counterline1 = 0;
   			counterline2 = 0;
   			a = false;
   			sizetail = 4; 
   			temp1 = 0;
   			temp2 = 0;
   			temp3 = 0;
   			temp4 = 0;
   			temp5 = 0;
   			temp6 = 0;
   			tailx[0] = startx;
   			taily[0] = starty;			
		}
	}
}

void hurdle1linehorizontal()
{
	//srand(time(NULL));
	collisiondetectorlines();
	Checker();
	if (linehorizontal == 1)
	{
		if (counterline1 != 150)
		{
			DrawLine(lx1 , ly1 , lx2 , ly2 , 20 , colors[71]);
		}
		else if (counterline1 == 150)
		{
			linerandomizer1();
			counterline1 = 0;
		}
	}
	if (linevertical == 1)
	{
		if (counterline2 != 150)
		{
			DrawLine(lx3 , ly3 , lx4 , ly4 , 20 , colors[71]);
		}
		else if (counterline2 == 150)
		{
			linerandomizer2();
			counterline2 = 0;
		}
	}
	if (linerandom == 0)
	{
		if (counterline3 != 150)
		{
			DrawLine(lx5 , ly5 , lx6 , ly6 , 20 , colors[71]);
		}
		else if (counterline3 == 150)
		{
			linerandomizer3();
			counterline3 = 0;
		}
	}
	if (linerandom == 1)
	{
		if (counterline4 != 150)
		{
			DrawLine(lx5 , ly5 , lx6 , ly6 , 20 , colors[71]);
		}
		else if (counterline4 == 150)
		{
			linerandomizer3();
			counterline4 = 0;
		}
	}	

		
}




void corrector2( int tempfruitx , int tempfruity)
{
        int random1 , random2;
        random1 = rand()%64*10;
        random2 = rand()%58*10;
        tempfruitx = random1;
        fruitx2 = tempfruitx;
        tempfruity = random2; 
        fruity2 = tempfruity;
        for (int i = 0 ; i < sizetail ; i++)
        {
        	if (tailx[i] == fruitx2 && taily[i] == fruity2)
        	{
        		temp3 = 1;
			tempfruit2();
        	}
        }
}

void corrector3( int tempfruitx , int tempfruity)
{
        int random1 , random2;
        random1 = rand()%64*10;
        random2 = rand()%58*10;
        tempfruitx = random1;
        fruitx3 = tempfruitx;	
        tempfruity = random2; 
        fruity3 = tempfruity;
        for (int i = 0 ; i < sizetail ; i++)
        {
        	if (tailx[i] == fruitx3 && taily[i] == fruity3)
        	{
        		temp4 = 1;
			tempfruit3();
        	}
        }
}

void corrector4( int tempfruitx , int tempfruity)
{
        int random1 , random2;
        random1 = rand()%64*10;
        random2 = rand()%58*10;
        tempfruitx = random1;
        fruitx4 = tempfruitx;
        tempfruity = random2; 
        fruity4 = tempfruity;
        for (int i = 0 ; i < sizetail ; i++)
        {
        	if (tailx[i] == fruitx4 && taily[i] == fruity4)
        	{
        		temp5 = 1;
			tempfruit4();
        	}
        }
}

void corrector5( int tempfruitx , int tempfruity)
{
        int random1 , random2;
        random1 = rand()%64*10;
        random2 = rand()%58*10;
        tempfruitx = random1;
        fruitx5 = tempfruitx;
        tempfruity = random2; 
        fruity5 = tempfruity;
        for (int i = 0 ; i < sizetail ; i++)
        {
        	if (tailx[i] == fruitx5 && taily[i] == fruity5)
        	{
        		temp6 = 1;
			tempfruit5();
        	}
        }
}

void corrector( int tempfruitx , int tempfruity)
{
        int random1 , random2;
        random1 = rand()%64*10;
        random2 = rand()%58*10;
        tempfruitx = random1;
        fruitx = tempfruitx;  	
        tempfruity = random2; 
        fruity = tempfruity;
        for (int i = 0 ; i < sizetail ; i++)
        {
        	if (tailx[i] == fruitx && taily[i] == fruity)
        	{
        		temp1 = 1;
			tempfruit();
        	}
        }
}

void pcorrector(int temppfruitx , int temppfruity)
{        
       	int random3 , random4;
        random3 = rand()%64*10;
        random4 = rand()%58*10; 
        if (random3 == fruitx || random3 == fruitx2 || random3 == fruitx3 || random3 == fruitx4 || random3 == fruitx5)
        {
        	random3 = rand()%64*10;
        } 
        if (random4 == fruity || random4 == fruity2 || random4 == fruity3 || random4 == fruity4 || random4 == fruity5)
        {
        	random4 = rand()%58*10;
        } 
        pfruitx = random3;
	pfruity = random4;
        for (int i = 0 ; i < sizetail ; i++)
        {
        	if (tailx[i] == pfruitx && taily[i] == pfruity)
        	{
        		temp2 = 1;
        		temppfruit();
        	}
        }		
	     	
}







void drawbackground(double , double);


void Display(){
    // set the background color using function glClearColotgr.
    // to change the background play with the red, green and blue values below.
    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.  	
	
        if (highscoreshower == true)
	{
		drawbackground(65 , 65);
		ifstream highscoreshower2;
		highscoreshower2.open("Highscore.txt");
		int highscore2;
		highscoreshower2 >> highscore2;
		DrawString(210 , 390 , "Highscore = " , colors[127]);
		DrawString(350 , 390 , to_string(highscore2) , colors[127]);
		DrawString(210 , 280 , "Press Escape Key to go back to Menu" , colors[127]);
		highscoreshower2.close();
	}	
	else if (!Menu)
	{
		drawbackground(65 , 65);
		if (box == 490)
		{
			DrawRoundRect(240 , box , 160 , 40 , colors[80] ,5); 
			DrawString(250 , 500 , "Start Game" , colors[47]);
		}
		else
		{
			DrawString(250 , 500 , "Start Game" , colors[127]);
		}
		if (box == 440)
		{
			DrawRoundRect(240 , box , 160 , 40 , colors[76] ,5);
			DrawString(250 , 450 , "Resume Game" , colors[48]);
		}
		else
		{
			DrawString(250 , 450 , "Resume Game" , colors[127]);
		}
		if (box == 390)
		{
			DrawRoundRect(240 , box , 160 , 40 , colors[77] ,5);
			DrawString(250 , 400 , "Change Level" , colors[47]);
		}
		else
		{
			DrawString(250 , 400 , "Change Level" , colors[127]);
		}
		if (box == 340)
		{
			DrawRoundRect(240 , box , 160 , 40 , colors[70] ,5);
			DrawString(250 , 350 , "High Score" , colors[47]);
		}
		else
		{
			DrawString(250 , 350 , "High Score" , colors[127]);
		}
		if (box == 290)
		{
			DrawRoundRect(240 , box , 160 , 40 , colors[79] ,5);
			DrawString(250 , 300 , "Game History" , colors[47]);
		}
		else
		{
			DrawString(250 , 300 , "Game History" , colors[127]);
		}
		if (box == 240)
		{
			DrawRoundRect(240 , box , 160 , 40 , colors[85] ,5);
			DrawString(250 , 250 , "Exit" , colors[47]);
		}
		else 
		{
			DrawString(250 , 250 , "Exit" , colors[127]);
		}
	}
	else if (!Gameover)
	{	
		
		if (!a)
		{
			corrector(0 , 0);
			corrector2(0 , 0);
			corrector3(0 , 0);
			corrector4(0 , 0);
			corrector5(0 , 0);
			pcorrector(0 , 0);
			linerandomizer1();
			linerandomizer2();
			linerandomizer3();
			a = true;	
		}
		
		
		srand(time(NULL));    	
		drawbackground(65 , 65);
		drawsnake();	
		showscore();
		powerfooddisplayer();
		foodchecker();
		hurdle1linehorizontal();
	
	
 		//Upper Bar  
        	DrawString( 20 , 600 , "SNAKE" , colors[127]); 
        	DrawLine( 110 , 610 ,  410 , 610 , 20 , colors[115] );         
        	DrawString( 480 , 600 , "SCORE = " , colors[127]);  
        	DrawLine(0 , 590 , 650 , 590 , 5 , colors[5]);
        	
  
		
        	if (sizetail >= 130)
        	{
        		Gameover = true;
        		endcounter = 0;
        		counterline1 = 0;
   			counterline2 = 0;
        	}

        	DrawSquare(fruitx , fruity , 10 , colors[5]);
        	DrawSquare(fruitx2 , fruity2 , 10 , colors[5]);
        	DrawSquare(fruitx3 , fruity3 , 10 , colors[5]);
        	DrawSquare(fruitx4 , fruity4 , 10 , colors[5]);
        	DrawSquare(fruitx5 , fruity5 , 10 , colors[5]);
      	
        	if (score > 0)
		{
			for (int i = 0 ; i < 30 ; i++)
			{
				if (score == array1[i])
				{
					int temp = score1[i];
					DrawLine(110 , 610 , temp , 610 , 20 , colors[30]);
					glutPostRedisplay();
				}
				if (score == array2[i])
				{
					int temp = score1[i];
					DrawLine(110 , 610 , temp , 610 , 20 , colors[30]);
					glutPostRedisplay();
				}
				if (score == array3[i])
				{
					int temp = score1[i];
					DrawLine(110 , 610 , temp , 610 , 20 , colors[30]);
					glutPostRedisplay();				
				}
				if (score == array4[i])
				{
					int temp = score1[i];
					DrawLine(110 , 610 , temp , 610 , 20 , colors[30]);
					glutPostRedisplay();
				}
			}
		}		      
        
        
             
        	
 	
//    glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
//            0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
//    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
    
//    DrawSquare( 300 , 300 ,10,colors[10]);  //This will draw a square shape of size 100x100  at x=300 and y=300
//    DrawString( 20 , 600 , "SNAKE" , colors[5]); // this will print given string at x=50 , y=600
//    DrawString( 50, 570, "You will use these to make your game", colors[MISTY_ROSE]); // this will print given string at x=50 , y=570
//    DrawCircle( 200 , 200 , 5 , colors[5]); // This will draw a circle at x=200,y=200 of radius 50
    //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
//   DrawRoundRect(float x, float y, float width, float height, float* color,float radius)    

     
   }
   else
   {
   	if (endcounter != 50)
   	{
   		drawbackground(65 , 65);
   		DrawString(150 , 580 , "Game Over" , colors[5]);
   		DrawString(150 , 530 , "Score = " , colors[15]);
   		DrawString(240 , 530 , to_string(score) , colors[15]);
   		
   		
   		ifstream showscore;
   		showscore.open("Highscore.txt");
   		int highscore3;
   		showscore >> highscore3;
   		if (score >= highscore3)
		{
			DrawString(150 , 450 , "HighScore = " , colors[15]);
			DrawString(280 , 450 , to_string(score) , colors[15]);
			ofstream scoresetter;
			scoresetter.open("Highscore.txt");
			scoresetter << score;
			scoresetter.close();	
		}
		else 
		{
			DrawString(150 , 450 , "HighScore = " , colors[15]);
			DrawString(280 , 450 , to_string(highscore3) , colors[15]);
		}
   		DrawString(150 , 380 , "Press Enter Key to Play Again OR " , colors[15]);
   		DrawString(150 , 300 , "Enter Escape to Exit." , colors[15]);
   		
   		showscore.close();
   	}
   	else if (endcounter == 50)
   	{
   		Gameover = false;
   		startx = 320;
   		starty = 400;
   		score = 0;
   		normalfood = 0;
   		normalfood2 = 0;
   		normalfood3 = 0;
   		normalfood4 = 0;
   		normalfood5 = 0;
   		powerfood = 0;
   		powerfood2 = 0;
   		endcounter = 0;
   		counterline1 = 0;
   		counterline2 = 0;
   		a = false;
   		sizetail = 4; 
   		temp1 = 0;
   		temp2 = 0;
   		temp3 = 0;
   		temp4 = 0;
   		temp5 = 0;
   		temp6 = 0;
   		tailx[0] = startx;
   		taily[0] = starty;
   		key1 = rand()%4+1;
   	}
   }
   glutSwapBuffers(); // do not modify this line..
}

void drawbackground(double x , double y)
{
	int count1 , count2;
    	for (count1 = 0 ; count1 < x ; count1++)
    	{
    		for (count2 = 0 ; count2 < y ; count2++)
		{
			DrawSquare(count1*10 , count2*10 , 11 , colors[131]);
		}
    	}	
}






/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int px, int py) {
	
	

    if (key == GLUT_KEY_LEFT   /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
    {
    		key1 = 1;
    		movesnake();
	
						// what to do when left key is pressed...
      
    }
    else if (key == GLUT_KEY_RIGHT  /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) 
    {
		key1 = 2;
		movesnake();
	
    } 
    else if (key == GLUT_KEY_UP) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ 
    {
    	if (!Menu)
    	{
    		box += 50;
    		if (box > 490)
    		{
    			box = 240;
    		}
    	}
    	else
    	{
    		key1 = 3;
    		movesnake();
    	}
     		
     		
    	  	
  
    }
    else if (key == GLUT_KEY_DOWN)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ 
    {
    	if (!Menu)
    	{
    		box -= 50;
    		if (box < 240)
    		{
    			box = 490;
    		}
    	}
    	else
    	{
    		key1 = 4;
    		movesnake();
    	}

		
			
		
    }
    
	/*for (int i = 1 ; i < sizetail ; i++)
	{	
		if (tailx[i] == startx && taily[i] == starty)
		{
			DrawSquare(startx,starty,25,colors[5]);
			
		}
	}*/
        
        
         
     
  
    

    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/
     glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        if (!Menu)
        {
        	exit(1);
        }
        else if (!Gameover)
        {
        	Menu = false;
        }
        else if (Gameover == true)
        {
        	Menu = false;
        }
        if (highscoreshower == true)
        {
        	Menu = false;
        	highscoreshower = false;
        }
        //exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    
    else if (int(key) == 13)
    {  
    	if (!Menu)
    	{
    		if (box == 490)
    		{
    			Menu = true;
    		}
    		if (box == 440)
    		{
    			Menu = true;
    		}
    		if (box == 340)
    		{
    			Menu = true;
    			highscoreshower = true;
    		}
    		if (box == 240)
    		{
    			exit(1);
    		}
    	}
   	if (Gameover == true)
   	{
   		Menu = false;
   		Gameover = false;
   		startx = 320;
   		starty = 400;
   		score = 0;
   		normalfood = 0;
   		normalfood2 = 0;
   		normalfood3 = 0;
   		normalfood4 = 0;
   		normalfood5 = 0;
   		powerfood = 0;
   		powerfood2 = 0;
   		endcounter = 0;
   		counterline1 = 0;
   		counterline2 = 0;
   		a = false;
   		sizetail = 4; 
   		temp1 = 0;
   		temp2 = 0;
   		temp3 = 0;
   		temp4 = 0;
   		temp5 = 0;
   		temp6 = 0;
   		tailx[0] = startx;
   		taily[0] = starty;
   		key1 = rand()%4+1;
	}
    } 	
    
    glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {

	normalfoodtimer();
	normalfoodtimer2();
	normalfoodtimer3();
	normalfoodtimer4();
	normalfoodtimer5();
	powerfoodtimer1();	
	movesnake();
	
	counterline1++;
	counterline2++;
	counterline3++;
	counterline4++;
	endcounter++;
	/*for (int i = 1 ; i < sizetail ; i++)
	{	
		if (tailx[i] == startx && taily[i] == starty)
		{
			Gameover = true;
			
		}
	}*/					
			
	
					// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0 / FPS, Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
    int width = 650, height = 650; // i have set my window size to be 800 x 600
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("18I-0737   Haroon Ali's'   Snake Game"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...

// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
    glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(5.0 / FPS, Timer, 0);
    
    
// now handle the control to library and it will call our registered functions when
// it deems necessary...
    glutMainLoop();
    return 1;
}
#endif /* Snake Game */

