#include <stdint.h> // so PID, RNG, ID, etc get the proper integer size
#include "io.h"
#include "func.h"

void ExactIVtoPID()       { IVtoPID(false, false); }
void minIVnHPtoPID()      { IVtoPID(true,  false); }
void minIVtoShinyPID()    { IVtoPID(false, true ); }
void minIVnHPtoShinyPID() { IVtoPID(true,  true ); }

/**
  * @brief Gets all possible IV distributions for a given PID
  * 
  * The user is asked a PID and a list of methods. Then all
  * possible IV distributions for that will be (hopefully) found.
  */
void PIDtoIV() {
  uint32_t pid = AskPID();
  int gba = AskMethods();

  uint32_t high_seed = pid << 16; // Any RNG state that leads to the PID must start with this
  uint16_t high_pid = pid >> 16;
  int count = 0;
  /* All the possible RNG seeds are tested */
  for (uint32_t low_seed = 0; low_seed < 65536; low_seed++)
    if (HighPIDmatches(low_seed | high_seed, high_pid))
      GetFromSeed(low_seed | high_seed, count, gba);

  if (!count)
    NoIVMsg();
  else
    EndOfResults();

  Pause();
}

/**
  * @brief Gets SID from a PID and a Trainer ID so the Pokémon is shiny
  */
void GetSID() {
  uint32_t pid = AskPID();
  uint16_t  id = AskID ();

  uint16_t pid_h = pid >> 16;
  uint16_t pid_l = pid;

  ShowSIDRange(((pid_h^pid_l)^id) | 7);
  Pause();
}

typedef void (*modefunc)(void); 
modefunc modes[] = {
  ExactIVtoPID,
  minIVnHPtoPID,
  minIVtoShinyPID,
  minIVnHPtoShinyPID,
  PIDtoIV,
  GetSID
};
int nmodes = sizeof(modes)/sizeof(modefunc);

int main() {
  char mode;
  do {
    mode = AskMode();

    if (mode > '0' && mode - nmodes <= '0')
      modes[mode - '1']();

  } while (mode != '0');
}
