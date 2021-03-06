# KERNEL_LOCALVERSION can be set to add a tag to the end of the
# kernel version string.  such as the commit id
KERNEL_LOCALVERSION ?= ""

# Check the defconfig file and see if it points to an in kernel
# defconfig that should be used, or if it is a complete config file

addtask setup_defconfig before do_configure after do_patch
do_setup_defconfig() {
    # Always copy the defconfig file to .config to keep consistency
    # between the case where there is a real config and the in kernel
    # tree config
    cp ${WORKDIR}/defconfig ${B}/.config
}

# define our own do_configure that will:
#   1. Check the .config file and see if string use-kernel-config= is present
#   2. If the use-kernel-config string is present parse out the config to use
#      and run make ${config}
#   3. else run yes '' | oe_runmake oldconfig like the default do_configure
#      does
do_configure() {
    echo ${KERNEL_LOCALVERSION} > ${B}/.scmversion
    #echo ${KERNEL_LOCALVERSION} > ${S}/.scmversion
    config=`cat ${B}/.config | grep use-kernel-config | cut -d= -f2`
    if [ "x${config}" != "x" ]
    then
        cd ${S}
        oe_runmake O=${B} ${config}
    else
        cd ${S}
        yes '' | oe_runmake O=${B} oldconfig
    fi
}
