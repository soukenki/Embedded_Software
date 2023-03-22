#ifndef __MatrixKey_H__
#define __MatrixKey_H__

#include <REGX52.H>
#include "LCD1602.h"



// Àı1£º°´¼ü1~16
void KeyDown(unsigned char* keynum);

// Àı2£º°´¼ü1~16
unsigned char MatrixKey();


// ÃÜÂëËø
void Password(unsigned char* keynum);

#endif