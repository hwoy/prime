#include <stdio.h>

#include "prime.h"
#include "function.h"
#include "opt.h"

#define DMIN 1
#define DCOL 1

#define BSIZE 64

static int showHelp(const char* ch, int ret,const char *opt[] ,const char *optstr[]);
static const char* cropPath(const char* ch);
static void printErr(const char* str[], int i);

static const char* errStr[] = { "Parameter is not match.",
    "Min > Max.",
    "One of parameter is not an unsigned number.",
    "COL must not be zero",
    "Number of Min or Max doesn't match",
    NULL};

enum {
    e_parNmatch,
    e_mOm,
    e_parNnum,
    e_col,
    e_dcount
};

static const char* opt[] = { "-c:", NULL };
static const char* optstr[] = { "Number of Column", NULL };

enum {
	opt_c
};

int main(int argc, const char* argv[])
{
    unsigned int min=DMIN, max=DMIN, num, count, COL=DCOL, col,dcount;

 {
        static char buff[BSIZE];
        int index;
        unsigned int ui_cindex;

        if(argc <2)
        {
            printErr(errStr, e_parNmatch);
            return showHelp(argv[0], 1 , opt, optstr);       
        }

        for (ui_cindex = DSTART,dcount=0; (index = opt_action(argc, argv, opt, buff,BSIZE, DSTART)) != e_optend; ui_cindex++)
        {

            switch (index) 
            {

                case opt_c:

                    if (!isUint(buff)) {
                        printErr(errStr, e_parNnum);
                        return showHelp(argv[0], 1, opt, optstr);
                    }

                    COL = s2ui(buff);

                	break;
                
                default:
                    if (!isUint(buff)) {
                        printErr(errStr, e_parNnum);
                        return showHelp(argv[0], 1, opt, optstr);
                    }

                    if(dcount++)
                        min = max;
                    
                    max = s2ui(buff);

                    break;
                    
            }
        }
 }

    if (!COL) {
        printErr(errStr, e_col);
        return showHelp(argv[0], 1, opt, optstr);
    }

    if (min > max) {
        printErr(errStr, e_mOm);
        return showHelp(argv[0], 1, opt, optstr);
    }

    if(dcount<1 || dcount>2)
    {
         printErr(errStr, e_dcount);
        return showHelp(argv[0], 1, opt, optstr);       
    }




    for (num = min, count = 0, col = 0; num <= max; ++num) {
        if (isPrime(num)) {
            printf("%u \t", num);
            
            count++;

            if(!(col=(col+1)%COL))
                putchar('\n');
        }
    }

    printf("\n\n%u to %u have %u\n", min, max, count);
    return 0;
}

/*********	End of main function	***********/

static int showHelp(const char* ch, int ret,const char *opt[] ,const char *optstr[])
{
    unsigned int i;
    const char* crop = cropPath(ch);

    fprintf(stderr,
        "\n%s is an utility that can generate prime numbers.\n\n",
        crop);
    fprintf(stderr,
        "USAGE:\t%s [option] number\nProgram generates prime numbers between %u to number.\n\n",
        crop, DMIN);
    fprintf(stderr,
        "USAGE:\t%s [option] min max\nProgram generates prime numbers between min to max.\n\n",
        crop);

    fprintf(stderr,"Options:\n\n");

    for(i=0;opt[i] && optstr[i];++i)
        fprintf(stderr,"%s \t=> \t %s\n",opt[i],optstr[i]);

    fprintf(stderr,"\nExample:\n");
    fprintf(stderr,"%s %s10 1000\n\n",crop,opt[0]);


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
