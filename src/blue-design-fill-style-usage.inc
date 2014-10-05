static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-design-fill-style [--name=STRING] \\\n");
  fprintf(stderr, "                           [--type=FILL_TYPE] \\\n");
  fprintf(stderr, "                           [--line-weight=NUMBER] \\\n");
  fprintf(stderr, "                           [--line-style=NAME] \\\n");
  fprintf(stderr, "                           "
                  "[--background-color-xml=FILENAME] \\\n");
  fprintf(stderr, "                           "
                  "[--pattern-color-xml=FILENAME] \\\n");
  fprintf(stderr, "                           [--angle1=NUMBER] \\\n");
  fprintf(stderr, "                           [--spacing1=DIMENSION] \\\n");
  fprintf(stderr, "                           [--angle2=NUMBER] \\\n");
  fprintf(stderr, "                           [--spacing2=DIMENSION] \\\n");
  fprintf(stderr, "                           [--source=SOURCENAME] \\\n");
  fprintf(stderr, "                           [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "                           [--input=FILENAME] \\\n");
  fprintf(stderr, "                           [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-fill-style -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-fill-style -h, --help\n");
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

  fprintf(stderr, "    --name=STRING\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of fill style.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --type=FILL_TYPE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of layer.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        FILL_TYPE is one of:\n");
  fprintf(stderr, "          line\n");
  fprintf(stderr, "          hatch\n");
  fprintf(stderr, "          stipple\n");
  fprintf(stderr, "          source-only\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --line-weight=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Thickness of drawn lines.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --line-style=NAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of line style.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --background-color-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of blueXML file containing color data.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --pattern-color-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of blueXML file containing color data.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --angle1=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Angle in degrees of 'vertical' lines.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --spacing1=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Spacing between 'vertical' lines.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --angle2=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Angle in degrees of 'horizontal' lines.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --spacing2=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Spacing between 'horizontal' lines.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --source=SOURCENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of pattern image source.  A filename or URL.\n");
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

