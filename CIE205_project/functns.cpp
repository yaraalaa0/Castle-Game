#include "stdafx.h"
#include "Castle.h"
#include <fstream>
#include <iostream>
using namespace std; 
extern int stamp;

Queue* createQueue(int max) {

	Queue* q = new Queue;
	q->qArr= new enemy[max];
	q->first = -1;
	q->last = -1;
	q->count = 0;
	return q;
}

//Enqueeee
void Enqueue(Queue*c, enemy &x) {
	
	if (c->count ==0) {
		c->first = 0;
		c->last = 0;
		c->count=1
		c->qArr[c->last] = x;
		return;
		
	}
	else {
		c->last++;
		c->count++;
		c->qArr[c->last] = x;
		return;
	}
}

//Dequeeee
enemy Dequeue(Queue*v) {
	enemy temp;
	
	if (v->count == 1) {
		temp = v->qArr[v->first];
		v->first = -1;
		v->last = -1;
		v->count = 0;
	}
	else {
		temp = v->qArr[v->first];
		v->first++;
		v->count--;
	}
	//if (v->first == NULL)
		//v->last = NULL;
	return temp;
}
/*
Queue* createQueue() {
	Queue* pQueue = new Queue;
	if (!pQueue) {
		return NULL;
	}
	pQueue->count = 0;
	pQueue->first = NULL;
	pQueue->last = NULL;
	return pQueue;
}

void Enqueue(Queue* pQueue, enemy killed) {
	if (pQueue->count == 0) {
		killed.next = NULL;
		pQueue->first = &killed;
		pQueue->last = &killed;
		pQueue->count++;
		return;
	}
	enemy* Last = pQueue->last;
	Last->next = &

}

enemy* Dequeue(Queue* pQueue);
*/
//////////////////////////////////////////////////////
heap* createHeap(int maxSize)
{
	heap* pHeap = new heap;
	pHeap->heapArr = new enemy[maxSize];
	if (!pHeap)
		return NULL;

	pHeap->maxSize = maxSize;
	pHeap->last = -1;
	pHeap->size = 0;

	return pHeap;

}

void insertInHeapPrior(heap*pHeap, enemy dataIn)
{
	if (pHeap->size == 0) //Heap Empty
	{
		pHeap->size = 1;
		pHeap->last = 0;
		if (pHeap->heapArr == NULL) {
			pHeap->heapArr = new enemy;
		}
		pHeap->heapArr[pHeap->last] = dataIn;
	}
	else {
		++(pHeap->last);
		++(pHeap->size);
		pHeap->heapArr[pHeap->last] = dataIn;
		reheapUpPrior(pHeap, pHeap->last);
	}
}

///////////////////////////////////////////////////
void reheapUpPrior(heap*pHeap, int chilLoc)
{
	int parent;
	enemy*heapArr;
	enemy hold;
	//if not at root of the heap [index 0]
	if (chilLoc)
	{
		heapArr = pHeap->heapArr;
		parent = (chilLoc - 1) / 2;
		if (heapArr[chilLoc].priority>heapArr[parent].priority)
		{//swap if child is greater than the parent
			hold = heapArr[parent];
			heapArr[parent] = heapArr[chilLoc];
			heapArr[chilLoc] = hold;
			reheapUpPrior(pHeap, parent);
		}
	}

	return;
}
/////////////////////////////////////////
void insertInHeapArriv(heap*pHeap, enemy dataIn)
{
	if (pHeap->size == 0) //Heap Empty
	{
		pHeap->size = 1;
		pHeap->last = 0;
		pHeap->heapArr[pHeap->last] = dataIn;
	}
	else {
		++(pHeap->last);
		++(pHeap->size);
		pHeap->heapArr[pHeap->last] = dataIn;
		reheapUpArriv(pHeap, pHeap->last);
	}
}

