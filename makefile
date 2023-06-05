all: 3DFase1 3DFase2 3DFase3 3DFase4

fase1:
	rm -r build || echo "build removido"
	cmake -S ./Fase_1/src -B build
	cmake --build build/

3dFase1: fase1
	./build/generator.exe cone 1 2 4 3 ./Fase_1/outputs/cone_1_2_4_3.3d
	./build/generator.exe sphere 1 10 10 ./Fase_1/outputs/sphere_1_10_10.3d 
	./build/generator.exe box 2 3 ./Fase_1/outputs/box_2_3.3d
	./build/generator.exe plane 2 3 ./Fase_1/outputs/plane_2_3.3d

3DFase1: fase4
	./build/generator.exe cone 1 2 4 3 ./Fase_1/outputs/cone_1_2_4_3.3d
	./build/generator.exe sphere 1 10 10 ./Fase_1/outputs/sphere_1_10_10.3d 
	./build/generator.exe box 2 3 ./Fase_1/outputs/box_2_3.3d
	./build/generator.exe plane 2 3 ./Fase_1/outputs/plane_2_3.3d

test_1_1:
	cd build/ && ./engine.exe ../Fase_1/configs/test_1_1.xml

test_1_2:
	cd build/ && ./engine.exe ../Fase_1/configs/test_1_2.xml

test_1_3:
	cd build/ && ./engine.exe ../Fase_1/configs/test_1_3.xml

test_1_4:
	cd build/ && ./engine.exe ../Fase_1/configs/test_1_4.xml

test_1_5:
	cd build/ && ./engine.exe ../Fase_1/configs/test_1_5.xml

fase2:
	rm -r build || echo "build removido"
	cmake -S ./Fase_2/src -B build
	cmake --build build/

3dFase2: fase2
	./build/generator.exe cone 1 2 4 3 ./Fase_2/outputs/cone_1_2_4_3.3d
	./build/generator.exe sphere 1 10 10 ./Fase_2/outputs/sphere_1_10_10.3d 
	./build/generator.exe box 2 3 ./Fase_2/outputs/box_2_3.3d
	./build/generator.exe plane 2 3 ./Fase_2/outputs/plane_2_3.3d
	./build/generator.exe sphere 1 40 40 ./Fase_2/outputs/sphere.3d
	./build/generator.exe ring 7 9 30 ./Fase_2/outputs/ring.3d
	./build/generator.exe sphere 1 8 8 ./Fase_2/outputs/sphere_1_8_8.3d

3DFase2: fase4
	./build/generator.exe cone 1 2 4 3 ./Fase_2/outputs/cone_1_2_4_3.3d
	./build/generator.exe sphere 1 10 10 ./Fase_2/outputs/sphere_1_10_10.3d 
	./build/generator.exe box 2 3 ./Fase_2/outputs/box_2_3.3d
	./build/generator.exe plane 2 3 ./Fase_2/outputs/plane_2_3.3d
	./build/generator.exe sphere 1 40 40 ./Fase_2/outputs/sphere.3d
	./build/generator.exe ring 7 9 30 ./Fase_2/outputs/ring.3d
	./build/generator.exe sphere 1 8 8 ./Fase_2/outputs/sphere_1_8_8.3d

test_2_1:
	cd build/ && ./engine.exe ../Fase_2/configs/demos/test_2_1.xml

test_2_2:
	cd build/ && ./engine.exe ../Fase_2/configs/demos/test_2_2.xml

test_2_3:
	cd build/ && ./engine.exe ../Fase_2/configs/demos/test_2_3.xml

test_2_4:
	cd build/ && ./engine.exe ../Fase_2/configs/demos/test_2_4.xml

solar2:
	cd build/ && ./engine.exe ../Fase_2/configs/solar.xml

solarAligned2:
	cd build/ && ./engine.exe ../Fase_2/configs/solarAligned.xml

solarRotatedInLine2:
	cd build/ && ./engine.exe ../Fase_2/configs/solarRotatedinLine.xml

fase3:
	rm -r build || echo "build removido"
	cmake -S ./Fase_3/src -B build
	cmake --build build/

3dFase3: fase3
	./build/generator.exe cone 1 2 4 3 ./Fase_3/outputs/cone_1_2_4_3.3d
	./build/generator.exe sphere 1 10 10 ./Fase_3/outputs/sphere_1_10_10.3d 
	./build/generator.exe box 2 3 ./Fase_3/outputs/box_2_3.3d
	./build/generator.exe plane 2 3 ./Fase_3/outputs/plane_2_3.3d
	./build/generator.exe patch 10 ./Fase_3/patches/teapot.patch ./Fase_3/outputs/bezier_10.3d
	./build/generator.exe ring 7 9 30 ./Fase_3/outputs/ring.3d

