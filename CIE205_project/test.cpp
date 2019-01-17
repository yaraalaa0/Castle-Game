#include <iostream>
using namespace std;

struct enemy {
	int ID;
	int arrivtime;
	int killtime = -1;
	int firShot = -1;
	float health;
	int fire;
	int delay;
	int remaining = 0;
	int distance = 60;
	int type;
	int priority;
	char region;
};

struct tower {
	int health;
	int nEnemies;
	int fire;
	int unpaved = 30;
	int damage;
};

struct heap
{
	enemy* heapArr;
	int last;
	int size;
	int maxSize;
	int parent(int i) { return (i - 1) / 2; }
	int left(int i) { return (2 * i + 1); }
	int right(int i) { return (2 * i + 2); }
};
int main() {
	


	int stamp = 0; //time stamp
	int flag = 0; //state of the game. flag =1 -> you lose , flag = 2 -> you win

	int c1;
	int c2;
	int c3;

	tower A;
	tower B;
	tower C;
	tower D;


	heap* ActivA = createHeap(50);
	heap* InactivA = createHeap(50);
	heap* ActivB = createHeap(50);
	heap* InactivB = createHeap(50);
	heap* ActivC = createHeap(50);
	heap* InactivC = createHeap(50);
	heap* ActivD = createHeap(50);
	heap* InactivD = createHeap(50);

	tower Towers[4];
	enemy Enemies[200];
	int numberEnemies = 0;



	return 0;
}

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