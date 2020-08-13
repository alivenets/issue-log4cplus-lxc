
Vagrant.configure(2) do |config|
    # Setup VirtualBox Provider
    config.vm.box = "bento/ubuntu-18.04"
    config.vm.box_check_update = false
    config.vm.provider "virtualbox" do |vb|
        vb.gui = false
    end

    # Make sure we have a fresh list from the package server
    config.vm.provision "shell", inline: "sudo apt update"
    # Run as shell scripts
    config.vm.provision "shell", inline: "sudo apt-get install -y build-essential cmake pkg-config gdb valgrind libtool m4 autoconf libcap-dev"

    config.vm.provision "shell", path: "install-log4cplus.sh"
    config.vm.provision "shell", inline: "sudo apt install -y libboost-log-dev"

    config.vm.provision "shell", inline: "apt-get remove -fyu --allow-downgrades --allow-remove-essential --allow-change-held-packages -fuy "\
        "lxcfs lxc lxc1 lxc-templates lxc-utils lxc-dev lxc-common liblxc1 liblxc-common liblxc-dev"

    config.vm.provision "shell", path: "install-lxc.sh"
    config.vm.provision "shell", path: "install-spdlog.sh"
    config.vm.provision "shell", path: "install-boost-log.sh"s
end

