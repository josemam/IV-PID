/**
  * @file func.h
  * @brief Functions for iv-pid
  */

#include "func.h"

extern void Print(uint32_t pid, uint16_t iv1, uint16_t iv2, int method, int count);

/* RNG constants */
const uint32_t MULTIPLIER = 1103515245U;
const uint32_t INVERSE_MULTIPLIER = 4005161829U;
const uint32_t INCREMENT = 24691;

uint16_t RNG(uint32_t &state) {
  state = state*MULTIPLIER + INCREMENT;
  return (state >> 16);
}

uint16_t antiRNG(uint32_t &state) {
  state = INVERSE_MULTIPLIER*(state - INCREMENT);
  return (state >> 16);
}

bool minIVtest(uint16_t n, int hp, int at, int df) {
  return (((31 << 10) & n) >= (df << 10)) && (((31 << 5) & n) >= (at << 5)) && ((31 & n) >= hp);
}

bool exactIVtest(uint16_t n, int hp, int at, int df) {
  return (0x7FFF & n) == ((df << 10) | (at << 5) | hp);
}

IVtester GetIVtester(bool exact) {
  return exact ? exactIVtest : minIVtest;
}

bool PIDtest(uint32_t pid, int nature, int ability) {
  return (nature == -1 || (int) pid%25 == nature) && (ability == 2 || (int) pid%2 == ability);
}

bool HPpretest(uint16_t iv, int hpt, int hpp) {
   bool type_ok = hpt == -1;
   bool power_ok = hpp == -1;
   if (type_ok && power_ok)   // any HP is allowed
      return true;

   int spa = ((iv>>5)&31), spd = ((iv>>10)&31), spe = (iv&31);
   if (!type_ok) {
      /* Checks if the wanted type is one of
         the possible types from the known IVs
      */
      int hp_type = (((spe&1) << 3) | ((spa&1) << 4) | ((spd&1) << 5)); // NOT the type ID! type ID is hp_type*15/63
      /* The wanted type is possible iff the wanted type range and
         the hp_type values range (which is 8 consecutive values
         as HP, Attack and Defense IVs can only increase hp_type
         by 1, 2 and 4 each or leave it as it is) overlap
      */
      type_ok = hp_type*15/63 <= hpt && (hp_type|7)*15/63 >= hpt;
      if (!type_ok)
         return false;
   }
   if (!power_ok) {
      /* Checks if the maximum possible HP power from the known IVs is enough */
      int max_possible_hp_power = ((((spe&2) << 2) | ((spa&2) << 3) | ((spd&2) << 4)) | 7)*40/63 + 30;
      power_ok = max_possible_hp_power >= hpp;
      if (!power_ok)
         return false;
   }
   return true;
}

bool HPtest(uint16_t iv1, uint16_t iv2, int hpt, int hpp) {
   bool type_ok = hpt == -1;
   bool power_ok = hpp == -1;
   if (type_ok && power_ok)   // any HP is allowed
      return true;

   int hp = (iv1&31), at = ((iv1>>5)&31), df = ((iv1>>10)&31), spa = ((iv2>>5)&31), spd = ((iv2>>10)&31), spe = (iv2&31);
   if (!type_ok) {
      int hp_type = ((hp&1) | ((at&1) << 1) | ((df&1) << 2) | ((spe&1) << 3) | ((spa&1) << 4) | ((spd&1) << 5))*15/63;
      type_ok = hp_type == hpt;
      if (!type_ok)
         return false;
   }
   if (!power_ok) {
      int hp_power = (((hp&2) >> 1) | (at&2) | ((df&2) << 1) | ((spe&2) << 2) | ((spa&2) << 3) | ((spd&2) << 4))*40/63 + 30;
      power_ok = hp_power >= hpp;
      if (!power_ok)
         return false;
   }
   return true;
}

bool XORtest(uint16_t pid_l, uint16_t pid_h, uint16_t IDxorSID) {
  return IDxorSID == 1 || ((pid_l^pid_h^IDxorSID)&0xFFF8) == 0;
}

void FindPID(uint32_t seed, uint16_t iv1, uint16_t iv2, const PokeData& pdata, int method, int &count) {
  uint16_t pid_h, pid_l;
  pid_h = antiRNG(seed);
  pid_l = antiRNG(seed);
  uint32_t pid = (pid_l | (pid_h << 16));
  for (int i = 0; i < 2; pid^=0x80008000, i++)
    if (PIDtest(pid, pdata.nature, pdata.ability)
            && HPtest(iv1, iv2, pdata.hp_type, pdata.hp_power)
            && XORtest(pid_l, pid_h, pdata.IDxorSID))
      Print(pid, iv1, iv2, method, ++count);
}

