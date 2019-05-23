
Vagrant.configure(2) do |config|
    # Setup VirtualBox Provider
    config.vm.box = "bento/ubuntu-16.04"
    config.vm.box_check_update = false
    config.vm.provider "virtualbox" do |vb|
        vb.gui = false
    end

    # Sync the repo root with this path in the VM
    config.vm.synced_folder "./", "/home/ubuntu/issue-log4cplus-lxc/", create: true

    # Make sure we have a fresh list from the package server
    config.vm.provision "shell", inline: "sudo apt update"
    # Run as shell scripts
    config.vm.provision "shell", inline: "sudo apt-get install -y build-essential cmake pkg-config lxc lxc-dev gdb valgrind"

    config.vm.provision "shell", inline: "/vagrant/install-log4cplus.sh"
    
end

