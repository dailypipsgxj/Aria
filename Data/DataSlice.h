#pragma once
#ifdef DATA_EXPORTS
#define DATA_API __declspec(dllexport)
#else
#define DATA_API __declspec(dllimport)
#endif

#include <boost/date_time.hpp>
#include <map>
#include <string>

#include "global.h"
#include "Resolution.h"
#include "Symbol.h"

class OHLCV;

class DATA_API DataSlice
{
public:
   DataSlice(void);
   DataSlice(const boost::posix_time::ptime& starttime, Resolution res);
   ~DataSlice(void);

public:
   Resolution get_resolution() { return m_res; }
   const boost::posix_time::ptime& get_start_time() { return m_starttime; }
   const boost::posix_time::ptime& get_end_time() { return m_endtime; }
   bool add_data(Symbol symbol, const boost::shared_ptr<OHLCV>& p_data);
   bool add_indicator(Symbol symbol, const std::string& indicator_name, double value);
   boost::shared_ptr<OHLCV> get_data(const Symbol& symbol) ;
   boost::shared_ptr<OHLCV> operator[] (const Symbol& symbol) { return get_data(symbol); }

private:
   Resolution m_res;
   boost::posix_time::ptime m_starttime;
   boost::posix_time::ptime m_endtime;
   std::map<Symbol, boost::shared_ptr<OHLCV> > m_data;
   std::map<Symbol, std::map<std::string, double> > m_indicators;
};

