static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-color [--tag=STRING] \\\n");
  fprintf(stderr, "               [--r=COLOR] \\\n");
  fprintf(stderr, "               [--b=COLOR] \\\n");
  fprintf(stderr, "               [--g=COLOR] \\\n");
  fprintf(stderr, "               [--a=ALPHA] \\\n");
  fprintf(stderr, "               [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "               [--input=FILENAME] \\\n");
  fprintf(stderr, "               [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-color -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-color -h, --help\n");
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
  fprintf(stderr, "        User defined reference name for color.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --r=COLOR\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Red value of color.\n");
  fprintf(stderr, "        Default: 0.0.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: COLOR is in range of 0.0 to 255.0\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --g=COLOR\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Green value of color.\n");
  fprintf(stderr, "        Default: 0.0.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: COLOR is in range of 0.0 to 255.0\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --b=COLOR\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Blue value of color.\n");
  fprintf(stderr, "        Default: 0.0.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: COLOR is in range of 0.0 to 255.0\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --a=ALPHA\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Transparency of color.\n");
  fprintf(stderr, "        Default: 0.0.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: ALPHA is in range of 0.0 to 1.0\n");
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

