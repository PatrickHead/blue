static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-render [--backend='cairo'|'dxf'] \\\n");
  fprintf(stderr, "                [--cairo-format='svg'|'pdf'|'ps'|'png'] \\\n");
  fprintf(stderr, "                [--output=FILENAME]\\\n");
  fprintf(stderr, "                [INPUT_FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-render -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-render -h, --help\n");
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

  fprintf(stderr, "    --backend='cairo'|'dxf'\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Rendering engine to use for generated output.\n");
  fprintf(stderr, "        Default: 'cairo'.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --cairo-format='svg'|'pdf'|'ps'|'png'\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        File format for generated cairo output.\n");
  fprintf(stderr, "        Default: 'svg'.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --output=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Basename (no extension) of generated output file.\n");
  fprintf(stderr, "        '-' is STDOUT.\n");
  fprintf(stderr, "        Default: STDOUT.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    INPUT_FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of input file.\n");
  fprintf(stderr, "        '-' or blank will read from STDIN.\n");
  fprintf(stderr, "        'xml' extension is optional.\n");
  fprintf(stderr, "\n");

  return;
}

