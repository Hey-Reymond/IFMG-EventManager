#ifndef CONFIG_ARMAZENAMENTO_H
#define CONFIG_ARMAZENAMENTO_H

#include "model/sistema.h"

void definirModoDeArmazenamento(Sistema *sistema, TipoArmazenamento modo);
TipoArmazenamento obterModoDeArmazenamento(Sistema *sistema);

#endif