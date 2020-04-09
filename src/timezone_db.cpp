#include "timezone_db.h"
#include <boost/date_time/local_time/local_time_io.hpp>
#include <boost/date_time/local_time/tz_database.hpp>

void TimeZoneDB::read(const std::string &tzdb_filepath) MAYTHROW
{
    boost::local_time::tz_database tz_db;
    tz_db.load_from_file(tzdb_filepath);
    for (const auto &region : tz_db.region_list()) {
        auto tz = tz_db.time_zone_from_region(region);
        auto dst_abbrev = tz->dst_zone_abbrev();
        if (not dst_abbrev.empty()) {
            tz_abbrev_db[dst_abbrev] = tz;
        }
        auto std_abbrev = tz->std_zone_abbrev();
        if (not std_abbrev.empty()) {
            tz_abbrev_db[std_abbrev] = tz;
        }
    }
}

void TimeZoneDB::query(const std::string &abbrev, std::ostream &out) MAYTHROW
{
    auto now = boost::posix_time::second_clock::universal_time();
    out.imbue(std::locale(out.getloc(), new boost::local_time::local_time_facet("%a %b %e %T %z %Y")));
    out << boost::local_time::local_date_time(now, tz_abbrev_db.at(abbrev)) << std::endl;
}
