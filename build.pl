#! /bin/env perl
#
# iceplayer项目编译脚本
# 
# Author: gjp1120@gmail.com
# GPLv2

use Carp;

use strict;
use warnings;

use 5.010;

mkdir 'Build';
chdir 'Build';

chomp (my $CMAKE = `which cmake`);
if (! -e $CMAKE )
{
  croak q{please install 'cmake' first};
}

system("$CMAKE ..");
system('make')
