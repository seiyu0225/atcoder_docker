for ((cnt=0; cnt<100; cnt++))
do
    echo $cnt
    if [ $cnt -ge 10 ]; then
        python3 now2.py < ./in/00$cnt.txt > ./out/now/now_00$cnt.txt
    else
        python3 now2.py < ./in/000$cnt.txt > ./out/now/now_000$cnt.txt
    fi
done