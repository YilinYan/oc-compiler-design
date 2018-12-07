mv oc TEST/
cd TEST
for filename in ../test/*.oc; do
    ./oc $filename
done
mv oc ../
