#ifndef SPDLOG_WRAPPER_H_
#define SPDLOG_WRAPPER_H_

#include <spdlog/spdlog.h>

#define LOG_ERROR(logger,...) spdlog::error(__VA_ARGS__)
#define LOG_WARN(logger,...) spdlog::warn(__VA_ARGS__)
#define LOG_INFO(logger,...) spdlog::info(__VA_ARGS__)
#define LOG_DEBUG(logger,...) spdlog::debug(__VA_ARGS__)
#define LOG_GET_LOGGER(...) nullptr
#define LOG_CONFIGURE(...) do { spdlog::set_level(spdlog::level::debug); } while(0)

#endif