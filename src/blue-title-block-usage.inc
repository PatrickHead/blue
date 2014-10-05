static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-title-block [--title=STRING] \\\n");
  fprintf(stderr, "                     [--part=STRING] \\\n");
  fprintf(stderr, "                     [--provider=STRING] \\\n");
  fprintf(stderr, "                     [--consumer=STRING] \\\n");
  fprintf(stderr, "                     [--revision=STRING] \\\n");
  fprintf(stderr, "                     [--reference=STRING] \\\n");
  fprintf(stderr, "                     [--page=STRING] \\\n");
  fprintf(stderr, "                     [--of=STRING] \\\n");
  fprintf(stderr, "                     [--time=TIME] \\\n");
  fprintf(stderr, "                     [--background-color-xml=FILENAME] \\\n");
  fprintf(stderr, "                     [--line-color-xml=FILENAME] \\\n");
  fprintf(stderr, "                     [--text-color-xml=FILENAME] \\\n");
  fprintf(stderr, "                     [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "                     [--input=FILENAME] \\\n");
  fprintf(stderr, "                     [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-title-block -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-title-block -h, --help\n");
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

  fprintf(stderr, "    --title=STRING\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Title of drawing.\n");
  fprintf(stderr, "        Default: 'TITLE'.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: Maximum of 30 characters.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --part=STRING\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Part Name.\n");
  fprintf(stderr, "        Default: 'PART'.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: Maximum of 30 characters.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --provider=STRING\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Producer of drawing.\n");
  fprintf(stderr, "        Default: 'PROVIDER'.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: Maximum of 20 characters.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --consumer=STRING\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Intended user of drawing.\n");
  fprintf(stderr, "        Default: 'CONSUMER'.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: Maximum of 20 characters.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --revision=STRING\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Revision number or code.\n");
  fprintf(stderr, "        Default: 'REVISION'.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: Maximum of 10 characters.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --reference=STRING\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Design or document reference number or code.\n");
  fprintf(stderr, "        Default: 'REFERENCE'.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: Maximum of 10 characters.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --page=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Current page number of drawing.\n");
  fprintf(stderr, "        Default: '1'.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: NUMBER should be a positive integer.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --of=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Total pages in drawing.\n");
  fprintf(stderr, "        Default: '1'.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: NUMBER should be a positive integer.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --time=TIME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Total pages in drawing.\n");
  fprintf(stderr, "        Default: <now>.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        TIME: ISO 8601 format (YYYY-MM-DDThh:mm:ss+hh:mm)\n");
  fprintf(stderr, "          Example: 2014-06-18T21:45:00-05:00\n");
  fprintf(stderr, "                   which is: June 6, 2014, 9:45PM EDT\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --background-color-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of blueXML file containing color data.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --line-color-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of blueXML file containing color data.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --text-color-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of blueXML file containing color data.\n");
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

