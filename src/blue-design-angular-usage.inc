static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-design-angular [--angle=DEGREE] \\\n");
  fprintf(stderr, "                        [--alpha=VERTEX] \\\n");
  fprintf(stderr, "                        [--beta=VERTEX] \\\n");
  fprintf(stderr, "                        [--gamma=VERTEX] \\\n");
  fprintf(stderr, "                        [--gap=DIMENSION] \\\n");
  fprintf(stderr, "                        [--extension=DIMENSION] \\\n");
  fprintf(stderr, "                        [--defaults-xml=FILENAME] \\\n");
  fprintf(stderr, "                        [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "                        [--input=FILENAME] \\\n");
  fprintf(stderr, "                        [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-angular -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-angular -h, --help\n");
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

  fprintf(stderr, "    --angle=DEGREE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Literal angular dimension in degrees.\n");
  fprintf(stderr, "        Default: 0.0.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: If angle is 0.0, the angle will automatically"
                  " be calculated.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --alpha=VERTEX\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Center coordinate of measured angle.\n");
  fprintf(stderr, "        Default: None.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        VERTEX: is in form of: '[x,y,z]'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --beta=VERTEX\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Second coordinate of measured angle.\n");
  fprintf(stderr, "        Default: None.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        VERTEX: is in form of: '[x,y,z]'\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: This coordinate should be the most\n");
  fprintf(stderr, "              positive angular direction.  0.0 is the\n");
  fprintf(stderr, "              positive X axis and 90.0 is the positive\n");
  fprintf(stderr, "              Y axis.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --gamma=VERTEX\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Third coordinate of measured angle.\n");
  fprintf(stderr, "        Default: None.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        VERTEX: is in form of: '[x,y,z]'\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: This coordinate should be the least\n");
  fprintf(stderr, "              positive angular direction.  0.0 is the\n");
  fprintf(stderr, "              positive X axis and 90.0 is the positive\n");
  fprintf(stderr, "              Y axis.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --gap=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Gap between beta/gamma and the respective"
                           " extension lines.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --extension=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Length of extension lines.\n");
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

