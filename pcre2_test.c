#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcre2posix.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef char chr;
typedef char* cstr;
typedef char** cstrarr;

typedef regex_t regex;
typedef regmatch_t match;

#define success exit(EXIT_SUCCESS);
#define failure exit(EXIT_FAILURE);

extern int pcre2_regcomp(regex_t *, const char *, int);
extern int pcre2_regexec(const regex_t *, const char *, size_t, regmatch_t *, int);
extern size_t pcre2_regerror(int, const regex_t *, char *, size_t);
extern void pcre2_regfree(regex_t *);

s32 main (s32 argc, cstrarr argv) {

    cstr expression =
    "^(1?[0-9]{1,2}|2[0-4][0-9]|25[0-5])(\\.(1?[0-9]{1,2}|2[0-4][0-9]|25[0-5])){3}$\0";

    fprintf(stdout, "Matching against the expression:\n%.*s\n\n", 77, expression);

    cstr src1 = "192.168.45.43\0";
    cstr src2 = "192.168.45.64g\0";
    cstr src3 = "192.256.76.23\0";

    fprintf(stdout, "Testing:\n");
    fprintf(stdout, "1.\t%.*s\n", 13, src1);
    fprintf(stdout, "2.\t%.*s\n", 14, src2);
    fprintf(stdout, "3.\t%.*s\n", 13, src3);
    fprintf(stdout, "\n");

    int error;
    size_t errlen;
    size_t errbuflen = 8192;
    chr errbuf[8192];

    regex expr;
    regex* exprp = &expr;
    error = pcre2_regcomp(&expr, (const cstr)expression, 0);
    if (error) {
        errlen = pcre2_regerror(error, (const regex*)exprp, errbuf, errbuflen);
        if (errlen > errbuflen) {
            fprintf(stderr, "\033[31mpcre2_test\033[39m: ERROR EXCEEDS BUFFER SIZE.\n");
            failure;
        }
        fprintf(stderr, "\033[31mpcre2_test\033[39m: libpcre2-posix reports: %.*s.\n", errlen, errbuf);
        failure;
    }

    match matches;

    error = pcre2_regexec((const regex*)exprp, (const cstr)src1, (size_t)1, &matches, 0);
    if (error) {
        errlen = pcre2_regerror(error, (const regex*)exprp, errbuf, errbuflen);
        if (errlen > errbuflen) {
            fprintf(stderr, "\033[31mpcre2_test\033[39m: ERROR EXCEEDS BUFFER SIZE.\n");
            failure;
        }
        fprintf(stderr, "\033[31mpcre2_test\033[39m: libpcre2-posix reports: %.*s.\n", errlen, errbuf);
        failure;
    }
    if (matches.rm_so == -1 && matches.rm_eo == -1) {
        fprintf(stdout, "\033[35mpcre2_test\033[39m: %.*s did not match.\n", 13, src1);
    } else {
        fprintf(stdout, "\033[35mpcre2_test\033[39m: %.*s within %.*s matched!\n",
                matches.rm_eo, src1,
                13, src1
        );
    }

    error = pcre2_regexec((const regex*)exprp, (const cstr)src2, (size_t)1, &matches, 0);
    if (error) {
        errlen = pcre2_regerror(error, (const regex*)exprp, errbuf, errbuflen);
        if (errlen > errbuflen) {
            fprintf(stderr, "\033[31mpcre2_test\033[39m: ERROR EXCEEDS BUFFER SIZE.\n");
            failure;
        }
        fprintf(stderr, "\033[31mpcre2_test\033[39m: libpcre2-posix reports: %.*s.\n", errlen, errbuf);
        failure;
    }
    if (matches.rm_so == -1 && matches.rm_eo == -1) {
        fprintf(stdout, "\033[35mpcre2_test\033[39m: %.*s did not match.\n", 14, src2);
    } else {
        fprintf(stdout, "\033[35mpcre2_test\033[39m: %.*s within %.*s matched!\n",
                matches.rm_eo, src2,
                14, src2
        );
    }

    error = pcre2_regexec((const regex*)exprp, (const cstr)src3, (size_t)1, &matches, 0);
    if (error) {
        errlen = pcre2_regerror(error, (const regex*)exprp, errbuf, errbuflen);
        if (errlen > errbuflen) {
            fprintf(stderr, "\033[31mpcre2_test\033[39m: ERROR EXCEEDS BUFFER SIZE.\n");
            failure;
        }
        fprintf(stderr, "\033[31mpcre2_test\033[39m: libpcre2-posix reports: %.*s.\n", errlen, errbuf);
        failure;
    }
    if (matches.rm_so == -1 && matches.rm_eo == -1) {
        fprintf(stdout, "\033[35mpcre2_test\033[39m: %.*s did not match.\n", 13, src3);
    } else {
        fprintf(stdout, "\033[35mpcre2_test\033[39m: %.*s within %.*s matched!\n",
                matches.rm_eo, src3,
                13, src3
        );
    }

    pcre2_regfree(&expr);

    success;
}
