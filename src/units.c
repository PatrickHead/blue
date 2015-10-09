/*!
    @file units.c

    @brief SOURCE_BRIEF

    @timestamp Fri, 09 Oct 2015 03:31:15 +0000

    @author Patrick Head  mailto:patrickhead@gmail.com

    @copyright Copyright (C) 2014  Patrick Head

    @license
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.@n
    @n
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.@n
    @n
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

  /*!

    @file units.c

    SOURCE_BRIEF

    SOURCE_DETAILS

  */

  // Required system headers

#include <string.h>
#include <assert.h>
#include <math.h>

  // Project related headers

#include "units.h"

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

units_t str2units(char* s)
{
    // Sanity check parameters.
  assert(s);

  if (!strcmp(s, "NONE")) return units_type_none;
  if (!strcmp(s, "Yottameter")) return units_type_Yottameter;
  if (!strcmp(s, "Ym")) return units_type_Ym;
  if (!strcmp(s, "Zettameter")) return units_type_Zettameter;
  if (!strcmp(s, "Zm")) return units_type_Zm;
  if (!strcmp(s, "Exameter")) return units_type_Exameter;
  if (!strcmp(s, "Em")) return units_type_Em;
  if (!strcmp(s, "Petameter")) return units_type_Petameter;
  if (!strcmp(s, "Pm")) return units_type_Pm;
  if (!strcmp(s, "Terameter")) return units_type_Terameter;
  if (!strcmp(s, "Tm")) return units_type_Tm;
  if (!strcmp(s, "Gigameter")) return units_type_Gigameter;
  if (!strcmp(s, "Gm")) return units_type_Gm;
  if (!strcmp(s, "Megameter")) return units_type_Megameter;
  if (!strcmp(s, "Mm")) return units_type_Mm;
  if (!strcmp(s, "kilometer")) return units_type_kilometer;
  if (!strcmp(s, "km")) return units_type_km;
  if (!strcmp(s, "hectometer")) return units_type_hectometer;
  if (!strcmp(s, "hm")) return units_type_hm;
  if (!strcmp(s, "decameter")) return units_type_decameter;
  if (!strcmp(s, "dam")) return units_type_dam;
  if (!strcmp(s, "meter")) return units_type_m;
  if (!strcmp(s, "m")) return units_type_m;
  if (!strcmp(s, "decimeter")) return units_type_decimeter;
  if (!strcmp(s, "dm")) return units_type_dm;
  if (!strcmp(s, "centimeter")) return units_type_centimeter;
  if (!strcmp(s, "cm")) return units_type_cm;
  if (!strcmp(s, "millimeter")) return units_type_millimeter;
  if (!strcmp(s, "mm")) return units_type_mm;
  if (!strcmp(s, "micrometer")) return units_type_micrometer;
  if (!strcmp(s, "um")) return units_type_um;
  if (!strcmp(s, "nanometer")) return units_type_nanometer;
  if (!strcmp(s, "nm")) return units_type_nm;
  if (!strcmp(s, "picometer")) return units_type_picometer;
  if (!strcmp(s, "pm")) return units_type_pm;
  if (!strcmp(s, "femtometer")) return units_type_femtometer;
  if (!strcmp(s, "fm")) return units_type_fm;
  if (!strcmp(s, "attometer")) return units_type_attometer;
  if (!strcmp(s, "am")) return units_type_am;
  if (!strcmp(s, "zeptometer")) return units_type_zeptometer;
  if (!strcmp(s, "zm")) return units_type_zm;
  if (!strcmp(s, "yoctometer")) return units_type_yoctometer;
  if (!strcmp(s, "ym")) return units_type_ym;
  if (!strcmp(s, "thou")) return units_type_thou;
  if (!strcmp(s, "th")) return units_type_th;
  if (!strcmp(s, "inch")) return units_type_inch;
  if (!strcmp(s, "in")) return units_type_in;
  if (!strcmp(s, "foot")) return units_type_foot;
  if (!strcmp(s, "ft")) return units_type_ft;
  if (!strcmp(s, "yard")) return units_type_yard;
  if (!strcmp(s, "yd")) return units_type_yd;
  if (!strcmp(s, "chain")) return units_type_chain;
  if (!strcmp(s, "ch")) return units_type_ch;
  if (!strcmp(s, "furlong")) return units_type_furlong;
  if (!strcmp(s, "fur")) return units_type_fur;
  if (!strcmp(s, "mile")) return units_type_mile;
  if (!strcmp(s, "mi")) return units_type_mi;
  if (!strcmp(s, "league")) return units_type_league;
  if (!strcmp(s, "lea")) return units_type_lea;
  if (!strcmp(s, "fathom")) return units_type_fathom;
  if (!strcmp(s, "ftm")) return units_type_ftm;
  if (!strcmp(s, "cable")) return units_type_cable;
  if (!strcmp(s, "nautical mile")) return units_type_nautical_mile;
  if (!strcmp(s, "link")) return units_type_link;
  if (!strcmp(s, "rod")) return units_type_rod;
  if (!strcmp(s, "point")) return units_type_point;
  if (!strcmp(s, "pt")) return units_type_point;

    // Return RETVAL
  return units_type_none;
}

