#ifndef BOOST_LOG_WRAPPER_H_
#define BOOST_LOG_WRAPPER_H_

#include <boost/log/trivial.h>

#define LOG_ERROR(logger,...) BOOST_LOG_TRIVIAL(error) << __VA_ARGS__
#define LOG_WARN(logger,...) BOOST_LOG_TRIVIAL(warn) << __VA_ARGS__
#define LOG_INFO(logger,...) BOOST_LOG_TRIVIAL(info) << __VA_ARGS__
#define LOG_DEBUG(logger,...) BOOST_LOG_TRIVIAL(debug) << __VA_ARGS__
#define LOG_GET_LOGGER(...) nullptr
#define LOG_CONFIGURE() do {} while(0)
#endif
