static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-design-text [--type=TYPE] \\\n");
  fprintf(stderr, "                     [--location=VERTEX] \\\n");
  fprintf(stderr, "                     [--rotation=DEGREE] \\\n");
  fprintf(stderr, "                     [--anchor-point=ANCHOR_TYPE] \\\n");
  fprintf(stderr, "                     [--size=DIMENSION] \\\n");
  fprintf(stderr, "                     [--text=STRING] \\\n");
  fprintf(stderr, "                     [--defaults-xml=FILENAME] \\\n");
  fprintf(stderr, "                     [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "                     [--input=FILENAME] \\\n");
  fprintf(stderr, "                     [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-text -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-text -h, --help\n");
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
  fprintf(stderr, "        Scaling type of text.\n");
  fprintf(stderr, "        Default: drawing.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        TYPE is one of:\n");
  fprintf(stderr, "          drawing\n");
  fprintf(stderr, "          annotation\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: drawing text is scaled relative to the"
                  " drawing design.\n");
  fprintf(stderr, "              annotation text is in real world units\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --location=VERTEX\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Coordinate of text anchor.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        VERTEX: is in form of: '[x,y,z]'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --rotation=DEGREE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Angular rotation of text around anchor location.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE:  0 degrees is positive X axis\n");
  fprintf(stderr, "              90 degrees is positive Y axis\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --anchor-point=ANCHOR_TYPE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Relation of anchor location to text.\n");
  fprintf(stderr, "        Default: upper-left\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        ANCHOR_TYPE is one of:\n");
  fprintf(stderr, "          upper-left\n");
  fprintf(stderr, "          upper-right\n");
  fprintf(stderr, "          center\n");
  fprintf(stderr, "          lower-left\n");
  fprintf(stderr, "          lower-right\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --size=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Height of text.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --text=STRING\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Text to display.\n");
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