///////////////////////////////////////////////////
void reheapUpArriv(heap*pHeap, int chilLoc)
{
	int parent;
	enemy*heapArr;
	enemy hold;
	//if not at root of the heap [index 0]
	if (chilLoc)
	{
		heapArr = pHeap->heapArr;
		parent = (chilLoc - 1) / 2;
		if (heapArr[chilLoc].arrivtime<heapArr[parent].arrivtime)
		{//swap if child is less than the parent
			hold = heapArr[parent];
			heapArr[parent] = heapArr[chilLoc];
			heapArr[chilLoc] = hold;
			reheapUpArriv(pHeap, parent);
		}
	}

	return;
}
/////////////////////////////////////////// THIS ONE ////////////////
void deleteFromHeapArriv(heap*pHeap, enemy &dataOut) 
{	
	dataOut = pHeap->heapArr[0];
	pHeap->heapArr[0] = pHeap->heapArr[pHeap->last];
	(pHeap->last)--;
	(pHeap->size)--;
	reheapDownArriv(pHeap, 0);
	return;
	
}
//////////////////////////////////////////////////
void reheapDownArriv(heap* pHeap, int root)
{
	enemy hold;
	enemy leftData;
	enemy rightData;
	int smallLoc;
	int last;

	last = pHeap->last;
	if ((root * 2 + 1) <= last) //left Subtree exist
								//There is at least one child
	{
		leftData = pHeap->heapArr[root * 2 + 1];

		if ((root * 2 + 2) <= last) //right Subtree exist
		{
			rightData = pHeap->heapArr[root * 2 + 2];
			//Determine which child is larger 
			if (leftData.arrivtime < rightData.arrivtime)
			{
				smallLoc = root * 2 + 1;//if there's no right or left is greater
			}
			else
			{
				smallLoc = root * 2 + 2;//if right exist and left is not greater
			}
		}
		else				//right Subtree doesn't exist
			smallLoc = root * 2 + 1;


		//test if root <  large subtree
		if (pHeap->heapArr[root].arrivtime > pHeap->heapArr[smallLoc].arrivtime)
		{
			hold = pHeap->heapArr[root];
			pHeap->heapArr[root] = pHeap->heapArr[smallLoc];
			pHeap->heapArr[smallLoc] = hold;
			reheapDownArriv(pHeap, smallLoc);
		}
	}
	return;
}

///////////////////////////////////////////
void deleteFromHeapPrior(heap*pHeap, enemy &dataOut)
{
	dataOut = pHeap->heapArr[0];
	pHeap->heapArr[0] = pHeap->heapArr[pHeap->last];
	(pHeap->last)--;
	(pHeap->size)--;
	reheapDownPrior(pHeap, 0);
	return;

}
//////////////////////////////////////////////////
void reheapDownPrior(heap* pHeap, int root)
{
	enemy hold;
	enemy leftData;
	enemy rightData;
	int largeLoc;
	int last;

	last = pHeap->last;
	if ((root * 2 + 1) <= last) //left Subtree exist
								//There is at least one child
	{
		leftData = pHeap->heapArr[root * 2 + 1];

		if ((root * 2 + 2) <= last) //right Subtree exist
		{
			rightData = pHeap->heapArr[root * 2 + 2];
			//Determine which child is larger 
			if (leftData.priority > rightData.priority)
			{
				largeLoc = root * 2 + 1;//if there's no right or left is greater
			}
			else
			{
				largeLoc = root * 2 + 2;//if right exist and left is not greater
			}
		}
		else				//right Subtree doesn't exist
			largeLoc = root * 2 + 1;


		//test if root <  large subtree
		if (pHeap->heapArr[root].priority < pHeap->heapArr[largeLoc].priority)
		{
			hold = pHeap->heapArr[root];
			pHeap->heapArr[root] = pHeap->heapArr[largeLoc];
			pHeap->heapArr[largeLoc] = hold;
			reheapDownPrior(pHeap, largeLoc);
		}
	}
	return;
}


////////////////////////////////////////////////
/*
void sortArriv(heap* &Inactiv) {
	int min = Inactiv->heapArr[0].arrivtime;
	int index = 0;
	enemy hold;
	int count = Inactiv->size;
	for (int i = 0; i < count; i++) {
		for (int j = i+1; j < count; j++) {
			if (Inactiv->heapArr[j].arrivtime < min) {
				min = Inactiv->heapArr[j].arrivtime;
				index = j;
			}
		}
		hold = Inactiv->heapArr[index];
		Inactiv->heapArr[index] = Inactiv->heapArr[i];
		Inactiv->heapArr[i] = hold; 
	}

}
*/
/////////////////////////////////////////////

//tranforms the inactive enemies with arrival time equals to current time into the active list
void IntoActiv(heap* Inactiv, heap* Activ, int curtime) {
	if (Inactiv->size == 0) {
		return;
	}
	while(Inactiv->heapArr[0].arrivtime == curtime){
			insertInHeapPrior(Activ, Inactiv->heapArr[0]);
			deleteFromHeapArriv(Inactiv, Inactiv->heapArr[0]);
		}
	return;
	}

/////////////////////////////////////////
void pave(heap* Activ, tower &T) {
	int count = Activ->size;
	if (Activ->size == 0) {
		return;
	}
	for (int i = 0; i < count; i++) {
		if (Activ->heapArr[i].type == 0) {
			if (Activ->heapArr[i].remaining == 0) {
				if (T.unpaved > 2) {
					T.unpaved = T.unpaved - Activ->heapArr[i].fire;
					Activ->heapArr[i].remaining = Activ->heapArr[i].delay;
				}
			}
			else {
				Activ->heapArr[i].remaining--;
			}
		}
	}
	return;
}

