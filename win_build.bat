@echo off
rem Windows version of the compile script, requires 32bit cURL in PATH
rem currently errors with this one
g++ *.cpp -DCURL_STATICLIB -I curl\include -L curl\lib -lcurldll -lssh2 -lidn -lrtmp -lssl -lcrypto -lz -lws2_32 -lwldap32