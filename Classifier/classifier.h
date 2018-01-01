#ifndef FOO_H_   /* Include guard */
#define FOO_H_

typedef enum {singleClench, doubleClench, clenchHold, noClench} clenchType;

int begin_function(char *input_name, clenchType type);

#endif // FOO_H_
