/**
  * @file esp.c
  * @brief Spanish strings for iv-pid
  */

char Y_CHAR = 's';
char N_CHAR = 'n';
const char
*CHAINED_SHINY_METHOD = "Shiny de PokéRadar",
*NATURE[25] = {
  "Fuerte", "Huraña", "Audaz", "Firme", "Pícara", "Osada", "Dócil",
  "Plácida", "Agitada", "Floja", "Miedosa", "Activa", "Seria",
  "Alegre", "Ingenua", "Modesta", "Afable", "Mansa", "Tímida",
  "Alocada", "Serena", "Amable", "Grosera", "Cauta", "Rara"
},
*HP_TYPE[16] = {
  "Lucha", "Volador", "Veneno", "Tierra", "Roca", "Bicho", "Fantasma", "Acero",
  "Fuego", "Agua", "Planta", "Eléctrico", "Psíquico", "Hielo", "Dragón", "Siniestro"
},
*MODE_MSG = "0: Salir\n"
            "1: IV --> PID\n"
            "2: IV mínimos + HP --> PID\n"
            "3: IV mínimos + ID + SID --> PID shiny\n"
            "4: IV mínimos + HP + ID + SID --> PID shiny\n"
            "5: IV + ID + SID --> PID shiny de PokéRadar\n"
            "6: PID --> IV\n"
            "7: PID shiny + ID --> SID\n"
            "Modo",
*PID_ASK_MSG = "PID (decimal)",
*ID_ASK_MSG = "ID",
*SID_ASK_MSG = "SID",
*IV_ASK_MSG = "IVs en PS, Ataque, Defensa, Ataque Especial, Defensa Especial y Velocidad",
*NATURE_ASK_MSG = "ID de la naturaleza (-1 si no importa, 90 para ver la lista)",
*HP_TYPE_ASK_MSG = "ID del tipo de HP (-1 si no importa, 90 para ver la lista)",
*HP_POWER_ASK_MSG = "Potencia mínima de HP (-1 si no importa)",
*ABILITY_ASK_MSG = "¿Alguna habilidad en particular? (n = no, 1 = primera, 2 = segunda)",
*GBA_ASK_MSG1 = "¿Incluir métodos de GBA?",
*GBA_ASK_MSG2 = "¿También los más raros? (El autor desconoce si son posibles)",
*ABILITY_TXT = "Habilidad",
*AB_F_S[2] = {"Primera", "Segunda"},
*GEN_VAL_TXT = "Valor de género",
*HP_TXT = "Poder Oculto",
*NO_PID_MSG = "No se encontraron PID válidos",
*IMPOSSIBLE_PID_MSG = "Este PID es imposible debido a la naturaleza del RNG",
*END_OF_RESULTS_MSG = "Fin de los resultados",
*PAUSE_MSG = "Pulsa una tecla para seguir o Esc para salir...",
*LICENSE = "Licencia",
*TEXT_BEFORE_GH_LINK = "Puedes ver el código, sugerir\ncambios y reportar errores en";
