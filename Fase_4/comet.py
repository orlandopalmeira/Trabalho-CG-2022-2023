from sys import argv
import random
from math import cos, sin, sqrt, pi
import numpy as np

if(len(argv) < 6):
    print("Insira os seguintes argumentos por ordem:")
    print(" 1) Seed para os números aleatórios")
    print(" 2) \"Raio\" do cometa")
    print(" 3) Altura máxima das irregularidades do cometa")
    print(" 4) Slices do cometa (em termos de patches)")
    print(" 5) Stacks do cometa (em termos de patches)")
    print(" 6) Ficheiro onde serão guardados os patches")
    exit(1)

random.seed(argv[1]) # seed para os números aleatórios
radius = float(argv[2]) # raio do cometa
max_height = float(argv[3]) # altura máxima das irregularidades do cometa
slices = int(argv[4])
stacks = int(argv[5])
file = argv[6]

def pontoSph(alpha: float, beta: float, radius: float):
    return (radius * cos(beta) * sin(alpha),
            radius * sin(beta),
            radius * cos(beta) * cos(alpha))

def rodaPonto(ponto: tuple, alpha: float):
    Rot =  np.array([[ cos(alpha), 0, sin(alpha)],
                     [ 0,          1,          0],
                     [-sin(alpha), 0, cos(alpha)]])
    (x,y,z) = ponto
    p = np.dot(Rot,np.array([[x],[y],[z]]))
    return (p[0][0], p[1][0], p[2][0])

def rodaPontos(pontos: list, alpha: float):
    return [rodaPonto(ponto,alpha) for ponto in pontos]

def irregularidade(ponto: tuple):
    (x,y,z) = ponto
    norma = sqrt(x*x + y*y + z*z)
    x,y,z = x/norma,y/norma,z/norma
    altura = random.uniform(radius-max_height,radius+max_height)
    return (x*altura, y*altura, z*altura)


def cometPatch(alpha: float, beta: float, a_delta: float, b_delta: float, radius: float):
    patch = [
        (alpha,beta,radius),(alpha+a_delta,beta,radius),(alpha+2*a_delta,beta,radius),(alpha+3*a_delta,beta,radius),
        (alpha,beta+b_delta,radius),(alpha+a_delta,beta+b_delta,radius),(alpha+2*a_delta,beta+b_delta,radius),(alpha+3*a_delta,beta+b_delta,radius),
        (alpha,beta+2*b_delta,radius),(alpha+a_delta,beta+2*b_delta,radius),(alpha+2*a_delta,beta+2*b_delta,radius),(alpha+3*a_delta,beta+2*b_delta,radius),
        (alpha,beta+3*b_delta,radius),(alpha+a_delta,beta+3*b_delta,radius),(alpha+2*a_delta,beta+3*b_delta,radius),(alpha+3*a_delta,beta+3*b_delta,radius)
    ]
    return [pontoSph(x,y,z) for (x,y,z) in patch]

# 0 , 1, 2, 3
# 4 , 5, 6, 7
# 8 , 9,10,11
# 12,13,14,15
def cometPatches(slices: int, stacks: int, radius: float):
    a_delta,b_delta = 2*pi/slices,(pi/2)/stacks
    patches = []
    for sl in range(slices):
        for st in range(stacks):
            patchUp = cometPatch(a_delta*sl,b_delta*st,a_delta/3,b_delta/3,radius)
            patchDown = rodaPontos([(z,-y,x) for (x,y,z) in patchUp],a_delta/2)
            for i in [5,6,9,10]:
                patchUp[i] = irregularidade(patchUp[i])
                patchDown[i] = irregularidade(patchDown[i])
            patches.append(patchUp)
            patches.append(patchDown)
    return patches 


def patchesToFile(filePath: str, patches: list):
    numPatches = len(patches)
    numControlPoints = numPatches*16
    indicesStr = ''
    controlPointsStr = ''
    i = 0
    for patch in patches:
        for k in range(len(patch)):
            indicesStr += f'{i}\n' if k == len(patch)-1 else f'{i},'
            i += 1
        controlPointsStr += ''.join([f'{p[0]:.7f},{p[1]:.7f},{p[2]:.7f}\n' for p in patch])
    
    with open(filePath, 'w') as f:
        f.write(f'{numPatches}\n{indicesStr}{numControlPoints}\n{controlPointsStr}')

patchesToFile(file,cometPatches(slices,stacks,radius))
print("Done!")