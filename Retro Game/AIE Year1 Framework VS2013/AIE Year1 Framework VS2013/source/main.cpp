#include "AIE.h"
#include <iostream>
#include "math.h"
#include <vector>

const int screenWidth = 1280;
const int screenHeight = 1024;

bool isGameRunning = true;

int playerS;
int boltS;
int enemyS;
int enemy2S;
int enemy3S;

int pHS;
int lives = 5;

unsigned int scoreBoard;
int pScore = 0;


unsigned int menu;
unsigned int back;

float loadTimer = 0;
float loadCool;
unsigned int loadScreen;

enum GAMESTATES
{
	eMAIN_MENU,
	eGAMEPLAY,
	eHIGHSCORES,
	eWIN,
	eLOSE,
	eLOAD,
	eEND
};

//Player classes
//---------------------------------------------
class Player
{
public:
	unsigned int playerS;
	const int playerWidth = 32;
	const int playerHeight = 32;

	float PlayerX = 640;
	float PlayerY = screenHeight * 0.5f;
	float PlayerSpeedX = 2.5f;
	float PlayerSpeedY = 2.5f;

	float radius = playerWidth * .5;
	float cooldown = .1;	// time between bullet
	float timer = .5;
	float timerLeft = .5;
	float cooldownLeft = .1;
	float timerRight = .5;
	float cooldownRight = .1;
	//bool Shoot;
};
//........................
class PlayerBolt
{
public: 
	unsigned int pBoltS;
	const int boltWidth = 32;
	const int boltHeight = 32;
	
	float boltX = 300;
	float boltY = screenHeight * 0.5f;

	float boltSpeedY = 4.f;
	float boltSpeedX = 4.f;

	float boltRadius = boltWidth * 0.5f;

	bool isActive = false;

	
};

std::vector<PlayerBolt> VectorBolts;

//-----------------------------------------------
class Enemy
{
public:
	unsigned int enemyS;
	const int enemyWidth = 64;
	const int enemyHeight = 64;

	bool isAlive = true;

	float enemyX = screenHeight * 0.5f;
	float enemyY = 940;
	float enemySpeedX;
	float enemySpeedY;
	float radius = 32;

	
};

class Enemy2
{
public:
	unsigned int enemy2S;
	const int enemy2Width = 64;
	const int enemy2Height = 64;

	bool is2Alive = true;

	float enemy2X = screenHeight * 0.5f + 200;
	float enemy2Y = 940;
	float Enemy2SpeedX;
	float enemy2SpeedY;
	float radius2 = 32;
};
class Enemy3
{
public:
	unsigned int enemy3S;
	const int enemy3Width = 64;
	const int enemy3Height = 64;

	bool is2Alive = true;

	float enemy3X = screenHeight * 0.5f + 400;
	float enemy3Y = 1000;
	float enemy3SpeedX;
	float enemy3SpeedY;
	float radius3 = 32;
};

Enemy enemy;
Enemy2 enemy2;
Enemy3 enemy3;
Player player;
//PlayerBolt bolt;
// ------------------------------------------------

void UpdateScoreBoard()
{
	DrawSprite(scoreBoard);
	
	MoveSprite(scoreBoard, screenWidth * 0.5f, screenHeight * 0.5f);
}

void updateMainMenu()
{
	if (IsKeyDown('Q'))
	{
		isGameRunning = false;
	}
	DrawSprite(menu);
	
	MoveSprite(menu, screenWidth * 0.5f, screenHeight * 0.5f);
}

void updateLoadScreen()
{
	DrawSprite(loadScreen);
	MoveSprite(loadScreen, screenWidth * 0.5f, screenHeight * 0.5f);
	loadCool = 3;
	loadTimer += GetDeltaTime();
	

}

