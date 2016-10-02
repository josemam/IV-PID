#include <stdint.h> // so PID, RNG, ID, etc get the proper integer size
#include "io.h"
#include "func.h"

/**
  * @brief Gets all possible PID values for given conditions
  * @param fixed_hp Whether the HP is fixed
  * @param shiny    Whether a shiny Pokémon is wanted
  * 
  * The user is asked some IVs, nature, ability, list of
  * allowed methods, maybe HP type and minimum power,
  * and maybe ID and SID. Then all possible PID for that will
  * (hopefully) be found.
  * 
  * @note The IVs are considered as minimum if any
  * of \p fixed_hp and \p shiny is true and are taken
  * as exact wanted IVs otherwise, as any other combination
  * would be pointless.
  */
void IVtoPID(bool fixed_hp, bool shiny) {
  bool exact = !fixed_hp && !shiny;
  PokeData pdata;
  AskIVs(pdata.hp, pdata.at, pdata.df, pdata.spa, pdata.spd, pdata.spe);

  pdata.nature  = AskNature ();
  pdata.ability = AskAbility();
  pdata.hp_type = pdata.hp_power = -1;
  pdata.IDxorSID = 1;
  int gba     = AskMethods();
  if (fixed_hp) {
    pdata.hp_type = AskHiddenPowerType();
    pdata.hp_power = AskHiddenPowerBasePower();
  }
  if (shiny) {
    uint16_t id = AskID(), sid = AskSID();
    pdata.IDxorSID = (id^sid)&0xFFF8;
  }

  int count = 0;
  TestAllPossibleSeedsBackwards(pdata, gba, exact, count);

  if (!count)
    NoPIDMsg();
  else
    EndOfResults();

  Pause();
}

void ExactIVtoPID()       { IVtoPID(false, false); }
void minIVnHPtoPID()      { IVtoPID(true,  false); }
void minIVtoShinyPID()    { IVtoPID(false, true ); }
void minIVnHPtoShinyPID() { IVtoPID(true,  true ); }

/**
  * @brief Gets all possible PID values for a chained shiny
  * 
  * The user is asked some IVs, nature, ability, ID
  * and SID. Then all possible PID for that will
  * (hopefully) be found.
  */
void ExactIVtoChainedShinyPID() {
  bool exact = true;
  PokeData pdata;
  AskIVs(pdata.hp, pdata.at, pdata.df, pdata.spa, pdata.spd, pdata.spe);

  pdata.nature  = AskNature ();
  pdata.ability = AskAbility();
  uint16_t id = AskID(), sid = AskSID();
  pdata.IDxorSID = (id^sid)&0xFFF8;

  int count = 0;
  TestAllPossibleSeedsBackwards(pdata, -1, exact, count);

  if (!count)
    NoPIDMsg();
  else
    EndOfResults();

  Pause();
}

/**
  * @brief Gets all possible IV distributions for a given PID
  * 
  * The user is asked a PID and a list of methods. Then all
  * possible IV distributions for that will be (hopefully) found.
  */
void PIDtoIV() {
  uint32_t pid = AskPID();
  int gba = AskMethods();

  int count = 0;
  TestAllPossibleSeedsForwards(pid, gba, count);

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

  ShowSIDRange(maxSIDforShiny(pid, id));
  Pause();
}

typedef void (*modefunc)(void); 
modefunc modes[] = {
  ExactIVtoPID,
  minIVnHPtoPID,
  minIVtoShinyPID,
  minIVnHPtoShinyPID,
  ExactIVtoChainedShinyPID,
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
