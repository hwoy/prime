#include <stdio.h>

#include "prime.h"
#include "function.h"
#include "opt.h"

#define DEFAULT_MIN 1

static int showHelp(const char* ch, int ret);
static const char* cropPath(const char* ch);
static void printErr(const char* str[], int i);

static const char* errStr[] = { "Parameter is not match.",
    "Min > Max.",
    "One of parameter is not an unsigned number." };

enum {
    e_parNmatch,
    e_mOm,
    e_parNnum
};

int main(int argc, const char* argv[])
{
    unsigned int min, max, i, count;

    /*********	Paramer management	***********/

    switch (argc) {
    case 2:
        min = DEFAULT_MIN;
        if (!isUint(argv[1])) {
            printErr(errStr, e_parNnum);
            return showHelp(argv[0], 1);
        }
        max = s2ui(argv[1]);

        break;
    case 3:

        if (!isUint(argv[1]) || !isUint(argv[2])) {
            printErr(errStr, e_parNnum);
            return showHelp(argv[0], 1);
        }
        min = s2ui(argv[1]);
        max = s2ui(argv[2]);
        break;

    default:
        printErr(errStr, e_parNmatch);
        return showHelp(argv[0], 1);
    }

    if (min > max) {
        printErr(errStr, e_mOm);
        return showHelp(argv[0], 1);
    }
    /*********	Paramer management	***********/

    for (i = min, count = 0; i <= max; i++) {
        if (isPrime(i)) {
            printf("%u\n", i);
            count++;
        }
    }

    printf("\n%u to %u have %u\n", min, max, count);
    return 0;
}

/*********	End of main function	***********/

static int
showHelp(const char* ch, int ret)
{

    const char* crop = cropPath(ch);

    fprintf(stderr,
        "\n%s is an utility that can generate prime numbers.\n\n",
        crop);
    fprintf(stderr,
        "USAGE:\t%s number\nProgram generates prime numbers between %u to number.\n\n",
        crop, DEFAULT_MIN);
    fprintf(stderr,
        "USAGE:\t%s min max\nProgram generates prime numbers between min to max.\n\n",
        crop);

    return ret;
}

static const char*
cropPath(const char* ch)
{
    const char* prog;

    for (prog = ch; *ch; ++ch)
        if (*ch == '\\' || *ch == '/')
            prog = ch + 1;

    return prog;
}

static void
printErr(const char* str[], int i)
{
    fprintf(stderr, "** Error number %d : %s **\n", i, ((char*)str[i]));
}
