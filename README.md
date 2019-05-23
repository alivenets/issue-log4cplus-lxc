# Log4Cplus and LXC issue reproducing example

This example reproduces the issue when using LXC together with Log4Cplus logging library.

It is related to `fork` system call in `do_lxcapi_create` call inside `liblxc`.

For LXC 2.0.8: lxccontainer.c:1505
```
    /*
     * Create the backing store
     * Note we can't do this in the same task as we use to execute the
     * template because of the way zfs works.
     * After you 'zfs create', zfs mounts the fs only in the initial
     * namespace.
     */
    pid = fork();
    if (pid < 0) {
	SYSERROR("failed to fork task for container creation template");
	goto out_unlock;
    }

    if (pid == 0) { // child
	struct bdev *bdev = NULL;

	if (!(bdev = do_bdev_create(c, bdevtype, specs))) {
	    ERROR("Error creating backing store type %s for %s",
		bdevtype ? bdevtype : "(none)", c->name);
	    exit(1);
	}

	/* save config file again to store the new rootfs location */
	if (!do_lxcapi_save_config(c, NULL)) {
	    ERROR("failed to save starting configuration for %s", c->name);
	    // parent task won't see bdev in config so we delete it
	    bdev->ops->umount(bdev);
	    bdev->ops->destroy(bdev);
	    exit(1);
	}
	exit(0);
    }
    if (wait_for_pid(pid) != 0)
	goto out_unlock;
```

In this configuration, the executable hangs forever after container is created.

## How to run

Steps:

```
$ sudo apt install vagrant
$ vagrant up
$ vagrant ssh
```

In Virtual Machine:
```
cd /vagrant
mkdir build
cd build
cmake ..
./log4cplus-lxc-issue
```

