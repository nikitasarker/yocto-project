./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 6 --length 0.005 --noise 0.0001 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_noise0001.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 6 --length 0.005 --noise 0.00025 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_noise00025.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 6 --length 0.005 --noise 0.0005 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_noise0005.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 6 --length 0.005 --noise 0.001 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_noise001.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 6 --length 0.005 --noise 0.0025 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_noise0025.png --resolution 720 --samples 30
./bin/yshape hair --shape tests/03_hair2/shapes/bunny.ply --output tests/03_hair2/shapes/bunny_hair.ply --hairs 100000 --steps 6 --length 0.005 --noise 0.005 --gravity 0.0 --radius 0.0001
./bin/yscene render --scene tests/03_hair2/hair2.json --output out/bunny01_noise005.png --resolution 720 --samples 30