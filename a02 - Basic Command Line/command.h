#ifndef TOKENIZER_H_
#define TOKENIZER

#include <string>
#include <list>

void separate_commands(std::list<std::list<char> > line);
void execute_commands(std::list<std::list<std::string> > commands);

#endif
