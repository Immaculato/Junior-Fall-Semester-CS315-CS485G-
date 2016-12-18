#!/bin/bash 
COUNTER=10
echo '' > experiment.dat
until [  $COUNTER -gt 250 ]; do
	./inputGenerator $COUNTER | ./uva00567 >> experiment.dat
	let COUNTER+=10
done
