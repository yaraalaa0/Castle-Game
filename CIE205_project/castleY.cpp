#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "Castle.h"
using namespace std;

int stamp;

int main() {
	using namespace std::this_thread;     // sleep_for, sleep_until
	using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
	using std::chrono::system_clock;
	stamp = 0;
	 //time stamp
	int flag = 0; //state of the game. flag =1 -> you lose , flag = 2 -> you win

	int c1, c2, c3;
	
	tower A;
	tower B;
	tower C;
	tower D;

	
	heap* ActivA = createHeap(20);
	heap* InactivA = createHeap(20);
	heap* ActivB = createHeap(20);
	heap* InactivB = createHeap(20);
	heap* ActivC = createHeap(20);
	heap* InactivC = createHeap(20);
	heap* ActivD = createHeap(20);
	heap* InactivD = createHeap(20);

	Queue* KilledE = createQueue(100);

	enemy Enemies[200];
	int numberEnemies = -1;
	readData(A, Enemies, c1, c2, c3,numberEnemies);

	B = A;
	C = A;
	D = A;

	for (int i = 0; i < numberEnemies; i++) {
		if (Enemies[i].region == 'A') {
			insertInHeapArriv(InactivA, Enemies[i]);
		}
		if (Enemies[i].region == 'B') {
			insertInHeapArriv(InactivB, Enemies[i]);
		}
		if (Enemies[i].region == 'C') {
			insertInHeapArriv(InactivC, Enemies[i]);
		}
		if (Enemies[i].region == 'D') {
			insertInHeapArriv(InactivD, Enemies[i]);
		}
	}

	int flag1 = 0;
	int flag2 = 0;
	int flag3 = 0;
	int flag4 = 0;
	bool TowerDestroyedA = 0;
	bool TowerDestroyedB = 0;
	bool TowerDestroyedC = 0;
	bool TowerDestroyedD = 0;

	while (flag == 0) {

		if (TowerDestroyedA == 1 && flag1 == 0) {
			int count = ActivA->size;
			for (int i = 0; i < count; i++) {
				insertInHeapPrior(ActivB, ActivA->heapArr[i]);
			}
			count = InactivA->size;
			for (int i = 0; i < count; i++) {
				insertInHeapArriv(InactivB, InactivA->heapArr[i]);
			}
			flag1 = 1;

		}

		if (TowerDestroyedB == 1 && flag2 == 0) {
			int count = ActivB->size;
			for (int i = 0; i < count; i++) {
				insertInHeapPrior(ActivC, ActivB->heapArr[i]);
			}
			count = InactivB->size;
			for (int i = 0; i < count; i++) {
				insertInHeapArriv(InactivC, InactivB->heapArr[i]);
			}
			flag2 = 1;
		}

		if (TowerDestroyedC == 1 && flag3 ==0) {
			int count = ActivC->size;
			for (int i = 0; i < count; i++) {
				insertInHeapPrior(ActivD, ActivC->heapArr[i]);
			}
			count = InactivC->size;
			for (int i = 0; i < count; i++) {
				insertInHeapArriv(InactivD, InactivC->heapArr[i]);
			}
			flag3 = 1;
		}

		if (TowerDestroyedD == 1&& flag4==0) {
			int count = ActivD->size;
			for (int i = 0; i < count; i++) {
				insertInHeapPrior(ActivA, ActivD->heapArr[i]);
			}
			count = InactivD->size;
			for (int i = 0; i < count; i++) {
				insertInHeapArriv(InactivA, InactivD->heapArr[i]);
			}
			flag4 = 1;
		}

		if (TowerDestroyedA == 0) {
			pave(ActivA, A);
			updateDist(ActivA, A);
			IntoActiv(InactivA, ActivA, stamp);
			updatePrior(ActivA, c1, c2, c3);
			sortPrior(ActivA);
			fireTtoE(A, ActivA, stamp, KilledE);
			TowerDestroyedA = fireEtoT(A, ActivA);
		}
		
		if (TowerDestroyedB == 0) {
			IntoActiv(InactivB, ActivB, stamp);
			pave(ActivB, B);
			updateDist(ActivB, B);
			updatePrior(ActivB, c1, c2, c3);
			sortPrior(ActivB);
			fireTtoE(B, ActivB, stamp, KilledE);
			TowerDestroyedB = fireEtoT(B, ActivB);
			
			}


		if (TowerDestroyedC == 0) {
			IntoActiv(InactivC, ActivC, stamp);
			pave(ActivC, C);
			updateDist(ActivC, C);
			updatePrior(ActivC, c1, c2, c3);
			sortPrior(ActivC);
			fireTtoE(C, ActivC, stamp, KilledE);
			TowerDestroyedC = fireEtoT(C, ActivC);
			
		}

		if (TowerDestroyedD == 0) {
			IntoActiv(InactivD, ActivD, stamp);
			pave(ActivD, D);
			updateDist(ActivD, D);
			updatePrior(ActivD, c1, c2, c3);
			sortPrior(ActivD);
			fireTtoE(D, ActivD, stamp, KilledE);
			TowerDestroyedD = fireEtoT(D, ActivD);
			
		}


		if (TowerDestroyedA == 1 && TowerDestroyedB == 1 && TowerDestroyedC == 1 && TowerDestroyedD == 1) {
			flag = 1; //You lose
		}
		if (KilledE->count >= numberEnemies) {
			flag = 2; //You win
		}

		//sleep_for(1s);
		stamp++;
	
	}

	
	int win;
	if (flag == 1) {
		win = 0;
	}
	if (flag == 2) {
		win = 1;
	}

	tower Towers[4];
	Towers[0] = A;
	Towers[1] = B;
	Towers[2] = C;
	Towers[3] = D;


	outputData(Towers, KilledE, win,numberEnemies);



	return 0;
}