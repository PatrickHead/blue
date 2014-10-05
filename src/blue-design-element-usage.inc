static void usage(void)
{
  fprintf(stderr, "\n");

  version();

  fprintf(stderr,
    "\nUSAGE:\n\n");
  fprintf(stderr, "    blue-design-element [--id=NUMBER] \\\n");
  fprintf(stderr, "                        [--units=UNIT_TYPE] \\\n");
  fprintf(stderr, "                        [--line-weight=NUMBER] \\\n");
  fprintf(stderr, "                        [--line-style=LINE_STYLE] \\\n");
  fprintf(stderr, "                        [--fill-style=FILL_STYLE] \\\n");
  fprintf(stderr, "                        [--color-xml=FILENAME] \\\n");
  fprintf(stderr, "                        [--dimension-xml=FILENAME] \\\n");
  fprintf(stderr, "                        [--elliptic-xml=FILENAME] \\\n");
  fprintf(stderr, "                        [--fill-xml=FILENAME] \\\n");
  fprintf(stderr, "                        [--line-xml=FILENAME] \\\n");
  fprintf(stderr, "                        [--point-xml=FILENAME] \\\n");
  fprintf(stderr, "                        [--polyline-xml=FILENAME] \\\n");
  fprintf(stderr, "                        [--spline-xml=FILENAME] \\\n");
  fprintf(stderr, "                        [--text-xml=FILENAME]\n");
  fprintf(stderr, "                        [--tolerance-xml=FILENAME] \\\n");
  fprintf(stderr, "                        [--defaults-xml=FILENAME] \\\n");
  fprintf(stderr, "                        [--mode=PROCESS_MODE] \\\n");
  fprintf(stderr, "                        [--input=FILENAME] \\\n");
  fprintf(stderr, "                        [--output=FILENAME]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-element -v, --version\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    blue-design-element -h, --help\n");
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

  fprintf(stderr, "    --line-weight=NUMBER\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Thickness of drawn lines.\n");
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

  fprintf(stderr, "    --color-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        Name of blueXML file containing color data.\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --dimension-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        XML file containing dimension data.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: This option will set type to 'dimension'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --elliptic-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        XML file containing elliptic data.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: This option will set type to 'elliptic'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --fill-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        XML file containing fill data.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: This option will set type to 'fill'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --line-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        XML file containing line data.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: This option will set type to 'line'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --point-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        XML file containing point data.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: This option will set type to 'point'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --polyline-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        XML file containing polyline data.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: This option will set type to 'polyline'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --spline-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        XML file containing spline data.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: This option will set type to 'spline'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --text-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        XML file containing text data.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: This option will set type to 'text'\n");
  fprintf(stderr, "\n");

  fprintf(stderr, "    --tolerance-xml=FILENAME\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        XML file containing tolerance data.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "        NOTE: This option will set type to 'tolerance'\n");
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

