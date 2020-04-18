#pragma once

template <uint8_t PIN>
class FastPin;
template <uint8_t PIN>
class FastPinBB : public FastPin<PIN> {};

// Utility templates for tracking down information about pins and ports
template <uint8_t port>
struct __FL_PORT_INFO {
    static bool hasPort() { return 0; }
    static const char *portName() { return "--"; }
    static const void *portAddr() { return NULL; }
};

// Give us our instantiations for defined ports - we're going to abuse this later for
// auto discovery of pin/port mappings for new variants.  Use _FL_DEFINE_PORT for ports that
// are numeric in nature, e.g. GPIO0, GPIO1.  Use _FL_DEFINE_PORT3 for ports that are letters.
// The first parameter will be the letter, the second parameter will be an integer/counter of smoe kind
// (this is because attempts to turn macro parameters into character constants break in some compilers)
#define _FL_DEFINE_PORT(L, BASE)                                             \
    template <>                                                              \
    struct __FL_PORT_INFO<L> {                                               \
        static bool hasPort() { return 1; }                                  \
        static const char *portName() { return #L; }                         \
        typedef BASE __t_baseType;                                           \
        static const void *portAddr() { return (void *)&__t_baseType::r(); } \
    };

#define _FL_DEFINE_PORT3(L, LC, BASE)                                        \
    template <>                                                              \
    struct __FL_PORT_INFO<LC> {                                              \
        static bool hasPort() { return 1; }                                  \
        static const char *portName() { return #L; }                         \
        typedef BASE __t_baseType;                                           \
        static const void *portAddr() { return (void *)&__t_baseType::r(); } \
    };

typedef volatile uint32_t &reg32_t;
typedef volatile uint32_t *ptr_reg32_t;