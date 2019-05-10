struct Pagetable {
	Pagetable *rootNode;
	int levelCount;
	unsigned long bitMask[];
	int shift[];
	int entryCount[];
};

struct Map {
	//Map struct?
};

struct Level {
	int depth;
	Pagetable *pagePtr;
	bool leaf;
	Level *nextLevel;
	Map *mapPtr;
};

unsigned int logicalToPage(unsigned int logicalAddress, unsigned int mask, unsigned int shift);

void firstPageInsert(Pagetable *pageTable, unsigned int logicalAddress, unsigned int frame);

void pageInsert(Level *level, unsigned int logicalAddress, unsigned int frame);

Map *pageLookUp(Pagetable *pageTable, unsigned int logicalAddress);