#!/bin/bash
# Release date: June 2015
# Author: Taewoo Lee, (twlee@speech.korea.ac.kr)
#
# Copyright (C) 2015 Taewoo Lee
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#
# Reference:
# [1] Taewoo Lee, Sukmoon Chang, and Dongsuk Yook, "Parallel SRP-PHAT for
#     GPUs," Computer Speech and Language, vol. 35, pp. 1-13, Jan. 2016.
#
rm -rf ./log
mkdir ./log
mkdir ./log/expM
mkdir ./log/expQ

./expM.sh
mv ./*.log ./log/expM
./expQ.sh
mv ./*.log ./log/expQ

rm -f ../../*.bin
rm -f ../../*.txt
rm -f ../../exp