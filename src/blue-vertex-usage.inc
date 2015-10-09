static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-vertex [--tag=STRING] \\\n");
  fprintf(stderr, "                [--x=DIMENSION] \\\n");
  fprintf(stderr, "                [--y=DIMENSION] \\\n");
  fprintf(stderr, "                [--z=DIMENSION] \\\n");
  fprintf(stderr, "                [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "                [--input=FILENAME] \\\n");
  fprintf(stderr, "                [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-vertex -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-vertex -h, --help\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "\nOPTIONS:\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    -h, --help\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Display a usage message on STDERR.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Display the program version on STDERR.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --tag=STRING\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        User defined reference tag for vertex.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --x=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        X ordinate of vertex.\n");
  fprintf(stderr, "        Default: 0.0.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --y=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Y ordinate of vertex.\n");
  fprintf(stderr, "        Default: 0.0.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --z=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Z ordinate of vertex.\n");
  fprintf(stderr, "        Default: 0.0.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --mode=PROCESS_MODE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Process mode for XML sieve.\n");
  fprintf(stderr, "        Default: 'passthru'.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        PROCESS_MODE is one of:\n");
  fprintf(stderr, "          passthru\n");
  fprintf(stderr, "          edit\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --input=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of input file.\n");
  fprintf(stderr, "        '-' is STDIN\n");
  fprintf(stderr, "        Default: STDIN\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --output=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of generated output file.\n");
  fprintf(stderr, "        '-' is STDOUT.\n");
  fprintf(stderr, "        Default: STDOUT.\n");
  fprintf(stderr, "\n");

  return;
}