/////////////////////////////////////////
void updatePrior(heap* Activ,int c1, int c2, int c3) {
	int count = Activ->size;
	if (count == 0) {
		return;
	}
	for (int i = 0; i < count; i++) {
		int distance = Activ->heapArr[i].distance;
		int enemy_fire = Activ->heapArr[i].fire;
		int remaining_time = Activ->heapArr[i].remaining;
		float enemy_health = Activ->heapArr[i].health;
		int enemy_type = Activ->heapArr[i].type;
		float new_priority = ((1 / distance)*enemy_fire*c1*(1 / (remaining_time + 1))) + (enemy_health*c2) + (enemy_type*c3);
		Activ->heapArr[i].priority = new_priority;
	}
	return;
}
//////////////////////////////////////////THIS ONE////////////////////

void sortPrior(heap* Activ) {
	if (Activ->size == 0 || Activ->size == 1) {
		return;
	}
	int max = Activ->heapArr[0].priority;
	int index = 0;
	enemy hold;
	int count = Activ->size;
	for (int i = 0; i < count; i++) {
	for (int j = i + 1; j < count; j++) {
	if (Activ->heapArr[j].priority > max) {
	max = Activ->heapArr[j].priority;
	index = j;
	}
	}
	hold = Activ->heapArr[index];
	Activ->heapArr[index] = Activ->heapArr[i];
	Activ->heapArr[i] = hold;
	}
	/*int count = Activ->size;
	enemy* hold = new enemy[count];
	for (int i = 0; i < count; i++) {
		hold[i] = Activ->heapArr[i];
	}
	Activ->last = -1;
	Activ->size = 0;
	Activ->heapArr = NULL;
	for (int i = 0; i < count; i++) {
		insertInHeapPrior(Activ, hold[i]);
	}*/
	return;
}
	
	/*int max = Activ->heapArr[0].priority;
	int index = 0;
	enemy hold;
	int count = Activ->size;
	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j < count; j++) {
			if (Activ->heapArr[j].priority > max) {
				max = Activ->heapArr[j].priority;
				index = j;
			}
		}
		hold = Activ->heapArr[index];
		Activ->heapArr[index] = Activ->heapArr[i];
		Activ->heapArr[i] = hold;
	}*/


///////////////////////////////////////////
void updateDist(heap* Activ, tower T) {
	int count = Activ->size;
	if (count == 0) {
		return;
	}
	for (int i = 0; i < count; i++) {
		if (Activ->heapArr[i].distance > T.unpaved) {
			if (Activ->heapArr[i].distance - 1 >= 2) {
				Activ->heapArr[i].distance--;
			}
		}
	}
	return;

}
//////////////////////////////////////////
void fireTtoE(tower &T, heap* Activ, int curtime, Queue* killed_enemies) {
	if (Activ->size == 0) {
		return;
	}
	int count;
	if (Activ->size < T.nEnemies) {
		count = Activ->size;
	}
	else {
		count = T.nEnemies;
	}

	for (int i = 0; i < count; i++) {
		float dis = (1.0 / (float)Activ->heapArr[i].distance);
		if (Activ->heapArr[i].firShot == -1) {
			Activ->heapArr[i].firShot = curtime;
		}
		if (Activ->heapArr[i].type == 2) 
		{ //Shielded enemy
			Activ->heapArr[i].health = ((Activ->heapArr[i].health) - (dis* (float)T.fire *0.5));
		}
		else { //paver or fighter
			Activ->heapArr[i].health = ((Activ->heapArr[i].health) - (dis*(float) T.fire));
		}
		if (stamp == 3)
			stamp = 3;
		cout << Activ->heapArr[i].health <<endl;
		//cout << Activ->heapArr[i].health;
		/*for (int i = 0; i < count; i++) {
		while (Activ->heapArr[i].health <= 0) {
		Activ->heapArr[i].killtime = curtime;
		Enqueue(killed_enemies, Activ->heapArr[i]);
		deleteFromHeapPrior(Activ, Activ->heapArr[i]);
		}
		}*/
		if (Activ->heapArr[i].health <= 0) {
			Activ->heapArr[i].killtime = curtime;
			Enqueue(killed_enemies, Activ->heapArr[i]);
			deleteFromHeapPrior(Activ, Activ->heapArr[i]);
		}
	}
	
	/*for (int i = 0; i < count; i++) {
		while (Activ->heapArr[i].health <= 0) {
			Activ->heapArr[i].killtime = curtime;
			Enqueue(killed_enemies, Activ->heapArr[i]);
			deleteFromHeapPrior(Activ, Activ->heapArr[i]);
		}
	}*/
	return;
}
	/*
	int counter = 0;
	int killed = 0;
	for (int i = 0; i < count; i++) {
		if (counter < T.nEnemies) {
			if (Activ->heapArr[i].killtime == -1) { //the enemy is not killed yet
				if (Activ->heapArr[i].firShot == -1) {
					Activ->heapArr[i].firShot = curtime;
				}
				if (Activ->heapArr[i].type == 2) { //Shielded enemy
					Activ->heapArr[i].health = (Activ->heapArr[i].health) - ((1 / Activ->heapArr[i].distance)* T.fire *0.5);
					counter++;
				}
				else { //paver or fighter
					Activ->heapArr[i].health = (Activ->heapArr[i].health) - ((1 / Activ->heapArr[i].distance)* T.fire);
					counter++;
				}
				if (Activ->heapArr[i].health <= 0) {
					Activ->heapArr[i].killtime = curtime;
				}
			}
			else { //the enemy is killed
				killed++;
			}
		}
		else {
			break;
		}
	}

	if (killed < count) {//number of killed enemies less than total number of enemies
		return true;
	}
	else {
		return false;
	}
	*/


