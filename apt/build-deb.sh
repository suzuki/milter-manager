#!/bin/sh

PACKAGE=$(cat /tmp/build-package)
USER_NAME=$(cat /tmp/build-user)
VERSION=$(cat /tmp/build-version)
DEPENDED_PACKAGES=$(cat /tmp/depended-packages)
BUILD_SCRIPT=/tmp/build-deb-in-chroot.sh

run()
{
    "$@"
    if test $? -ne 0; then
	echo "Failed $@"
	exit 1
    fi
}

if [ ! -x /usr/bin/aptitude ]; then
    run apt-get install -y aptitude
fi
run aptitude update -V -D
run aptitude safe-upgrade -V -D -y

if test "$(lsb_release --id --short)" = "Ubuntu"; then
    run aptitude install -V -D -y language-pack-ja
else
    if ! dpkg -l | grep 'ii  locales' > /dev/null 2>&1; then
	run aptitude install -V -D -y locales
	run dpkg-reconfigure locales
    fi
fi

run aptitude install -V -D -y devscripts ${DEPENDED_PACKAGES}
run aptitude clean

if ! id $USER_NAME >/dev/null 2>&1; then
    run useradd -m $USER_NAME
fi

cat <<EOF > $BUILD_SCRIPT
#!/bin/sh

rm -rf build
mkdir -p build

cp /tmp/${PACKAGE}-${VERSION}.tar.gz build/${PACKAGE}_${VERSION}.orig.tar.gz
cd build
tar xfz ${PACKAGE}_${VERSION}.orig.tar.gz
cd ${PACKAGE}-${VERSION}/
cp -rp /tmp/${PACKAGE}-debian debian
if ! aptitude show librrd-ruby1.8 > /dev/null 2>&1; then
    sed -i'' -e 's/librrd-ruby1\.8/rrdtool/g' debian/control
fi
debuild -us -uc
EOF

run chmod +x $BUILD_SCRIPT
run su - $USER_NAME $BUILD_SCRIPT
