static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-design-elliptic [--center=VERTEX] \\\n");
  fprintf(stderr, "                         [--width=DIMENSION] \\\n");
  fprintf(stderr, "                         [--height=DIMENSION] \\\n");
  fprintf(stderr, "                         [--rotation=DEGREE] \\\n");
  fprintf(stderr, "                         [--start-angle=DEGREE] \\\n");
  fprintf(stderr, "                         [--end-angle=DEGREE] \\\n");
  fprintf(stderr, "                         [--defaults-xml=FILENAME] \\\n");
  fprintf(stderr, "                         [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "                         [--input=FILENAME] \\\n");
  fprintf(stderr, "                         [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-elliptic -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-elliptic -h, --help\n");
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

  fprintf(stderr, "    --center=VERTEX\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Center coordinate of elliptic shape.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        VERTEX: is in form of: '[x,y,z]'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --width=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Major radius of elliptic shape.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --height=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Minor radius of elliptic shape.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --rotation=DEGREE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Angular rotation of elliptic shape.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE:  0 degrees is the positive X axis.\n");
  fprintf(stderr, "              90 degrees is the positive Y axis.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --start-angle=DEGREE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Beginning end point (angular) of elliptic shape.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE:  0 degrees is the positive X axis.\n");
  fprintf(stderr, "              90 degrees is the positive Y axis.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --end-angle=DEGREE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Ending end point (angular) of elliptic shape.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE:  0 degrees is the positive X axis.\n");
  fprintf(stderr, "              90 degrees is the positive Y axis.\n");
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

