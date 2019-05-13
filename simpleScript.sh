#!/bin/bash
set -u

userList=$(cat users.txt)
for user in ${userList}
do
    home=/home/${user}/workspace
    echo ${user} >> results.txt
    source=$(find ${home} "primes.c")
    cat ${source}
    if((${source} == 0))
    then
        program=$(gcc -o ${source} primes)
        echo "0" >> results.txt
        if((${program}==0))
        then
            echo "0" >> results.txt
            gcc -o ${source} primes
            test=$(./primes 10 20) > testResult.txt
            if(($(diff testResult.txt correctOutput.txt)==0))
            then
                echo "0" >> results.txt
            else
                echo "-1" >> results.txt
            fi
        else
            echo "-1 -1" >> results.txt
        fi
    else
        echo "-1 -1 -1" >> results.txt
    fi
done