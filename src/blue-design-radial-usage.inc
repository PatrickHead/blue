static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-design-radial [--type=TYPE] \\\n");
  fprintf(stderr, "                       [--center=VERTEX] \\\n");
  fprintf(stderr, "                       [--major=DIMENSION] \\\n");
  fprintf(stderr, "                       [--minor=DIMENSION] \\\n");
  fprintf(stderr, "                       [--angle=DEGREE] \\\n");
  fprintf(stderr, "                       [--leader=DIMENSION] \\\n");
  fprintf(stderr, "                       [--defaults-xml=FILENAME] \\\n");
  fprintf(stderr, "                       [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "                       [--input=FILENAME] \\\n");
  fprintf(stderr, "                       [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-radial -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-radial -h, --help\n");
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

  fprintf(stderr, "    --type=TYPE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Literal angular dimension in degrees.\n");
  fprintf(stderr, "        Default: radius\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        TYPE is one of:\n");
  fprintf(stderr, "          radius\n");
  fprintf(stderr, "          diameter\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --center=VERTEX\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Center coordinate of measured elliptic.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        VERTEX: is in form of: '[x,y,z]'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --major=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Major radius or diameter dimension.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --minor=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Minor radius or diameter dimension.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --angle=DEGREE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Literal angular dimension in degrees.\n");
  fprintf(stderr, "        Default: 0.0.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --leader=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Length of leader.\n");
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

