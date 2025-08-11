#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

wchar_t AsciiText[] = L"Simple English text.";
wchar_t SBCSText[] = L"Sömè fÛnnÿ têxt";
wchar_t DBCSText[] = L"日本語テクスト";
wchar_t MixedText[] = L"日NI本HON語GO";
wchar_t BadText[] = {L'テ', L'く', 0xDC00, L'ト'};

#ifdef _UCRT
/**
 * Text which contains UTF-16 surrogate pairs
 */
wchar_t UTF8SurrogatePairs[] = L"🧡🩷";
#endif

int main (void) {
  const wchar_t *original_text = NULL;
  const wchar_t *text = NULL;
  size_t         text_length = 0;

  char      buffer[BUFSIZ];
  mbstate_t state = {0};

  /**
   * Test "C" locale
   */
  assert (setlocale (LC_ALL, "C") != NULL);
  assert (MB_CUR_MAX == 1);

  /* Test ASCII input */

  original_text = AsciiText;
  text_length = _countof (AsciiText) - 1;

  /**
   * Get length of converted AsciiText
   *
   * - return value must be `text_length`
   * - value of `test` must not change
   * - value of `errno` must not change
   * - `state` must be in initial state
   */
  text = original_text;

  assert (wcsrtombs (NULL, &text, 0, &state) == text_length);
  assert (text == original_text);
  assert (mbsinit (&state));
  assert (errno == 0);

  /**
   * Convert AsciiText
   *
   * - return value must be `text_length`
   * - value of `test` must be NULL
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must be terminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == text_length);
  assert (text == NULL);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[text_length] == '\0');

  /**
   * Convert 10 wide characters in AsciiText
   *
   * - return value must be 10
   * - value of `test` must be `original_text + 10`
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must not be terminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, 10, &state) == 10);
  assert (text == original_text + 10);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[10] == EOF);

  /* Test SBCS input */

  original_text = SBCSText;
  text_length = _countof (SBCSText) - 1;

  /**
   * Get length of converted SBCSText
   *
   * - return value must be 15
   * - value of `text` must not change
   * - value of `errno` must not change
   * - `state` must be in initial state
   */
  text = original_text;

  assert (wcsrtombs (NULL, &text, 0, &state) == text_length);
  assert (text == original_text);
  assert (mbsinit (&state));
  assert (errno == 0);

  /**
   * Convert SBCSText
   *
   * - return value must be 15
   * - value of `text` must be NULL
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must be terminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == text_length);
  assert (text == NULL);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[text_length] == '\0');

  /**
   * Convert 10 wide characters in SBCSText
   *
   * - return value must be 10
   * - value of `text` must be `original_text + 10`
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must not be terminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, 10, &state) == 10);
  assert (text == original_text + 10);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[10] == EOF);

  /* Test DBCS input */

  original_text = DBCSText;
  text_length = _countof (DBCSText) - 1;

  /**
   * Try get length of converted DBCSText
   *
   * - return value must be (size_t)-1
   * - value of `text` must not change
   * - value of `errno` must be EILSEQ
   * - `state` must be in initial state
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == (size_t) -1);
  assert (text == original_text);
  assert (mbsinit (&state));
  assert (errno == EILSEQ);
  assert (buffer[0] == EOF);

  // reset errno
  _set_errno (0);

  /**
   * Try convert DBCSText
   *
   * - return value must be (size_t)-1
   * - value of `text` must not change
   * - value of `errno` must be EILSEQ
   * - `state` must be in initial state
   */
  text = original_text;

  assert (wcsrtombs (NULL, &text, 0, &state) == (size_t) -1);
  assert (text == original_text);
  assert (mbsinit (&state));
  assert (errno == EILSEQ);

  // reset errno
  _set_errno (0);

  /**
   * Test SBCS code page
   */
  assert (setlocale (LC_ALL, "English_United States.ACP") != NULL);
  assert (MB_CUR_MAX == 1);

  /* Test ASCII input */

  original_text = AsciiText;
  text_length = _countof (AsciiText) - 1;

  /**
   * Get length of converted AsciiText
   *
   * - return value must be `text_length`
   * - value of `test` must not change
   * - value of `errno` must not change
   * - `state` must be in initial state
   */
  text = original_text;

  assert (wcsrtombs (NULL, &text, 0, &state) == text_length);
  assert (text == original_text);
  assert (mbsinit (&state));
  assert (errno == 0);

  /**
   * Convert AsciiText
   *
   * - return value must be `text_length`
   * - value of `test` must be NULL
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must be terminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == text_length);
  assert (text == NULL);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[text_length] == '\0');

  /**
   * Convert 10 wide characters in AsciiText
   *
   * - return value must be 10
   * - value of `test` must be `original_text + 10`
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must not be terminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, 10, &state) == 10);
  assert (text == original_text + 10);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[10] == EOF);

  /* Test SBCS input */

  original_text = SBCSText;
  text_length = _countof (SBCSText) - 1;

  /**
   * Get length of converted SBCSText
   *
   * - return value must be 15
   * - value of `text` must not change
   * - value of `errno` must not change
   * - `state` must be in initial state
   */
  text = original_text;

  assert (wcsrtombs (NULL, &text, 0, &state) == text_length);
  assert (text == original_text);
  assert (mbsinit (&state));
  assert (errno == 0);

  /**
   * Convert SBCSText
   *
   * - return value must be 15
   * - value of `text` must be NULL
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must be terminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == text_length);
  assert (text == NULL);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[text_length] == '\0');

  /**
   * Convert 10 wide characters in SBCSText
   *
   * - return value must be 10
   * - value of `text` must be `original_text + 10`
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must not be terminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, 10, &state) == 10);
  assert (text == original_text + 10);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[10] == EOF);

  /* Test DBCS input */

  original_text = DBCSText;
  text_length = _countof (DBCSText) - 1;

  /**
   * Try get length of converted DBCSText
   *
   * - return value must be (size_t)-1
   * - value of `text` must not change
   * - value of `errno` must be EILSEQ
   * - `state` must be in initial state
   */
  text = original_text;

  assert (wcsrtombs (NULL, &text, 0, &state) == (size_t) -1);
  assert (text == original_text);
  assert (mbsinit (&state));
  assert (errno == EILSEQ);

  // reset errno
  _set_errno (0);

  /**
   * Try convert DBCSText
   *
   * - return value must be (size_t)-1
   * - value of `text` must not change
   * - value of `errno` must be EILSEQ
   * - `state` must be in initial state
   * - nothing must be written to `buffer`
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == (size_t) -1);
  assert (text == original_text);
  assert (mbsinit (&state));
  assert (errno == EILSEQ);
  /* This assertion fails with CRT's version */
  assert (buffer[0] == EOF);

  // reset errno
  _set_errno (0);
#if __MSVCRT_VERSION__ >= 0x0200
  /**
   * Test DBCS code page
   */
  assert (setlocale (LC_ALL, "Japanese_Japan.ACP") != NULL);
  assert (MB_CUR_MAX == 2);

  /* Test ASCII input */

  original_text = AsciiText;
  text_length = _countof (AsciiText) - 1;

  /**
   * Get length of converted AsciiText
   *
   * - return value must be `text_length`
   * - value of `test` must not change
   * - value of `errno` must not change
   * - `state` must be in initial state
   */
  text = original_text;

  assert (wcsrtombs (NULL, &text, 0, &state) == text_length);
  assert (text == original_text);
  assert (mbsinit (&state));
  assert (errno == 0);

  /**
   * Convert AsciiText
   *
   * - return value must be `text_length`
   * - value of `test` must be NULL
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must be terminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == text_length);
  assert (text == NULL);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[text_length] == '\0');

  /**
   * Convert 10 wide characters in AsciiText
   *
   * - return value must be 10
   * - value of `test` must be `original_text + 10`
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must not be terminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, 10, &state) == 10);
  assert (text == original_text + 10);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[10] == EOF);

  /* Test DBCS input */

  original_text = DBCSText;
  text_length = _countof (DBCSText) - 1;

  /**
   * Get length of converted DBCSText
   *
   * - return value must be 14
   * - value of `text` must not change
   * - value of `errno` must not change
   * - `state` must be in initial state
   */
  text = original_text;

  assert (wcsrtombs (NULL, &text, 0, &state) == 14);
  assert (text == original_text);
  assert (mbsinit (&state));
  assert (errno == 0);

  /**
   * Convert DBCSText
   *
   * - return value must be 14
   * - value of `text` must be NULL
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must be terminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == 14);
  assert (text == NULL);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[14] == '\0');

  /**
   * Convert 5 wide characters in DBCSText
   *
   * - return value must be 10
   * - value of `text` must be `original_text + 5`
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must not be terminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, 11, &state) == 10);
  assert (text == original_text + 5);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[10] == EOF);

  /* Test mixed input */

  original_text = MixedText;
  text_length = _countof (MixedText) - 1;

  /**
   * Get length of converted MixedText
   *
   * - return value must be 13
   * - value of `test` must not change
   * - value of `errno` must not change
   * - `state` must be in initial state
   */
  text = original_text;

  assert (wcsrtombs (NULL, &text, 0, &state) == 13);
  assert (text == original_text);
  assert (mbsinit (&state));
  assert (errno == 0);

  /**
   * Convert MixedText
   *
   * - return value must be 13
   * - value of `test` must be NULL
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must be teminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == 13);
  assert (text == NULL);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[13] == '\0');

  /**
   * Convert 7 wide characters in MixedText
   *
   * - return value must be 9
   * - value of `test` must be `original_text + 7`
   * - value of `errno` must not change
   * - `state` must be in initial state
   * - converted string must not be teminated with '\0'
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, 10, &state) == 9);
  assert (text == original_text + 7);
  assert (mbsinit (&state));
  assert (errno == 0);
  assert (buffer[9] == EOF);

  /* Test bad input */

  original_text = BadText;
  text_length = _countof (BadText) - 1;

  /**
   * Try get length of converted BadText
   *
   * - return value must be (size_t)-1
   * - value of `text` must not change
   * - value of `errno` must be EILSEQ
   * - `state` must be in initial state
   */
  text = original_text;

  assert (wcsrtombs (NULL, &text, 0, &state) == (size_t) -1);
  assert (text == original_text);
  assert (mbsinit (&state));
  assert (errno == EILSEQ);

  /**
   * Try convert BadText
   *
   * - return value must be (size_t)-1
   * - value of `text` must be `original_text + 2`
   * - value of `errno` must be EILSEQ
   * - `state` must be in initial state
   */
  memset (buffer, EOF, BUFSIZ);
  text = original_text;

  assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == (size_t) -1);
  assert (text == original_text + 2);
  assert (mbsinit (&state));
  assert (errno == EILSEQ);
  /* This assertion fails with CRT's version */
  assert (buffer[3] != EOF && buffer[4] == EOF);

  // reset errno
  _set_errno (0);
