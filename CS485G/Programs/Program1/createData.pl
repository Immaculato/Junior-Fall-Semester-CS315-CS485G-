#!/usr/bin/perl -w
# createData.pl
# Raphael Finkel © 2015

use strict;

binmode STDOUT, ":raw";

print pack('i', 10);
print pack('h8',"AAAAAAAA");
print pack('h8',"55555555");
print pack('h8',"0000FFFF");
print pack('h8',"FFFF0000");
print pack('h8',"0F0F0F0F");
print pack('h8',"F0F0F0F0");
print pack('h8',"00000001");
print pack('h8',"10000000");
print pack('h8',"11111111");
print pack('h8',"00000000");

