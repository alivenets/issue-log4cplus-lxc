#ifndef LOG4CPLUS_WRAPPER_H_
#define LOG4CPLUS_WRAPPER_H_

#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/initializer.h>
#include <log4cplus/layout.h>
#include <log4cplus/log4cplus.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#define LOG_ERROR(args...) do { LOG4CPLUS_ERROR(args); } while(0)
#define LOG_WARN(args...) do { LOG4CPLUS_WARN(args); } while(0)
#define LOG_INFO(args...) do { LOG4CPLUS_INFO(args); } while(0)
#define LOG_DEBUG(args...) do { LOG4CPLUS_DEBUG(args); } while(0)
#define LOG_GET_LOGGER(args...) log4cplus::Logger::getInstance(args)
#define LOG_CONFIGURE()  log4cplus::Initializer initializer; do { log4cplus::BasicConfigurator::doConfigure(); } while(0)

#endif
