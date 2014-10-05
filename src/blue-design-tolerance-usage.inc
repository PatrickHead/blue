static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-design-tolerance [--location=VERTEX] \\\n");
  fprintf(stderr, "                          [--text-size=DIMENSION] \\\n");
  fprintf(stderr, "                          [--plus=NUMBER] \\\n");
  fprintf(stderr, "                          [--minus=NUMBER] \\\n");
  fprintf(stderr, "                          [--precision=NUMBER] \\\n");
  fprintf(stderr, "                          [--defaults-xml=FILENAME] \\\n");
  fprintf(stderr, "                          [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "                          [--input=FILENAME] \\\n");
  fprintf(stderr, "                          [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-tolerance -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-tolerance -h, --help\n");
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

  fprintf(stderr, "    --location=VERTEX\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Center coordinate of tolerance box.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        VERTEX: is in form of: '[x,y,z]'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --text-size=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Height of displayed text.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --plus=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Plus tolerance value.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --minus=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Minus tolerance value.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --precision=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Number of digits after decimal point in tolerance"
                  " text.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --defaults-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        XML file containing defaults data.\n");
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

