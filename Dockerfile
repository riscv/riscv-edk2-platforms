# Since we need at least qemu 5.2 we need at least ubuntu 21.04
FROM ubuntu:21.04

RUN apt-get update
RUN apt-get -y install qemu-system-misc

# Copies your code file from your action repository to the filesystem path `/` of the container
COPY run-virt.sh /run-virt.sh
COPY run-u540.sh /run-u540.sh
