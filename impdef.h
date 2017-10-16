#define SWAP16(X) 		\
( 						        \
((X & 0x00ffU) << 8) | 	        \
((X & 0xff00U) >> 8)            \
)

#define SWAP32(X)           \
(                                 \
((X & 0x000000ffUL) << 24) |      \
((X & 0x0000ff00UL) << 8)  |      \
((X & 0x00ff0000UL) >> 8)  |      \
((X & 0xff000000UL) >> 24)        \
)

#define SWAP64(X)                     \
(                                           \
((X & 0x00000000000000ffULL) << 56) |       \
((X & 0x000000000000ff00ULL) << 40) |       \
((X & 0x0000000000ff0000ULL) << 24) |       \
((X & 0x00000000ff000000ULL) << 8)  |       \
((X & 0x000000ff00000000ULL) >> 8)  |       \
((X & 0x0000ff0000000000ULL) >> 24) |       \
((X & 0x00ff000000000000ULL) >> 40) |       \
((X & 0xff00000000000000ULL) >> 56)         \
)
