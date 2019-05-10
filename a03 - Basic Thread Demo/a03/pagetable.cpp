#include "pagetable.h"
#include <stdio.h>

unsigned int logicalToPage(unsigned int logicalAddress, unsigned int mask, unsigned int shift) {
	unsigned int andResult = logicalAddress & mask;	//bitwise AND
	unsigned int pageNumber = andResult >> shift;	//bitwise right shift
	return pageNumber;
}

void firstPageInsert(Pagetable *pageTable, unsigned int logicalAddress, unsigned int frame) {
	Level rootNode = { 0, pageTable, false, nullptr, nullptr };
	pageInsert(&rootNode, logicalAddress, frame);
}

void pageInsert(Level *level, unsigned int logicalAddress, unsigned int frame) {
	if (level->leaf) { //Need a way to determine when a node is a leaf

	}
	else {
		Level newLevel = { level->depth + 1, level->pagePtr, false, nullptr, nullptr };
		*level->nextLevel = newLevel;
		//Need an array of Levels?
		pageInsert(&newLevel, logicalAddress, frame); //Update address and frame??
	}
}

Map *pageLookUp(Pagetable *pageTable, unsigned int logicalAddress) {
	//traverse pagetable according to the given address
}