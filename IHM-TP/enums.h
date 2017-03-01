//HANSER Florian
//BAUER Guillaume

#ifndef ENUMS_H
#define ENUMS_H

typedef enum {
    UPSTREAM,
    DOWNSTREAM
} Side;

typedef enum {
    OPEN,
    OPENING,
    CLOSING,
    CLOSED,
    ALERT
} State;

#endif // ENUMS_H
