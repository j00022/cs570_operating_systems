#include "tokenizer.h"
#include "command.h"

int  main(int argc, char* argv[]) {
    while(1) {
        tokenizer(argc, argv);
        separate_commands(tokens);
    }
}
