# Lab 1.4

El proyecto del primer parcial de lab de sistemas embebidos. A continuación, se
presentan los requerimientos del proyecto.

# Requerimientos

## Funcionalidad

Este es un sistema de semaforos con 1 cruce peatonal. El sistema de semaforos
es una maquina de estados y el cruce peatonal es una secuencia de interrupción.

### Semaforo

La maquina de estado se encuentra en el documento de las especificaiones.
No hay inputs.
Los output son las luces led de del semaforo.

### Cruce peatonal

- Esta entre el semaforo 2 y semaforo 3
- El peaton **no** puede alterar la secuencia actua
- Cuando llega la luz verde **en el sentido vehicular que el peaton quiere
  cruzar**, y el peaton había **oprimido** el boton, se le da el **mismo tiempo
  que sería para la calle en ese sentido** para cruzar.
- Si esta en verde y se presiona el cruce peatonal, no se debe otorgar el paso,
  si no hasta la siguiente vez.
- Seria un boton para cada uno de los semaforos

Los inputs son los botones en los cruces. Los outputs son los displays de 7
segmentos.

Los estados que estan involucrados en este proceso son:

- E1
- E2
- E3

## Presentacion

Los detalles de la presentacion son los siguientes:

- [ ] Hacer presentacion
  - [ ] Front cover
  - [ ] Introduction
  - [ ] Development and solution
    - [ ] Control algorithm or strategy
  - [ ] hardware
    - [ ] lista de materiales
  - [ ] conclusiones
- [ ] demostracion

# Notas de implementacion

No creo que se necesite manejar las clases de maquinas de estado, a menos que
manejemos el cruce peatonal como un estado adicional.

```cpp
volatile bool peaton;
// Estado 1
Semaforo1(1,0,0,0);
Semaforo2(1,0,0,0);
Semaforo3(1,0,0,0);

// Estado 2
if (peaton){
    //.. secuencia de peaton
}

Semaforo1(1,0,0,0);
Semaforo2(1,0,0,0);
Semaforo3(1,0,0,0);


```

Sin embargo, si queremos ser mas manejables con los estados:

```cpp
volatile bool peaton;

if (peaton){
    context->transitionTo(new EstadoPeaton());
} else {
    context->transitionTo(new Estado1());

}
```

# Seven display segment

Usar esta libreria
https://github.com/dgduncan/SevenSegment
=======
# 7 Display

Taken from [official documentation](https://github.com/DeanIsMe/SevSeg)

- Cathode (negative pins)
