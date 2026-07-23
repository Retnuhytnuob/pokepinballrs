# Guia del selector de generacion y habitats

Esta guia documenta el sistema nuevo que permite escoger una generacion antes
de elegir tablero. La idea es que el mismo tablero Ruby/Sapphire pueda cargar
tablas de encuentros distintas segun la generacion seleccionada.

## Estado actual

- El selector aparece antes de `STATE_FIELD_SELECT`.
- La seleccion se guarda en RAM con `gSelectedGeneration`.
- No se guarda en el save, asi que no toca el layout del guardado.
- Gen 1 usa `gWildMonLocationsGen1`.
- Gen 2 usa `gWildMonLocationsGen2`.
- Gen 3 usa la tabla original `gWildMonLocations`.
- Gen 4 a Gen 10 y `RANDOM` aparecen en el selector, pero estan bloqueadas
  hasta que tengan contenido aprobado.
- Huevos y eventos especiales quedan para mas adelante.

## Archivos importantes

```text
include/constants/generations.h
src/generation_select.c
src/catch_hatch_picker.c
data/mon_locations.inc
data/rom_2.s
ld_script.txt
```

## Flujo del selector

El flujo principal es:

1. El menu principal entra en `STATE_GENERATION_SELECT`.
2. `GenerationSelectMain` dibuja la pantalla de seleccion.
3. El jugador mueve el cursor en una cuadricula de 2x5 y un boton `RANDOM`
   centrado debajo.
4. Al pulsar `A` o `START`, si la opcion no esta bloqueada, se actualiza
   `gSelectedGeneration`.
5. El juego pasa a `STATE_FIELD_SELECT`.
6. El selector de tablero Ruby/Sapphire funciona como siempre.

Las opciones bloqueadas estan en `sDisabledGenerationOptions`, dentro de:

```c
src/generation_select.c
```

Cuando una generacion se complete, se quita de esa lista para activarla.

## Como se elige la tabla de encuentros

Archivo:

```c
src/catch_hatch_picker.c
```

Funcion clave:

```c
static u16 GetWildMonForSelectedGeneration(s16 area, s16 threeArrows, s16 index)
```

La funcion devuelve:

- `gWildMonLocationsGen1` si se eligio Gen 1.
- `gWildMonLocationsGen2` si se eligio Gen 2.
- `gWildMonLocations` si se eligio Gen 3.

Esto mantiene el codigo de captura bastante estable, porque el resto del juego
sigue pidiendo "dame el Pokemon de esta zona", sin saber de donde sale la tabla.

## Modo random

La opcion `RANDOM` existe visualmente debajo de las generaciones, pero sigue
bloqueada hasta definir sus reglas. No genera tablas temporales todavia.

## Como editar habitats

Archivo:

```asm
data/mon_locations.inc
```

Cada generacion tiene bloques por zona:

```asm
gWildMonLocationsGen1::
    @ Forest | Ruby | Two arrows
    .2byte SPECIES_BULBASAUR
    ...

gWildMonLocationsGen2::
    @ Forest | Ruby | Two arrows
    .2byte SPECIES_CHIKORITA
    ...
```

Cada bloque debe tener exactamente 8 entradas. El orden importa:

- Las primeras entradas tienen mas peso practico porque se revisan antes en
  algunos flujos.
- Repetir una especie aumenta su probabilidad.
- `Two arrows` deberia tener especies mas comunes.
- `Three arrows` puede meter raros, starters o especiales.

## Criterio de reparto actual

Usamos primero las zonas del juego base:

- `Forest`: planta, bicho, pajaros de bosque, Pokemon pequenos.
- `Plains`: normales, electricos sencillos, terrestres y Pokemon de ruta.
- `Ocean`: agua salada, fosiles marinos y Pokemon de costa.
- `Lake`: agua dulce, anfibios y lineas de rio/lago.
- `Cave`: roca, tierra, veneno, psiquico raro y fantasmas.
- `Volcano`: fuego, humo, acero/calor y especies volcanicas.
- `Safari Zone`: especies raras, exoticas o de captura especial.
- `Wilderness`: desierto, campo abierto, electricos y especies sueltas.
- `Ruin`: legendarios, miticos, fosiles o especies antiguas.
- `Test Area`: pruebas rapidas y casos que aun no tienen flujo final.

Si una generacion se queda sin espacio, antes de crear zonas nuevas conviene
reordenar Ruby/Sapphire para que no repitan exactamente lo mismo. Si aun asi no
cabe, las zonas nuevas mas utiles serian:

- `Power Plant`: electricos y magneticos.
- `Ice Cave`: hielo y especies de cueva fria.
- `Haunted Ruins`: fantasmas, psiquicos y miticos.
- `Deep Sea`: agua profunda y legendarios marinos.

## Legendarios y miticos

De momento pueden estar en Ruin o en slots raros de `Three arrows`, pero el plan
bueno es tratarlos como eventos especiales, parecido a Latios/Latias.

La zona donde mirar es:

```c
src/catch_hatch_picker.c
```

Busca el bloque que mete `SPECIES_LATIOS` y `SPECIES_LATIAS`. Ese patron se
puede extender para:

- aves legendarias despues de ciertos viajes o capturas.
- Mewtwo/Mew despues de completar un porcentaje de Pokedex.
- perros legendarios como encuentros rotatorios.
- Lugia/Ho-Oh vinculados a Ocean/Volcano/Ruin.

Mejor no meter todos los legendarios como encuentros normales definitivos,
porque perderian gracia y saturarian habitats.

## Fondo editable del selector

Hay una imagen editable colocada junto al fondo de opciones:

```text
graphics/options/generation_select_background.png
```

Es un PNG de `240x160`, indexado a 16 colores. Ahora mismo sirve como fuente
editable/localizable para disenar el fondo del selector sin tener que buscarlo
por el proyecto.

El selector actual todavia dibuja el fondo por codigo en:

```c
src/generation_select.c
```

Cuando queramos que el PNG se use dentro de la ROM, el siguiente paso sera
convertirlo a `.4bpp`/tilemap y cargarlo igual que hace la pantalla de opciones
con:

```asm
graphics/options/background.png
graphics/options/background.bin
graphics/options/background.gbapal
```
