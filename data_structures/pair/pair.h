#ifndef PAIR_H
#define PAIR_H

#define DECLARE_PAIR(T) \
typedef struct {   \
    T fi;   \
    T se;   \
} Pair_##T;  \
\

DECLARE_PAIR(int)

#endif
