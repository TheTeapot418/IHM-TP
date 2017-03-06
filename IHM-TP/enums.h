//HANSER Florian
//BAUER Guillaume

#ifndef ENUMS_H
#define ENUMS_H

enum Side{
    UPSTREAM,
    DOWNSTREAM
} ;

enum State {
    OPEN,
    OPENING,
    CLOSING,
    CLOSED,
    ALERT,
    STOPPED
} ;

enum Level {
    LOW,
    MID,
    HIGH
};

#endif // ENUMS_H