const char* units2str(units_t t)
{
  switch (t)
  {
    case units_type_none: return "NONE";
    case units_type_Ym: return "Ym";
    case units_type_Zm: return "Zm";
    case units_type_Em: return "Em";
    case units_type_Pm: return "Pm";
    case units_type_Tm: return "Tm";
    case units_type_Gm: return "Gm";
    case units_type_Mm: return "Mm";
    case units_type_km: return "km";
    case units_type_hm: return "hm";
    case units_type_dam: return "dam";
    case units_type_m: return "m";
    case units_type_dm: return "dm";
    case units_type_cm: return "cm";
    case units_type_mm: return "mm";
    case units_type_um: return "um";
    case units_type_nm: return "nm";
    case units_type_pm: return "pm";
    case units_type_fm: return "fm";
    case units_type_am: return "am";
    case units_type_zm: return "zm";
    case units_type_ym: return "ym";
    case units_type_th: return "th";
    case units_type_in: return "in";
    case units_type_ft: return "ft";
    case units_type_yd: return "yd";
    case units_type_ch: return "ch";
    case units_type_fur: return "fur";
    case units_type_mi: return "mi";
    case units_type_lea: return "lea";
    case units_type_ftm: return "ftm";
    case units_type_cable: return "cable";
    case units_type_nautical_mile: return "nautical mile";
    case units_type_link: return "link";
    case units_type_rod: return "rod";
    case units_type_point: return "pt";
    default: break;
  }

    // Return RETVAL
  return "m";
}

  /*!

     @brief FUNCTION_BRIEF

     FUNCTION_DETAILS

     @param PARMNAME    PARM_DESCRIPTION

     @retval "RETTYPE" success
     @retval RETVAL    failure

  */

