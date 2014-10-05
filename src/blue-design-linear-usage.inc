static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-design-linear [--start=DEGREE] \\\n");
  fprintf(stderr, "                       [--end=VERTEX] \\\n");
  fprintf(stderr, "                       [--gap=DIMENSION] \\\n");
  fprintf(stderr, "                       [--extension-above=DIMENSION] \\\n");
  fprintf(stderr, "                       [--extension-below=DIMENSION] \\\n");
  fprintf(stderr, "                       [--dimension=DIMENSION] \\\n");
  fprintf(stderr, "                       [--defaults-xml=FILENAME] \\\n");
  fprintf(stderr, "                       [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "                       [--input=FILENAME] \\\n");
  fprintf(stderr, "                       [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-linear -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-linear -h, --help\n");
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

  fprintf(stderr, "    --start=VERTEX\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Coordinate of first end of line.\n");
  fprintf(stderr, "        Default: None.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        VERTEX: is in form of: '[x,y,z]'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --end=VERTEX\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Coordinate of last end of line.\n");
  fprintf(stderr, "        Default: None.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        VERTEX: is in form of: '[x,y,z]'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --gap=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Gap between beta/gamma and the respective"
                           " extension lines.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --extension-above=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Length of extension lines on positive angular"
                  " side of dimension line.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --extension-below=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Length of extension lines on negative angular"
                  " side of dimension line.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --dimension=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Literal dimension value.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: If 0.0, dimension will be automatically"
                  " calculated.\n");
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

