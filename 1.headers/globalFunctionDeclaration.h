#pragma once
#include "general.h"
void YNInput(const char* notion, const char* answerA = "Yes", const char* answerB = "No");
void YNInput(int i, const char* answerA, const char* answerB);
void BasicInfoOutput(const char* notion, const char* answerA, const char* answerB);
void YNInput(const char* notion, const char* answerA, int numberOfAnswers);

bool equal(int* a, const int* b);
void getsubString(int* source, int start, int length, int* destination);

inline void quickOutput(const char* sentence, int x = 0, int y = 0);
/*inline */void quickOutput(char* sentence, int x = 0, int y = 0);
/*inline */void quickOutput(string toBeOuput, int x = 0, int y = 0);
void quickOutput(const char* sentence, const char* line, int lineNumber);
void quickOutput(string sentence, const char* line, int lineNumber);
void quickOutput(const char* sentence, int x, int y, int R, int G, int B);
void quickOutput(string toBeOuput, int x, int y, int R, int G, int B);
