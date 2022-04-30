./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 1 --length 0.001 --noise 0.0 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_length001.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 1 --length 0.0025 --noise 0.0 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_length0025.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 1 --length 0.005 --noise 0.0 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_length005.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 1 --length 0.01 --noise 0.0 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_length01.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 1 --length 0.02 --noise 0.0 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_length02.png --resolution 720 --samples 30