/*FACTORY_CONTROLLER.H*/
#ifndef FACTORY_CONTROLLER_H
#define FACTORY_CONTROLLER_H

#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>
#include <queue>
#include <string>

class Candy {
public:
	Candy(int _product_id);
	int product_id;
	std::string name;
};
void push(int product_id, std::queue<Candy*> *belt);
int pop(std::string consumer, std::queue<Candy*> *belt);
void tracker(int product_id, int amount, std::string consumer = "0");
void print_summary();
void print_report();

#endif