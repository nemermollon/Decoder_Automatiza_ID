#!/bin/bash

gcc extrai_dados_automatiza.c -o extrai_dados_automatiza
./extrai_dados_automatiza $(ls *.dat | grep 'user' | sort -r | head -n1) > users
./extrai_dados_automatiza $(ls *.dat | grep 'user' | sort -r | head -n1) | cut -d ":" -f3 | tr -d ' ' > ids
paste ids users | sort
