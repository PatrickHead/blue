static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-margins [--units=UNIT] \\\n");
  fprintf(stderr, "                 [--top=DIMENSION] \\\n");
  fprintf(stderr, "                 [--bottom=DIMENSION] \\\n");
  fprintf(stderr, "                 [--left=DIMENSION] \\\n");
  fprintf(stderr, "                 [--right=DIMENSION] \\\n");
  fprintf(stderr, "                 [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "                 [--input=FILENAME] \\\n");
  fprintf(stderr, "                 [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-margins -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-margins -h, --help\n");
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

  fprintf(stderr, "    --units=UNIT\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Unit specifier for all dimensions of border.\n");
  fprintf(stderr, "        Default: 'cm'.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        UNIT is one of:\n");
  fprintf(stderr, "          'Yottameter' --or-- 'Ym'\n");
  fprintf(stderr, "          'Zettameter' --or-- 'Zm'\n");
  fprintf(stderr, "          'Exameter' --or-- 'Em'\n");
  fprintf(stderr, "          'Petameter' --or-- 'Pm'\n");
  fprintf(stderr, "          'Terameter' --or-- 'Tm'\n");
  fprintf(stderr, "          'Gigameter' --or-- 'Gm'\n");
  fprintf(stderr, "          'Megameter' --or-- 'Mm'\n");
  fprintf(stderr, "          'kilometer' --or-- 'km'\n");
  fprintf(stderr, "          'hectometer' --or-- 'hm'\n");
  fprintf(stderr, "          'decameter' --or-- 'dam'\n");
  fprintf(stderr, "          'meter' --or-- 'm'\n");
  fprintf(stderr, "          'decimeter' --or-- 'dm'\n");
  fprintf(stderr, "          'centimeter' --or-- 'cm'\n");
  fprintf(stderr, "          'millimeter' --or-- 'mm'\n");
  fprintf(stderr, "          'micrometer' --or-- 'um'\n");
  fprintf(stderr, "          'nanometer' --or-- 'nm'\n");
  fprintf(stderr, "          'picometer' --or-- 'pm'\n");
  fprintf(stderr, "          'femtometer' --or-- 'fm'\n");
  fprintf(stderr, "          'attometer' --or-- 'am'\n");
  fprintf(stderr, "          'zeptometer' --or-- 'zm'\n");
  fprintf(stderr, "          'yoctometer' --or-- 'ym'\n");
  fprintf(stderr, "          'thou' --or-- 'th'\n");
  fprintf(stderr, "          'inch' --or-- 'in'\n");
  fprintf(stderr, "          'foot' --or-- 'ft'\n");
  fprintf(stderr, "          'yard' --or-- 'yd'\n");
  fprintf(stderr, "          'chain' --or-- 'ch'\n");
  fprintf(stderr, "          'furlong' --or-- 'fur'\n");
  fprintf(stderr, "          'mile' --or-- 'mi'\n");
  fprintf(stderr, "          'league' --or-- 'lea'\n");
  fprintf(stderr, "          'fathom' --or-- 'ftm'\n");
  fprintf(stderr, "          'cable'\n");
  fprintf(stderr, "          'nautical mile'\n");
  fprintf(stderr, "          'link'\n");
  fprintf(stderr, "          'rod'\n");
  fprintf(stderr, "          'point' --or-- 'pt'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --top=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Top margin.\n");
  fprintf(stderr, "        Default: 6.35mm (0.25in).\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --bottom=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Bottom margin.\n");
  fprintf(stderr, "        Default: 6.35mm (0.25in).\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --left=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Left margin.\n");
  fprintf(stderr, "        Default: 6.35mm (0.25in).\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --right=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Right margin.\n");
  fprintf(stderr, "        Default: 6.35mm (0.25in).\n");
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

