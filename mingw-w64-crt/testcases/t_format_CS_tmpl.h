#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>

#define ARRAY_COUNT(a) (sizeof(a)/sizeof(a[0]))

#define PRINT_NARROW_BUF(buf) \
	for (i = 0; i < ARRAY_COUNT(buf); i++) { \
		if ((buf)[i] == '\n' || ((buf)[i] >= 0x20 && (buf)[i] <= 0x7E && (buf)[i] != '\\')) \
			fputc((buf)[i], stderr); \
		else \
			fprintf(stderr, "\\x%02X", (unsigned int)(unsigned char)(buf)[i]); \
	}

#define PRINT_WIDE_BUF(buf) \
	for (i = 0; i < ARRAY_COUNT(buf); i++) { \
		if ((buf)[i] == L'\n' || ((buf)[i] >= 0x20 && (buf)[i] <= 0x7E && (buf)[i] != L'\\')) \
			fputc((char)(buf)[i], stderr); \
		else \
			fprintf(stderr, "\\x%04X", (unsigned int)(wint_t)(buf)[i]); \
	} \

int main() {
	char abuf[37];
	char abuf2[13];
	wchar_t wbuf[33];
	wchar_t wbuf2[13];
	wchar_t wbuf3[5];
	int ret;
	size_t i;

	memset(abuf, 0xff, sizeof(abuf));
	ret = snprintf(abuf, ARRAY_COUNT(abuf), "%c %C %hc %hC %lc %lC %s %S %hs %hS %ls %lS", 'c', L'C', 'c', 'c', L'C', L'C', "str", L"STR", "str", "str", L"STR", L"STR");
	if (ret != ARRAY_COUNT(abuf)-2 || memcmp(abuf, "c C c c C C str STR str str STR STR\x00\xFF", ARRAY_COUNT(abuf)) != 0) {
		fprintf(stderr, "ret: expected=%d got=%d\n", ARRAY_COUNT(abuf)-2, ret);
		fprintf(stderr, "abuf:\n");
		PRINT_NARROW_BUF(abuf);
		fprintf(stderr, "\n");
		return 1;
	}
	printf("OK abuf\n");

	memset(wbuf, 0xff, sizeof(wbuf));
	ret = swprintf(wbuf, ARRAY_COUNT(wbuf), L"%c %C %hc %hC %lc %lC %s %S %hs %hS %ls", L'C', 'c', 'c', 'c', L'C', L'C', L"STR", "str", "str", "str", L"STR");
	if (ret != ARRAY_COUNT(wbuf)-2 || wmemcmp(wbuf, L"C c c c C C STR str str str STR\x0000\xFFFF", ARRAY_COUNT(wbuf)) != 0) {
		fprintf(stderr, "ret: expected=%d got=%d\n", ARRAY_COUNT(wbuf)-2, ret);
		fprintf(stderr, "wbuf:\n");
		PRINT_WIDE_BUF(wbuf);
		fprintf(stderr, "\n");
		return 1;
	}
	printf("OK wbuf\n");

#if __MSVCRT_VERSION__ < 0x200 || __MSVCRT_VERSION__ > 0x400

	/*
	 * These two tests do not work with msvcrt20.dll, msvcrt40.dll and msvcr40d.dll
	 * which do not support w length modifier. All older and new CRT libraries support it.
	 */

	memset(abuf2, 0xff, sizeof(abuf2));
	ret = snprintf(abuf2, ARRAY_COUNT(abuf2), "%wc %wC %ws %wS", L'C', L'C', L"STR", L"STR");
	if (ret != ARRAY_COUNT(abuf2)-2 || memcmp(abuf2, "C C STR STR\x00\xFF", ARRAY_COUNT(abuf2)) != 0) {
		fprintf(stderr, "ret: expected=%d got=%d\n", ARRAY_COUNT(abuf2)-2, ret);
		fprintf(stderr, "abuf2:\n");
		PRINT_NARROW_BUF(abuf2);
		fprintf(stderr, "\n");
		return 1;
	}
	printf("OK abuf2\n");

	memset(wbuf2, 0xff, sizeof(wbuf2));
	ret = swprintf(wbuf2, ARRAY_COUNT(wbuf2), L"%wc %wC %ws %wS", L'C', L'C', L"STR", L"STR");
	if (ret != ARRAY_COUNT(wbuf2)-2 || wmemcmp(wbuf2, L"C C STR STR\x0000\xFFFF", ARRAY_COUNT(wbuf2)) != 0) {
		fprintf(stderr, "ret: expected=%d got=%d\n", ARRAY_COUNT(wbuf2)-2, ret);
		fprintf(stderr, "wbuf2:\n");
		PRINT_WIDE_BUF(wbuf2);
		fprintf(stderr, "\n");
		return 1;
	}
	printf("OK wbuf2\n");

#endif

#if __MSVCRT_VERSION__ >= 0x600 || __USE_MINGW_ANSI_STDIO == 1

#if __USE_MINGW_ANSI_STDIO == 0 && !defined(_UCRT)
	HMODULE msvcrt_dll = GetModuleHandleA("msvcrt.dll");
	IMAGE_DOS_HEADER *msvcrt_dos = (IMAGE_DOS_HEADER *)msvcrt_dll;
	IMAGE_NT_HEADERS *msvcrt_pe = (msvcrt_dos && msvcrt_dos->e_magic == IMAGE_DOS_SIGNATURE) ? (IMAGE_NT_HEADERS *)((BYTE *)msvcrt_dos + msvcrt_dos->e_lfanew) : NULL;
	DWORD msvcrt_version = (msvcrt_pe && msvcrt_pe->Signature == IMAGE_NT_SIGNATURE) ? ((msvcrt_pe->OptionalHeader.MajorImageVersion << 16) | msvcrt_pe->OptionalHeader.MinorImageVersion) : 0;
	/* Win9x, pre-WinXP and VC42-VC60 msvcrt.dll have zero value in MajorImageVersion/MinorImageVersion */
	/* When msvcrt_dll is NULL then we are not using msvcrt.dll library, but some versioned msvcr*.dll library */
	if (!msvcrt_dll || msvcrt_version >= 0x0501 /* XP+ */)
#endif
	{

	/*
	 * This test do not work with crtdll.dll, msvcrt20.dll, msvcrt40.dll, msvcr40d.dll and msvcrt.dll before Windows XP
	 * which treats %lS format wprintf as narrow char* and not as wide wchar_t*.
	 */

	memset(wbuf3, 0xff, sizeof(wbuf3));
	ret = swprintf(wbuf3, ARRAY_COUNT(wbuf3), L"%lS", L"STR");
	if (ret != ARRAY_COUNT(wbuf3)-2 || wmemcmp(wbuf3, L"STR\x0000\xFFFF", ARRAY_COUNT(wbuf3)) != 0) {
		fprintf(stderr, "ret: expected=%d got=%d\n", ARRAY_COUNT(wbuf3)-2, ret);
		fprintf(stderr, "wbuf3:\n");
		PRINT_WIDE_BUF(wbuf3);
		fprintf(stderr, "\n");
		return 1;
	}
	printf("OK wbuf3\n");

	}

#endif

	return 0;
}