double units_convert(double value, units_t from_type, units_t to_type)
{
    // Convert "from" unitss to meters
  switch (from_type)
  {
    case units_type_none: break;
    case units_type_Ym: value *= pow(10.0,24.0); break;
    case units_type_Zm: value *= pow(10.0,21.0); break;
    case units_type_Em: value *= pow(10.0,18.0); break;
    case units_type_Pm: value *= pow(10.0,15.0); break;
    case units_type_Tm: value *= pow(10.0,12.0); break;
    case units_type_Gm: value *= pow(10.0,9.0); break;
    case units_type_Mm: value *= pow(10.0,6.0); break;
    case units_type_km: value *= pow(10.0,3.0); break;
    case units_type_hm: value *= pow(10.0,2.0); break;
    case units_type_dam: value *= pow(10.0,1.0); break;
    case units_type_m: break;
    case units_type_dm: value /= pow(10.0,1.0); break;
    case units_type_cm: value /= pow(10.0,2.0); break;
    case units_type_mm: value /= pow(10.0,3.0); break;
    case units_type_um: value /= pow(10.0,6.0); break;
    case units_type_nm: value /= pow(10.0,9.0); break;
    case units_type_pm: value /= pow(10.0,12.0); break;
    case units_type_fm: value /= pow(10.0,15.0); break;
    case units_type_am: value /= pow(10.0,18.0); break;
    case units_type_zm: value /= pow(10.0,21.0); break;
    case units_type_ym: value /= pow(10.0,24.0); break;
    case units_type_th: value /= 39370.1; break;
    case units_type_in: value /= 39.3701; break;
    case units_type_ft: value /= (39.3701 / 12.0); break;
    case units_type_yd: value /= (39.3701 / 36.0); break;
    case units_type_ch: value /= (39.3701 / 792.0); break;
    case units_type_fur: value /= (39.3701 / 7920.0); break;
    case units_type_mi: value /= (39.3701 / 63360.0); break;
    case units_type_lea: value /= (39.3701 / 190080.0); break;
    case units_type_ftm: value /= (39.3701 / 72.0); break;
    case units_type_cable: value /= (39.3701 / 7200.0); break;
    case units_type_nautical_mile: value /= (39.3701 / 72000.0); break;
    case units_type_link: value /= (39.3701 / 7.92); break;
    case units_type_rod: value /= (39.3701 / 198.0); break;
    case units_type_point: value /= (39.3701 * 72.0); break;
  }

    // Convert meters to "to" unitss
  switch (to_type)
  {
    case units_type_none: break;
    case units_type_Ym: value /= pow(10.0,24.0); break;
    case units_type_Zm: value /= pow(10.0,21.0); break;
    case units_type_Em: value /= pow(10.0,18.0); break;
    case units_type_Pm: value /= pow(10.0,15.0); break;
    case units_type_Tm: value /= pow(10.0,12.0); break;
    case units_type_Gm: value /= pow(10.0,9.0); break;
    case units_type_Mm: value /= pow(10.0,6.0); break;
    case units_type_km: value /= pow(10.0,3.0); break;
    case units_type_hm: value /= pow(10.0,2.0); break;
    case units_type_dam: value /= pow(10.0,1.0); break;
    case units_type_m: break;
    case units_type_dm: value *= pow(10.0,1.0); break;
    case units_type_cm: value *= pow(10.0,2.0); break;
    case units_type_mm: value *= pow(10.0,3.0); break;
    case units_type_um: value *= pow(10.0,6.0); break;
    case units_type_nm: value *= pow(10.0,9.0); break;
    case units_type_pm: value *= pow(10.0,12.0); break;
    case units_type_fm: value *= pow(10.0,15.0); break;
    case units_type_am: value *= pow(10.0,18.0); break;
    case units_type_zm: value *= pow(10.0,21.0); break;
    case units_type_ym: value *= pow(10.0,24.0); break;
    case units_type_th: value *= 39370.1; break;
    case units_type_in: value *= 39.3701; break;
    case units_type_ft: value *= (39.3701 / 12.0); break;
    case units_type_yd: value *= (39.3701 / 36.0); break;
    case units_type_ch: value *= (39.3701 / 792.0); break;
    case units_type_fur: value *= (39.3701 / 7920.0); break;
    case units_type_mi: value *= (39.3701 / 63360.0); break;
    case units_type_lea: value *= (39.3701 / 190080.0); break;
    case units_type_ftm: value *= (39.3701 / 72.0); break;
    case units_type_cable: value *= (39.3701 / 7200.0); break;
    case units_type_nautical_mile: value *= (39.3701 / 72000.0); break;
    case units_type_link: value *= (39.3701 / 7.92); break;
    case units_type_rod: value *= (39.3701 / 198.0); break;
    case units_type_point: value *= (39.3701 * 72.0); break;
  }

    // Return RETVAL
  return value;
}

