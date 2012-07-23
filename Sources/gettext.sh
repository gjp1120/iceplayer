#! /bin/sh

xgettext -o ../data/iceplayer.pot -k_ -kN_ *.[ch]

cd ../data/
msgmerge -U zh_CN.po iceplayer.pot

read -p "按任意键继续" TEMP
msgfmt -o locale/zh_CN/iceplayer.mo zh_CN.po
sudo cp locale/zh_CN/iceplayer.mo /usr/share/locale/zh_CN/LC_MESSAGES/

