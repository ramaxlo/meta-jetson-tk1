SUMMARY = "Base systemd files for TK1"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/LICENSE;md5=4d92cd373abda3937c2bc47fbc49d690"

PR = "r1"

DEPENDS = "systemd"
inherit allarch

SRC_URI = "file://wired.network"

S = "${WORKDIR}"

do_install() {
	install -d ${D}${sysconfdir}/systemd/network
	install -m 0644 ${WORKDIR}/wired.network ${D}${sysconfdir}/systemd/network
}
