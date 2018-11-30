cd clib
make && cp libuuidx.so /usr/lib64/
echo make ok
cd ../lib
cp resty/* /usr/local/share/lua/5.1/resty/
echo cp to /usr/local/share/lua/5.1/resty/
cd ../../
