pkgname=juiced-willv19
pkgver=1.0.0
pkgrel=1
pkgdesc='A lightweight battery daemon.'
arch=('i686' 'x86_64')
license=('MIT')
depends=('libnotify')
url="https://github.com/drkhsh/juiced"
source=(arg.h concat.h strlcat.h strlcpy.h config.def.h config.mk juiced.1 juiced.c LICENSE Makefile README)
sha256sums=(SKIP SKIP SKIP SKIP SKIP SKIP SKIP SKIP SKIP SKIP SKIP)

prepare() {
  cd $srcdir
}

build() {
  cd $srcdir
  make clean
}

package() {
  cd $srcdir
  make DESTDIR="$pkgdir" install
  install -Dm644 LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
  install -Dm644 README "$pkgdir/usr/share/doc/$pkgname/README"
}
