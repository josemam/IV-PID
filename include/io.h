/**
  * @file io.h
  * @brief Command line I/O for iv-pid
  */

#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>

void Pause();

/**
  * @brief Prints a given IV-PID combination
  */
void Print(uint32_t pid, uint16_t iv1, uint16_t iv2, int method, int count);

bool AvoidLoops();

/**
  * @brief Shows all natures and their IDs
  */
void ShowAllNatures();

/**
  * @brief Shows all types and their IDs
  * @note The IDs do not match the in-game internal IDs
  */
void ShowAllTypes();

void AskIVs(int &hp, int &at, int &df, int &spa, int &spd, int &spe);
uint32_t AskPID();
int AskNature();
int AskHiddenPowerType();
int AskHiddenPowerBasePower();
int AskAbility();
bool AskYN(const char* msg);
int AskMethods();
uint16_t AskID(bool SID = false);
uint16_t AskSID();
char AskMode();

void ShowSIDRange(uint16_t sid_max);
void NoPIDMsg();
void NoIVMsg();
void EndOfResults();

#endif
