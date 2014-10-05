static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-design-layer [--id=NUMBER] \\\n");
  fprintf(stderr, "                      [--name=STRING] \\\n");
  fprintf(stderr, "                      [--visibility=VISIBILITY_TYPE] \\\n");
  fprintf(stderr, "                      [--defaults-xml=FILENAME] \\\n");
  fprintf(stderr, "                      [--elements-xml=FILENAME] \\\n");
  fprintf(stderr, "                      [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "                      [--input=FILENAME] \\\n");
  fprintf(stderr, "                      [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-layer -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-layer -h, --help\n");
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

  fprintf(stderr, "    --id=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Unique id number.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: If this option is omitted, the id"
                  " will be created automatically.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --name=STRING\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of layer.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --visibility=VISIBILITY_TYPE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Visibility of layer.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        VISIBILITY_TYPE is one of:\n");
  fprintf(stderr, "          visible\n");
  fprintf(stderr, "          hidden\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --defaults-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        XML file containing defaults data.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --elements-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        XML file containing elements data.\n");
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

