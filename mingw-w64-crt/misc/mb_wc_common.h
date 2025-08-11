/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <wchar.h>
#include <string.h>

unsigned int __cdecl ___lc_codepage_func(void);

/**
 * Internal interpretation of `mbstate_t`.
 */
typedef struct {
  char bytes[4];
} __mingw_conversion_state;

/**
 * Set `state` to initial conversion state.
 */
static __inline__ void conversion_state_init (mbstate_t *state) {
  memset (state, 0, sizeof (mbstate_t));
}

/**
 * Return `1` if `state`'s conversion state is valid, and `0` otherwise.
 */
static __inline__ int conversion_state_is_valid (mbstate_t *state) {
#ifdef _UCRT
  return state->_Wchar == 0 || (state->_Wchar > 0x7F && state->_Wchar < 0x100);
#else
  return *state == 0 || (*state > 0x7F && *state < 0x100);
#endif
}

/**
 * Copy conversion state from `state` to `s`.
 */
static __inline__ void conversion_state_get_bytes (__mingw_conversion_state *s, mbstate_t *state) {
#ifdef _UCRT
  memcpy (s->bytes, &state->_Wchar, 4);
#else
  memcpy (s->bytes, state, 4);
#endif
}

/**
 * Copy conversion state from `s` to `state`.
 */
static __inline__ void conversion_state_set_bytes (mbstate_t *state, __mingw_conversion_state *s) {
#ifdef _UCRT
  memcpy (&state->_Wchar, s->bytes, 4);
#else
  memcpy (state, s->bytes, 4);
#endif
}
