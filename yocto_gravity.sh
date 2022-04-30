./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 6 --length 0.005 --noise 0.001 --gravity 0.0001 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny03_gravity0001.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 6 --length 0.005 --noise 0.001 --gravity 0.0005 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny03_gravity0005.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 6 --length 0.005 --noise 0.001 --gravity 0.001 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny03_gravity001.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 6 --length 0.005 --noise 0.001 --gravity 0.005 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_gravity005.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 6 --length 0.005 --noise 0.001 --gravity 0.0075 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_gravity0075.png --resolution 720 --samples 30
# ./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 6 --length 0.005 --noise 0.001 --gravity 0.1 --radius 0.0001
# ./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_gravity1.png --resolution 720 --samples 30
