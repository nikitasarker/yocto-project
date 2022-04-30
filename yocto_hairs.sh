./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 10000 --steps 1 --length 0.005 --noise 0.0 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_hairs10000.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 50000 --steps 1 --length 0.005 --noise 0.0 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_hairs50000.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 1 --length 0.005 --noise 0.0 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_hairs100000.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 200000 --steps 1 --length 0.005 --noise 0.0 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_hairs200000.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 500000 --steps 1 --length 0.005 --noise 0.0 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_hairs500000.png --resolution 720 --samples 30