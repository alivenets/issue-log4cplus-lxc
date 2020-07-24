#ifndef LOG4CPLUS_WRAPPER_H_
#define LOG4CPLUS_WRAPPER_H_

#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/initializer.h>
#include <log4cplus/layout.h>
#include <log4cplus/log4cplus.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#define LOG_ERROR(...) LOG4CPLUS_ERROR(__VA_ARGS__)
#define LOG_WARN(...) LOG4CPLUS_WARN(__VA_ARGS__)
#define LOG_INFO(...) LOG4CPLUS_INFO(__VA_ARGS__)
#define LOG_DEBUG(...) LOG4CPLUS_DEBUG(__VA_ARGS__)
#define LOG_GET_LOGGER(...) log4cplus::Logger::getInstance(__VA_ARGS__)
#define LOG_CONFIGURE()  log4cplus::Initializer initializer; do { log4cplus::BasicConfigurator::doConfigure(); } while(0)

#endif