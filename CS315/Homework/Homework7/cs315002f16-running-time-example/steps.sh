#cs315002 Fall 2016 CS-UK JWJ
#steps to perform experiments with FLoyd_Warshall
echo "---START------\n"
echo "cat steps.sh\n"
cat steps.sh
echo "--------------\n"
echo "cat FloydWarshall-instrumented.cpp\n"
cat FloydWarshall-instrumented.cpp
echo "--------------\n"
echo "g++ --std=c++11 FloydWarshall-instrumented.cpp\n"
g++ --std=c++11 FloydWarshall-instrumented.cpp
echo "--------------\n"
echo "cat main_1.in\n"
cat main_1.in
echo "--------------\n"
echo "./a.out < main_1.in > a.dat\n"
./a.out < main_1.in > a.dat
echo "--------------\n"
echo "cat a.dat\n"
cat a.dat
echo "--------------\n"
echo "cat gp.scrip\n"
cat gp.script
echo "--------------\n"
echo "gnuplot gp.script\n"
gnuplot gp.script
echo "--------------\n"
echo "gimp data_p.png\n"
gimp data_p.png
echo "---END--------\n"
