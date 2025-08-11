#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

static void set_conversion_state (mbstate_t *state, int bytes) {
#ifdef _UCRT
  state->_Wchar = bytes;
#else
  *state = bytes;
#endif
}

char Ascii[] = {'a'};
char NonAscii[] = {(char) 0x80};
char Multibyte[] = {(char) 0x81, (char) 0x81};
char InvalidMultibyte[] = {(char) 0x81, 0};

#ifdef _UCRT
/**
 * Valid UTF-8 character which can be represented by a single wchar_t.
 */
char UTF8[] = "語";

/**
 * Valid UTF-8 character which cannot be represented by a single wchar_t.
 */
char UTF8SurrogatePair[] = "🧡";
#endif

int main (void) {
  mbstate_t state = {0};
  wchar_t   wc = WEOF;

  /**
   * Test "C" locale
   */
  assert (setlocale (LC_ALL, "C") != NULL);
  assert (MB_CUR_MAX == 1);

  /**
   * All bytes in range [0,255] are valid and must convert to themselves
   */
  for (unsigned char c = 0;; ++c) {
    assert (mbrtowc (&wc, (char *) &c, MB_CUR_MAX, &state) == !!c);
    assert (wc == c);
    assert (mbsinit (&state));
    assert (errno == 0);

    if (c == 0xFF) {
      break;
    }
  }

  /**
   * Detect invalid conversion state
   *
   * NOTE: this is optional error condition specified in POSIX.
   * This check fails with CRT's mbrtowc.
   */
  set_conversion_state (&state, Ascii[0]);
  wc = WEOF;

  assert (mbrtowc (&wc, (char *) &Ascii, MB_CUR_MAX, &state) == (size_t) -1);
  assert (wc == WEOF);
  assert (!mbsinit (&state));
  assert (errno == EINVAL);

  // reset errno
  _set_errno (0);

  /**
   * Set conversion state to initial state
   */
  wc = WEOF;

  assert (mbrtowc (&wc, NULL, 0, &state) == 0);
  assert (wc == WEOF);
  assert (mbsinit (&state));
  assert (errno == 0);

  /**
   * Test SBCS code page
   * NOTE: Code page 28951 is ISO-8859-1
   */
  assert (setlocale (LC_ALL, "English_United States.28591") != NULL);
  assert (MB_CUR_MAX == 1);

  /**
   * All bytes must be valid
   *
   * We test ISO-8859-1 so that all bytes must convert to themselves
   */
  for (unsigned char c = 0;; ++c) {
    wc = WEOF;

    assert (mbrtowc (&wc, (char *) &c, MB_CUR_MAX, &state) == !!c);
    assert (wc == c);
    assert (mbsinit (&state));
    assert (errno == 0);

    if (c == 0xFF) {
      break;
    }
  }
#if __MSVCRT_VERSION__ >= 0x0200
  /**
   * Test DBCS code page
   */
  assert (setlocale (LC_ALL, "Japanese_Japan.ACP") != NULL);
  assert (MB_CUR_MAX == 2);

  /**
   * Make sure ASCII characters are handled correctly
   */
  for (char c = 0;; ++c) {
    wc = WEOF;

    assert (mbrtowc (&wc, &c, 1, &state) == !!c);
    assert (wc == c);
    assert (mbsinit (&state));
    assert (errno == 0);

    if (c == 0x7F) {
      break;
    }
  }

  /**
   * Try convert incomplete multibyte character
   */
  wc = WEOF;

  assert (mbrtowc (&wc, (char *) Multibyte, 1, &state) == (size_t) -2);
  /* This assertion fails with CRT's version */
  assert (wc == WEOF);
  assert (!mbsinit (&state));
  assert (errno == 0);

  /**
   * Complete multibyte character
   */
  wc = WEOF;

  assert (mbrtowc (&wc, (char *) Multibyte + 1, 1, &state) == 1);
  assert (wc != WEOF);
  assert (mbsinit (&state));
  assert (errno == 0);

  /**
   * Convert complete multibyte character
   */
  wc = WEOF;

  assert (mbrtowc (&wc, (char *) Multibyte, MB_CUR_MAX, &state) == 2);
  assert (wc != WEOF);
  assert (mbsinit (&state));
  assert (errno == 0);

  /**
   * Try convert invalid multibyte character
   */
  wc = WEOF;

  assert (mbrtowc (&wc, (char *) InvalidMultibyte, MB_CUR_MAX, &state) == (size_t) -1);
  /* This assertion fails with CRT's version */
  assert (wc == WEOF);
  assert (mbsinit (&state));
  assert (errno == EILSEQ);

  // reset errno
  _set_errno (0);
#endif
#ifdef _UCRT
  /**
   * Test UTF-8
   */
  if (setlocale (LC_ALL, "en_US.UTF-8")) {
    assert (MB_CUR_MAX == 4);

    /**
     * Make sure ASCII characters are handled correctly
     */
    for (char c = 0;; ++c) {
      assert (mbrtowc (&wc, &c, 1, &state) == !!c);
      assert (wc == c);
      assert (mbsinit (&state));
      assert (errno == 0);

      if (c == 0x7F) {
        break;
      }
    }

    /**
     * Convert multibyte character
     */
    wc = WEOF;

    assert (mbrtowc (&wc, (char *) UTF8, MB_CUR_MAX, &state) == 3);
    assert (wc == L'語');
    assert (mbsinit (&state));
    assert (errno == 0);

    /**
     * Get length of incomplete multibyte character
     */
    wc = WEOF;

    assert (mbrtowc (&wc, (char *) UTF8, 1, &state) == (size_t) -2);
    // assert (wc == WEOF);
    assert (!mbsinit (&state));
    assert (errno == 0);

    assert (mbrtowc (&wc, (char *) UTF8 + 1, 1, &state) == (size_t) -2);
    // assert (wc == WEOF);
    assert (!mbsinit (&state));
    assert (errno == 0);

    assert (mbrtowc (&wc, (char *) UTF8 + 2, 1, &state) == 1);
    assert (wc == L'語');
    assert (mbsinit (&state));
    assert (errno == 0);

    /**
     * Try convert multibyte character which cannot fit into single wchar_t
     */
    wc = WEOF;

    assert (mbrtowc (&wc, (char *) UTF8SurrogatePair, MB_CUR_MAX, &state) == 4);
    assert (wc == 0xFFFD);
    assert (mbsinit (&state));
    assert (errno == 0);

    /**
     * Try convert invalid multibyte character
     */
    UTF8[1] = '\0';
    wc = WEOF;

    assert (mbrtowc (&wc, (char *) UTF8, MB_CUR_MAX, &state) == (size_t) -1);
    // assert (wc == WEOF);
    assert (mbsinit (&state));
    assert (errno == EILSEQ);

    // reset errno
    _set_errno (0);
  }
#endif

  return 0;
}
