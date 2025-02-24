#ifndef BUFFERS_H
#define BUFFERS_H

#include <Vertex.hpp>

enum class Buffers{
    Color, 
    Depth
};

inline Buffers operator|(Buffers a, Buffers b){
    return Buffers((int) a | (int) b);
}
inline Buffers operator&(Buffers a, Buffers b){
    return Buffers((int) a & (int) b);
}

enum class Primitive{
    Line,
    Triangle
};

struct pos_buf_id{
    int pos_id = 0;
};

struct ind_buf_id{
    int ind_id = 0;
};

struct col_buf_id{
    int col_id = 0;
};

#endif