//////////////////////////////////////////
bool fireEtoT(tower &T, heap* Activ) {
	//Fire the tower by the enemies, Returns 1 if the tower is destroyed, Returns 0 if it is not yet destroyed
	int count = Activ->size;
	if (count == 0) {
		return false;
	}
	for (int i = 0; i < count; i++) {
		if (T.damage >= T.health) {
			return true;
		}
		else {
			if (Activ->heapArr[i].type != 0) { //enemy is not paver
					if (Activ->heapArr[i].remaining == 0) {//enemy is ready to shoot
						float x = (float) (1 / Activ->heapArr[i].distance);
						T.damage = T.damage + x*(Activ->heapArr[i].fire);
						Activ->heapArr[i].remaining = Activ->heapArr[i].delay;
					}
					else {
						Activ->heapArr[i].remaining--;
					}
				}
			}
		}
	if (T.damage >= T.health) {
		return true;
	}
	return false;
}
/////////////////////////////////////////////////////

void readData(tower &towers, enemy enemies[], int &c1, int &c2, int &c3, int &nofEnemies) {
	
	ifstream inputFile;
	inputFile.open("input.txt");

	//Checking if file failed to open for any reason 
	/*if (inputFile.fail()) {
		cerr << "Error Opening File" << endl;
		exit(1);
	}*/
	if (inputFile.is_open()) {
		//Putting the data of the first line into the first tower
		inputFile >> towers.health >> towers.nEnemies >> towers.fire;

		//Putting the data of the second line into the constants
		inputFile >> c1 >> c2 >> c3;

		//Reading enemies data line by line untill the end of the file
		//Assuming that there is no -1 at the end of the file
		int j = 0;
		while (!inputFile.eof()) {
			inputFile >> enemies[j].ID >> enemies[j].arrivtime >> enemies[j].health >>
				enemies[j].fire >> enemies[j].delay >> enemies[j].type >> enemies[j].region;
			j++;
			nofEnemies++;
		}

		inputFile.close();
	}
}



//////////////////////////////////////////////////////
void outputData(tower towers[], Queue* Killed, bool win, int nofEnemies) {
	int killed_enemies = Killed->count;
	enemy hold;
	double avgFD, avgKD;
	int sum1 = 0, sum2 = 0;
	ofstream outputFile;
	outputFile.open("output.txt");
	while (Killed->count != 0) {
		hold = Dequeue(Killed);
		int FD, KD, FT;
		FD = hold.firShot - hold.arrivtime;
		sum1 += FD;
		KD = hold.killtime - hold.firShot;
		sum2 += KD;
		FT = hold.killtime + hold.arrivtime;
		outputFile << hold.killtime << " " << hold.ID << " " << FD << " " << KD << " " << FT << endl;
	}

	int aliveEnemies = nofEnemies - killed_enemies;

	for (int i = 0; i < 4; i++) {
		outputFile << towers[i].damage << " ";
	}
	outputFile << endl;

	for (int i = 0; i < 4; i++) {
		outputFile << towers[i].unpaved << " ";
	}
	outputFile << endl;

	if (win == 1) {
		outputFile << "WIN" << endl;
		outputFile << nofEnemies << endl;
		
		avgFD = (double)sum1 / (double)nofEnemies;
		avgKD = (double)sum2 / (double)nofEnemies;
		outputFile << avgFD << endl;
		outputFile << avgKD << endl;
	}

	else {
		outputFile << "LOSS" << endl;
		outputFile << killed_enemies << endl;
		outputFile << aliveEnemies << endl;
			
		avgFD = (double)sum1 / (double)killed_enemies;
		avgKD = (double)sum2 / (double)killed_enemies;
		outputFile << avgFD << endl;
		outputFile << avgKD << endl;
	}
	outputFile.close();
}
