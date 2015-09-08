#include <stdio.h>
#include "prime.h"

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_SUBMINOR 0

#define DEFAULT_MIN 1

static const char _VERSION_STR[] = "1.0.0";


static int showHelp (const char *ch, int ret);
static unsigned int cropPath (const char *ch);
static void printErr (const char *str[], int i);

static const char *errStr[] = { "Parameter is not match.",
  "Min > Max.",
  "One of parameter is not an unsigned number."
};

enum
{
  e_parNmatch, e_mOm, e_parNnum
};


int
main (int argc, const char *argv[])
{
  unsigned int min, max, i, count;

/*********	Paramer management	***********/


  switch (argc)
    {
    case 2:
      min = DEFAULT_MIN;
      if (!isUint (argv[1]))
	{
	  printErr (errStr, e_parNnum);
	  return showHelp (argv[0], 1);
	}
      max = s2ui (argv[1]);

      break;
    case 3:


      if (!isUint (argv[1]) || !isUint (argv[2]))
	{
	  printErr (errStr, e_parNnum);
	  return showHelp (argv[0], 1);
	}
      min = s2ui (argv[1]);
      max = s2ui (argv[2]);
      break;

    default:
      printErr (errStr, e_parNmatch);
      return showHelp (argv[0], 1);
    }

  if (min > max)
    {
      printErr (errStr, e_mOm);
      return showHelp (argv[0], 1);
    }
/*********	Paramer management	***********/

  for (i = min, count = 0; i <= max; i++)
    {
      if (isPrime (i))
	{
	  printf ("%u\n", i);
	  count++;
	}

    }

  printf ("\n%u to %u have %u\n", min, max, count);
  return 0;
}


/*********	End of main function	***********/

static int
showHelp (const char *ch, int ret)
{
  unsigned int i;
  i = cropPath (ch);

  fprintf
    (stderr,
     "\n%s version %s is an utility that can generate prime numbers.\n\n",
     (char *) ch + i, _VERSION_STR);
  fprintf (stderr,
	   "USAGE:\t%s number\nProgram generates prime numbers between 1 to number.\n",
	   (char *) ch + i);
  fprintf (stderr,
	   "USAGE:\t%s min max\nProgram generates prime numbers between min to max.\n\n",
	   (char *) ch + i);

  return ret;
}

static unsigned int
cropPath (const char *ch)
{
  unsigned int i, j;
  for (i = 0, j = 0; ch[i]; i++)
    {
      if (ch[i] == '\\' || ch[i] == '/')
	{
	  j = i;
	}
    }
  return (j == 0) ? 0 : j + 1;
}

static void
printErr (const char *str[], int i)
{
  fprintf (stderr, "** Error number %d : %s **\n", i, ((char *) str[i]));
}