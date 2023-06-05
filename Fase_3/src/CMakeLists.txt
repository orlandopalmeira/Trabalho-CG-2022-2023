cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(fase3)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(OpenGL REQUIRED) 
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

# Define os executáveis a serem construídos neste projecto
add_executable(engine.exe ./engine/engine.cpp)
add_executable(generator.exe ./generator/generator.cpp)

# Biblioteca das figuras, pontos e estruturas de dados.
add_library(
	utils_lib
	./utils/ponto.cpp
	./utils/ponto.hpp
	./utils/figura.cpp
	./utils/figura.hpp
	./utils/list.cpp
	./utils/list.hpp
	./utils/tree.cpp
	./utils/tree.hpp
	./utils/matrix.cpp
	./utils/matrix.hpp 
) 

# Biblioteca de parsing de XML
add_library(
	tinyXML
	./tinyXML/tinystr.cpp
	./tinyXML/tinyxmlerror.cpp
	./tinyXML/tinyxmlparser.cpp
	./tinyXML/tinystr.h
	./tinyXML/tinyxml.h
	./tinyXML/tinyxml.cpp
)

# Biblioteca de configuração do engine.
add_library(
	config_lib
	./engine/config.cpp
	./engine/config.hpp
)

# Associa a biblioteca de parsing XML à biblioteca de configuração do engine.
target_link_libraries(config_lib tinyXML)
target_link_libraries(config_lib utils_lib)
# Associa a biblioteca das figuras e dos pontos aos executáveis
target_link_libraries(generator.exe utils_lib)
target_link_libraries(engine.exe utils_lib tinyXML config_lib)

if  (WIN32)

	message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")
	
	if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")	
	
	if (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")
		message(ERROR ": GLEW not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")	
	
	if (NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/devIL.lib")
		message(ERROR ": DevIL not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/devIL.lib")	
	
	include_directories(${TOOLKITS_FOLDER}/glut ${TOOLKITS_FOLDER}/glew ${TOOLKITS_FOLDER}/devil)
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} 
										  ${TOOLKITS_FOLDER}/glut/glut32.lib 
										  ${TOOLKITS_FOLDER}/devil/devIL.lib
										  ${TOOLKITS_FOLDER}/glew/glew32.lib )
	
	if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll"
													AND EXISTS "${TOOLKITS_FOLDER}/devil/devil.dll")
		file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
		file(COPY ${TOOLKITS_FOLDER}/devil/devil.dll DESTINATION ${CMAKE_BINARY_DIR})
		file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll"
													AND EXISTS "${TOOLKITS_FOLDER}/devil/devil.dll")
	
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	 
else (WIN32) #Linux and Mac

	set( CMAKE_CXX_FLAGS� "${CMAKE_CXX_FLAGS} Wno-deprecated")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})
	
	if (NOT APPLE)
		find_package(GLEW REQUIRED)
		include_directories(${GLEW_INCLUDE_DIRS})
		link_libraries(${GLEW_LIBRARIES})
	endif(NOT APPLE)
	
	target_link_libraries(engine.exe ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} )
	if(NOT GLUT_FOUND)
	   message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)
	
endif(WIN32)




