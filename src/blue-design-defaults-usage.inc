static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-design-defaults [--UNITS=UNIT_TYPE] \\\n");
  fprintf(stderr, "                         [--line-weight=DIMENSION] \\\n");
  fprintf(stderr, "                         [--line-style=LINE_STYLE] \\\n");
  fprintf(stderr, "                         [--fill-style=LINE_STYLE] \\\n");
  fprintf(stderr, "                         [--dimension-text-size=DIMENSION]"
                  " \\\n");
  fprintf(stderr, "                         [--dimension-precision=NUMBER]"
                  " \\\n");
  fprintf(stderr, "                         [--angular-gap=DIMENSION] \\\n");
  fprintf(stderr, "                         [--angular-extension=DIMENSION]"
                  " \\\n");
  fprintf(stderr, "                         [--linear-gap=DIMENSION]"
                  " \\\n");
  fprintf(stderr, "                         [--linear-extension-above=DIMENSION]"
                  " \\\n");
  fprintf(stderr, "                         [--linear-extension-below=DIMENSION]"
                  " \\\n");
  fprintf(stderr, "                         [--tolerance-text-size=DIMENSION]"
                  " \\\n");
  fprintf(stderr, "                         [--tolerance-plus=NUMBER] \\\n");
  fprintf(stderr, "                         [--tolerance-minus=NUMBER] \\\n");
  fprintf(stderr, "                         [--tolerance-precision=NUMBER]"
                  " \\\n");
  fprintf(stderr, "                         [--background-color-xml=FILENAME]"
                  " \\\n");
  fprintf(stderr, "                         [--element-color-xml=FILENAME] \\\n");
  fprintf(stderr, "                         [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "                         [--input=FILENAME] \\\n");
  fprintf(stderr, "                         [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-defaults -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-defaults -h, --help\n");
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

  fprintf(stderr, "    --units=UNIT_TYPE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Unit type for element dimensions.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        UNIT_TYPE is one of:\n");
  fprintf(stderr, "          Yottameter, Ym\n");
  fprintf(stderr, "          Zettameter, Zm\n");
  fprintf(stderr, "          Exameter, Em\n");
  fprintf(stderr, "          Petameter, Pm\n");
  fprintf(stderr, "          Terameter, Tm\n");
  fprintf(stderr, "          Gigameter, Gm\n");
  fprintf(stderr, "          Megameter, Mm\n");
  fprintf(stderr, "          kilometer, km\n");
  fprintf(stderr, "          hectometer, hm\n");
  fprintf(stderr, "          decameter, dam\n");
  fprintf(stderr, "          meter, m\n");
  fprintf(stderr, "          decimeter, dm\n");
  fprintf(stderr, "          centimeter, cm\n");
  fprintf(stderr, "          millimeter, mm\n");
  fprintf(stderr, "          micrometer, um\n");
  fprintf(stderr, "          nanometer, nm\n");
  fprintf(stderr, "          picometer, pm\n");
  fprintf(stderr, "          femtometer, fm\n");
  fprintf(stderr, "          attometer, am\n");
  fprintf(stderr, "          zeptometer, zm\n");
  fprintf(stderr, "          yoctometer, ym\n");
  fprintf(stderr, "          thou, th\n");
  fprintf(stderr, "          inch, in\n");
  fprintf(stderr, "          foot, ft\n");
  fprintf(stderr, "          yard, yd\n");
  fprintf(stderr, "          chain, ch\n");
  fprintf(stderr, "          furlong, fur\n");
  fprintf(stderr, "          mile, mi\n");
  fprintf(stderr, "          league, lea\n");
  fprintf(stderr, "          fathom, ftm\n");
  fprintf(stderr, "          cable\n");
  fprintf(stderr, "          nautical mile\n");
  fprintf(stderr, "          link\n");
  fprintf(stderr, "          rod\n");
  fprintf(stderr, "          point, pt\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --line-weight=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Line thickness in element units.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --line-style=LINE_STYLE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Style of drawn lines.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        EXAMPLE: 'dotted'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --fill-style=LINE_STYLE\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Style of drawn fills.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        EXAMPLE: 'hatch'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --dimension-text-size=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Height of dimension text in element units.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --dimension-precision=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Number of digits after decimal point.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --angular-gap=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Gap between beta/gamma and the respective extension"
                  " lines.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --angular-extension=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Length of extension lines.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --linear-gap=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Distance from dimension line to measured line.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --linear-extension-above=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Length of extension line away from measured line.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --linear-extension-below=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Length of extension line toward from measured"
                  " line.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --tolerance-text-size=DIMENSION\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Height of tolerance text in element units.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --tolerance-plus=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Plus (over) tolerance.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --tolerance-minus=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Minus (under) tolerance.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --tolerance-precision=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Number of digits after decimal point.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --background-color-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of blueXML file containing color data.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --element-color-xml=FILENAME\n");
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

