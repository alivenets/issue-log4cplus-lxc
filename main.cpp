#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <lxc/lxccontainer.h>

#include "log_wrapper.h"

void tryCreateContainer()
{
    auto logger = LOG_GET_LOGGER("main");

    LOG_DEBUG(logger, "Creating container");

    const char *containerID = "TestForkFault";

    // Creating a new LXC pointer
    // After this point all failures should do rollback
    struct lxc_container *container = lxc_container_new(containerID, nullptr);
    if (!container) {
        LOG_ERROR(logger, "Error creating a new container");
        return;
    }

    if (container->is_defined(container)) {
        LOG_ERROR(logger, "ContainerID is already in use");
        lxc_container_put(container);
        return;
    }

    LOG_DEBUG(logger, "Successfully created container object");

    int flags = 0;
    std::vector<char *> argv{nullptr};

    container->set_config_item(container, "lxc.logfile", "/tmp/lxc.log");
    container->set_config_item(container, "lxc.loglevel", "0");

    if (!container->create(container, "busybox", nullptr, nullptr, flags, &argv[0])) {
        LOG_ERROR(logger, "Error creating container");
        lxc_container_put(container);
        return;
    }

    LOG_DEBUG(logger, "Container is created");

    char commandEnv[] = "env";
    char commandSleep[] = "/bin/sleep";
    char commandSleepTime[] = "100000000";
    char* const args[] = { commandEnv, commandSleep, commandSleepTime, nullptr };

    if (!container->start(container, false, args)) {
        LOG_ERROR(logger, "Error starting container");
        lxc_container_put(container);
        return;
    }

    LOG_DEBUG(logger, "Container started");

    pid_t pid = container->init_pid(container);

    // Execute function in container and log from there

    if (!container->stop(container)) {
        LOG_ERROR(logger, "Failed to stop container");
    }

    LOG_DEBUG(logger, "Container stopped");
    container->destroy(container);
    
    LOG_DEBUG(logger, "Container destroyed");

    lxc_container_put(container);
}

int main()
{
    LOG_CONFIGURE();

    auto logger = LOG_GET_LOGGER("main");

    LOG_WARN(logger, "Hello, World!");

    tryCreateContainer();

    return 0;
}
