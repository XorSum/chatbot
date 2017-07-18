#! /bin/bash
wget https://raw.githubusercontent.com/rustch3n/dgk_lost_conv/master/dgk_shooter_min.conv.zip
unzip  dgk_shooter_min.conv.zip
python3 decode_conv.py
python3 data_utils.py

