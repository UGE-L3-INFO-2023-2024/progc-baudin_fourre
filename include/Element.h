#ifndef __ELEMENT_H__
#define __ELEMENT_H__

typedef enum {
    NONE,
    PYRO = 1,
    DENDRO = 2,
    HYDRO = 4,
} Element;

// hue to element

// 1 << rand(0, 3);

// switch (element1 | element2) {
//     case PYRO | DENDRO:
//         break;
// }

#endif // __ELEMENT_H__
