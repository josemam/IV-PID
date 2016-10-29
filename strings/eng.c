/**
  * @file eng.c
  * @brief English strings for iv-pid
  */

char Y_CHAR = 'y';
char N_CHAR = 'n';
const char
*CHAINED_SHINY_METHOD = "Chained shiny",
*NATURE[25] = {
  "Hardy", "Lonely", "Brave", "Adamant", "Naughty", "Bold",
  "Docile", "Relaxed", "Impish", "Lax", "Timid", "Hasty",
  "Serious", "Jolly", "Naive", "Modest", "Mild", "Quiet",
  "Bashful", "Rash", "Calm", "Gentle", "Sassy", "Careful", "Quirky"
},
*HP_TYPE[16] = {
  "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel",
  "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon", "Dark"
},
*MODE_MSG = "0: Exit\n"
            "1: IV --> PID\n"
            "2: Minimum IV + HP --> PID\n"
            "3: Minimum IV + ID + SID --> shiny PID\n"
            "4: Minimum IV + HP + ID + SID --> shiny PID\n"
            "5: IV + ID + SID --> chained shiny PID\n"
            "6: PID --> IV\n"
            "7: Shiny PID + ID --> SID\n"
            "Mode",
*PID_ASK_MSG = "PID (decimal)",
*ID_ASK_MSG = "ID",
*SID_ASK_MSG = "SID",
*IV_ASK_MSG = "HP, Attack, Defense, Special Attack, Special Defense & Speed IVs",
*NATURE_ASK_MSG = "Nature ID (-1 if any, 90 to show list)",
*HP_TYPE_ASK_MSG = "HP Type ID (-1 if any, 90 to show list)",
*HP_POWER_ASK_MSG = "Minimum HP Power (-1 if any)",
*ABILITY_ASK_MSG = "Ability? (n = any, 1 = first, 2 = second)",
*GBA_ASK_MSG1 = "Test GBA methods?",
*GBA_ASK_MSG2 = "Even rare ones? (The author does not know whether they are possible)",
*ABILITY_TXT = "Ability",
*AB_F_S[2] = {"First", "Second"},
*GEN_VAL_TXT = "Gender value",
*HP_TXT = "Hidden Power",
*NO_PID_MSG = "No valid PID found",
*IMPOSSIBLE_PID_MSG = "That PID is impossible due to RNG mechanism",
*END_OF_RESULTS_MSG = "End of results",
*PAUSE_MSG = "Press any key to continue or Esc to exit...",
*LICENSE = "License",
*TEXT_BEFORE_GH_LINK = "You can read the code, make\nsuggestions and report bugs at";