#endif
#ifdef _UCRT
  if (setlocale (LC_ALL, "en_US.UTF-8") != NULL) {
    assert (MB_CUR_MAX == 4);

    /**
     * Test ASCII input
     */
    original_text = AsciiText;
    text_length = _countof (AsciiText) - 1;

    /**
     * Get length of converted AsciiText
     *
     * - return value must be `text_length`
     * - value of `test` must not change
     * - value of `errno` must not change
     * - `state` must be in initial state
     */
    text = AsciiText;

    assert (wcsrtombs (NULL, &text, 0, &state) == text_length);
    assert (text == original_text);
    assert (mbsinit (&state));
    assert (errno == 0);

    /**
     * Convert AsciiText
     *
     * - return value must be `text_length`
     * - value of `test` must be NULL
     * - value of `errno` must not change
     * - `state` must be in initial state
     * - converted string must be terminated with '\0'
     */
    memset (buffer, EOF, BUFSIZ);
    text = AsciiText;

    assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == text_length);
    assert (text == NULL);
    assert (mbsinit (&state));
    assert (errno == 0);
    assert (buffer[text_length] == '\0');

    /**
     * Convert 10 wide characters in AsciiText
     *
     * - return value must be 10
     * - value of `test` must be `original_text + 10`
     * - value of `errno` must not change
     * - `state` must be in initial state
     * - converted string must not be terminated with '\0'
     */
    memset (buffer, EOF, BUFSIZ);
    text = AsciiText;

    assert (wcsrtombs (buffer, &text, 10, &state) == 10);
    assert (text == original_text + 10);
    assert (mbsinit (&state));
    assert (errno == 0);
    assert (buffer[10] == EOF);

    /**
     * Test SBCS input
     */
    original_text = SBCSText;
    text_length = _countof (SBCSText) - 1;

    /**
     * Get length of converted SBCSText
     *
     * - return value must be `text_length + 5`
     * - value of `text` must not change
     * - value of `errno` must not change
     * - `state` must be in initial state
     */
    text = SBCSText;

    assert (wcsrtombs (NULL, &text, 0, &state) == text_length + 5);
    assert (text == original_text);
    assert (mbsinit (&state));
    assert (errno == 0);

    /**
     * Convert SBCSText
     *
     * - return value must be `text_length + 5`
     * - value of `text` must be NULL
     * - value of `errno` must not change
     * - `state` must be in initial state
     * - converted string must be terminated with '\0'
     */
    memset (buffer, EOF, BUFSIZ);
    text = SBCSText;

    assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == text_length + 5);
    assert (text == NULL);
    assert (mbsinit (&state));
    assert (errno == 0);
    assert (buffer[text_length + 5] == '\0');

    /**
     * Convert 9 wide characters in SBCSText
     *
     * - return value must be 14
     * - value of `text` must be `original_text + 9`
     * - value of `errno` must not change
     * - `state` must be in initial state
     * - converted string must not be terminated with '\0'
     */
    memset (buffer, EOF, BUFSIZ);
    text = SBCSText;

    assert (wcsrtombs (buffer, &text, 13, &state) == 12);
    assert (text == original_text + 9);
    assert (mbsinit (&state));
    assert (errno == 0);
    assert (buffer[12] == EOF);

    /**
     * Test DBCS input
     */
    original_text = DBCSText;
    text_length = _countof (DBCSText) - 1;

    /**
     * Get length of converted DBCSText
     *
     * - return value must be 21
     * - value of `text` must not change
     * - value of `errno` must not change
     * - `state` must be in initial state
     */
    text = original_text;

    assert (wcsrtombs (NULL, &text, 0, &state) == 21);
    assert (text == original_text);
    assert (mbsinit (&state));
    assert (errno == 0);

    /**
     * Convert DBCSText
     *
     * - return value must be 21
     * - value of `text` must be NULL
     * - value of `errno` must not change
     * - `state` must be in initial state
     * - converted string must be terminated with '\0'
     */
    memset (buffer, EOF, BUFSIZ);
    text = original_text;

    assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == 21);
    assert (text == NULL);
    assert (mbsinit (&state));
    assert (errno == 0);
    assert (buffer[21] == '\0');

    /**
     * Convert 5 wide characters in DBCSText
     *
     * - return value must be 15
     * - value of `text` must be `original_text + 5`
     * - value of `errno` must not change
     * - `state` must be in initial state
     * - converted string must not be terminated with '\0'
     */
    memset (buffer, EOF, BUFSIZ);
    text = original_text;

    assert (wcsrtombs (buffer, &text, 17, &state) == 15);
    assert (text == original_text + 5);
    assert (mbsinit (&state));
    assert (errno == 0);
    assert (buffer[15] == EOF && buffer[16] == EOF);

    /**
     * Test mixed input
     */
    original_text = MixedText;
    text_length = _countof (MixedText) - 1;

    /**
     * Get length of converted MixedText
     *
     * - return value must be 16
     * - value of `test` must not change
     * - value of `errno` must not change
     * - `state` must be in initial state
     */
    text = original_text;

    assert (wcsrtombs (NULL, &text, 0, &state) == 16);
    assert (text == original_text);
    assert (mbsinit (&state));
    assert (errno == 0);

    /**
     * Convert MixedText
     *
     * - return value must be 16
     * - value of `test` must be NULL
     * - value of `errno` must not change
     * - `state` must be in initial state
     * - converted string must be teminated with '\0'
     */
    memset (buffer, EOF, BUFSIZ);
    text = original_text;

    assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == 16);
    assert (text == NULL);
    assert (mbsinit (&state));
    assert (errno == 0);
    assert (buffer[16] == '\0');

    /**
     * Convert 7 wide characters in MixedText
     *
     * - return value must be 11
     * - value of `test` must be `original_text + 7`
     * - value of `errno` must not change
     * - `state` must be in initial state
     * - converted string must not be teminated with '\0'
     */
    memset (buffer, EOF, BUFSIZ);
    text = original_text;

    assert (wcsrtombs (buffer, &text, 13, &state) == 11);
    assert (text == original_text + 7);
    assert (mbsinit (&state));
    assert (errno == 0);
    assert (buffer[11] == EOF && buffer[12] == EOF);

    /**
     * Test bad input
     */
    original_text = BadText;
    text_length = _countof (BadText) - 1;

    /**
     * Try get length of converted BadText
     *
     * - return value must be (size_t)-1
     * - value of `text` must not change
     * - value of `errno` must be EILSEQ
     * - `state` must be in initial state
     */
    text = original_text;

    assert (wcsrtombs (NULL, &text, 0, &state) == (size_t) -1);
    assert (text == original_text);
    assert (mbsinit (&state));
    assert (errno == EILSEQ);

    /**
     * Try convert BadText
     *
     * - return value must be (size_t)-1
     * - value of `text` must be `original_text + 2`
     * - value of `errno` must be EILSEQ
     * - `state` must be in initial state
     */
    memset (buffer, EOF, BUFSIZ);
    text = original_text;

    assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == (size_t) -1);
    assert (text == original_text + 2);
    assert (mbsinit (&state));
    assert (errno == EILSEQ);
    assert (buffer[5] != EOF && buffer[6] == EOF);

    // reset errno
    _set_errno (0);

    /**
     * Test input which contains surrogate pairs
     */
    original_text = UTF8SurrogatePairs;

    /**
     * Get length of converted UTF8SurrogatePairs
     *
     * - return value must be 8
     * - value of `test` must not change
     * - value of `errno` must not change
     * - `state` must be in initial state
     */
    text = original_text;

    assert (wcsrtombs (NULL, &text, 0, &state) == 8);
    assert (text == original_text);
    assert (mbsinit (&state));
    assert (errno == 0);

    /**
     * Convert UTF8SurrogatePairs
     *
     * - return value must be 8
     * - value of `test` must be `NULL`
     * - value of `errno` must not change
     * - `state` must be in initial state
     * - converted string must be teminated with '\0'
     */
    memset (buffer, EOF, BUFSIZ);
    text = original_text;

    assert (wcsrtombs (buffer, &text, BUFSIZ, &state) == 8);
    assert (text == NULL);
    assert (mbsinit (&state));
    assert (errno == 0);
    assert (buffer[8] == L'\0');

    /**
     * Convert single multibyte character in UTF8SurrogatePairs
     *
     * - return value must be 4
     * - value of `test` must be `original_text + 2`
     * - value of `errno` must not change
     * - `state` must be in initial state
     * - converted string must not be teminated with '\0'
     */
    memset (buffer, EOF, BUFSIZ);
    text = original_text;

    assert (wcsrtombs (buffer, &text, 7, &state) == 4);
    assert (text == original_text + 2);
    assert (mbsinit (&state));
    assert (errno == 0);
    assert (buffer[4] == EOF);
  }
#endif

  return 0;
}