void updateGameState(float a_fDeltaTime)
{
	DrawSprite(back);
	
	MoveSprite(back, screenWidth * 0.5f, screenHeight * 0.5f);
	DrawSprite(playerS);
	MoveSprite(playerS, player.PlayerX, player.PlayerY);
	//DrawSprite(boltS);
//	MoveSprite(boltS, bolt.boltX, bolt.boltY);
	//Enemyshet
//===========================================================================
	MoveSprite(enemyS, enemy.enemyX, enemy.enemyY);
	MoveSprite(enemy2S, enemy2.enemy2X, enemy2.enemy2Y);
	MoveSprite(enemy3S, enemy3.enemy3X, enemy3.enemy3Y);
	if (enemy.isAlive == true)
	{
		DrawSprite(enemyS);
	}
	//+++++++++++++++++++++++++
	if (enemy2.is2Alive == true)
	{
		DrawSprite(enemy2S);
	}
	//++++++++++++++++++++++++++
	if (enemy3.is2Alive == true)
	{
		DrawSprite(enemy3S);
	}


	//Respawn
//--------------------------------------------------------------------
	if (enemy.isAlive == false)
	{
		enemy.isAlive = true;
		enemy.enemyX = screenHeight * 0.5f;
		enemy.enemyY = 940;
	}
	if (enemy2.is2Alive == false)
	{
		enemy2.is2Alive = true;
		enemy2.enemy2X = screenHeight * 0.5f + 200;
		enemy2.enemy2Y = 950;
	}
	if (enemy3.is2Alive == false)
	{
		enemy3.is2Alive = true;
		enemy3.enemy3X = screenHeight * 0.5f + 400;
		enemy3.enemy3Y = 1000;
	}

//----------------------------------------------------------------------
//========================================================================
	

	//All of the bolt stuff (for gamestate)
//_______________________________________________________________

	if (IsKeyDown(GLFW_KEY_UP) && player.timer > player.cooldown)
	{
		//bolt.isActive = true;
		//bolt.boltX = player.PlayerX;
		//bolt.boltY = player.PlayerY;
		
		PlayerBolt BoltClone;
		
		BoltClone.pBoltS = CreateSprite("./images/FireBolt.png", BoltClone.boltWidth, BoltClone.boltHeight, true);
		BoltClone.isActive = true;
		BoltClone.boltX = player.PlayerX;
		BoltClone.boltY = player.PlayerY;
		BoltClone.boltSpeedX = 0;
		VectorBolts.push_back(BoltClone);
		player.timer = 0;
	}
	if (IsKeyDown(GLFW_KEY_LEFT) && player.timerLeft > player.cooldownLeft)
	{
		PlayerBolt BoltClone2;
		
		BoltClone2.pBoltS = CreateSprite("./images/FireboltLeft.png", BoltClone2.boltWidth, BoltClone2.boltHeight, true);
		BoltClone2.isActive = true;
		BoltClone2.boltX = player.PlayerX;
		BoltClone2.boltY = player.PlayerY;
		BoltClone2.boltSpeedX = -5;

		VectorBolts.push_back(BoltClone2);
		player.timerLeft = 0;
	}
	if (IsKeyDown(GLFW_KEY_RIGHT) && player.timerRight > player.cooldownRight)
	{
		PlayerBolt BoltClone2;

		BoltClone2.pBoltS = CreateSprite("./images/FireboltRight.png", BoltClone2.boltWidth, BoltClone2.boltHeight, true);
		BoltClone2.isActive = true;
		BoltClone2.boltX = player.PlayerX;
		BoltClone2.boltY = player.PlayerY;
		BoltClone2.boltSpeedX = 5;

		VectorBolts.push_back(BoltClone2);
		player.timerRight = 0;
	}

	for (int i = 0; i < VectorBolts.size(); i++)
	{
		if (VectorBolts[i].isActive == true) 
		{
			VectorBolts[i].boltY += VectorBolts[i].boltSpeedY;
			VectorBolts[i].boltX += VectorBolts[i].boltSpeedX;
			MoveSprite(VectorBolts[i].pBoltS, VectorBolts[i].boltX, VectorBolts[i].boltY);
			DrawSprite(VectorBolts[i].pBoltS);
		}

		if (VectorBolts[i].boltY > 1000)
		{
			VectorBolts[i].isActive = false;
		}

		if (VectorBolts[i].isActive == false)
		{
			VectorBolts[i].boltX = 2000;
			VectorBolts[i].boltY = 2000;
		}
		float boltDistance = sqrt(pow(VectorBolts[i].boltX - enemy.enemyX, 2) + pow(VectorBolts[i].boltY - enemy.enemyY, 2));
		if (boltDistance < VectorBolts[i].boltRadius + enemy.radius)
		{
			pScore += 10;
			enemy.isAlive = false;
			VectorBolts[i].isActive = false;

		}
		float boltDistance2 = sqrt(pow(VectorBolts[i].boltX - enemy2.enemy2X, 2) + pow(VectorBolts[i].boltY - enemy2.enemy2Y, 2));
		if (boltDistance2 < VectorBolts[i].boltRadius + enemy2.radius2)
		{
			pScore += 10;
			enemy2.is2Alive = false;
			VectorBolts[i].isActive = false;

		}
		float boltDistance3 = sqrt(pow(VectorBolts[i].boltX - enemy3.enemy3X, 2) + pow(VectorBolts[i].boltY - enemy3.enemy3Y, 2));
		if (boltDistance3 < VectorBolts[i].boltRadius + enemy3.radius3)
		{
			pScore += 10;
			enemy3.is2Alive = false;
			VectorBolts[i].isActive = false;

		}
	}



	//if (bolt.isActive == true)
	//{
	//	bolt.boltY += bolt.boltSpeedY;
	//	DrawSprite(boltS);
	//}
	//if (bolt.boltY > 1000)
	//{

	//	bolt.isActive = false;
	//}
	//if (bolt.isActive == false )
	//{
	//	bolt.boltX = 2000;
	//	bolt.boltY = 2000;
	//}


	//Collision for enemies
	//***************************************************************************************************
	//float boltDistance = sqrt(pow(bolt.boltX - enemy.enemyX, 2) + pow(bolt.boltY - enemy.enemyY, 2));
	//if (boltDistance < bolt.boltRadius + enemy.radius)
	//{
	//	pScore += 10;
	//	enemy.isAlive = false;
	//	bolt.isActive = false;

	//}
	//float boltDistance2 = sqrt(pow(bolt.boltX - enemy2.enemy2X, 2) + pow(bolt.boltY - enemy2.enemy2Y, 2));
	//if (boltDistance2 < bolt.boltRadius + enemy2.radius2)
	//{
	//	pScore += 10;
	//	enemy2.is2Alive = false;
	//	bolt.isActive = false;

	//}
	//float boltDistance3 = sqrt(pow(bolt.boltX - enemy3.enemy3X, 2) + pow(bolt.boltY - enemy3.enemy3Y, 2));
	//if (boltDistance3 < bolt.boltRadius + enemy3.radius3)
	//{
	//	pScore += 10;
	//	enemy3.is2Alive = false;
	//	bolt.isActive = false;

	//}

	//***************************************************************************************************
//_______________________________________________________________________
	


	if (IsKeyDown('S'))
	{
		player.PlayerY -= player.PlayerSpeedY;
		if (player.PlayerY < 40)
		{
			player.PlayerY = 40;
		}
	}

	if (IsKeyDown('W'))
	{
		player.PlayerY += player.PlayerSpeedY;
		if (player.PlayerY > 940)
		{
			player.PlayerY = 940;
		}

	}
	if (IsKeyDown('A'))
	{
		player.PlayerX -= player.PlayerSpeedX;
		if (player.PlayerX < 40)
		{
			player.PlayerX = 40;
		}
	}

	if (IsKeyDown('D'))
	{
		player.PlayerX += player.PlayerSpeedX;
		if (player.PlayerX > 1240)
		{
			player.PlayerX = 1240;
		}

	}
	MoveSprite(playerS, player.PlayerX, player.PlayerY);
	enemy.enemyY -= 1.f;
	enemy2.enemy2Y -= 1.f;
	enemy3.enemy3Y -= 1.f;
	/*if (enemy.enemyY < 600)
	{
		enemy.enemyX += enemy.enemySpeedX;
	}*/
	//bolt.boltY = 1.f;
	if (enemy.enemyY < 32)
	{
		lives -= 1;
		pScore -= 10;
		enemy.isAlive = false;	
	}
	if (enemy2.enemy2Y < 32)
	{
		lives -= 1;
		pScore -= 10;
		enemy2.is2Alive = false;
	}
	if (enemy3.enemy3Y < 32)
	{
		lives -= 1;
		pScore -= 10;
		enemy3.is2Alive = false;
	}
	
	enemy.enemyY += enemy.enemySpeedY;
	enemy.enemyX += enemy.enemySpeedX;
	enemy2.enemy2Y += enemy2.enemy2SpeedY;
	enemy2.enemy2X += enemy2.Enemy2SpeedX;
	enemy3.enemy3Y += enemy3.enemy3SpeedY;
	enemy3.enemy3X += enemy3.enemy3SpeedX;

	float Distance = sqrt(pow(enemy.enemyX - player.PlayerX, 2) + pow(enemy.enemyY - player.PlayerY, 2));
	if (Distance < enemy.radius + player.radius)
	{
		lives -= 1;
		enemy.isAlive = false;
	
	}
	float Distance2 = sqrt(pow(enemy2.enemy2X - player.PlayerX, 2) + pow(enemy2.enemy2Y - player.PlayerY, 2));
	if (Distance2 < enemy2.radius2 + player.radius)
	{
		lives -= 1;
		enemy2.is2Alive = false;

	}
	float Distance3 = sqrt(pow(enemy3.enemy3X - player.PlayerX, 2) + pow(enemy3.enemy3Y - player.PlayerY, 2));
	if (Distance3 < enemy3.radius3 + player.radius)
	{
		lives -= 1;
		enemy3.is2Alive = false;

	}

	player.timer += a_fDeltaTime;
	player.timerLeft += a_fDeltaTime;
	player.timerRight += a_fDeltaTime;

	char Score[100];
	char Lives[10];
	itoa(pScore, Score, 10);
	itoa(lives, Lives, 10);
	DrawString(Score, screenWidth * 0.5f, screenHeight - 40);
	DrawString("SCORE", screenWidth * 0.5f - 150, screenHeight - 40);
	DrawString(Lives, screenWidth * 0.5f, screenHeight);
	DrawString("LIVES", screenWidth * 0.5f - 150, screenHeight);
}
char HS[1000];

