#include "StdAfx.h"
#include <ctime>
#include "gwin.h"
#include "World.h"
#include "Jet.h"
#include "Obstacle.h"
#include "Star.h"
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//All the constant variables goes here...
const int MAXJETPOINTS = 12;
const int MAXSCORE = 10;

struct Point
{
	double x;
	double y;
};

struct HighScore  //data structure for storing player highscores.
{
	string PlayerName;
	int TotalScore;	
};

World::World()
{
	screenWidth = 1100;
	screenHeight = 600;
}

void World::runGame()
{
	HighScore PlayerScore[MAXSCORE];
	ifstream IFfile ("highscore.txt");
	int linecount = 0;
	while (!IFfile.eof()) //Reading everything in the highscore.txt and putting it in the Highscore data structure. 
	{
		IFfile >> PlayerScore[linecount].PlayerName >> PlayerScore[linecount].TotalScore;
		linecount++;
	}

	srand(time(0));

	//world variables/objects
	GWindow Gwin(screenWidth,screenHeight);
	Jet jet(100,250); // initial position of the jet at the start of the game
	GImage background("Store/background.png");
	GImage jetstar("Store/jetstarLogo.png");
	GImage instructionpage("Store/intropage.png");
	GImage highscorebanner("Store/highscorebanner.png");
	GImage instructionbanner("Store/instructionbanner.png");
	GImage gameoverbanner("Store/gameoverbanner.png");
	GImage play1("Store/play1.png");
	GImage play2("Store/play2.png");
	GImage instruction1("Store/instruction1.png");
	GImage instruction2("Store/instruction2.png");
	GImage highscore1("Store/highscore1.png");
	GImage highscore2("Store/highscore2.png");
	GImage jetimage("Store/jet.png");
	GImage obstacleimage("Store/obstaclev1.png");
	GImage obstacleimage2("Store/obstaclev2.png");
	GImage obstacleimage3("Store/obstaclev3.png");
	int shootCounter = 0;			
	int shootDelay = 10;
	std::vector<Obstacle> obstacles;
	int spawnCounter = 0;
	int starSpawnCounter = 0;
	std::vector<Star> stars;
	int spawnDelay = 12;
	int starSpawnDelay = 15;
	GTimer timer;
	timer.start();
	Point jetPoints[MAXJETPOINTS];
	int Score = 0;
	int screen = 1;
	bool gameRun = true;
	
	//assign values to each point
	jetPoints[0].x = jet.x;
	jetPoints[0].y = jet.y;
	jetPoints[1].x = jet.x + 26.25;
	jetPoints[1].y = jet.y;
	jetPoints[2].x = jet.x + 52.5;
	jetPoints[2].y = jet.y;
	jetPoints[3].x = jet.x + 52.5 +26.25;
	jetPoints[3].y = jet.y;
	jetPoints[4].x = jet.x + 105;
	jetPoints[4].y = jet.y;
	jetPoints[5].x = jet.x + 105;
	jetPoints[5].y = jet.y + 20;
	jetPoints[6].x = jet.x + 105;
	jetPoints[6].y = jet.y + 40;
	jetPoints[7].x = jet.x + 52.5 +26.25;
	jetPoints[7].y = jet.y + 40;
	jetPoints[8].x = jet.x + 52.5;
	jetPoints[8].y = jet.y + 40;
	jetPoints[9].x = jet.x + 26.25;
	jetPoints[9].y = jet.y + 40;
	jetPoints[10].x = jet.x;
	jetPoints[10].y = jet.y + 40;
	jetPoints[11].x = jet.x;
	jetPoints[11].y = jet.y + 20;

	GKey key(0);
	int runMenu = 1;

	while (gameRun) //Game loop starts here, there are 4 more sub loops inside this loop
		{
		//MAIN MENU SCREEN
		while(screen == 1)
		{
			if (key == GwinKeyNames::CURSOR_DOWN)
			{
				runMenu+=1;
			}
			if ( key == GwinKeyNames::CURSOR_UP)
			{
				runMenu-= 1;
			}
			if (runMenu == 4)
			{
				runMenu = 1;
			}
			if (runMenu == 0)
			{
				runMenu = 3;
			}
						
			Gwin.refresh();

			Gwin.drawImage(0,0, &background);
			Gwin.drawImage(200,20,&jetstar);
			GFont font("Arial", 15, GwinFontStyles::BOLD);
			Gwin.setFont(&font);
			Gwin.setPenColour(RED);
			Gwin.writeText(300,Gwin.getHeight() - 30, "Navigate using up and down arrow keys, to select an option press enter.");

			if(runMenu == 1)
			{
				Gwin.drawImage(425,200,&play2);
				Gwin.drawImage(425,300,&instruction1);
				Gwin.drawImage(425,400,&highscore1);
				Gwin.refresh();
				key = Keyboard.waitKey();

				if(Keyboard.isPressed(GwinKeyNames::RETURN))
				{
					screen = 2;
				}
			}
			else if(runMenu == 2)
			{
				Gwin.drawImage(425,200,&play1);
				Gwin.drawImage(425,300,&instruction2);
				Gwin.drawImage(425,400,&highscore1);
				Gwin.refresh();
				key = Keyboard.waitKey();
				if(Keyboard.isPressed(GwinKeyNames::RETURN))
				{
					screen = 5;
				}
			}
			else if(runMenu == 3)
			{
				Gwin.drawImage(425,200,&play1);
				Gwin.drawImage(425,300,&instruction1);
				Gwin.drawImage(425,400,&highscore2);
				Gwin.refresh();
				key = Keyboard.waitKey();
				if (Keyboard.isPressed(GwinKeyNames::RETURN))
				{
					screen = 4;
				}
			}
			Gsleep(1);
		}

		while (screen == 5)
		{
			Gwin.clear();
			Gwin.drawImage(0,0,&background);
			Gwin.drawImage(300,25, &instructionbanner);
			Gwin.drawImage(200,162, &instructionpage);
			Gwin.setPenColour(RED);
			GFont font("Arial", 15, GwinFontStyles::BOLD);
			Gwin.setFont(&font);
			Gwin.writeText(300,Gwin.getHeight() - 30, "Please press back space to go back to the main menu");
			Gwin.refresh();
			key = Keyboard.waitKey();
			if(Keyboard.isPressed(GwinKeyNames::BACKSPACE))
			{
				screen = 1;
			}
			Gwin.refresh();
		}
		
		//Reset all objects positions before the game loop starts 
		jet.health = 5;
		Jet jet(100,250);
		Score = 0;
		obstacles.clear ();

		//GAME SCREEN
		while(screen == 2)
		{
			timer.reset();
			Gwin.clear(BLACK);
			Gwin.setPenColour(WHITE);

			//check user input for jet movement
			if(Keyboard.isPressed(GwinKeyNames::CURSOR_UP) && jet.y > 0)
			{
				jet.move(0,-5.5);
			}
			if(Keyboard.isPressed(GwinKeyNames::CURSOR_DOWN) && jet.y < screenHeight - jetimage.getHeight())
			{
				jet.move(0,5.5);
			}
			if(Keyboard.isPressed(GwinKeyNames::CURSOR_LEFT) && jet.x > 0)
			{
				jet.move(-5.5,0);
			}
			if(Keyboard.isPressed(GwinKeyNames::CURSOR_RIGHT) && jet.x < screenWidth - jetimage.getWidth())
			{
				jet.move(5.5,0);
			}
			
			//update shoot counter
			if(shootCounter > 0)
			{
				shootCounter--;
			}

			//check user input for shooting missiles
			if(shootCounter == 0)
			{
				if(Keyboard.isPressed('Z')) //GwinKeyNames::SPACE))
					jet.shoot(jet.x+jetimage.getWidth(),jet.y+20,1);
				/*else if(Keyboard.isPressed('X'))
					jet.shoot(jet.x+jetimage.getWidth(),jet.y+20,1);*/
				shootCounter = shootDelay;
			}

			//update values of each jet collision point
			jetPoints[0].x = jet.x;
			jetPoints[0].y = jet.y;
			jetPoints[1].x = jet.x + 26.25;
			jetPoints[1].y = jet.y;
			jetPoints[2].x = jet.x + 52.5;
			jetPoints[2].y = jet.y;
			jetPoints[3].x = jet.x + 52.5 +26.25;
			jetPoints[3].y = jet.y;
			jetPoints[4].x = jet.x + 105;
			jetPoints[4].y = jet.y;
			jetPoints[5].x = jet.x + 105;
			jetPoints[5].y = jet.y + 20;
			jetPoints[6].x = jet.x + 105;
			jetPoints[6].y = jet.y + 40;
			jetPoints[7].x = jet.x + 52.5 +26.25;
			jetPoints[7].y = jet.y + 40;
			jetPoints[8].x = jet.x + 52.5;
			jetPoints[8].y = jet.y + 40;
			jetPoints[9].x = jet.x + 26.25;
			jetPoints[9].y = jet.y + 40;
			jetPoints[10].x = jet.x;
			jetPoints[10].y = jet.y + 40;
			jetPoints[11].x = jet.x;
			jetPoints[11].y = jet.y + 20;

			//update spawn counter
			if(spawnCounter > 0)
			{
				spawnCounter--;
			}

			//update star spawn couter
			if(starSpawnCounter > 0)
			{
				starSpawnCounter--;
			}

			//check if it's time to spawn a new obstacle
			if(spawnCounter == 0)
			{
				obstacles.push_back(Obstacle(screenWidth+(rand()%100),(rand()%(screenHeight-200))+100,10+(rand()%20)));
				spawnCounter = spawnDelay;
			}

			//check if it's time to spawn a new star
			if(starSpawnCounter == 0)
			{
				stars.push_back(Star(screenWidth+(rand()%100),(rand()%(screenHeight-5))));
				starSpawnCounter = starSpawnDelay;
			}

			//update health of obstacles and missiles that have collided
			for(int i=0; i<obstacles.size(); i++)
			{
				for(int j=0; j<jet.missiles.size(); j++)	
				{
					double dx = jet.missiles[j].x-obstacles[i].x;
					double dxSquared = dx * dx;
					double dy = jet.missiles[j].y-obstacles[i].y;
					double dySquared = dy * dy;
					double distance = sqrt(dxSquared + dySquared);
					if (distance < obstacles[i].radius)
					{
						while(jet.missiles[j].health != 0 && obstacles[i].health != 0)
						{
							jet.missiles[j].health--;
							obstacles[i].health--;
							Score+=5;
						}
					}
				}
			}

			//CHECKING COLLISION BETWEEN OBSTACLES AND JET/ REDUCING HEALTH IF COLLIDED.
			for (int k = 0; k < obstacles.size(); k++)
			{
				for(int m = 0; m < MAXJETPOINTS; m++)
				{
					double dx = jetPoints[m].x - obstacles[k].x;
					double dxSquared = dx * dx;
					double dy = jetPoints[m].y - obstacles[k].y;
					double dySquared = dy * dy;
					double distanceJetToObstacle = sqrt(dxSquared + dySquared);
					if (distanceJetToObstacle <= obstacles[k].radius)
					{
						while (jet.health != 0 && obstacles[k].health != 0)
						{
							jet.health--;
							obstacles[k].health--;
						}
					}
				}
			}
		
			//update missiles' positions
			for(int i=0; i<jet.missiles.size(); i++)
			{
				jet.missiles[i].move(jet.missiles[i].dx,jet.missiles[i].dy);
			}

			//update obstacles' positions and angle
			for(int i=0; i<obstacles.size(); i++)//obstacles
			{
				obstacles[i].move(obstacles[i].dx,obstacles[i].dy);
				//obstacles[i].angle += obstacles[i].spin;
			}

			//update stars' positions
			for(int i=0; i<stars.size(); i++)
			{
				stars[i].move(stars[i].dx,stars[i].dy);
			}

			//destroy obstacles that have gone out left of the screen or have a health of 0 or less
			for(int i=0; i<obstacles.size(); i++)//obstacles
			{
				if(obstacles[i].x + obstacles[i].radius < 0 || obstacles[i].health <= 0)
				{
					obstacles.erase(obstacles.begin()+i);
					i--;
				}
			}

			//destroy stars that have gone out left of the screen
			for(int i=0; i<stars.size(); i++)//stars
			{
				if(stars[i].x < 0)
				{
					stars.erase(stars.begin()+i);
					i--;
				}
			}

			//destroy any missiles that are out of screen or have a health of 0 or less
			for(int i=0; i<jet.missiles.size(); i++)
			{
				if(jet.missiles[i].x > screenWidth || jet.missiles[i].x < 0 || jet.missiles[i].y < 0 || jet.missiles[i].y > screenHeight || jet.missiles[i].health <= 0)
				{
					jet.missiles.erase(jet.missiles.begin()+i);
					i--;
				}
			}

			 //destroy jet if it has a health of 0 or less
			if (jet.health == 0)
			{
				screen = 3;
			}

			//DRAW EVERYTHING 
			for(int i=0; i<stars.size(); i++)//stars
			{
				Gwin.setPenColour(WHITE);
				//Gwin.outlineCircle(stars[i].x, stars[i].y, 1);
				Gwin.circle(stars[i].x, stars[i].y,1);
			}

			Gwin.drawImage(jet.x,jet.y,&jetimage);//jet

			for(int i=0; i<obstacles.size(); i++)//obstacles
			{
				if(obstacles[i].health == 3)
					//Gwin.drawImageScaledRotated(obstacles[i].x,obstacles[i].y,obstacles[i].radius*2,obstacles[i].radius*2,&obstacleimage,obstacles[i].angle);
					Gwin.drawImageScaled(obstacles[i].x,obstacles[i].y-obstacles[i].radius,obstacles[i].radius*2,obstacles[i].radius*2,&obstacleimage);
				else if(obstacles[i].health == 2)
					//Gwin.drawImageScaledRotated(obstacles[i].x,obstacles[i].y,obstacles[i].radius*2,obstacles[i].radius*2,&obstacleimage2,obstacles[i].angle);
					Gwin.drawImageScaled(obstacles[i].x,obstacles[i].y-obstacles[i].radius,obstacles[i].radius*2,obstacles[i].radius*2,&obstacleimage2);
				else if(obstacles[i].health == 1)
					//Gwin.drawImageScaledRotated(obstacles[i].x,obstacles[i].y,obstacles[i].radius*2,obstacles[i].radius*2,&obstacleimage3,obstacles[i].angle);
					Gwin.drawImageScaled(obstacles[i].x,obstacles[i].y-obstacles[i].radius,obstacles[i].radius*2,obstacles[i].radius*2,&obstacleimage3);			
					//Gwin.circle(obstacles[i].x,obstacles[i].y,obstacles[i].radius);
			} 

			for(int i=0; i<jet.missiles.size(); i++)//missiles
			{
				/*if(jet.missiles[i].health == 3)
					Gwin.setPenColour(GREEN);
				else if(jet.missiles[i].health == 2)
					Gwin.setPenColour(GREEN);
				else if(jet.missiles[i].health == 1)
					Gwin.setPenColour(GREEN);*/
				Gwin.circle(jet.missiles[i].x,jet.missiles[i].y,4);
			}

			//DISPLAY JET HEALTH AND PLAYER'S SCORE DURING GAME RUNTIME... 
			GFont font("Arial", 20);
			Gwin.setFont(&font);
			Gwin.setPenColour(LIGHTBLUE);
			Gwin.writeText(screenWidth-383, 8, "Jet Health: ");
			Gwin.writeInt(screenWidth-280, 8, jet.health);
			Gwin.writeText(screenWidth-225, 8, "Score: ");
			Gwin.writeInt(screenWidth-163, 8, Score);

			Gwin.refresh();

			//setting FPS to 70ishhhhh...
			while(timer.getTime() < 1000.0/130)
			Gsleep(1);
		}

		//GAME OVER SCREEN
		while(screen == 3)
		{
			//The player will always come to this screen after he/she dies in the game. In this screen the player's score gets checked, if it is high enough to be in the high score
			//table then the system will ask for player's name but if it is not it will quickly go to the High score screen and display all the highscores.
			Gwin.clear(BLACK);
			GFont font("Arial", 25, GwinFontStyles::BOLD);
			Gwin.setFont(&font);
			Gwin.setPenColour(LIGHTBLUE);
			Gwin.drawImage(0,0, &background);
			Gwin.drawImage(300,20, &gameoverbanner);
			Gwin.writeText(150,200,"CONTRATULATIONS! Your score is high enough");
			Gwin.writeText(150,230,"to be listed in the high score table!");
			Gwin.writeText(150,300, "Your total score: "); 
			Gwin.writeText(150,350, "Please enter your name: ");
			GFont font1("Arial", 15, GwinFontStyles::BOLD);
			Gwin.setFont(&font1);
			Gwin.setPenColour(RED);
			Gwin.writeText(300,Gwin.getHeight() - 30, "Press return after you have entered your name");

			//finding the minimum score in the hgihscore list
			int x = 0;
			int min = PlayerScore[0].TotalScore;
			for ( int i = 1; i < MAXSCORE; i++)
			{
				if(PlayerScore[i].TotalScore < min)
				{
					min = PlayerScore[i].TotalScore;
					x = i;
				}
			}

			GFont font2("Arial", 25, GwinFontStyles::BOLD);
			Gwin.setFont(&font2);
			Gwin.setPenColour(GREEN);

			Gwin.writeInt(400,300,Score); //Writting out player's score in the game over screen after the game.
			// if new score is greater than the minimum score then ask for player's name.
			if (Score > PlayerScore[x].TotalScore)
			{
				PlayerScore[x].TotalScore = Score;
				PlayerScore[x].PlayerName = Gwin.readString(500,350,20);
			}

			ofstream OFfile; //Writting everything from the struct into the file
			OFfile.open("highscore.txt");
			for (int i = 0; i < MAXSCORE; i++)
			{
				OFfile << PlayerScore[i].PlayerName << " " << PlayerScore[i].TotalScore << endl;
			}

			OFfile.close();

			screen = 4;
			Gwin.refresh();
			//key = Keyboard.waitKey();
		}

		//HIGHSCORE SCREEEN (display all the highscores here in this screen in ascending order...)
		while (screen == 4)
		{
			Gwin.clear();
			Gwin.drawImage(0,0, &background);
			Gwin.drawImage(300,20, &highscorebanner);
			GFont font("Arial", 15, GwinFontStyles::BOLD);
			Gwin.setFont(&font);
			Gwin.setPenColour(RED);
			Gwin.writeText(300,Gwin.getHeight() - 30, "Please press back space to go back to the main menu");
			Gwin.setPenColour(LIGHTBLUE);
			
			//Before printing out high scores on screen, temporary variables are needed to store score and player's name...
			int tempscore; 
			string tempname;

			//This is the bubble sort, it is sorting the high scores in descending order starting from highest to lowest.
			for( int i = 0; i <= MAXSCORE-2; i++)
			{
				for (int j = i+1; j<=MAXSCORE-1; j++)
				{
					if(PlayerScore[i].TotalScore < PlayerScore[j].TotalScore)
					{
						tempscore = PlayerScore[i].TotalScore;
						tempname = PlayerScore[i].PlayerName;
						PlayerScore[i].TotalScore = PlayerScore[j].TotalScore;
						PlayerScore[i].PlayerName = PlayerScore[j].PlayerName;
						PlayerScore[j].TotalScore = tempscore;
						PlayerScore[j].PlayerName = tempname;
					}
				}
			}

			//After arranging the high scores in ascending order its time to display it on the high score screen...
			int ypos = 175;
			for (int i = 0; i < MAXSCORE; i++)
			{
				Gwin.writeString(400,ypos,PlayerScore[i].PlayerName);
				Gwin.writeInt(620, ypos,PlayerScore[i].TotalScore);
				ypos += 35;
			}
			Gwin.refresh();
			key = Keyboard.waitKey();
			if(Keyboard.isPressed(GwinKeyNames::BACKSPACE)) //hit backspace to go back the main menu screen
			{
				screen = 1;
			}
			Gwin.refresh();
		}
	Gwin.refresh();
	}	
}