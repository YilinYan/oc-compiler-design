mkdir TEST
rm TEST/*.*
mv oc TEST/
cd TEST
for filename in ../test/struct/*.oc; do
    ./oc $filename
done
mv oc ../
