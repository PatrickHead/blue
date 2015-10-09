/*!
    @file units.h

    @brief HEADER_BRIEF

    @timestamp Tue, 11 Nov 2014 07:22:33 +0000

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

    @file units.h

    HEADER_BRIEF

    HEADER_DETAILS

  */

#ifndef UNITS_H
#define UNITS_H

  /*!
    @brief TYPEDEF_BRIEF
  */

typedef enum
{
    // Default
  units_type_none,
    // SI units of length
  units_type_Yottameter,
  units_type_Ym = units_type_Yottameter,
  units_type_Zettameter,
  units_type_Zm = units_type_Zettameter,
  units_type_Exameter,
  units_type_Em = units_type_Exameter,
  units_type_Petameter,
  units_type_Pm = units_type_Petameter,
  units_type_Terameter,
  units_type_Tm = units_type_Terameter,
  units_type_Gigameter,
  units_type_Gm = units_type_Gigameter,
  units_type_Megameter,
  units_type_Mm = units_type_Megameter,
  units_type_kilometer,
  units_type_km = units_type_kilometer,
  units_type_hectometer,
  units_type_hm = units_type_hectometer,
  units_type_decameter,
  units_type_dam = units_type_decameter,
  units_type_meter,
  units_type_m = units_type_meter,
  units_type_decimeter,
  units_type_dm = units_type_decimeter,
  units_type_centimeter,
  units_type_cm = units_type_centimeter,
  units_type_millimeter,
  units_type_mm = units_type_millimeter,
  units_type_micrometer,
  units_type_um = units_type_micrometer,
  units_type_nanometer,
  units_type_nm = units_type_nanometer,
  units_type_picometer,
  units_type_pm = units_type_picometer,
  units_type_femtometer,
  units_type_fm = units_type_femtometer,
  units_type_attometer,
  units_type_am = units_type_attometer,
  units_type_zeptometer,
  units_type_zm = units_type_zeptometer,
  units_type_yoctometer,
  units_type_ym = units_type_yoctometer,
    // Imperial units of length
  units_type_thou,
  units_type_th = units_type_thou,
  units_type_inch,
  units_type_in = units_type_inch,
  units_type_foot,
  units_type_ft = units_type_foot,
  units_type_yard,
  units_type_yd = units_type_yard,
  units_type_chain,
  units_type_ch = units_type_chain,
  units_type_furlong,
  units_type_fur = units_type_furlong,
  units_type_mile,
  units_type_mi = units_type_mile,
  units_type_league,
  units_type_lea = units_type_league,
  units_type_fathom,
  units_type_ftm = units_type_fathom,
  units_type_cable,
  units_type_nautical_mile,
  units_type_link,
  units_type_rod,
    // printing units
  units_type_point,
} units_t;

units_t str2units(char* s);
const char* units2str(units_t t);
double units_convert(double value, units_t from_type, units_t to_type);

#endif // UNITS_H

