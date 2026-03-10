#pragma once

//条件编译 DEBUG模式下，每执行一次gl函数都检查错误
#ifdef DEBUG
#define GL_CALL(func) func; checkErr();
#else
#define GL_CALL(func) func;
#endif

void checkErr();