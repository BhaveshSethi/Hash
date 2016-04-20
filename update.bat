cp ../Snefru.cpp		Snefru/Snefru.cpp
cp ../MD4.cpp			MD4.cpp
cp ../MD5.cpp			MD5.cpp

cp ../../INCLUDE/Snefru.h	Snefru/Snefru.h
git add .
git commit -m "$1"
git push -u origin master
