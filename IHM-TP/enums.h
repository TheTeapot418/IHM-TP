//HANSER Florian
//BAUER Guillaume

#ifndef ENUMS_H
#define ENUMS_H

//Types enums utilisés dans le programme

//Côté de l'écluse (amont/aval)
enum Side{
    UPSTREAM,
    DOWNSTREAM
};

//Etat d'un élément
enum State {
    OPEN,
    OPENING,
    CLOSING,
    CLOSED,
    ALERT,
    STOPPED
};

//Niveau de l'eau
enum Level {
    LOW,
    MID,
    HIGH
};

#endif // ENUMS_H
