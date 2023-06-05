fase1:
	rm -r build || echo "build removido"
	cmake -S ./Fase_1/src -B build
	cmake --build build/
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