void TestAllPossibleSeedsBackwards(const PokeData& pdata, int gba, bool exact, int& count) {
  IVtester IVtest = GetIVtester(exact);
  for (int spa_ = (exact ? pdata.spa : 31); spa_ >= pdata.spa; spa_--)
    for (int spd_ = (exact ? pdata.spd : 31); spd_ >= pdata.spd; spd_--)
      for (int spe_ = (exact ? pdata.spe : 31); spe_ >= pdata.spe; spe_--) {
        uint32_t high_seed = (spe_ | (spa_ << 5) | (spd_ << 10)) << 16;
        for (uint32_t low_seed = 0; low_seed < 65536; low_seed++)
          Test(low_seed | high_seed, pdata, gba, IVtest, count);
      }
}

void FindChainedPID(uint32_t seed, int iv1, int iv2, const PokeData& pdata, int &count) {
  uint16_t pid_corrector = 0;
  for (int i = 15; i >= 3; i--)
    pid_corrector |= ((antiRNG(seed) & 1) << i);

  uint16_t pid_h, pid_l;
  pid_h = ((antiRNG(seed) & 7) | ((pdata.IDxorSID^pid_corrector) & (~7)));
  pid_l = ((antiRNG(seed) & 7) | pid_corrector);
  uint32_t pid = (pid_l | (pid_h << 16));
  if (PIDtest(pid, pdata.nature, pdata.ability))
    Print(pid, iv1, iv2, -1, ++count);
}

void Test(uint32_t seed, const PokeData& pdata, int gba, IVtester& IVtest, int &count) {
  uint16_t n2 = seed >> 16;
  if (!HPpretest(n2, pdata.hp_type, pdata.hp_power))
    return;

  uint16_t n1 = antiRNG(seed);

  if (IVtest(n1, pdata.hp, pdata.at, pdata.df)) {
    if (gba == -1)
      return FindChainedPID(seed, n1, n2, pdata, count);

    FindPID(seed, n1, n2, pdata, 0, count);
    if (gba) {
      uint32_t seed_copy = seed;
      antiRNG(seed_copy);
      FindPID(seed_copy, n1, n2, pdata, 1, count);

      if (gba > 1) {
        antiRNG(seed_copy);
        FindPID(seed_copy, n1, n2, pdata, 4, count);
      }
    }
  }

  if (gba) {
    n1 = antiRNG(seed);   
    if (IVtest(n1, pdata.hp, pdata.at, pdata.df)) {
      FindPID(seed, n1, n2, pdata, 2, count);

      if (gba > 1) {
        antiRNG(seed);
        FindPID(seed, n1, n2, pdata, 3, count);
      }
    }
  }
}

bool HighPIDmatches(uint32_t state, uint16_t pid_h) {
  return RNG(state) == pid_h;
}

void GetFromSeed(uint32_t seed, int &count, int gba) {
  uint32_t pid = ((seed >> 16) | (RNG(seed) << 16));
  uint16_t n2, n3;
  n2 = RNG(seed);
  n3 = RNG(seed);
  Print(pid, n2, n3, 0, ++count);

  if (gba) {
    uint16_t n4;
    n4 = RNG(seed);
    Print(pid, n3, n4, 1, ++count);
    Print(pid, n2, n4, 2, ++count);

    if (gba > 1) {
      uint16_t n5;
      n5 = RNG(seed);
      Print(pid, n3, n5, 3, ++count);  
      Print(pid, n4, n5, 4, ++count);
    }
  }
}

void TestAllPossibleSeedsForwards(uint32_t pid, int gba, int& count) {
  uint32_t high_seed = pid << 16; // Any RNG state that leads to the PID must start with this
  uint16_t high_pid = pid >> 16;
  for (uint32_t low_seed = 0; low_seed < 65536; low_seed++)
    if (HighPIDmatches(low_seed | high_seed, high_pid))
      GetFromSeed(low_seed | high_seed, count, gba);
}

uint16_t maxSIDforShiny(uint32_t pid, uint16_t id) {
  uint16_t pid_h = pid >> 16;
  uint16_t pid_l = pid;

  return ((pid_h^pid_l)^id) | 7;
}