int main( int argc, char* argv[] )
{	
    Initialise(screenWidth, screenHeight, false, "Retro Game");
	playerS = CreateSprite("./images/Ship.png", player.playerWidth, player.playerHeight, true);
	menu = CreateSprite("./images/PixelPlanetsMenu.png", screenWidth, screenHeight, true);
	scoreBoard = CreateSprite("./images/High ScoreBG.png", screenWidth, screenHeight, true);
	back = CreateSprite("./images/GrungeSimpleAtom.png", screenWidth, screenHeight, true);
//	boltS = CreateSprite("./images/FireBolt.png", bolt.boltWidth, bolt.boltHeight, true);
	enemyS = CreateSprite("./images/Nelon_13.png", enemy.enemyWidth, enemy.enemyHeight, true);
	enemy2S = CreateSprite("./images/Nelon_13.png", enemy2.enemy2Width, enemy2.enemy2Height, true);
	enemy3S = CreateSprite("./images/Nelon_13.png", enemy3.enemy3Width, enemy3.enemy3Height, true);
	//playerS = CreateSprite("./images/RetroShip.png", player.playerWidth, player.playerHeight, true);
	loadScreen = CreateSprite("./images/LoadingScreen.png", screenWidth, screenHeight, true);
    
    //SetBackgroundColour(SColour(0, 0, 0, 255));
	
    

	GAMESTATES eCurrentState = eLOAD;

    //Game Loop
    do
    {
		//DrawSprite(playerS);
		//MoveSprite(playerS, player.PlayerX, player.PlayerY);
		switch (eCurrentState)
		{
		case eLOAD:
			updateLoadScreen();
			

			if (loadTimer > loadCool)
			{
				eCurrentState = eMAIN_MENU;
				
			}
			ClearScreen();
			break;
		case eMAIN_MENU:
			updateMainMenu();

			if (IsKeyDown('B'))
			{
				eCurrentState = eGAMEPLAY;
			}
			if (IsKeyDown('H'))
			{
				eCurrentState = eHIGHSCORES;
			}
			ClearScreen();
			break;
		case eHIGHSCORES:
		{

					UpdateScoreBoard();
					itoa(pHS, HS, 10);
					DrawString(HS, screenWidth / 2, (screenHeight / 2));
					DrawString("Player: ", (screenWidth / 2) - 130, (screenHeight / 2));
					
				
					if (IsKeyDown('R'))
					{

						eCurrentState = eMAIN_MENU;
					}
					ClearScreen();
					break;
		}
		case eGAMEPLAY:
			updateGameState(GetDeltaTime());
			if (IsKeyDown('P'))
			{
				pHS = pScore;
				eCurrentState = eMAIN_MENU;
			}
			if (lives == 0)
			{
				eCurrentState = eMAIN_MENU;
				pHS = pScore;
				pScore = 0;
				lives = 5;
			}
		/*	if (Score1 > 10)
			{
				eCurrentState = eMAIN_MENU;
				p1HS = Score1;
				Score1 = 0;
				Score2 = 0;
			}
			*/
			ClearScreen();
			break;
		default:
			break;
		}

    } while(!FrameworkUpdate()&& isGameRunning);

    Shutdown();

    return 0;
}
