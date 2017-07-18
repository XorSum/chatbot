#!/bin/bash

serve_arg="false"
test_arg="false"
bleu_arg="-1"
if [ ! -z $1 ]
then
    if [ $1 == "test" ]
    then
        test_arg="true"
        serve_arg="false"
    elif [ $1 == "serve" ]
    then
        test_arg="false"
        serve_arg="true"
    elif [ $1 == "bleu" ]
    then
        if [ ! -z $2 ]
        then
            bleu_arg="$2"
        fi  
    fi
fi

python3 s2s.py \
--size 1024 \
--num_layers 3 \
--num_epoch 5 \
--batch_size 64 \
--num_per_epoch 500000 \
--test $test_arg \
--serve $serve_arg \
--bleu $bleu_arg \
--model_dir ./model/model1 \
--port 8082
