#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Castle.h"

using namespace std;

//enum enemyType { paver, fighter, shielded };

int killedEnemies = 0;
int nofEnemies = 0;
int aliveEnemies = nofEnemies - killedEnemies;

struct Tower {

	int Health;
	int nEnemies;
	int firePower;
	int unPavedRout = 30;
	int damage;

};

struct Enemy {
	int ID; //unused till the data collection part
	int Health;
	int hitPeriod;
	int remainingTime;
	int firPower;
	int distance;
	int arrivalTime;
	char region;
	int firShot;
	int type;
	
	int T;  //death time for output data
	int FD; //fight delay for output data
	int KD; //Kill delay for output data
	int FT; //total fight time for output data
};


void readData(tower towers[], enemy enemies[],int &c1, int &c2, int &c3) {
	ifstream inputFile;
	inputFile.open("input.txt");

	//Checking if file failed to open for any reason 
	if (inputFile.fail()) {
		cerr << "Error Opening File" << endl;
		exit(1);
	}
	//Putting the data of the first line into the first tower
	inputFile >> towers[0].Health >> towers[0].nEnemies >> towers[0].firePower;
	towers[0].damage = 0;
	//Copying the data to all towers
	for (int i = 1; i < 4; i++) {
		towers[i].Health = towers[0].Health;
		towers[i].nEnemies = towers[0].nEnemies;
		towers[i].firePower = towers[0].firePower;
		towers[i].damage = towers[0].damage;
	}

	//Putting the data of the second line into the constants
	inputFile >> c1 >> c2 >> c3;

	//Reading enemies data line by line untill the end of the file
	//Assuming the there is no -1 at the end of the file
	int j = 0;
	while (!inputFile.eof()) {
		inputFile >> enemies[j].ID >> enemies[j].arrivalTime >> enemies[j].Health >>
			enemies[j].firPower >> enemies[j].hitPeriod >> enemies[j].type >> enemies[j].region;
		enemies[j].distance = 60;
		enemies[j].firShot = -1;
		enemies[j].T = -1;
		j++;
		nofEnemies++;
	}
	inputFile.close();
}

void outputData(Enemy enemies[],Tower towers[], bool win) {
	ofstream outputFile;
	outputFile.open("output.txt");
	for (int i=0; i < nofEnemies; i++) {
		outputFile << enemies[i].T << " " << enemies[i].ID << " " << enemies[i].FD << " " <<
			enemies[i].KD << " " << enemies[i].FT << endl;
	}
	for (int i = 0; i < 4; i++) {
		outputFile << towers[i].damage << " ";
	}
	outputFile << endl;
	for (int i = 0; i < 4; i++) {
		outputFile << towers[i].unPavedRout << " ";
	}
	outputFile << endl;
	if (win) {
		outputFile << "win" << endl;
		outputFile << nofEnemies << endl;
		double avgFD, avgKD;
		int sum1 = 0, sum2 = 0;
		for (int i = 0; i < nofEnemies; i++) {
			sum1 += enemies[i].FD;
			sum2 += enemies[i].KD;
		}
		avgFD = (double)sum1 / nofEnemies;
		avgKD = (double)sum2 / nofEnemies;
		outputFile << avgFD << endl;
		outputFile << avgKD << endl;
	}
	else {
		outputFile << "loss" << endl;
		outputFile << killedEnemies << endl;
		outputFile << aliveEnemies << endl;
		//avg FD and KD are to be implemented later
	}
	outputFile.close();
}

int main()
{
	Enemy* enemies = new Enemy[100];
	Tower* towers = new Tower[4];
	int C1, C2, C3;
	readData(towers, enemies, C1, C2, C3);

	//Testing some data to ensure the reading succeeded
	cout << "C1 = " << C1 << " C2 = " << C2 << " C3 = " << C3 << endl;
	cout << "Tower's Health = " << towers[0].Health << endl;
	cout << "Tower's number of enemies per shot = " << towers[1].nEnemies << endl;
	cout << "Tower's Fire Power = " << towers[2].firePower << endl;
	for (int i = 0; i < 3; i++) {
		cout << "Enemy " << enemies[i].ID << "'s region is " << enemies[i].region << endl;
		cout << "Enemy " << enemies[i].ID << "'s Health is " << enemies[i].Health << endl;
		cout << "Enemy " << enemies[i].ID << "'s Fire Power is " << enemies[i].firPower << endl;
	}
	return 0;
}
