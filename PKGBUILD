pkgname="Gnoridor"
pkgver=1.0
pkgrel=1
arch=('x86_64')
pkgdesc="Quoridor game using GTK"
depends=("${MINGW_PACKAGE_PREFIX}-gtk3>=3.20")
makedepends=("${MINGW_PACKAGE_PREFIX}-gcc"
            "${MINGW_PACKAGE_PREFIX}-pkg-config")

license=("GPL")
sources=("..")

prepare() {
    echo prepare
    cd ..
    pwd
    mkdir buildir
    meson.py buildir
}

build() {
    echo build
    cd ..
    cd buildir
    ninja
}

package() {
    echo hey
    cd ..
    cd buildir
    ninja install
}