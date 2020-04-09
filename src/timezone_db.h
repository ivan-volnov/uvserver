#ifndef TIMEZONE_DB_H
#define TIMEZONE_DB_H

#include <boost/date_time/local_time/local_time_types.hpp>
#include <unordered_map>
#include "tools/global.h"

class TimeZoneDB
{
public:
    void read(const std::string &tzdb_filepath) MAYTHROW;
    void query(const std::string &abbrev, std::ostream &out) MAYTHROW;

private:
    std::unordered_map<std::string, boost::local_time::time_zone_ptr> tz_abbrev_db;
};

#endif // TIMEZONE_DB_H
