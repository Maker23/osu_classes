#ifndef FLAG_H
#define FLAG_H

#define DEBUG false
#define ASSIGN false

#ifndef TEST
#define TEST false // override this on the compiler command line
#endif

//TODO: make this a static member of the Character class.
// Can enum be a static member? Haven't have time to test yet
enum CharType {GOBLIN,BARBARIAN,REPTILE,BLUECHIX,SHADOW};

#endif
