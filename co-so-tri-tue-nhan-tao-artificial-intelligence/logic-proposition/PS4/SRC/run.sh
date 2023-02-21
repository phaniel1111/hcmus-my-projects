#!/bin/bash
count=$(ls -l \INPUT | grep ^- | wc -l)
						
python main.py $count
echo DA TIM THAY $count INPUT
echo DA HOAN THANH, XIN HAY KIEM TRA THU MUC /OUTPUT
sleep 4s

EXIT