/**
  * @file strings.h
  * @brief Strings for iv-pid
  */

#ifndef __STRINGS_H__
#define __STRINGS_H__

const char* BAR = "\n=============================\n";
extern const char* CHAINED_SHINY_METHOD;
const char* METHOD_[] = {CHAINED_SHINY_METHOD, "A-B-C-D", "A-B-D-E", "A-B-C-E", "A-B-D-F", "A-B-E-F"};
const char** METHOD = METHOD_ + 1;

/* Language-dependant strings */
extern const char Y_CHAR, N_CHAR;
extern const char
*NATURE[25],
*HP_TYPE[16],
*MODE_MSG,
*PID_ASK_MSG,
*ID_ASK_MSG,
*SID_ASK_MSG,
*IV_ASK_MSG,
*NATURE_ASK_MSG,
*HP_TYPE_ASK_MSG,
*HP_POWER_ASK_MSG,
*ABILITY_ASK_MSG,
*GBA_ASK_MSG1,
*GBA_ASK_MSG2,
*ABILITY_TXT,
*AB_F_S[2],
*GEN_VAL_TXT,
*HP_TXT,
*NO_PID_MSG,
*IMPOSSIBLE_PID_MSG,
*END_OF_RESULTS_MSG,
*PAUSE_MSG;

#endif
