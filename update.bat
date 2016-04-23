cp ../Snefru.cpp		Snefru/Snefru.cpp
cp ../Snefru_F.cpp		Snefru/Snefru_F.cpp
cp ../MD4.cpp			MD4.cpp
cp ../MD5.cpp			MD5/MD5.cpp
cp ../MD5_File.cpp		MD5/MD5_File.cpp
cp ../SHA2.cpp			SHA2/SHA2.cpp
cp ../SHA2_F.cpp		SHA2/SHA2_F.cpp
cp ../RIPE_MD.cpp		RIPE-MD/RIPE_MD.cpp
cp ../RIPEMD_F.cpp		RIPE-MD/RIPEMD_F.cpp

cp ../../INCLUDE/Snefru.h	Snefru/Snefru.h

cp ../ALL_HASH.cpp		ALL_HASH/ALL_HASH.cpp
cp ../../INCLUDE/SNEFRU_F.h	ALL_HASH/SNEFRU_F.h
cp ../../INCLUDE/MD5_FILE.h	ALL_HASH/MD5_FILE.h
cp ../../INCLUDE/SHA2_F.h	ALL_HASH/SHA2_F.h
cp ../../INCLUDE/RIPEMD_F.h	ALL_HASH/RIPEMD_F.h

git add .
git commit -m "$1"
git push -u origin master
