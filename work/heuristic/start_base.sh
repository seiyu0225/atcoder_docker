for ((cnt=0; cnt<100; cnt++))
do
    echo $cnt
    if [ $cnt -ge 10 ]; then
        python3 base_line.py < ./in/00$cnt.txt > ./out/base_line/base_line_00$cnt.txt
    else
        python3 base_line.py < ./in/000$cnt.txt > ./out/base_line/base_line_000$cnt.txt
    fi
done