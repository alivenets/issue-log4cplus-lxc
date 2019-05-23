#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/initializer.h>
#include <log4cplus/layout.h>
#include <log4cplus/log4cplus.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <lxc/lxccontainer.h>

void tryCreateContainer()
{
    auto logger = log4cplus::Logger::getInstance("main");

    LOG4CPLUS_DEBUG(logger, "Creating container");

    const char *containerID = "TestForkFault";

    // Creating a new LXC pointer
    // After this point all failures should do rollback
    struct lxc_container *container = lxc_container_new(containerID, nullptr);
    if (!container) {
        LOG4CPLUS_ERROR(logger, "Error creating a new container");
        return;
    }

    if (container->is_defined(container)) {
        LOG4CPLUS_ERROR(logger, "ContainerID " << containerID << "' is already in use.");
        lxc_container_put(container);
        return;
    }

    LOG4CPLUS_DEBUG(logger, "Successfully created container object");

    int flags = 0;
    std::vector<char *> argv;

    container->set_config_item(container, "lxc.logfile", "/tmp/lxc.log");
    container->set_config_item(container, "lxc.loglevel", "0");

    if (!container->create(container, "busybox", nullptr, nullptr, flags, &argv[0])) {
        LOG4CPLUS_ERROR(logger, "Error creating container");
        lxc_container_put(container);
        return;
    }

    LOG4CPLUS_DEBUG(logger, "Container is created");

    char commandEnv[] = "env";
    char commandSleep[] = "/bin/sleep";
    char commandSleepTime[] = "100000000";
    char* const args[] = { commandEnv, commandSleep, commandSleepTime, nullptr };

    if (!container->start(container, false, args)) {
        LOG4CPLUS_ERROR(logger, "Error starting container");
        lxc_container_put(container);
        return;
    }

    LOG4CPLUS_DEBUG(logger, "Container started");

    pid_t pid = container->init_pid(container);

    if (!container->stop(container)) {
        LOG4CPLUS_ERROR(logger, "Container stopped");
    }

    container->destroy(container);

    lxc_container_put(container);
}

int main()
{
    log4cplus::Initializer initializer;

    log4cplus::BasicConfigurator::doConfigure();

    auto logger = log4cplus::Logger::getInstance("main");

    LOG4CPLUS_WARN(logger, "Hello, World! " << getpid());

    tryCreateContainer();

    return 0;
}
