/*FACTORY_CONTROLLER.CPP*/
#include "factory_controller.h"

using namespace std;

int frogs, escargots, total;
int total_F, total_E;
int lucy_F, lucy_E, ethel_F, ethel_E;

Candy::Candy(int _product_id) {
	product_id = _product_id;
	if (product_id == 0)
		name = "crunchy frog bite";
	if (product_id == 1)
		name = "escargot sucker";
}

void push(int product_id, queue<Candy*> *belt) {
	Candy *candy = new Candy(product_id);
	belt->push(candy);
	tracker(candy->product_id, 1);
	printf("Added %s.\n", candy->name.c_str());
}

int pop(string consumer, queue<Candy*> *belt) {
	Candy *candy = belt->front();
	belt->pop();
	tracker(candy->product_id, -1, consumer.c_str());
	printf("%s consumed %s.\n", consumer.c_str(), candy->name.c_str());

	return candy->product_id;
}

void tracker(int product_id, int amount, string consumer) {
	/*LIVE count of candies on belt*/
	if (product_id == 0)
		frogs += amount;
	if (product_id == 1)
		escargots += amount;

	/*Totals for producers and consumers*/
	if (amount > 0) {			/*Being produced*/
		total++;
		if (product_id == 0)	/*Frog*/
			total_F++;
		if (product_id == 1)	/*Escargot*/
			total_E++;
	}
	else {						/*Being consumed*/
		if (product_id == 0) {	/*Frog*/
			if (consumer.compare("Lucy") == 0)
				lucy_F++;
			else
				ethel_F++;
		}
		if (product_id == 1) {	/*Escargot*/
			if (consumer.compare("Lucy") == 0)
				lucy_E++;
			else
				ethel_E++;
		}
	}
	print_summary();
}

void print_summary() {
	printf("Belt: %d frogs + %d escargots = %d. produced: %d\t", frogs, escargots, frogs + escargots, total);
}

void print_report() {
	printf("\nPRODUCTION REPORT\n----------------------------------------\n");
	printf("crunchy frog bite producer generated %d candies\n", total_F);
	printf("escargot sucker producer generated %d candies\n", total_E);
	printf("Lucy consumed %d crunchy frog bites + %d escargot suckers = %d\n", lucy_F, lucy_E, lucy_E + lucy_F);
	printf("Ethel consumed %d crunchy frog bites + %d escargot suckers = %d\n", ethel_F, ethel_E, ethel_E + ethel_F);
}