3DFase3: fase4
	./build/generator.exe cone 1 2 4 3 ./Fase_3/outputs/cone_1_2_4_3.3d
	./build/generator.exe sphere 1 10 10 ./Fase_3/outputs/sphere_1_10_10.3d 
	./build/generator.exe box 2 3 ./Fase_3/outputs/box_2_3.3d
	./build/generator.exe plane 2 3 ./Fase_3/outputs/plane_2_3.3d
	./build/generator.exe patch ./Fase_3/patches/teapot.patch 10 ./Fase_3/outputs/bezier_10.3d
	./build/generator.exe ring 7 9 30 ./Fase_3/outputs/ring.3d

test_3_1:
	cd build/ && ./engine.exe ../Fase_3/configs/demos/test_3_1.xml

test_3_2:
	cd build/ && ./engine.exe ../Fase_3/configs/demos/test_3_2.xml

solarAnimated3:
	cd build/ && ./engine.exe ../Fase_3/configs/solarAnimated.xml

fase4:
	rm -r build || echo "build removido"
	cmake -S ./Fase_4/src -B build
	cmake --build build/
	
3DFase4: fase4
	./build/generator.exe box 2 3 ./Fase_4/outputs/demos/box_2_3.3d
	./build/generator.exe cone 1 2 20 20 ./Fase_4/outputs/demos/cone_1_2_20_20.3d
	./build/generator.exe cone 1 2 40 40 ./Fase_4/outputs/hd/cone.3d
	./build/generator.exe sphere 1 40 40 ./Fase_4/outputs/hd/sphere.3d
	./build/generator.exe plane 2 3 ./Fase_4/outputs/demos/plane_2_3.3d
	./build/generator.exe ring 1 3 15 ./Fase_4/outputs/demos/ring_1_3_15.3d
	./build/generator.exe patch ./Fase_4/patches/teapot.patch 10 ./Fase_4/outputs/demos/bezier_10.3d
	./build/generator.exe cone 1 2 4 3 ./Fase_4/outputs/demos/cone_1_2_4_3.3d
	./build/generator.exe sphere 1 8 8 ./Fase_4/outputs/demos/sphere_1_8_8.3d
	./build/generator.exe sphere 1 40 40 ./Fase_4/outputs/hd/sphere.3d
	./build/generator.exe ring 3 5 200 ./Fase_4/outputs/hd/ring_3_5_200.3d
	./build/generator.exe patch ./Fase_4/patches/teapot.patch 20 ./Fase_4/outputs/hd/teapot.3d
	./build/generator.exe patch ./Fase_4/patches/comet.patch 10 ./Fase_4/outputs/hd/comet.3d
	./build/generator.exe box 2 100 ./Fase_4/outputs/demos/box_2_100.3d

box:
	cd build/ && ./engine.exe ../Fase_4/configs/demos/box.xml

cone:
	cd build/ && ./engine.exe ../Fase_4/configs/demos/cone.xml

gelado:
	cd build/ && ./engine.exe ../Fase_4/configs/demos/gelado.xml

holofote:
	cd build/ && ./engine.exe ../Fase_4/configs/demos/holofote.xml

plano:
	cd build/ && ./engine.exe ../Fase_4/configs/demos/plano.xml

ring:
	cd build/ && ./engine.exe ../Fase_4/configs/demos/ring.xml

teapot:
	cd build/ && ./engine.exe ../Fase_4/configs/demos/teapot.xml

test_4_1:
	cd build/ && ./engine.exe ../Fase_4/configs/demos/test_4_1.xml

test_4_2:
	cd build/ && ./engine.exe ../Fase_4/configs/demos/test_4_2.xml

test_4_3:
	cd build/ && ./engine.exe ../Fase_4/configs/demos/test_4_3.xml

test_4_4:
	cd build/ && ./engine.exe ../Fase_4/configs/demos/test_4_4.xml

test_4_5:
	cd build/ && ./engine.exe ../Fase_4/configs/demos/test_4_5.xml

test_4_6:
	cd build/ && ./engine.exe ../Fase_4/configs/demos/test_4_6.xml

solarAnimated4:
	cd build/ && ./engine.exe ../Fase_4/configs/solarAnimated.xml

solarStatic4:
	cd build/ && ./engine.exe ../Fase_4/configs/solarStatic.xml