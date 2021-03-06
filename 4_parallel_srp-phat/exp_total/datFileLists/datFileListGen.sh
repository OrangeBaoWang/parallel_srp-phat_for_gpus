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
# Out: datFileListToProcess_Mch_Dir.txt
#
rm -f ./*.txt

for m in 8 16 32; do
  for dir in 090 120 150 180; do
    touch "datFileListToProcess_$m""ch_$dir.txt"
    if ((m==8)); then
      echo "../1_gen_simul_data/simul_data/$dir/2m/044cm/reverb430/info.dat" >> "datFileListToProcess_$m""ch_$dir.txt"
			for ch in 0 2 10 12 14 16 28 30; do
				echo "../1_gen_simul_data/simul_data/$dir/2m/044cm/reverb430/""$ch"".dat" >> "datFileListToProcess_$m""ch_$dir.txt"
			done
    elif ((m==16)); then
      echo "../1_gen_simul_data/simul_data/$dir/2m/044cm/reverb430/info.dat" >> "datFileListToProcess_$m""ch_$dir.txt"
      for ch in 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30; do
				echo "../1_gen_simul_data/simul_data/$dir/2m/044cm/reverb430/""$ch"".dat" >> "datFileListToProcess_$m""ch_$dir.txt"
			done
		elif ((m==32)); then	
      echo "../1_gen_simul_data/simul_data/$dir/2m/044cm/reverb430/info.dat" >> "datFileListToProcess_$m""ch_$dir.txt"
			for ((ch=0; ch<$m; ch++));	do
				echo "../1_gen_simul_data/simul_data/$dir/2m/044cm/reverb430/""$ch"".dat" >> "datFileListToProcess_$m""ch_$dir.txt"
			done
		fi
	done
done
