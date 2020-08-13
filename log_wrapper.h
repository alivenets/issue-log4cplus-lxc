#ifndef LOG_WRAPPER_H_
#define LOG_WRAPPER_H_

#if USE_LOG4CPLUS
#  include "log4cplus_wrapper.h"
#elif USE_BOOST_LOG
#  include "boost_log_wrapper.h"
#elif USE_SPDLOG
#  include "spdlog_wrapper.h"
#endif

#endif
