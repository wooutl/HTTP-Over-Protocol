#include "standard.h"

void error(char const *errorMsg);
void info(char const *message);
void warn(char const *message);

void fillTimeBuffer(char *timebuf);
int setNonBlocking(int fd);