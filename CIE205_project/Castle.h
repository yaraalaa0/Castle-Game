struct enemy {
	int ID;
	int arrivtime;
	int killtime = -1;
	int firShot= -1;
	float health;
	int fire;
	int delay;
	int remaining=0;
	int distance=60;
	int type;
	float priority=-1;
	char region;
	enemy* next;
};

struct tower {
	int health;
	int nEnemies;
	int fire;
	int unpaved = 30;
	float damage=0;
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

struct Queue {
	enemy* qArr;
	int first;
	int last;
	int count;
};

heap* createHeap(int maxSize);
void  insertInHeapPrior(heap*pHeap, enemy dataIn);
void  insertInHeapArriv(heap*pHeap, enemy dataIn);
void  deleteFromHeapArriv(heap*pHeap, enemy &dataOut);
void  deleteFromHeapPrior(heap*pHeap, enemy &dataOut);
void reheapUpPrior(heap*pHeap, int chilLoc);
void reheapUpArriv(heap*pHeap, int chilLoc);
void reheapDownArriv(heap*pHeap, int root);
void reheapDownPrior(heap*pHeap, int root);

void updatePrior(heap* Activ, int c1, int c2, int c3); //Calculates the priority for each of the active enemies and updates it 
void sortPrior(heap* Activ); //Sorts the active enemies based on their priority value
void IntoActiv(heap* Inactiv, heap* Activ, int curtime); //tranforms the inactive enemies with arrival time equals to current time into the active list 
void pave(heap* Activ, tower &T); //check the type of the active enemies and update the unpaved distance of the tower based on the enemies type
void updateDist(heap* Activ, tower T); //Updates the distance of the enemies for 1 time step
void fireTtoE(tower &T, heap* Activ, int curtime, Queue* killed_enemies); //Fire the enemies by the tower, Returns 1 if all the enemies are killed, Returns 0 if not all of them are killed yet
bool fireEtoT(tower &T, heap* Activ); //Fire the tower by the enemies, Returns 1 if the tower is destroyed, Returns 0 if it is not yet destroyed
void readData(tower &towers, enemy enemies[], int &c1, int &c2, int &c3, int &nofenemies);
void outputData(tower towers[], Queue* Killed, bool win, int nofEnemies);

Queue* createQueue(int max);
void Enqueue(Queue* pQueue, enemy &killed);
enemy Dequeue(Queue* pQueue);