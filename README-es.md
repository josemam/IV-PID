# IV⇆PID
Calculadora IV⇆PID para Pokémon de 3ª y 4ª Generación rápida y de código abierto (jo, en inglés queda más compacto)

### ¿Qué es esto?

El generador de números aleatorios, RNG por sus siglas en inglés, para los juegos de Pokémon de Tercera y Cuarta Generación es un [generador congruencial lineal] (https://en.wikipedia.org/wiki/Linear_congruential_generator) que devuelve números de 16 bits (los 16 bits más significativos de su estado). Esto supone que si se saben dos números consecutivos obtenidos con el RNG, se puede determinar (casi unívocamente) el único candidato a ser el siguiente número. Esto no suele ser útil en el juego, dado que es difícil conocer el número que ha devuelto el RNG en el juego, pero esto supone que los IVs de un cierto Pokémon están ligados a su PID, puesto que el PID se obtiene por concatenación de dos números consecutivos obtenidos con el RNG y los IVs se obtienen a continuación.

Esta relación IV-PID puede entenderse como un gran agujero en los Pokémon posibles. Por ejemplo, no se puede encontrar un Pokémon salvaje de naturaleza Osada y 31 IVs en todas las estadísticas en estos juegos. Algunos programas que comprueban la legalidad de Pokémon de Tercera y Cuarta Generación aprovechan esta relación y comprueban si los IVs y el PID de un Pokémon la cumple: si no lo hacen (y el Pokémon fue capturado y no eclosionado de un huevo ni recibido como regalo), el Pokémon ha sido modificado.

__Este programa puede usarse para listar todas las posibles combinaciones IV-PID a partir de un PID o de un conjunto de IVs__. Puede filtrarse la búsqueda por naturaleza, habilidad o el ser shiny (aspectos que dependen del PID) y por potencia y tipo de Poder Oculto (que dependen de los IVs). El programa aplica para ello la teoría desarrollada en [este artículo de Smogon] (http://www.smogon.com/ingame/rng/pid_iv_creation), y aprovecha la secuencia inversa del RNG para obtener el PID a partir de los IVs rápidamente.

Hay otro programa que hace algo parecido: SCV's PID/IV Generator. Ese ofrece menos opciones para filtrar los resultados, puede dar algunas combinaciones IV-PID no legales (porque asumió que podía darse un método que no puede darse) y es superado en tiempo de ejecución por este a la hora de encontrar PIDs de un Pokémon shiny con un mínimo de IVs.


### ¿Cómo funciona el programa?

El PID se obtiene concatenando los resultados de dos llamadas seguidas al RNG. La primera supone los 16 bits menos significativos, y la segunda los otros 16. Después los IVs se escogen a partir de otros dos números del RNG (los 15 bits menos significativos del primer número determinan los de PS, Ataque y Defensa, y los 15 bits menos significativos del segundo deciden el resto de IVs).

En los juegos de GameBoy Advance, el RNG podría _quemar_ un número aleatorio entre dos de estos números. La posición del número descartado determina el __método__. Por ejemplo, el método A-B-C-E representa que el cuarto número (D) ha sisdo saltado y ha sido el quinto (E) el que se ha usado para los IVs en Ataque Especial, Defensa Especial y Velocidad. _Es posible que A-B-C-E se use solo para Pokémon pescados y A-B-D-E para Pokémon salvajes encontrados caminando o haciendo Surf_, mientras que (y esto sí está comprobado) A-B-C-D se puede usar para cualquier Pokémon salvaje, incluyendo Pokémon especiales como los que no se obtienen moviéndose ni pescando. Hay gente que afirma que en muy raras ocasiones se usan otros métodos para Pokémon salvajes. El método es siempre A-B-C-D en los juegos de Nintendo DS, es decir, no se _queman_ números.

#### PID a IV
Se saben los 16 bits más significativos del estado del RNG tras la primera llamada al RNG: son los 16 bits menos significativos del PID. Después se exploran los 65 536 posibles estados del RNG a ver si el siguiente número coincide con el resto de bits del PID. Si así es, se muestra la distribución de IVs. Si se admiten los métodos de GBA, se muestra una distribución de IVs para cada método.

#### IV a PID
En este caso se saben 15 bits del estado del RNG después de que el último número se haya obtenido (los 16 bits más significativos excepto el más significativo de todos), ya que determinaron los últimos IVs. Se explora usando la secuencia inversa del RNG: se miran todos los 2·65 536 estados posibles a ver si coinciden con los IVs queridos para PS, Ataque y Defensa. De ser así, se obtiene el PID y se muestra.

El usuario puede pedir más condiciones: una naturaleza, una habilidad, un Poder Oculto o que sea shiny para un ID de entrenador y un ID secreto de entrenador. Se puede escoger entre pedir los IVs exactos o unos IVs que sean al menos una cierta cantidad para cada estadística (en este caso, todos los valores en Ataque Especial, Defensa Especial y Velocidad que sean iguales o mayores a los pedidos son explorados).


### ¿Cómo has encontrado la secuencia inversa del RNG?

El autor del artículo de Smogon afirma con orgullo [aquí] (http://www.smogon.com/forums/threads/ivs-to-pid-applet.45172/#post-1445205) que él y otro usuario de Smogon han _descubierto_ la secuencia inversa del RNG independientemente, y por ello quien aplique la secuencia inversa del RNG debería dar crédito a alguno de ellos _(eso suena como si Leibniz hubiese dicho que quien use el cálculo infinitesimal debe dar crédito a él o a Newton, lol)_. Pero cualquiera con un poco de conocimientos sobre generadores congruenciales lineales y aritmética modular puede encontrar la secuencia inversa del RNG con bastante facilidad.

En estos juegos, el RNG tiene un estado de 32 bits. Sea `S` el estado del RNG en un instante determinado. Entonces el siguiente será `S' = 1103515245 · S + 24691`. Las operaciones deben verse en aritmética modular módulo 2<sup>32</sup>, o lo que es lo mismo, si el resultado es al menos 2<sup>32</sup>, entonces se le resta 2<sup>32</sup> hasta que sea menor que 2<sup>32</sup>. Entonces `S' - 24691 = 1103515245 · S` y `(S' - 24691) · X = S · 1103515245 · X` para todo `X`. Si además `X` es tal que `1103515245 · X = 1` en aritmética modular módulo 2<sup>32</sup> (y por ello es un entero tal que `1103515245 · X = 1 - 2^32 · Y` para algún entero `Y`, o `1103515245 · X + 2^32 · Y = 1`), entonces `(S' - 24691) · X = S`. La [identidad de Bézout] (https://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity) garantiza que tal entero existe.

El [Algoritmo de Euclides extendido] (https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm) puede usarse para obtener `X` e `Y` si se usa 2<sup>32</sup> y 1103515245 como entrada. Sale que `X = -289805467, Y = 74460346`, así que `1103515245 · (-289805467) + 2^32 · 74460346 = 1`. -289805467 equivale a 2<sup>32</sup> - 289805467 = 4005161829.

Así que la secuencia inversa del RNG es `S = (S' - 24691) · 4005161829` (también se puede escribir que `S = S' · 4005161829 - 24691 · 4005161829`, pero no hace falta calcular `24691 · 4005161829`). Usando esto se puede buscar un PID para unos IVs explorando solo los estados que devuelven los IVs en Ataque Especial, Defensa Especial y Velocidad que se quieran (que, si se buscan unos IVs exactos, son _tan solo_ 2 por 65536), generar los números aleatorios hacia atrás y ver si estos números cumplen el resto de condiciones pedidas.


### ¿Qué sentido tiene hacer una herramienta para estos juegos tan viejos?
¿Qué sentido tiene jugar un juego de Pokémon más reciente, si no tienen Casa Treta?


### ¡Rubí Omega y Zafiro Alfa sí que tienen Casa Treta!
Ahí me has pillado.
